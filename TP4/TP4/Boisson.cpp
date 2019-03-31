//
/*
 * Titre : Boisson.cpp - Travail Pratique #4
 * Date : 25 Mars 2019
 * Équipe : Estefan Vega-Calcada (1934346) & Yanis Toubal (1960266)
 */


#include "Boisson.h"
// TODO
Boisson::Boisson (string_view nom, double prix): nom_(nom), prix_(prix)
{// TODO
    setTaxe();
}

Boisson::~Boisson(){}

void Boisson::setTaxe()
{
    taxe_ = 0.12;
}

double Boisson::getTaxe() const
{
    return taxe_;
}

string_view Boisson::getNom() const
{
    return nom_;
}
double Boisson::getPrix()  const
{
    return prix_;
}
