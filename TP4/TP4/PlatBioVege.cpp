//
/*
 * Titre : PlatBioVege.cpp - Travail Pratique #4
 * Date : 25 Mars 2019
 * ƒquipe : Estefan Vega-Calcada (1934346) & Yanis Toubal (1960266)
 */
#include "PlatBioVege.h"

PlatBioVege::PlatBioVege(string nom, double prix, double cout, double ecotaxe, double vitamines, double proteines, double mineraux) :
PlatBio(nom, prix, cout, ecotaxe),
Vege(nom,vitamines,proteines,mineraux)
{ // TODO
}
PlatBioVege:: ~PlatBioVege(){}

//TODO
void PlatBioVege::afficherPlat(ostream & os) const
{   //TODO
    PlatBio::afficherPlat(os);
    os << "ET ";
    Vege::afficherVege(os);
}

Plat * PlatBioVege::clone() const
{ //TODO
    Plat* copiePlat = new PlatBioVege(Plat::nom_, prix_, cout_, ecoTaxe_, vitamines_, proteines_, mineraux_);
    return copiePlat;
}

double PlatBioVege::calculerApportNutritif() const
{
    return (vitamines_ * proteines_ / mineraux_) * RAPPORT_NUTRITIF_BIO *
    AVANTAGE_SANS_PESTICIDE;
}

