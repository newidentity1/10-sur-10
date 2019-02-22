

/*
 * Titre : Plat.cpp - Travail Pratique #3
 * Date : 18 Janvier 2019
 * Auteur : Allan BEDDOUK
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

//autres methodes

double PlatCustom::calculerSupplement() const
{
    return (nbIngredients_ * FRAIS_CUSTOMISATION);
}

ostream& operator<<(ostream& os, const PlatCustom& plat)
{
	os << static_cast<Plat>(plat) << "\t contient " << plat.getNbIngredients() << " elements modifies pour un supplement total de :" << plat.getSupplement() << "$" << endl;
    return os;
}
