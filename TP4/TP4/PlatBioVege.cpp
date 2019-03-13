/*
* Date : 25 février 2019
* Auteur : AbdeB
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

