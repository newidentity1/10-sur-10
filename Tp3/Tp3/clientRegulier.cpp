/*
* Titre : clientRegulier.cpp - Travail Pratique #3
* Date : 24 Février 2019
* Équipe : Estefan Vega-Calcada (1934346) & Yanis Toubal (1960266)
*/

#include "ClientRegulier.h"


// constructeurs
ClientRegulier::ClientRegulier() :
    Client(),
    nbPoints_(0)
{
    statut_ = Fidele;
}

// constructeur par parametres 
ClientRegulier::ClientRegulier(string nom, string prenom, int tailleGroupe, int nbPoints) :
    Client (nom, prenom, tailleGroupe),
    nbPoints_(nbPoints)
{
    statut_ = Fidele;
}

//Accesseurs

int ClientRegulier::getNbPoints() const
{
    return nbPoints_;
}


// Permet d'ajouter un bonus a l'attribut nbPoints_
void ClientRegulier::augmenterNbPoints(int bonus)
{
    nbPoints_ += bonus;
}

//Affichage: surcharge de l'operateur << 
ostream& operator<<(ostream& os, const ClientRegulier& client)
{
    os << static_cast<Client> (client) <<"Possede " <<client.getNbPoints() <<" points." <<endl;
    return os;
}
