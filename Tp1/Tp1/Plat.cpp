/*
 * Titre : Plat.cpp - Travail Pratique #1
 * Date : 01 Fevrier 2019
 * Auteur : Yanis Toubal et Estefan Vega Calcada
 */

#include "Plat.h"

Plat::Plat() {
        setNom("inconnu");
        setPrix(0.00);
        cout_ = 0.00;
}

Plat::Plat(string nom, double prix, double cout){
        setNom(nom);
        setPrix(prix);
        cout_ = cout;
}

Plat::~Plat(){}

string Plat::getNom() const
{
        return nom_;
}

double Plat::getPrix() const
{
        return prix_;
}

double Plat::getCout() const
{
        return cout_;
}

void Plat::setNom(string nom)
{
        nom_ = nom;
}

void Plat::setPrix(double prix)
{
        prix_ = prix;
}

void Plat::afficher() const
{
        cout << "\t\t" << nom_ << " - " << prix_ << "$ (" << cout_ << "$ pour le restaurant)" << endl;
}
