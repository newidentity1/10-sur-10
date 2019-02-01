//
//  Table.cpp
//  Tp1
//
//  Created by Yanis Toubal on 2019-01-31.
//  Copyright © 2019 Yanis Toubal. All rights reserved.
//

#include "Table.h"

Table::Table() {
    capacite_ = MAXCAP;
    id_ = -1;
    nbPlaces_ = 1;
    nbPlats_ = 0;
    occupee_ = false;
    commande_ = new Plat*[capacite_];
    
}

Table::Table(int id, int nbPlaces){
    id_ = id;
    nbPlats_ = 0;
    nbPlaces_ = nbPlaces;
    capacite_ = nbPlaces_;
    occupee_ = false;
    commande_ = new Plat*[capacite_];
    
}

Table::~Table(){
    if (commande_ != nullptr){
        for (unsigned i=0; i<nbPlats_; i++){
            delete commande_[i];
        }
    
    delete [] commande_;
    commande_ = nullptr;
    }
}

int Table::getId() const {
    return id_;
}

int Table::getNbPlaces() const {
    return nbPlaces_;
}

bool Table::estOccupee() const {
    return occupee_;
    
}

void Table::libererTable() {
    occupee_ = false;
    delete [] commande_;
    commande_ = nullptr;
    
}

void Table::placerClient() {
    occupee_ = true;
}

void Table::setId(int id){
    id_ = id;
    
}

void Table::commander(Plat* plat){
    
    if( capacite_ == 0)
        capacite_= MAXPLAT;
    
    if (capacite_ == nbPlats_ ){
        capacite_ *= 2;
        Plat** nouveauTableau = new Plat* [capacite_];
        
        for (unsigned i=0; i < nbPlats_; i++) {
            nouveauTableau[i] = commande_[i];
    
        }
        delete [] commande_;
        commande_= nouveauTableau;
        commande_[nbPlats_++] = plat;
        
    } else {
        commande_[nbPlats_++] = plat;
    }
}

double Table::getChiffreAffaire() const {
    double chiffreAffaire = 0.0;
    
    for (unsigned i=0; i< nbPlats_; i++){
        chiffreAffaire += (commande_[i]->getPrix() - commande_[i]->getCout());
    }
    return chiffreAffaire;
}

void Table::afficher() const {
   
    if(occupee_){
            cout <<"\t\tLa table numéro " << id_ <<" est occupee.";
        if(nbPlats_ == 0){
            cout<< " Mais ils n'ont rien commander pour l'instant."<<endl;
        }else{
            cout<< " Voici la commande passe par les clients :"<<endl;
        
            for (unsigned i=0; i< nbPlats_; i++){
                commande_[i]->afficher();
            }
        }
    }else {
        cout<<"\t\tLa table numéro " << id_ << " est libre." << endl;
    }
}
