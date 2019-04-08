/********************************************
* Titre: Travail pratique #5 - gestionnaireTables.h
* Date: 21 mars 2019
* Auteur: Moussa Traor� & Ryan Hardie & Wassim Khene
*******************************************/

#pragma once

#include "Table.h"
#include "Foncteur.h"
#include "GestionnaireGenerique.h"

#include <set>

using namespace std;

class GestionnaireTables : public GestionnaireGenerique<Table*, set<Table*>> // TODO : Ajouter l'héritage
{
public:
    //constructeur
	GestionnaireTables() = default;
	
    //destructeur
    ~GestionnaireTables();
    
    //recherche
    Table* getTable(int id) const; // TODO
	Table* getMeilleureTable(int tailleGroupe) const; // TODO
	
    //lire fichier texte
    void lireTables(const string& nomFichier);
    
    //affichage
	void afficherTables(ostream& os) const; // TODO
};
