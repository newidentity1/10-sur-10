//
/*
 * Titre : ClientOccasionnel.cpp - Travail Pratique #4
 * Date : 25 Mars 2019
 * ƒquipe : Estefan Vega-Calcada (1934346) & Yanis Toubal (1960266)
 */
#include "ClientOccasionnel.h"

ClientOccasionnel::ClientOccasionnel(string_view nom, string_view prenom, int tailleGroupe) :
Client(nom, prenom, tailleGroupe)
{ // TODO
}

ClientOccasionnel::~ClientOccasionnel(){}

int ClientOccasionnel::getNbPoints() const
{
    return 0; //TODO
}

void ClientOccasionnel::afficherClient(ostream & os) const
{
    //TODO
    Client::afficherClient(os);
}

double ClientOccasionnel::getReduction(const Restaurant & res, double montant, bool estLivraison)
{ // TODO
    return 0.0;
}
