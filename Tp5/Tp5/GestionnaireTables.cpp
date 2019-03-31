/********************************************
* Titre: Travail pratique #5 - gestionnaireTables.cpp
* Date: 21 mars 2019
* Auteur: Moussa Traor� & Ryan Hardie & Wassim Khene
*******************************************/


#include "GestionnaireTables.h"
#include "LectureFichierEnSections.h"

void GestionnaireTables::lireTables(const string& nomFichier)
{
	LectureFichierEnSections fichier{ nomFichier };
	fichier.allerASection("-TABLES");
	while (!fichier.estFinSection()) {
		int id, nbPlaces;
		fichier >> id >> nbPlaces;
		ajouter(new Table(id, nbPlaces));
	}
}

Table* GestionnaireTables::getTable(int id) const
{
    auto it = conteneur_.begin();
    
    while (it != conteneur_.end())
    {
        if ((*it)->getId() == id)
            return  *it;
        it++;
    }
    return nullptr; // si il ne trouve pas la table
}

Table* GestionnaireTables::getMeilleureTable(int tailleGroupe) const
{
    
    auto it = conteneur_.begin();
    Table* meilleurTable = nullptr;
    bool tableTrouve = false;
    
    while (it != conteneur_.end())
    {
        if (!(*it)->estOccupee() && (*it)->getNbPlaces() >= tailleGroupe)
        {
            if (!tableTrouve) //si une table correspondante na pas ete trouver en assigne une
            {
                meilleurTable = *it;
                tableTrouve = true;
            }
            else if (meilleurTable->getNbPlaces() <= (*it)->getNbPlaces()) //sinon verifie si elle est la meilleur
            meilleurTable = *it;
            
            it++;
        }
    }
    return meilleurTable; //retourne nullptr si non trouve
}

void GestionnaireTables::afficherTables(ostream& os) const
{
    auto it = conteneur_.begin();
    
    while (it != conteneur_.end())
    {
        os << *(*it);
        it++;
    }
}
