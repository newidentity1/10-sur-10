#ifndef MENU_H
#define MENU_H 

#include "Plat.h"
#include <fstream>

enum TypeMenu{Matin, Midi, Soir};
const string CHOISIR_TYPE_MENU[3] = {"-MATIN", "-MIDI", "-SOIR"};
const int MAXPLAT = 5;

class Menu
{
public: 
	// constructeurs
	Menu(); 
	Menu(const string& fichier, TypeMenu type);
    
    // destructeurs
    ~Menu();

	//getters
	int getNbPlats() const;
	
	//affichage 
	void afficher() const;

	//methodes en plus
	Plat* trouverPlat(const string& nom) const;
	void ajouterPlat(Plat & plat); 
	void ajouterPlat(const string& nom, double montant, double cout);
	bool lireMenu(const string& fichier);
	
private : 
	unsigned int capacite_;
	Plat** listePlats_;  
	unsigned int nbPlats_; 
	TypeMenu type_;
};

#endif // !MENU_H
