/********************************************
* Titre: Travail pratique #5 - Foncteur.h
* Date: 21 mars 2019
* Auteur: Moussa Traor� & Ryan Hardie & Wassim Khene
*******************************************/

#pragma once

#include <algorithm>
#include "Plat.h"


class FoncteurPlatMoinsCher
{ // TODO
public:
//    bool operator()(const Plat& platGauche,const Plat& platDroit) const
//    {
//        return (platGauche.getPrix() < platDroit.getPrix());
//    }
    
    bool operator()(const pair<string, Plat*>& platGauche,const pair<string, Plat*>&  platDroit) const
    {
        return (platGauche.second->getPrix() < platDroit.second->getPrix());
    }

};

class FoncteurIntervalle
{
   // TODO
public:
    FoncteurIntervalle(double borneInf, double borneSup) :
    borneInf_(borneInf), borneSup_(borneSup) {};
    
    bool operator()(const pair<string, Plat*>& plat) const
    {
        return (plat.second->getPrix() >= borneInf_ &&
                plat.second->getPrix() <= borneSup_);
    }
    
private:
    double borneInf_;
    double borneSup_;
    
};
