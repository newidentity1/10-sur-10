/*
* Date : 25 février 2019
* Auteur : AbdeB
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
