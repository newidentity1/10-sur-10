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
	GestionnaireTables() = default;
	Table* getTable(int id) const; // TODO
	Table* getMeilleureTable(int tailleGroupe) const; // TODO
	void lireTables(const string& nomFichier);
    ~GestionnaireTables(); 
	void afficherTables(ostream& os) const; // TODO
};
