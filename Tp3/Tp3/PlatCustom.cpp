/*
 * Titre : PlatCustom.cpp - Travail Pratique #3
* Date : 24 Février 2019
* Équipe : Estefan Vega-Calcada (1934346) & Yanis Toubal (1960266)
 */


#include "PlatCustom.h"


//constructeur
PlatCustom::PlatCustom(string nom, double prix, double cout, int nbIngredients) :
    nbIngredients_(nbIngredients),
    Plat(nom, prix, cout)
{
	type_ = Custom;
    supplement_ = calculerSupplement();
}
//getters

int PlatCustom::getNbIngredients() const
{
    return nbIngredients_;
}

double PlatCustom::getSupplement() const
{
    return supplement_;
}

//setters
void PlatCustom::setNbIngredients(int nIngredients)
{
    nbIngredients_ = nIngredients;
}

// calcule les frais additionnels qui s'ajoutent lors de l'ajout
// d'ingredients a un plat 
double PlatCustom::calculerSupplement() const
{
    return (nbIngredients_ * FRAIS_CUSTOMISATION);
}

// Affichage : surcharge de l'operateur << 
ostream& operator<<(ostream& os, const PlatCustom& plat)
{
	os << static_cast<Plat>(plat) << "\t contient " << plat.getNbIngredients() << " elements modifies pour un supplement total de :" << plat.getSupplement() << "$" << endl;
    return os;
}
