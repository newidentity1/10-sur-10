/********************************************
* Titre: Travail pratique #5 - gestionnairePlats.cpp
* Date: 21 mars 2019
* Auteur: Moussa Traor� & Ryan Hardie & Wassim Khene
*******************************************/

#include "GestionnairePlats.h"
#include "LectureFichierEnSections.h"
#include "PlatBio.h"
#include "PlatVege.h"
#include "PlatBioVege.h"

using namespace std;

void GestionnairePlats::lirePlats(const string& nomFichier, TypeMenu type)
{
	LectureFichierEnSections fichier{ nomFichier };
	fichier.allerASection(entetesDesTypesDeMenu[static_cast<int>(type)]);
	while (!fichier.estFinSection())
		ajouter(lirePlatDe(fichier));
}

pair<string, Plat*> GestionnairePlats::lirePlatDe(LectureFichierEnSections& fichier)
{
	auto lectureLigne = fichier.lecteurDeLigne();
	Plat* plat;
	string nom, typeStr;
	TypePlat type;
	double prix, coutDeRevient;
	lectureLigne >> nom >> typeStr >> prix >> coutDeRevient;
	type = TypePlat(stoi(typeStr));
	double ecotaxe, vitamines, proteines, mineraux;
	switch (type) {
	case TypePlat::Bio:
		lectureLigne >> ecotaxe;
		plat = new PlatBio{ nom, prix, coutDeRevient, ecotaxe };
		break;
	case TypePlat::BioVege:
		lectureLigne >> ecotaxe >> vitamines >> proteines >> mineraux;
		plat = new PlatBioVege(nom, prix, coutDeRevient, ecotaxe, vitamines, proteines, mineraux);
		break;
	case TypePlat::Vege:
		lectureLigne >> vitamines >> proteines >> mineraux;
		plat = new PlatVege(nom, prix, coutDeRevient, vitamines, proteines, mineraux);
		break;
	default:
		plat = new Plat{ nom, prix, coutDeRevient };
	}
	return pair<string, Plat*>(plat->getNom(), plat);
}


GestionnairePlats::GestionnairePlats(const string& nomFichier, TypeMenu type) : type_(type)
{
    lirePlats(nomFichier, type);
}

GestionnairePlats::GestionnairePlats(GestionnairePlats* gestionnaire) : type_(gestionnaire->getType())
{
    auto it = conteneur_.begin();
   
    while (it != conteneur_.end())
    {
        string copieNomPlat = it->first;
        Plat* copiePointeurPlat = new Plat(*(it->second));
        
        ajouter(pair<string, Plat*>(copieNomPlat, copiePointeurPlat));
        it++;
    }
}

GestionnairePlats::~GestionnairePlats()
{
    auto it = conteneur_.begin();
    
    while(it != conteneur_.end())
    {
        delete  it->second;
        it++;
    }
    
}

TypeMenu GestionnairePlats::getType() const
{
    return type_;
}

Plat* GestionnairePlats::allouerPlat(Plat* plat)
{
    Plat* copiePlat = new Plat(*plat);
    return copiePlat;
}

Plat* GestionnairePlats::trouverPlatMoinsCher() const
{
    if (!conteneur_.empty())
    {
    return  min_element(conteneur_.begin(), conteneur_.end(), FoncteurPlatMoinsCher())->second;
    }
    return nullptr;
}

Plat* GestionnairePlats::trouverPlatPlusCher() const
{
    if (!conteneur_.empty())
    {
    return max_element(conteneur_.begin(), conteneur_.end(),
        [](const pair<string, Plat*>& platGauche, const pair<string, Plat*>& platDroit) {
            return platGauche.second->getPrix() < platDroit.second->getPrix();
        })->second;
    }
    return nullptr;
}

Plat* GestionnairePlats::trouverPlat(const string& nom) const
{
   auto it = conteneur_.begin();
    
    while(it != conteneur_.end())
    {
        if (it->first == nom)
            return it->second;
        it++;
    }
    return nullptr; //si le plat nest pas trouve
}

vector<pair<string, Plat*>> GestionnairePlats::getPlatsEntre(double borneInf, double borneSup)
{
    auto it = conteneur_.begin();
    vector<pair<string, Plat*>> platDansIntervalle;
    FoncteurIntervalle foncteur(borneInf, borneSup);
   
    while(it != conteneur_.end())
    {
        if (foncteur(*it))
            platDansIntervalle.push_back(*it);
        it++;
    }
    return platDansIntervalle;
}

void GestionnairePlats::afficherPlats(ostream& os) const
{
    auto it = conteneur_.begin();
    
    while (it != conteneur_.end()) {
        it->second->afficherPlat(os);
        it++;
    }
}
