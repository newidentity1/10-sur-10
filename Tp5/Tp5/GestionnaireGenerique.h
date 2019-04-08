/********************************************
* Titre: Travail pratique #5 - GestionnaireGenerique.h
* Date: 21 mars 2019
* Auteur: Moussa Traor� & Ryan Hardie & Wassim Khene
*******************************************/

/*
* Titre : Implémentation de GestionnaireGenerique.h - Travail Pratique #5
* Date : 8 Avril 2019
* Auteur : Yanis Toubal (1960266) et Estefan Vega Calcada (1934346)
*/



#pragma once

#include <algorithm>
#include "Foncteur.h"

using namespace std;
//T   = pair<string, Plat*> ou Table*;
//C   = map<string, Plat*> ou set<Table*>;

template<typename T, typename C>
class GestionnaireGenerique
{
public:
	C getConteneur() const; //TODO
	void ajouter(const T& t);//TODO
	size_t getNombreElements() const;//TODO

protected:
	C conteneur_;
};

//retourne une copie du conteneur du type generique C
template<typename T, typename C>
C GestionnaireGenerique<T, C>::getConteneur() const
{
    return conteneur_;
}

//insert un objet du type generique C dans le conteneur du type generique T
template<typename T, typename C>
void GestionnaireGenerique<T, C>::ajouter(const T& t)
{
    conteneur_.insert(t);
}

//retourne la taille du conteneur du type generique C
template<typename T, typename C>
size_t GestionnaireGenerique<T, C>::getNombreElements() const
{
    return conteneur_.size();
}
