/*
 * Titre : Restaurant.cpp - Travail Pratique #1
 * Date : 01 Fevrier 2019
 * Auteur : Yanis Toubal et Estefan Vega Calcada
 */

#include "Restaurant.h"

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

string Restaurant::getNom() const
{
    return *nom_;
}

TypeMenu Restaurant::getMoment() const
{
    return momentJournee_;
}

void Restaurant::setMoment(TypeMenu moment)
{
    momentJournee_ = moment;
}

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

void Restaurant::libererTable(int id)
{
    for (unsigned i = 0; i < nbTables_; i++){
        if (tables_[i]->getId() == id) {
            chiffreAffaire_ += tables_[i]->getChiffreAffaire();
            tables_[i]->libererTable();
            
        }
    }
}

void Restaurant::commanderPlat(string& nom, int idTable)
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

void Restaurant::placerClients(int nbClients)
{
    Table meilleurTable(-1, INT_MAX);
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

void Restaurant::afficher() const
{
    if (chiffreAffaire_ == 0.0) {
        cout << "Le restaurant " << *nom_ << " n'a pas fait de benefice ou le chiffre n'est pas encore calcule." << endl;
    }
    else {
        cout << "Le restaurant " << *nom_ << " a fait un chiffre d'affaire de : "<< chiffreAffaire_ << " $." << endl;
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
