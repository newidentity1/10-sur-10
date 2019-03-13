/*
* Titre : Table.cpp - Travail Pratique #1
* Date : 01 Fevrier 2019
* Auteur : Yanis Toubal (1960266) et Estefan Vega Calcada (1934346)
* Description : Ce fichier contient les méthodes implémentées de la classe Table.h qui représente la table d'un restaurant ayant un ID et qui contient la commande de plats ainsi que le nombre de place.
*/

#include "Table.h"

// Constructeur par défaut 
Table::Table()
{
    commande_ = new Plat*[capacite_];
    capacite_ = MAXCAP;
    nbPlats_ = 0;
    setId(-1);
    nbPlaces_ = 1;
    occupee_ = false;
}

// Constructeur par paramètres
Table::Table(int id, int nbPlaces)
{
    commande_ = new Plat*[capacite_];
    capacite_ = MAXCAP;
    nbPlats_ = 0;
    setId(id);
    nbPlaces_ = nbPlaces;
    occupee_ = false;
}

// Destructeur, désalloue la mémoire et remet les pointeurs à nullptr
Table::~Table()
{
    if (commande_ != nullptr) {
        for (unsigned i = 0; i < nbPlats_; i++)
            delete commande_[i];
    
    delete [] commande_;
    commande_ = nullptr;
    }
}

// Méthode d'accès, retourne l'ID
int Table::getId() const
{
    return id_;
}

// Méthode d'accès, retourne le nombre de places
int Table::getNbPlaces() const
{
    return nbPlaces_;
}

// Méthode d'accès, retourne l'état de la table, un booléen
bool Table::estOccupee() const
{
    return occupee_;
}

// Méthode de modification permettant de libérer une table, ajuste l'état de la table et désalloue la mémoire de l'attribut commande 
void Table::libererTable()
{
    occupee_ = false;
    delete [] commande_;
    commande_ = nullptr;
}

// Méthode de modification permettant de placer un client, change l'état de la table
void Table::placerClient()
{
    occupee_ = true;
}

// Méthode de modification 
void Table::setId(int id)
{
    id_ = id;
}

// Méthode permettant de commander un plat 
void Table::commander(Plat* plat)
{
    if (capacite_ == nbPlats_ ) {
        capacite_ *= 2;
        Plat** nouveauTableau = new Plat* [capacite_];
        
        for (unsigned i = 0; i < nbPlats_; i++)
            nouveauTableau[i] = commande_[i];
    
        delete [] commande_;
        commande_= nouveauTableau;
        commande_[nbPlats_++] = plat;
    }
    else {
        commande_[nbPlats_++] = plat;
    }
}

// Méthode permettant de calculer le chiffre d'affaire
double Table::getChiffreAffaire() const
{
    double chiffreAffaire = 0.0;
    
    for (unsigned i = 0; i < nbPlats_; i++)
        chiffreAffaire += (commande_[i]->getPrix() - commande_[i]->getCout());
    
    return chiffreAffaire;
}

// Méthode d'affichage d'une table 
void Table::afficher() const
{
    if (occupee_) {
            cout << "\t\tLa table numéro " << id_ <<" est occupee.";
        if (nbPlats_ == 0) {
            cout << " Mais ils n'ont rien commander pour l'instant."<<endl;
        }
        else {
            cout << " Voici la commande passe par les clients :"<<endl;
        
            for (unsigned i = 0; i < nbPlats_; i++)
                commande_[i]->afficher();
        }
    }
    else {
        cout << "\t\tLa table numéro " << id_ << " est libre." << endl;
    }
}
