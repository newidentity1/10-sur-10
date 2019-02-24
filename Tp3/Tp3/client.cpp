/*
* Titre : client.cpp - Travail Pratique #3
* Date : 24 Février 2019
* Équipe : Estefan Vega-Calcada (1934346) & Yanis Toubal (1960266)
*/


#include "Client.h"

//constructeur
Client::Client() :
    nom_("inconnu"),
    prenom_("inconnu"),
    statut_(Occasionnel)
{}
//constructeur par parametres 
Client::Client(const string& nom, string prenom, int tailleGroupe) :
    nom_(nom),
    prenom_(prenom),
    tailleGroupe_(tailleGroupe),
    statut_(Occasionnel)
{}

//getters
StatutClient Client::getStatut() const
{
    return statut_;
}

int Client::getTailleGroupe() const
{
    return tailleGroupe_;
}

string Client::getNom() const
{
    return nom_;
}

string Client::getPrenom() const
{
    return prenom_;
}

// sert a convertir le statut d'un client en un string  
string Client::convertirStatutString() const
{
    switch (statut_) {
            
        case (Occasionnel) : return "Occasionnel";
            break;
            
        case (Fidele) : return "Regulier";
            break;
            
        case (Prestige) : return "Prestige";
            break;
    }
}

// Affichage : surcharge de l'operateur << 
ostream& operator<<(ostream& os, const Client& client)
{
    os << "Le client principal est:\n\t" << "-" << client.getNom() << " " <<client.getPrenom() << " statut: " <<client.convertirStatutString() << " ";
    return os;
}
