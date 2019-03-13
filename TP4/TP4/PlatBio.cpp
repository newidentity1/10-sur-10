/*
* Date : 25 février 2019
* Auteur : AbdeB
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
    Plat* copiePlat = new PlatBio(nom_, prix_, cout_, ecoTaxe_);
    return copiePlat;
}
double PlatBio:: getPrixDeRevient()
{
    return (prix_ - cout_ + ecoTaxe_);

}
void PlatBio::afficherPlat(ostream& os) const
{
    //TODO
    os <<"Plat bio\t comprend une Taxe ecologique de : " << ecoTaxe_ <<"$" << endl;
}
