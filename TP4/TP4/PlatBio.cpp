//
/*
 * Titre : PlatBio.cpp - Travail Pratique #4
 * Date : 25 Mars 2019
 * ƒquipe : Estefan Vega-Calcada (1934346) & Yanis Toubal (1960266)
 */
#include "PlatBio.h"

PlatBio::PlatBio(string nom, double prix, double cout, double ecotaxe): Plat(nom, prix, cout), ecoTaxe_(ecotaxe)
{
}

PlatBio::~ PlatBio(){}

double PlatBio::getEcoTaxe() const
{
	return ecoTaxe_;
}

void PlatBio::setEcoTaxe(double ecoTaxe)
{
	ecoTaxe_ = ecoTaxe;
}

//TODO
Plat * PlatBio:: clone () const
{
   // Plat* copiePlat = new PlatBio(nom_, prix_, cout_, ecoTaxe_);
   // return copiePlat;
    return (new PlatBio(*this));
}
double PlatBio:: getPrixDeRevient()
{
    return (prix_ - cout_ + ecoTaxe_);

}
void PlatBio::afficherPlat(ostream& os) const
{
    //TODO
    Plat::afficherPlat(os);
    os <<"Plat Bio\t comprend une Taxe ecologique de : " << ecoTaxe_ <<"$" << endl;
}
