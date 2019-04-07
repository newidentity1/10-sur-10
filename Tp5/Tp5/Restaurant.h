
/*
* Titre : Restaurant.h - Travail Pratique #1
* Date : 18 Janvier 2019
* Auteur : Allan BEDDOUK
*/

#ifndef RESTAURANT_H
#define RESTAURANT_H

#include "Table.h"
#include "Client.h"
#include "ClientPrestige.h"
#include "pointers.h"
#include "GestionnaireTables.h"
#include "GestionnairePlats.h"
#include "def.h"

#include <string_view>
#include <iostream>



class Client;
class Table;
class Restaurant {
public:
	// Constructeurs.

	Restaurant();
	Restaurant(const string& nomFichier, string_view nom, TypeMenu moment);
	Restaurant(const Restaurant& autre) = delete;  //? Le programme ne fait jamais de copie de restaurant,
                                                   //donc cette methode n"est jamais cree par defaut par le compilateur
    
	// Destructeur.
	~Restaurant();

	// Setters.

	void setMoment(TypeMenu moment);
	void setNom(string_view nom); 
    void setChiffreAffaire( double chiffre);
	// Getters.

	string getNom() const;
	TypeMenu getMoment() const;
    double getChiffreAffaire() const;
	GestionnaireTables* getTables() const; // TODO : À implémenter
	
    GestionnairePlats* getMenu(TypeMenu typeMenu) const; // TODO: retourner un GestionnairePlats* a la place
	
    double getFraisLivraison(ZoneHabitation zone) const;
	string getNomTypeMenu(TypeMenu typeMenu) const;

	// Autres methodes.
	void lireAdresses(const string& fichier);
	void libererTable(int id);

    void commanderPlat(const string&  nom, int idTable);
	bool operator <(const Restaurant& restau) const ;
	Restaurant& operator=(const Restaurant& autre) = delete;  //? Le programme ne fait jamais de copie de restaurant, donc cette fonction n'�tait pas test�e et par cons�quent probablement �rron�e.
	
	bool placerClients(Client* client);
	bool livrerClient(Client* client, const vector<string>& nomPlats);
	
	double calculerReduction(Client* client, double montant, bool livraison) const;
    
	 friend ostream& operator<<(ostream& os, const Restaurant& restaurant);

private:
	GestionnairePlats* menuActuel() const; // TODO : retourner GestionnairePlats

	string nom_;
	TypeMenu momentJournee_;
	double chiffreAffaire_;

	// Differents menus en fonction du moment de la journ�e.
    GestionnairePlats* menuMatin_;
    GestionnairePlats* menuMidi_;
    GestionnairePlats* menuSoir_;
    
    
	// Liste des tables.
    GestionnaireTables* tables_;
    
	// Tarif des trois zones de livraison.
	double fraisLivraison_[NB_ZONES_LIVR]; 
};


#endif // !RESTAURANT_H
