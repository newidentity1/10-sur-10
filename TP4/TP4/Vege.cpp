/*
* Date : 25 f�vrier 2019
* Auteur : AbdeB
*/
#include "Vege.h"

Vege::Vege(string nom, double vitamines, double proteines, double mineraux): nom_(nom),vitamines_(vitamines), proteines_(proteines), mineraux_(mineraux)
{
}

double Vege::getVitamines() const
{
	return vitamines_;
}

double Vege::getProteines() const
{
	return proteines_;
}

double Vege::getMineraux() const
{
	return mineraux_;
}

void Vege::setVitamines(double vitamines)
{
	vitamines_ = vitamines;
}

void Vege::setProteines(double proteines)
{
	proteines_ = proteines;
}

void Vege::setMineraux(double mineraux)
{
	mineraux_ = mineraux;
}
void Vege::afficherVege(ostream & os) const
{   //TODO
    os << "PLAT VEGE "<< nom_ <<  " \tvitamines "<< vitamines_ << " Proteines " << proteines_ << " Mineraux " << mineraux_  <<endl;
}


