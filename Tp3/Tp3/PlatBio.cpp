
/*
* Titre : Plat.cpp - Travail Pratique #3
* Date : 18 Janvier 2019
* Auteur : Allan BEDDOUK
*/


#include "PlatBio.h"


//constructeur


PlatBio::PlatBio (string nom, double prix, double cout, double ecotaxe) :
    ecoTaxe_(ecotaxe),
    Plat(nom, prix, cout)
{
    type_ = Bio;
}

//getters

double PlatBio::getEcoTaxe() const
{
    return ecoTaxe_;
}


//setters
void PlatBio::setEcoTaxe(double ecoTaxe)
{
    ecoTaxe_ = ecoTaxe;
}

//autres methodes

ostream& operator<<(ostream& os, const PlatBio& plat)
{
    os << static_cast<Plat>(plat) << endl << "\tcomprend une Taxe ecologique de :" << plat.getEcoTaxe() << "$";
    return os;
}
