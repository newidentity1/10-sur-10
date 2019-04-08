/********************************************
* Titre: Travail pratique #5 - gestionnairePlats.cpp
* Date: 21 mars 2019
* Auteur: Moussa Traor� & Ryan Hardie & Wassim Khene
*******************************************/

/*
* Titre :Implémentation de GestionnairePlats.cpp - Travail Pratique #5
* Date : 8 Avril 2019
* Auteur : Yanis Toubal (1960266) et Estefan Vega Calcada (1934346)
*/


#include "GestionnairePlats.h"
#include "LectureFichierEnSections.h"
#include "PlatBio.h"
#include "PlatVege.h"
#include "PlatBioVege.h"

using namespace std;

//Rempli le conteneur (map<string,Plat*>) d'un type de menu avec des plats provenant de la section correspodante dans un fichier texte
void GestionnairePlats::lirePlats(const string& nomFichier, TypeMenu type)
{
	LectureFichierEnSections fichier{ nomFichier };
	fichier.allerASection(entetesDesTypesDeMenu[static_cast<int>(type)]);
	while (!fichier.estFinSection())
		ajouter(lirePlatDe(fichier));
}

//Lit les plats dans le fichier texte et initialise dynamiquement le pointeur de base avec le constructeur du type representant le plat lu
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

//Constructeur qui remplit le conteneur
GestionnairePlats::GestionnairePlats(const string& nomFichier, TypeMenu type) : type_(type)
{
    lirePlats(nomFichier, type);
}

//Constructeur par copie qui prend en paramere un pointeur
GestionnairePlats::GestionnairePlats(GestionnairePlats* gestionnaire) : type_(gestionnaire->getType())
{
    auto it = conteneur_.begin();
   
    while (it != conteneur_.end())
    {
        string copieNomPlat = it->first;
        Plat* copiePointeurPlat = allouerPlat(it->second);
        
        ajouter(make_pair(copieNomPlat, copiePointeurPlat));
        it++;
    }
}

//destructeur
GestionnairePlats::~GestionnairePlats()
{
    auto it = conteneur_.begin();
    
    while(it != conteneur_.end())
    {
        delete it->second;
        it++;
    }
}

//retourne le type de menu (Matin, Midi, Soir)
TypeMenu GestionnairePlats::getType() const
{
    return type_;
}

//Alloue dynamiquement le bon de type en le camouflant dans un pointeur de plat qui est retourne
Plat* GestionnairePlats::allouerPlat(Plat* plat) const
{
    return plat->clone();
}

//Utilise l'algorithme min_element et le foncteur FoncteurPlatMoinsCher pour trouver l'iterateur vers la pair qui contient le plat le moins cher du conteneur. On retourne le pointeur vers ce plat.
Plat* GestionnairePlats::trouverPlatMoinsCher() const
{
    return  min_element(conteneur_.begin(), conteneur_.end(), FoncteurPlatMoinsCher())->second;
}

//Utilise l'algorithme max_element et une fonction lambda qui compare le prix de 2 plats pour trouver l'iterateur vers la pair qui contient le plat le plus cher du conteneur. On retourne le pointeur vers ce plat.
Plat* GestionnairePlats::trouverPlatPlusCher() const
{
    return max_element(conteneur_.begin(), conteneur_.end(),
        [](const pair<string, Plat*>& platGauche, const pair<string, Plat*>& platDroit) {
            return (*(platGauche.second) < *(platDroit.second));
        })->second;
}

//Parcours le conteneur et recherche a l'aide du nom une correspondance. Si il trouve le nom, retourne le pointeur vers le Plat sinon retourne nullptr.
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

//utilise l'algorithme copy_if et le foncteur FoncteurIntervalle pour trouver les plats dont les prix sont dans l'intervalle et les ajouter dans le vector platDansIntervalle qui est retourne.
vector<pair<string, Plat*>> GestionnairePlats::getPlatsEntre(double borneInf, double borneSup)
{
    vector<pair<string, Plat*>> platDansIntervalle;
    
    copy_if(conteneur_.begin(), conteneur_.end(), back_inserter(platDansIntervalle),
        FoncteurIntervalle(borneInf, borneSup));
    
    return platDansIntervalle;
}

//Affiche tous les plats contenus dans le conteneur.
void GestionnairePlats::afficherPlats(ostream& os) const
{
    auto it = conteneur_.begin();
    
    while (it != conteneur_.end())
    {
        it->second->afficherPlat(os);
        it++;
    }
}
