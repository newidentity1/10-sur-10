
#ifndef TABLE_H
#define TABLE_H

#include "Menu.h"

const  int MAXCAP = 5;

class Table
{
public:
	//constructeurs 
	Table(); 
	Table(int id, int nbPlaces);
    
    //destructeur
    ~Table();

	//getters 
	int getId() const;
	int getNbPlaces() const;
	bool estOccupee() const;

	//setters 
	void libererTable();
	void placerClient();
	void setId(int id) ;

	//autres methodes 
	void commander(Plat* plat); 
	double getChiffreAffaire() const;

	//affichage
	void afficher() const; 

private :
	Plat** commande_; 
	unsigned int capacite_; 
	unsigned int nbPlats_; 

	int id_; 
	unsigned int nbPlaces_; 
	bool occupee_; 
};

#endif // !TABLE_H
