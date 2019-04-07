/********************************************
* Titre: Travail pratique #5 - gestionnaireTables.cpp
* Date: 21 mars 2019
* Auteur: Moussa Traor� & Ryan Hardie & Wassim Khene
*******************************************/


#include "GestionnaireTables.h"
#include "LectureFichierEnSections.h"

//Rempli le conteneur de tableau dynamiquement en lisant un fichier texte.
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

//destructeur
GestionnaireTables::~GestionnaireTables()
{
	auto it = conteneur_.begin();

	while (it != conteneur_.end()) {
		delete *it;
		it++;
	}
}

//Parcours le conteneur en recherchant la table à l'aide de son id. L'a retourne si elle est trouve sinon return nullptr.
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

//Parcours le conteneur et compare les tables pour trouver la meilleure. Retourne la meilleure table disponible selon la taille du groupe.
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
            else if (meilleurTable->getNbPlaces() >= (*it)->getNbPlaces()) //sinon verifie si elle est la meilleure
            meilleurTable = *it;
        }
         it++;
    }
    return meilleurTable; //retourne nullptr si non trouve
}

//Parcours le conteneur et affiche toutes les tables en utilisant l'operator << de Table
void GestionnaireTables::afficherTables(ostream& os) const
{
    auto it = conteneur_.begin();
    
    while (it != conteneur_.end())
    {
        os << *(*it);
        it++;
    }
}
