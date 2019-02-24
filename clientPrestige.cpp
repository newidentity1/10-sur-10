#include "ClientPrestige.h"

//constructeurs

ClientPrestige::ClientPrestige() :
    ClientRegulier()
{
	statut_ = Prestige;
    addresse_ = Zone3;
}

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

//autres fonctions

ostream& operator<<(ostream& os, const ClientPrestige& client)
{
    os << static_cast<ClientRegulier>(client) << "\tHabite dans la Zone " <<
    (1 + client.getAddresseCode());
    
    return os;
}
