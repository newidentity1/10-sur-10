/*
* Titre : Restaurant.cpp - Travail Pratique #1
* Date : 01 Fevrier 2019
* Auteur : Yanis Toubal (1960266) et Estefan Vega Calcada (1934346)
* Description : Ce fichier contient les méthodes implémentées de la classe Restaurant.h qui contient plusieurs tables et 3 types de menus qui contiennent des plats. 
*/

#include "Restaurant.h"

// Constructeur par défaut 
Restaurant::Restaurant()
{
    nom_ = nullptr;
    chiffreAffaire_ = 0.0;
    setMoment(Matin);
    menuMatin_ = nullptr;
    menuMidi_ = nullptr;
    menuSoir_ = nullptr;
    capaciteTables_ = INTTABLES;
    tables_ = new Table*[capaciteTables_];
    nbTables_ = 0;
}

// Constructeur par paramètres
Restaurant::Restaurant(const string& fichier,const string& nom, TypeMenu moment)
{
    nom_ = new string;
    *nom_ = nom;
    chiffreAffaire_ = 0.0;
    setMoment(moment);
    menuMatin_ = new Menu(fichier, Matin);
    menuMidi_ = new Menu(fichier, Midi);
    menuSoir_ = new Menu(fichier, Soir);
    capaciteTables_ = INTTABLES;
    tables_ = new Table*[capaciteTables_];
    nbTables_ = 0;
    lireTable(fichier);
}

// Destructeur, désalloue la mémoire et remet les pointeurs à nullptr
Restaurant::~Restaurant()
{
    for (unsigned i = 0; i < nbTables_; i++)
        delete tables_[i];
    
    delete [] tables_;
    tables_ = nullptr;
    
    delete menuMatin_;
    menuMatin_ = nullptr;
   
    delete menuMidi_;
    menuMatin_ = nullptr;
    
    delete menuSoir_;
    menuMatin_ = nullptr;
    
    delete nom_;
    nom_ = nullptr;
}


// Méthode d'accès, retourne le nom
string Restaurant::getNom() const
{
    return *nom_;
}

// Méthode d'accès, retourne le moment de la journée 
TypeMenu Restaurant::getMoment() const
{
    return momentJournee_;
}

// Méthode de modification, permet de modifier le moment de la journée 
void Restaurant::setMoment(TypeMenu moment)
{
    momentJournee_ = moment;
}

// Méthode qui permet de lire l'onglet Table dans le fichier Polyfood.txt
void Restaurant::lireTable(const string& fichier)
{
    ifstream fichierLu(fichier);
    string motLu;
    
    if (fichierLu.fail()) {
        cout << "Erreur d'ouverture de fichier" << endl;
    }
    else {
           while (!ws(fichierLu).eof()) {
                fichierLu >> motLu;
        
                if (motLu == "-TABLES") {
                    while (!ws(fichierLu).eof()) {
                        int id, nbPlaces;
                        fichierLu >> id >> nbPlaces;
                        ajouterTable(id, nbPlaces);
                    }
                }
           }
    }
}

// Méthode qui permet d'ajouter une table 
void Restaurant::ajouterTable(int id, int nbPlaces)
{
    
    if (nbTables_ == capaciteTables_) {
        capaciteTables_ *= 2;
        Table** nouveauTableau = new Table*[capaciteTables_];
    
        for (unsigned i =0; i < nbTables_; i++)
            nouveauTableau[i] = tables_[i];
        
        delete [] tables_;
        tables_ = nouveauTableau;
        tables_[nbTables_++] = new Table(id, nbPlaces);
    }
    else {
        tables_[nbTables_++] = new Table(id, nbPlaces);
    }
}

// Méthode qui permet de liberer une table et ajuste le chiffre d'affaire
void Restaurant::libererTable(int id)
{
    for (unsigned i = 0; i < nbTables_; i++){
        if (tables_[i]->getId() == id) {
            chiffreAffaire_ += tables_[i]->getChiffreAffaire();
            tables_[i]->libererTable();
            
        }
    }
}

// Méthode qui permet de commander un plat à partir d'un Menu
void Restaurant::commanderPlat(string nom, int idTable)
{
    bool idTrouver = false;
    int indexID = -1;
    Plat* platTrouve = nullptr;
    
    for (unsigned i = 0; i < nbTables_; i++){
        if (tables_[i]->getId() == idTable) {
            idTrouver = true;
            indexID = i;
           
            switch (momentJournee_) {
                case(Matin): platTrouve = menuMatin_->trouverPlat(nom);
                    break;
                
                case(Midi): platTrouve = menuMidi_->trouverPlat(nom);
                    break;
                
                case(Soir): platTrouve = menuSoir_->trouverPlat(nom);
                    break;
            }
        }
    }
    
    if (idTrouver && platTrouve != nullptr) {
            tables_[indexID]->commander(platTrouve);
    }
    else {
        cout << "Erreur : table non occupee ou plat introuvable" << endl;
    }
    
}

// Place un client en vérifiant si la table n'est pas occupée et si le nombre de places est suffisant
void Restaurant::placerClients(int nbClients)
{
    Table meilleurTable(-1, 99999);
    int indexMeilleurTable = meilleurTable.getId(); // -1

    for (unsigned i = 0; i < nbTables_; i++) {
        if (!tables_[i]->estOccupee() && (tables_[i]->getNbPlaces() >= nbClients)) {
            if (tables_[i]->getNbPlaces() < meilleurTable.getNbPlaces()) {
                indexMeilleurTable = i;
            }
        }
    }
        if (indexMeilleurTable != -1) {
            tables_[indexMeilleurTable]->placerClient();
        }
        else {
            cout << "Erreur : il n'y a plus/pas de table disponible pour le client" << endl;
        }
}

// Méthode d'affichage d'un Restaurant
void Restaurant::afficher() const
{
    if (chiffreAffaire_ == 0.0) {
        cout << "Le restaurant " << *nom_ << " n'a pas fait de benefice ou le chiffre n'est pas encore calcule." << endl;
    }
    else {
        cout << "Le restaurant " << *nom_ << " a fait un chiffre d'affaire de : "<< chiffreAffaire_ << " $."<<endl;
    }
    cout << "Voici les tables :" << endl;
    
    for (unsigned i = 0; i < nbTables_; i++) {
        tables_[i]->afficher();
        cout << endl;
    }
    cout << endl;
    cout << "-Voici le menu :\n";
    menuMatin_->afficher();
    menuMidi_->afficher();
    menuSoir_->afficher();
}
