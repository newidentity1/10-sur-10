/*
* Titre : Table.cpp - Travail Pratique #2
* Date : 18 Janvier 2019
* Auteur : Allan BEDDOUK
*/

#include "Table.h"

//constructeurs
Table::Table()
{
	//capacite_ = MAXCAP;
	//commande_ = new Plat*[MAXCAP];
	//nbPlats_ = 0;
	id_ = -1;
	nbPlaces_ = 1;
	nbClientsATable_ = 0;
}

Table::Table(int id, int nbPlaces)
{
	//capacite_ = MAXCAP;
	//commande_ = new Plat*[capacite_];
	//nbPlats_ = 0;
	id_ = id;
	nbPlaces_ = nbPlaces;
	nbClientsATable_ = 0;
}

//destructeur
Table::~Table()
{}

//getters
int Table::getId() const
{
	return id_;
}

int Table::getNbPlaces() const
{
	return nbPlaces_;
}

int Table::getnbClientATable() const
{
	return nbClientsATable_;
}

bool Table::estPleine() const
{
	return nbPlaces_==0;
}

bool Table::estOccupee() const
{
	return nbClientsATable_!=0;
}

//setters
void Table::setId(int id)
{
	id_ = id;
}

void Table::libererTable()
{
	nbPlaces_ += nbClientsATable_;
	nbClientsATable_ = 0;
	//A MODIFIER
    commande_.clear();
	
}

void Table::placerClient(int nbClients)
{
	nbClientsATable_ = nbClients;
	nbPlaces_ -= nbClients;
}

//autres methodes
void Table::commander(Plat* plat)
{
	// A MODIFIER
	commande_.push_back(plat);
}

double Table::getChiffreAffaire() const
{
	double chiffre = 0;
	for (int i = 0; i < commande_.size(); i++) {
		chiffre += (commande_[i]->getPrix() - commande_[i]->getCout());
	}
	return chiffre;
}

//affichage
ostream& operator<<(ostream& sortie, const Table& table){
    
    sortie << "La table numero " << table.getId();
    if (table.estOccupee()) {
        sortie << " est occupee. ";
        if (table.commande_.size() != 0) {
             sortie << "Voici la commande passee par les clients : " << endl;
            for (int i = 0; i < table.commande_.size(); i++) {
                sortie  << "\t";
                sortie << table.commande_[i];
            }
        }
        else
             sortie << "Mais ils n'ont rien conmmande pour l'instant. " << endl;
    }
    else {
        sortie << " est libre. " << endl;
    }
    return sortie;
}

