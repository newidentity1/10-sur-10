/*
* Date : 25 f�vrier 2019
* Auteur : AbdeB
*/
#include "ClientPrestige.h"
#include "Restaurant.h"

ClientPrestige::ClientPrestige()
{
	adresse_ = ZoneHabitation::Zone3;
}

ClientPrestige::ClientPrestige(string_view nom, string_view prenom, int tailleGroupe, int nbPoints, ZoneHabitation adresse) :
ClientRegulier(nom, prenom, tailleGroupe, nbPoints),
adresse_(adresse)
{
   //TODO
}

ClientPrestige::~ClientPrestige(){};

ZoneHabitation ClientPrestige::getAdresseCode() const
{
	return adresse_;
}

void ClientPrestige::afficherClient(ostream & os) const
{
    Client::afficherClient(os);
}
string ClientPrestige::getAdressCodeString() const
{
	string zone;
	switch (adresse_)
	{
	case ZoneHabitation::Zone1:
		zone = "Zone 1";
		break;
	case  ZoneHabitation::Zone2:
		zone = " Zone 2";
		break;
	case  ZoneHabitation::Zone3:
		zone = "Zone 3";
		break;

	default:
		zone = "erreur zone";
		break;
	}
	return zone;
}
double ClientPrestige :: getReduction(const Restaurant & res, double montant , bool estLivraison)
{   //TODO
    if (estLivraison && nbPoints_ > SEUIL_LIVRAISON_GRATUITE)
        return -1 * (res.getFraisLivraison(adresse_));
    else
        return -1 * montant * TAUX_REDUC_PRESTIGE;
}
