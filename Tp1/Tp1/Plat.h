/*
* Titre : Plat.h - Travail Pratique #1
* Date : 01 Fevrier 2019
* Auteur : Yanis Toubal et Estefan Vega Calcada
*/

#ifndef PLAT_H
#define PLAT_H

#include <string>
#include <iostream>

using namespace std; 

class Plat
{
public: 
	// constructeurs
	Plat(); 
	Plat(string nom, double prix, double cout);

    // destructeur
    ~Plat();
    
	//getters 
	string getNom() const;
	double getPrix() const;
	double getCout() const;

	//setters 
	void setNom(string nom); 
	void setPrix(double prix); 
	
	//affichage
	void afficher() const;

private: 
	string nom_; 
	double prix_; 
	double cout_; 
};

#endif // !PLAT_H
