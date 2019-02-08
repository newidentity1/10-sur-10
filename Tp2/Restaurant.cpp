/*
* Titre : Restaurant.cpp - Travail Pratique #2
* Date : 18 Janvier 2019
* Auteur : Allan BEDDOUK
*/

#include "Restaurant.h"

//constructeurs
Restaurant::Restaurant() {
	nom_ = new string("Inconnu");

	chiffreAffaire_ = 0;

	momentJournee_ = Matin;

	menuMatin_ = new Menu("menu.txt", Matin);
	menuMidi_ = new Menu("menu.txt", Midi);
	menuSoir_ = new Menu("menu.txt",  Soir);

	//capaciteTables_ = INTTABLES;
	//nbTables_ = 0;
	//tables_ = new Table*[capaciteTables_];


}

Restaurant::Restaurant(const string& fichier,  const string& nom, TypeMenu moment) {
	nom_ = new string(nom);

	chiffreAffaire_ = 0.0;

	momentJournee_ = moment;

	menuMatin_ = new Menu(fichier, Matin);
	menuMidi_ = new Menu(fichier,  Midi);
	menuSoir_ = new Menu(fichier,  Soir);
    
    cout << *menuSoir_ << endl;

	//capaciteTables_ = INTTABLES;
	//nbTables_ = 0;
	//tables_ = new Table*[capaciteTables_];

	lireTable(fichier);
}

Restaurant::Restaurant(const Restaurant& restaurant) : tables_ (restaurant.tables_), menuMatin_(nullptr), menuMidi_(nullptr), menuSoir_(nullptr), nom_(nullptr)
{
    nom_ = new string(*(restaurant.nom_));
    
    chiffreAffaire_ = restaurant.chiffreAffaire_;
    
    momentJournee_ = restaurant.momentJournee_;
    
    menuMatin_ = new Menu(*(restaurant.menuMatin_));
    menuMidi_ = new Menu (*(restaurant.menuMidi_));
    menuSoir_ = new Menu (*(restaurant.menuSoir_));
}

//destructeur
Restaurant::~Restaurant() {
	delete nom_;
	delete menuMatin_;
	delete menuMidi_;
	delete menuSoir_;

	//A MODIFIER
	for (int i = 0; i < tables_.size(); i++)
		delete tables_[i];
	tables_.clear();
}


//setter

void Restaurant::setMoment(TypeMenu moment) {
	momentJournee_ = moment;
}

void Restaurant::setNom(string nom) {
    nom_ = new string(nom);
}
//getters
string Restaurant::getNom() const {
	return *nom_;
}

TypeMenu Restaurant::getMoment() const {
	return momentJournee_;
}

//autres methodes


void Restaurant::libererTable(int id) {
	for (int i = 0; i < tables_.size(); i++) {
		if (id == tables_[i]->getId()) {
			chiffreAffaire_ += tables_[i]->getChiffreAffaire();
			tables_[i]->libererTable();
		}
	}
}
ostream& operator<<(ostream& sortie, const Restaurant& restaurant){
	sortie << "Le restaurant " << restaurant.getNom();
	if (restaurant.chiffreAffaire_ != 0)
		sortie << " a fait un chiffre d'affaire de : " << restaurant.chiffreAffaire_ << "$" << endl;
	else
		sortie << " n'a pas fait de benefice ou le chiffre n'est pas encore calcule." << endl;
	sortie << "-Voici les tables : " << endl;
	for (int i = 0; i < restaurant.tables_.size(); i++) {
		sortie << "\t";
		sortie << restaurant.tables_[i];
		sortie << endl;
	}
	sortie << endl;


	sortie << "-Voici son menu : " << endl;
	sortie << "Matin : " << endl;
	sortie << restaurant.menuMatin_;
	sortie << "Midi : " << endl;
	sortie << restaurant.menuMidi_;
	sortie << "Soir : " << endl;
	sortie << restaurant.menuSoir_;
    
    return sortie;
}

Restaurant& Restaurant::operator=(const Restaurant& restaurant)
{
    if (this != & restaurant){
    
        for (int i = 0; i < tables_.size(); i++)
            delete tables_[i];
        tables_.clear();
    
        tables_ = restaurant.tables_;
    
        delete nom_;
        nom_ = new string(*(restaurant.nom_));
        
        delete menuMatin_;
        delete menuMidi_;
        delete menuSoir_;
        
        menuMatin_ = new Menu(*(restaurant.menuMatin_));
        menuMidi_ = new Menu (*(restaurant.menuMidi_));
        menuSoir_ = new Menu (*(restaurant.menuSoir_));
        
        chiffreAffaire_ = restaurant.chiffreAffaire_;
        momentJournee_ = restaurant.getMoment();
    }
    return *this;
}

bool Restaurant::operator<(const Restaurant& restaurant)
{
    return (chiffreAffaire_ < restaurant.chiffreAffaire_);
}

void Restaurant::commanderPlat(const string& nom, int idTable) {
	Plat* plat = nullptr;
	int index;
    for (int i = 0; i < tables_.size(); i++) {
		if (idTable == tables_[i]->getId()) {
			index = i;
			switch (momentJournee_) {
			case Matin :
				plat = menuMatin_->trouverPlat(nom);
				break;
			case Midi :
				plat = menuMidi_->trouverPlat(nom);
				break;
			case Soir :
				plat = menuSoir_->trouverPlat(nom);
				break;
			}
		}
	}
	if (plat != nullptr && tables_[index]->estOccupee()) {
		tables_[index]->commander(plat);
	}
	else cout << "Erreur : table non occupee ou plat introuvable" << endl;
}

void Restaurant::lireTable(const string& fichier) {
	ifstream file(fichier, ios::in);

	if (file) {
		string ligne;

		string idString;
		int id;

		string nbPersonnesString;
		int nbPersonnes;

		int curseur;
		while (!file.eof()) {
			getline(file, ligne);
			if (ligne == "-TABLES") {
				while (!file.eof()) {
					getline(file, ligne);
					for (int i = 0; i < ligne.size(); i++) {
						if (ligne[i] == ' ') {
							curseur = i;
							break;
						}
						idString += ligne[i];
					}

					id = stoi(idString);

					nbPersonnesString = ligne.substr(curseur + 1);
					nbPersonnes = stoi(nbPersonnesString);

					Table* table = new Table(id, nbPersonnes);
                    tables_.push_back(table);
                    nbPersonnesString = "";
					idString = "";
				}
			}
		}
		file.close();
	}
}

Restaurant& Restaurant::operator+=(Table* table) {
	
    tables_.push_back(table);
    
    return *this;
}

void Restaurant::placerClients(int nbClients) {
	int indexTable = -1;
	int minimum = 100;
    
	for (int i = 0; i < tables_.size(); i++) {
		if (tables_[i]->getNbPlaces() >= nbClients && !tables_[i]->estOccupee() && tables_[i]->getNbPlaces() < minimum) {
			indexTable = i;
			minimum = tables_[i]->getNbPlaces();
		}
	}
	if (indexTable == -1) {
		cout << "Erreur : il n'y a plus/pas de table disponible pour le client. " << endl;
	}else
	tables_[indexTable]->placerClient(nbClients);
}
