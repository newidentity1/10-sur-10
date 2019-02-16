/*
* Titre : Table.cpp - Travail Pratique #3
* Date : 11 F�vrier 2019
* Auteur :Fatou S. MOUNZEO
*/

#include "Table.h"

//constructeurs
Table::Table() :
    id_(-1),
    nbPlaces_(1),
    nbClientsATable_(0)
{}

Table::Table(int id, int nbPlaces) :
    id_(id),
    nbPlaces_(nbPlaces),
    nbClientsATable_(0)
{}

//getters
int Table::getId() const {
	return id_;
}

int Table::getNbPlaces() const {
	return nbPlaces_;
}

bool Table::estOccupee() const
{
	return nbClientsATable_!=0;
}

bool Table::estPleine() const {
	return nbPlaces_ == 0;
}

int Table::getNbClientsATable() const
{
	return nbClientsATable_;
}
vector<Plat*> Table::getCommande() const
{
	return commande_;
}

Client* Table::getCliengtPrincipal() const
{
    return clientPrincipal_;
}


//setters
void Table::setId(int id) {
	id_ = id;
}


void Table::libererTable() {
	nbPlaces_ += nbClientsATable_;
	nbClientsATable_ = 0;
	commande_.clear();
}

void Table::placerClients(int nbClient) {
	nbPlaces_ -= nbClient;
	nbClientsATable_ = nbClient;
}

void Table::setClientPrincipal(Client* clientPrincipal)
{
    clientPrincipal_ = clientPrincipal;
}

//autres methodes
void Table::commander(Plat* plat) {
	commande_.push_back(plat);
}

double Table::getChiffreAffaire() const {
	///TODO
	///Modifier pour que le chiffre d'Affaire prenne en compte le type de plat
	///voir �nonc�
	double chiffre = 0.0;
	
    for (unsigned i = 0; i < commande_.size(); ++i)
        switch (commande_[i]->getType()) {
            
            case (Occasionnel):
               
                chiffre += (commande_[i]->getPrix() - commande_[i]->getCout());
                break;
            
            case (Fidele):
                chiffre += (static_cast<PlatBio*>(commande_[i])->getEcoTaxe() + commande_[i]->getPrix()) - commande_[i]->getCout();
                break;
            
            case (Prestige):
                chiffre += (static_cast<PlatCustom*>(commande_[i])->getSupplement() + commande_[i]->getPrix()) - commande_[i]->getCout();
                break;
        }
	return chiffre;
}

//affichage

ostream& operator<<(ostream& os, const Table& table)
{
	os << "La table numero " << table.id_;
	if (table.estOccupee())
	{
        os << " est occupee. ";
        
        switch (table.clientPrincipal_->getStatut()) {
            case Occasionnel:
                os << (*(table.clientPrincipal_)) << endl;
                break;
                
            case Fidele:
                os << *(static_cast<ClientRegulier*>(table.clientPrincipal_)) << endl;
                break;
                
            case Prestige:
                os << *(static_cast<ClientPrestige*>(table.clientPrincipal_)) << endl;
                break;
        }
                if (!table.commande_.empty())
		{
			os << "Voici la commande passee par les clients : " << endl;
			for (unsigned i = 0; i < table.commande_.size(); ++i)
			{
				os << "\t" << *table.commande_[i];
			}
		}
		else
			os << "Mais ils n'ont rien commande pour l'instant. " << endl;
	}
	else
		os << " est vide. " << endl;

	return os;
}

