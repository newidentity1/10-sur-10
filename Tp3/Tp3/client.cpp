/*
 * Titre : Plat.cpp - Travail Pratique #3
 * Date : 18 Janvier 2019
 * Auteur : Allan BEDDOUK
 */


#include "Client.h"

//constructeur
Client::Client() :
    nom_("inconnu"),
    prenom_("inconnu"),
    statut_(Occasionnel)
{}

Client::Client(string nom, string prenom, int tailleGroupe) :
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

//autres methodes

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

ostream& operator<<(ostream& os, const Client& client)
{
    os << "Le client principal est:\n\t" << "-" << client.getNom() << " " <<client.getPrenom() << " statut: " <<client.convertirStatutString() << " ";
    return os;
}
