/*
* Titre : Menu.cpp - Travail Pratique #3
* Date : 24 F�vrier 2019
* �quipe : Estefan Vega-Calcada (1934346) & Yanis Toubal (1960266)
*/

#include "Menu.h"

//constructeurs 

Menu::Menu() : type_(Matin)
{}

//constructeur par parametre 
Menu::Menu(const string& fichier, TypeMenu type) : type_(type)
{
	//lecture du fichier -- creation du menu
	lireMenu(fichier); 
}

// Constructeur de copie 
Menu::Menu(const Menu & menu): type_(menu.type_)
{
	for (unsigned i = 0; i < menu.listePlats_.size(); i++)
	{
        switch (menu.listePlats_[i]->getType()) {
            case Regulier:
                listePlats_.push_back(new Plat(*menu.listePlats_[i]));
                break;
                
            case Bio:
                listePlats_.push_back(new PlatBio(menu.listePlats_[i]->getNom(), menu.listePlats_[i]->getPrix(), menu.listePlats_[i]->getCout(), static_cast<PlatBio*>(menu.listePlats_[i])->getEcoTaxe()));
                break;
        }
	}
}

//destructeur
Menu::~Menu()
{
	for (unsigned i = 0; i < listePlats_.size(); i++)
		delete listePlats_[i];
	
	listePlats_.clear();
}

//getters
vector<Plat*> Menu::getListePlats() const
{
	return listePlats_;
}

//Affichage: surcharge de l'operateur << 
ostream& operator<<(ostream& os, const Menu& menu)
{
	for (unsigned i = 0; i < menu.listePlats_.size(); i++) 
	{
        switch (menu.listePlats_[i]->getType()) 
		{
            case Regulier:
                os << "\t" << *menu.listePlats_[i];
                break;
            
            case Bio:
				os << "\t" << *(static_cast<PlatBio*>(menu.listePlats_[i]));
                break;
        }
    }
	return os;
}


// Surcharge de l'operateur +=, permet d'ajouter un plat Bio au Menu
Menu& Menu::operator+=(const PlatBio& plat)
{
	listePlats_.push_back(new PlatBio(plat));
	return *this;
}

// Surcharge de l'operateur : permet d'ajouter un plat au Menu
Menu& Menu::operator+=(const Plat& plat) 
{
	listePlats_.push_back(new Plat(plat));
		return *this;
}


// Surcharge de l'operateur = , permet d'assigner un nouveau Menu au Menu
// existant (Ecrase les donnees du menu actuel) (assignation)
Menu & Menu::operator=(const Menu & menu)
{
	if (this != &menu)
	{
		type_ = menu.type_;
        
        for (unsigned i = 0; i < menu.listePlats_.size(); i++)
           delete listePlats_[i];
        listePlats_.clear();

		for (unsigned i = 0; i < menu.listePlats_.size(); i++)
            switch (menu.listePlats_[i]->getType()) {
                case Regulier:
                    listePlats_.push_back(new Plat(*menu.listePlats_[i]));
                    break;
                    
                case Bio:
                    listePlats_.push_back(new PlatBio(menu.listePlats_[i]->getNom(), menu.listePlats_[i]->getPrix(), menu.listePlats_[i]->getCout(), static_cast<PlatBio*>(menu.listePlats_[i])->getEcoTaxe()));
                    break;
            }
	}
	return *this;
}

// Permet d'initialiser le Menu avec un fichier 
void Menu::lireMenu(const string& fichier) {
	ifstream file(fichier, ios::in); 

	if (!file) {
		cout << "ERREUR : le fichier n'a pas pu etre ouvert" << endl; 
	}
	else {
		string type; 
		switch (type_) {
		case Matin :
			type = "-MATIN"; 
			break; 
		case Midi : 
			type = "-MIDI";
			break;
		case Soir : 
			type = "-SOIR"; 
			break;
		}
		string ligne; 

		string nom; 
		
		string prixString;
		double prix; 

		string coutString; 
		double cout;

		string typeString;
		int typePlat;

		string ecotaxeString;
		double ecoTaxe;


		// lecture
		while (!file.eof()) {
			std::getline(file, ligne); 
			//trouver le bon type de menu (section)
			if (ligne == type){ 
				//commencer a lire -- s'arrete si fin du fichier ou encore si on arrive a une nouvelle section du menu 
				std::getline(file, ligne);
				int curseur; 
				while (ligne[0] != '-' && !file.eof()) {
					//trouver le nom 
					for (int i = 0; i < int(ligne.size()); i++) {
						if (ligne[i] == ' ') {
							curseur = i;
							break;
						}
						nom += ligne[i]; 
					}

					//trouver le type 
					for (int i = curseur + 1; i < int(ligne.size()); i++) {
						if (ligne[i] == ' ') {
							curseur = i;
							break;
						}
						typeString += ligne[i];

					}

					typePlat = stoi(typeString);

					//trouver le prix 

					for (int i = curseur + 1; i < int(ligne.size()); i++) {
						if (ligne[i] == ' ') {
							curseur = i; 
							break; 
						}
						prixString += ligne[i]; 
						
					}
					//passer le prixString en double --- indice dans l'enonce 
					prix = stof(prixString.c_str()); 

					for (int i = curseur + 1; i < int(ligne.size()); i++) {
						if (ligne[i] == ' ') {
							if (typePlat == Bio)
								curseur = i;
							break;

						}

						coutString += ligne[i]; 
					}

					cout = stod(coutString.c_str()); 

					//lire le taux si plat bio

					if (typePlat == TypePlat::Bio) {

						for (int i = curseur + 1; i < int(ligne.size()); i++) {
							if (ligne[i] == ' ')
								break;
							ecotaxeString += ligne[i];
						}
						ecoTaxe = stod(ecotaxeString);
						*this += PlatBio(nom, prix, cout, ecoTaxe);
					}
					else {
						*this += Plat(nom, prix, cout);
					}

					nom = ""; 
					prixString = ""; 
					coutString = ""; 
					typeString = "";
					ecotaxeString ="";

					std::getline(file, ligne);
				}
			}
		}

		file.close(); 
	}
}

// Retourne un pointeur vers le Plat le moins cher de Menu
Plat * Menu::trouverPlatMoinsCher() const
{
	Plat minimum(*listePlats_[0]);
	int found = 0;

	for (unsigned i = 0; i < listePlats_.size(); i++)
	{
		if (*listePlats_[i] < minimum)
		{
			minimum = *listePlats_[i];
			found = i;
		}
	}
	return listePlats_[found];
}

// Permet de trouver un plat a l'aide de son nom 
Plat* Menu::trouverPlat(const string& nom) const
{
	for (unsigned i = 0; i < listePlats_.size(); ++i) {
		if (listePlats_[i]->getNom() == nom)
			return listePlats_[i]; 
	}
	return nullptr; 
}

