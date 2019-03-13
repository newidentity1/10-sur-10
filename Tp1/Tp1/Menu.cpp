/*
* Titre : Menu.cpp - Travail Pratique #1
* Date : 01 Fevrier 2019
* Auteur : Yanis Toubal et Estefan Vega Calcada (1934346)
* Description : Ce fichier contient les méthodes implémentées de la classe Menu.h
*/

#include "Menu.h"

// Constructeur par défaut 
Menu::Menu()
{
    capacite_ = MAXPLAT;
    listePlats_ = new Plat* [capacite_];
    nbPlats_ = 0;
    type_ = Matin;
}

// Constructeur par paramètres 
Menu::Menu(const string& fichier, TypeMenu type )
{
    capacite_ = MAXPLAT;
    listePlats_ = new Plat* [capacite_];
    nbPlats_ = 0;
    type_ = type;
    lireMenu(fichier);
}

// Destructeur de la classe 
Menu::~Menu()
{
    for (unsigned i = 0; i < nbPlats_; i++)
        delete listePlats_[i];
    
        delete [] listePlats_;
        listePlats_ = nullptr;
}

// Méthode d'accès, retourne le nombre de plats 
int Menu::getNbPlats() const{
    return nbPlats_;
}

// Méthode permettant de trouver une plat dans la liste de plats 
Plat* Menu::trouverPlat(const string& nom) const
{
    for (unsigned i = 0; i < nbPlats_; i++) {
            if (listePlats_[i]->getNom() == nom)
                return listePlats_[i];
        }
    return nullptr;
}

// Méthode permettant d'ajouter un plat à la liste de plats à partir d'un plat
void Menu::ajouterPlat(Plat& plat)
{
    if (capacite_ == nbPlats_ ) {
        capacite_ *= 2;
        Plat** nouveauTableau = new Plat* [capacite_];
        
        for (unsigned i = 0; i < nbPlats_; i++)
            nouveauTableau[i] = listePlats_[i];
        
        delete [] listePlats_;
        listePlats_ = nouveauTableau;
        listePlats_[nbPlats_++] = &plat;
   
    }
    else {
        listePlats_[nbPlats_++] = &plat;
    }
}

// Méthode permettant d'ajouter un plat à la liste de plats à partir du nom, montant et cout. 
void Menu::ajouterPlat(const string& nom, double montant, double cout)
{
    Plat* nouveauPlat = new Plat(nom, montant, cout);
    ajouterPlat(*nouveauPlat);
}

bool Menu::lireMenu(const string& fichier)
{
    ifstream fichierPlats(fichier);
    
    if (fichierPlats.fail()) {
        cout << "Erreur d'ouverture de fichier" << endl;
        return false;
    }
    else {
        while (!ws(fichierPlats).eof()) {
            string motLu="";
            fichierPlats >> motLu;
            
            if (CHOISIR_TYPE_MENU[type_] == motLu) {
                while (true) {
                    string nom;
                    double prix,coutResto;
                    fichierPlats >> nom >> prix >> coutResto;
                    
                    if (nom == "-MIDI" || nom == "-SOIR" || nom == "-TABLES")
                        return true;
                   
                    ajouterPlat(nom, prix, coutResto);
                }
            }
        }
        return false;
    }
}

// Méthode d'affichage d'un menu
void Menu::afficher() const
{
    cout << CHOISIR_TYPE_MENU[type_] << " :" << endl;
    
    for (unsigned i = 0; i < nbPlats_; i++)
        listePlats_[i]->afficher();
}
