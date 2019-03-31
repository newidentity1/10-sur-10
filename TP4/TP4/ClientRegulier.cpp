//
/*
 * Titre : ClientRegulier.cpp - Travail Pratique #4
 * Date : 25 Mars 2019
 * ƒquipe : Estefan Vega-Calcada (1934346) & Yanis Toubal (1960266)
 */
#include "ClientRegulier.h"

ClientRegulier::ClientRegulier()
{
	nbPoints_ = 0;
}

ClientRegulier::ClientRegulier(string_view nom, string_view prenom, int tailleGroupe, int npoints) :
Client(nom, prenom, tailleGroupe),
nbPoints_(npoints)
{ // TODO
}

ClientRegulier::~ClientRegulier() {}

int ClientRegulier::getNbPoints() const
{
	return nbPoints_;
}

void ClientRegulier::augmenterNbPoints(int bonus)
{
	nbPoints_ += bonus;
}

void ClientRegulier::afficherClient(ostream & os) const
{
    Client::afficherClient(os);
}

double ClientRegulier::getReduction(const Restaurant & res, double montant, bool estLivraison)
{
	//TODO
    if (nbPoints_ > SEUIL_DEBUT_REDUCTION)
        return (-montant * TAUX_REDUC_REGULIER);
    return 0.0;
}
