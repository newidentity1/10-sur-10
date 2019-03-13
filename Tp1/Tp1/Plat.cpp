/*
* Titre : Plat.cpp - Travail Pratique #1
* Date : 01 Fevrier 2019
* Auteur : Yanis Toubal (1960266) et Estefan Vega Calcada (1934346)
* Description : Ce fichier contient les méthodes implémentées de la classe Plat.h qui représente les plats du restaurant présent dans le Menu.
*/

#include "Plat.h"

// Constructeur par défaut 
Plat::Plat() {
        setNom("inconnu");
        setPrix(0.00);
        cout_ = 0.00;
}

// Constructeur par paramètres 
Plat::Plat(string nom, double prix, double cout){
        setNom(nom);
        setPrix(prix);
        cout_ = cout;
}

// Destructeur 
Plat::~Plat(){}

// Méthode d'accès, retourne le nom 
string Plat::getNom() const
{
        return nom_;
}

// Méthode d'accès, retourne le prix
double Plat::getPrix() const
{
        return prix_;
}

// Méthode d'accès, retourne le cout 
double Plat::getCout() const
{
        return cout_;
}

// Méthode de modification, modifie le nom  
void Plat::setNom(string nom)
{
        nom_ = nom;
}
// Méthode de modification, modifie le prix
void Plat::setPrix(double prix)
{
        prix_ = prix;
}
// Méthode d'affichage d'un plat
void Plat::afficher() const
{
        cout << "\t\t" << nom_ << " - " << prix_ << "$ (" << cout_ << "$ pour le restaurant)" << endl;
}
