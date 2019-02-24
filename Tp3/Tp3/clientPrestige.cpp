/*
* Titre : clientPrestige .cpp - Travail Pratique #3
* Date : 24 Février 2019
* Équipe : Estefan Vega-Calcada (1934346) & Yanis Toubal (1960266)
*/

#include "ClientPrestige.h"

//constructeurs

ClientPrestige::ClientPrestige() :
        ClientRegulier() 
{
	statut_ = Prestige;
    addresse_ = Zone3;
}

//constructeur par parametres 
ClientPrestige::ClientPrestige(string nom, string prenom, int tailleGroupe, int nbPoints, AddressCode addresse) :
    ClientRegulier(nom, prenom, tailleGroupe, nbPoints)
{
	statut_ = Prestige;
    addresse_ = addresse;
}

//Accesseur

AddressCode ClientPrestige::getAddresseCode() const
{
    return addresse_;
}


//Affichage: surcharge de l'operateur << 
ostream& operator<<(ostream& os, const ClientPrestige& client)
{
    os << static_cast<ClientRegulier>(client) << "\tHabite dans la Zone " <<
    (1 + client.getAddresseCode());
    
    return os;
}
