//
/*
 * Titre : Client.cpp - Travail Pratique #4
 * Date : 25 Mars 2019
 * ƒquipe : Estefan Vega-Calcada (1934346) & Yanis Toubal (1960266)
 */
#include "Client.h"

Client::Client()
{
    tableOccupee_ = nullptr;
}

Client::Client(string_view nom, string_view prenom, int tailleGroupe) :
	nom_(nom), prenom_(prenom), tailleGroupe_(tailleGroupe)
{
    tableOccupee_ = nullptr;
}

int Client::getTailleGroupe() const
{
	return tailleGroupe_;
}

string Client::getNom() const
{
	return nom_;
}

string Client::getPrenom() const
{
	return prenom_;
}
void Client:: setTable(Table * ta)
{
    tableOccupee_ = ta;
    
}

Table * Client:: getTable() const
{
    return tableOccupee_;
}

void Client::afficherClient(ostream & os) const
{ // TODO
    if (tableOccupee_ != nullptr)
        os <<"Le nom du client principal est " << nom_ << " " << prenom_ << ". Il occupe la table numero " << tableOccupee_->getId() <<endl;
}

