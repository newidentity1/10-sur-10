/*
 * Titre : Table.cpp - Travail Pratique #1
 * Date : 01 Fevrier 2019
 * Auteur : Yanis Toubal et Estefan Vega Calcada
 */

#include "Table.h"

Table::Table()
{
    commande_ = new Plat*[capacite_];
    capacite_ = MAXCAP;
    nbPlats_ = 0;
    setId(-1);
    nbPlaces_ = 1;
    occupee_ = false;
}

Table::Table(int id, int nbPlaces)
{
    commande_ = new Plat*[capacite_];
    capacite_ = MAXCAP;
    nbPlats_ = 0;
    setId(id);
    nbPlaces_ = nbPlaces;
    occupee_ = false;
}

Table::~Table()
{
    if (commande_ != nullptr) {
        for (unsigned i = 0; i < nbPlats_; i++)
            delete commande_[i];
    
    delete [] commande_;
    commande_ = nullptr;
    }
}

int Table::getId() const
{
    return id_;
}

int Table::getNbPlaces() const
{
    return nbPlaces_;
}

bool Table::estOccupee() const
{
    return occupee_;
}

void Table::libererTable()
{
    occupee_ = false;
    delete [] commande_;
    commande_ = nullptr;
}

void Table::placerClient()
{
    occupee_ = true;
}

void Table::setId(int id)
{
    id_ = id;
}

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

double Table::getChiffreAffaire() const
{
    double chiffreAffaire = 0.0;
    
    for (unsigned i = 0; i < nbPlats_; i++)
        chiffreAffaire += (commande_[i]->getPrix() - commande_[i]->getCout());
    
    return chiffreAffaire;
}

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
