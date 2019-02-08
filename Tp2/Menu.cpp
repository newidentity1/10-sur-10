/*
* Titre : Menu.cpp - Travail Pratique #2
* Date : 18 Janvier 2019
* Auteur : Allan BEDDOUK
*/

#include "Menu.h"

//constructeurs

Menu::Menu()
{
	type_ = Matin;
}

Menu::Menu(string fichier, TypeMenu type)
{
	type_ = type;
    
	//lecture du fichier -- creation du menu
	lireMenu(fichier);
}

Menu::Menu(const Menu& menu)
{
    for (int i = 0; i < menu.listePlats_.size(); i++){
        Plat* copiePlat = new Plat(*(menu.listePlats_[i]));
        listePlats_.push_back(copiePlat);
    }
    type_ = menu.type_;
}

//destructeur
Menu::~Menu()
{
	for (int i = 0; i < listePlats_.size(); i++)
		delete listePlats_[i];
    listePlats_.clear();
}

//getters
int Menu::getNbPlats() const
{
	return int(listePlats_.size());
}

//autres methodes
ostream& operator<< (ostream& sortie, const Menu& menu)
{
	for (int i = 0; i < menu.listePlats_.size(); i++) {
		sortie << "\t";
        sortie << *(menu.listePlats_[i]);
	}
    return sortie;
}

Menu& Menu::operator+=(Plat&  plat)
{
    listePlats_.push_back(&plat);
    return *this;
}

Menu& Menu::operator=(Menu& menu)
{
    if (this != &menu)
    {
   // for (int i = 0; i < listePlats_.size(); i++)
   //    delete listePlats_[i];
   // listePlats_.clear();
  
        for (int i = 0; i < menu.listePlats_.size(); i++) {
            Plat* copiePlat = new Plat(*(menu.listePlats_[i]));
            listePlats_.push_back(copiePlat);
        }
    type_ = menu.type_;
    }
        return *this;
}

bool Menu::lireMenu(const string& fichier) {
    ifstream fichierPlats(fichier);
    
    if (fichierPlats.fail()) {
        cout << "Erreur d'ouverture de fichier" << endl;
        return false;
    }
    else {
        while (!ws(fichierPlats).eof()) {
            string motLu="";
            fichierPlats >> motLu;
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
                    if (type == motLu) {
                        while (true) {
                            string nom;
                            double prix,coutResto;
                            fichierPlats >> nom >> prix >> coutResto;
                            
                            if (nom == "-MIDI" || nom == "-SOIR" || nom == "-TABLES")
                                return true;
                            Plat* plat = new Plat(nom, prix, coutResto);
                            listePlats_.push_back(plat);
                        }
                    }
            }
            return false;
    }
     /*ifstream file(fichier, ios::in);

	if (!file) {
		cout << "ERREUR : le fichier n'a pas pu etre ouvert" << endl;
        return false;
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
		int coutResto;


		// lecture
		while (!file.eof()) {
            getline(file, ligne,'\r');
         
			//trouver le bon type de menu (section)
			if (ligne == type){
				//commencer a lire -- s'arrete si fin du fichier ou encore si on arrive a une nouvelle section du menu
				getline(file, ligne, '\r');
                cout<< ligne << endl;
				int curseur;^
				while (ligne[0] != '-' && !file.eof()) {
					//trouver le nom
					for (int i = 0; i < int(ligne.size()); i++) {
						if (ligne[i] == ' ') {
							curseur = i;
							break;
						}
						nom += ligne[i];
					}
					//trouver le prix

					for (int i = (curseur + 1); i < int(ligne.size()); i++) {
						if (ligne[i] == ' ') {
							curseur = i;
							break;
						}
						prixString += ligne[i];

					}
					//passer le prixString en double --- indice dans l'enonce
					prix = stof(prixString.c_str());
                    cout << prix<< endl;

					for (int i = curseur + 1; i < int(ligne.size()); i++) {
						if (ligne[i] == ' ')
							break;
						coutString += ligne[i];
					}

					coutResto =int( stof(coutString.c_str()));
                   
					//ajouterPlat( Plat(nom, prix, cout));
                    Plat* plat = new Plat(nom, prix, coutResto);
                    listePlats_.push_back(plat);
                    nom = "";
					prixString = "";
					coutString = "";

					getline(file, ligne, '\r');
				}
			}
		}

		file.close();
		return true;
	}*/
}

Plat * Menu::trouverPlatMoinsCher() const
{
	Plat minimum(*listePlats_[0]);
	int found = 0;

	for (unsigned i = 0; i < listePlats_.size(); ++i)
	{
		if (*listePlats_[i] < minimum)
		{
			minimum = *listePlats_[i];
			found = i;
		}
	}

	return listePlats_[found];
}

Plat* Menu::trouverPlat(const string& nom) const {
	
    for (int i = 0; i < listePlats_.size(); i++) {
		if (listePlats_[i]->getNom() == nom)
			return listePlats_[i];
	}
	return nullptr;
}
