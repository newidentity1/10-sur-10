/*
* Titre : PlatBio.cpp - Travail Pratique #3
* Date : 24 Février 2019
* Équipe : Estefan Vega-Calcada (1934346) & Yanis Toubal (1960266)
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

//Affichage: surcharge de l'operateur << 
ostream& operator<<(ostream& os, const PlatBio& plat)
{
    os << static_cast<Plat>(plat) << "\t\tcomprend une Taxe ecologique de :" << plat.getEcoTaxe() << "$" << endl;
    return os;
}
