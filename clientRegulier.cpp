#include "ClientRegulier.h"


// constructeurs
ClientRegulier::ClientRegulier() :
    Client(),
    nbPoints_(0)
{
    statut_ = Fidele;
}

ClientRegulier::ClientRegulier(string nom, string prenom, int tailleGroupe, int nbPoints) :
    Client (nom, prenom, tailleGroupe),
    nbPoints_(nbPoints)
{
    statut_ = Fidele;
}

//Accesseurs

int ClientRegulier::getNbPoints() const
{
    return nbPoints_;
}

// Autre Methodes

void ClientRegulier::augmenterNbPoints(int bonus)
{
    nbPoints_ += bonus;
}

ostream& operator<<(ostream& os, const ClientRegulier& client)
{
    os << static_cast<Client> (client) <<"Possede " <<client.getNbPoints() <<" points." <<endl;
    return os;
}
