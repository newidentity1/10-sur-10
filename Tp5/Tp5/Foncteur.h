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
    bool operator()(const Plat& platGauche,const Plat& platDroit) const
    {
        return (platGauche.getPrix() < platDroit.getPrix());
    }

};

class FoncteurIntervalle
{
   // TODO
public:
    FoncteurIntervalle(double borneInf, double borneSup) :
    borneInf_(borneInf), borneSup_(borneSup) {};
    
    bool operator()(const Plat& plat) const
    {
        return (plat.getPrix() >= borneInf_ && plat.getPrix() <= borneSup_);
    }
    
private:
    double borneInf_;
    double borneSup_;
    
};

*
