/*
* Titre : Restaurant.cpp - Travail Pratique #2
* Date : 24 Février 2019
* Équipe : Estefan Vega-Calcada (1934346) & Yanis Toubal (1960266)
*/

#include "Restaurant.h"

//constructeurs 
Restaurant::Restaurant() :
    nom_(new string("Inconnu")),
    chiffreAffaire_(0.0),
    momentJournee_(Matin),
    menuMatin_(new Menu("menu.txt", Matin)),
    menuMidi_(new Menu("menu.txt", Midi)),
    menuSoir_(new Menu("menu.txt", Soir))
{}

//constructeur par parametres 
Restaurant::Restaurant(const string& fichier,  const string& nom, TypeMenu moment) :
    nom_(new string(nom)),
    chiffreAffaire_(0.0),
    momentJournee_(moment),
    menuMatin_(new Menu(fichier, Matin)),
    menuMidi_(new Menu(fichier, Midi)),
    menuSoir_(new Menu(fichier, Soir))
{
	lireTable(fichier); 
	lireAdresses(fichier);
}

//constructeur de copie 
Restaurant::Restaurant(const Restaurant & restau) : nom_(new string(*restau.nom_)),
    chiffreAffaire_(restau.chiffreAffaire_),
    momentJournee_(restau.momentJournee_),
    menuMatin_(new Menu(*restau.menuMatin_)),
    menuMidi_(new Menu(*restau.menuMidi_)),
    menuSoir_(new Menu(*restau.menuSoir_))
{
	for (unsigned i = 0; i < restau.tables_.size(); i++)
		tables_.push_back(new Table(*restau.tables_[i]));
	
	for (unsigned i = 0; i < NB_ZONES_LIVR; i++) 
		fraisTransport_[i] = restau.getFraisTransports(i);
}
//destructeur 
Restaurant::~Restaurant() 
{
	delete nom_; 
	delete menuMatin_; 
	delete menuMidi_; 
	delete menuSoir_; 

	for (unsigned i = 0; i < tables_.size(); i++)
	{
		for (unsigned j = 0; j < tables_[i]->getCommande().size(); j++) 
		{
			if (tables_[i]->getCommande()[j]->getType() == Custom)
				delete tables_[i]->getCommande()[j];
		}	
		delete tables_[i];
	}
}

//setter 
void Restaurant::setMoment(TypeMenu moment) 
{
	momentJournee_ = moment; 
}
void Restaurant::setNom(const string & nom)
{
	nom_ = new string(nom);
}

//getters 
string Restaurant::getNom() const 
{
	return *nom_; 
}

TypeMenu Restaurant::getMoment() const 
{
	return momentJournee_; 
}

double Restaurant::getFraisTransports(int index) const
{
	return fraisTransport_[index];
}


//autres methodes 
//libere la table et incremente le chiffre daffaire du restaurant
void Restaurant::libererTable(int id) 
{
	for (unsigned i = 0; i < tables_.size(); i++) 
	{
		if (id == tables_[i]->getId()) 
		{
			double prixTotalCommande = 0.0; 
			
			for (unsigned j = 0; j < tables_[i]->getCommande().size(); j++)
				prixTotalCommande += tables_[i]->getCommande()[j]->getPrix(); 
			
			chiffreAffaire_ += tables_[i]->getChiffreAffaire() - calculerReduction(tables_[i]->getClientPrincipal(), prixTotalCommande, (i == INDEX_TABLE_LIVRAISON)); // // On applique le rabais sur le prix total de la commande
			
			tables_[i]->libererTable(); 
			break;
		}
	}
}

// Affichage du restaurant : surcharge de l'operateur << 
ostream& operator<<(ostream& os, const Restaurant& restau)
{
	os << "Le restaurant " << *restau.nom_;
	if (restau.chiffreAffaire_ != 0.0)
		os << " a fait un chiffre d'affaire de : " << restau.chiffreAffaire_ << "$" << endl;
	else
		os << " n'a pas fait de benefice ou le chiffre n'est pas encore calcule." << endl;

	os << "-Voici les tables : " << endl;

	for (unsigned i = 0; i < restau.tables_.size(); i++) {
		os  << *restau.tables_[i] << endl;
	}
	os << endl;


	os << "-Voici son menu : " << endl;
	os << "Matin : " << endl
		<<*restau.menuMatin_<<endl << "Le plat le moins cher est : " << *restau.menuMatin_->trouverPlatMoinsCher() << endl;

	os << "Midi : " << endl
		<< *restau.menuMidi_<<endl << "Le plat le moins cher est : " << *restau.menuMidi_->trouverPlatMoinsCher() << endl;
	os << "Soir : " << endl
		<< *restau.menuSoir_<<endl << "Le plat le moins cher est : " << *restau.menuSoir_->trouverPlatMoinsCher() <<endl;

	return os;
}

// Ajoute un plat au vecteur de commande 
void Restaurant::commanderPlat(const string& nom, int idTable,TypePlat type, int nbIngredients) 
{
	Plat* plat = nullptr;
	int index; 
	
	for (unsigned i = 0; i < tables_.size(); i++) 
	{
		if (idTable == tables_[i]->getId()) 
		{
			index = i; 
			switch (momentJournee_) 
			{
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

			break;
		}
	}

	if (plat == nullptr || !tables_[index]->estOccupee()) 
	{
		cout << "Erreur : table vide ou plat introuvable" << endl << endl;
	}
	else
	{
        if (type == Custom)
		{
			Plat* platCustom = new PlatCustom(plat->getNom(), plat->getPrix(), plat->getCout(), nbIngredients);
			tables_[index]->commander(platCustom);
        }
		else 
		{
            tables_[index]->commander(plat);
        }
	}
}

// Comparaison de chiffres d'affaires de Restaurants 
bool Restaurant::operator<(const Restaurant & restau) const 
{
	return this->chiffreAffaire_ < restau.chiffreAffaire_;
}

// Assignation d'un restaurant a un autre. Écrase les données 
Restaurant& Restaurant::operator=(const Restaurant & restau)
{
	if (this != &restau)
	{
		delete menuMatin_;
		delete menuMidi_;
		delete menuSoir_;

		
		chiffreAffaire_ = restau.chiffreAffaire_;
		momentJournee_ = restau.momentJournee_;

		for (unsigned i = 0; i < NB_ZONES_LIVR; i++)
			fraisTransport_[i] = restau.fraisTransport_[i];

		menuMatin_ = new Menu(*restau.menuMatin_);
		menuMidi_ = new Menu(*restau.menuMidi_);
		menuSoir_ = new Menu(*restau.menuSoir_);
		
		for (unsigned i = 0; i < tables_.size(); i++)
			delete tables_[i];

		tables_.clear();
		
		for (unsigned j = 0; j < restau.tables_.size(); j++)
			tables_.push_back(new Table(*restau.tables_[j]));
		
		for (unsigned k = 0; k < NB_ZONES_LIVR; k++)
			fraisTransport_[k] = restau.getFraisTransports(k);

	}
	return *this;
}

void Restaurant::lireTable(const string& fichier) 
{
	ifstream file(fichier, ios::in); 

	if (file) {
		string ligne; 
		
		string idString; 
		int id; 

		string nbPersonnesString; 
		int nbPersonnes; 

		int curseur; 
		while ( !file.eof()) {
			getline(file, ligne); 
			if (ligne == "-TABLES") {
					getline(file, ligne); 
				do {
					for (unsigned i = 0; i < ligne.size(); i++) {
						if (ligne[i] == ' ') {
							curseur = i; 
							break; 
						}
						idString += ligne[i]; 
					}

					id = stoi(idString); 

					nbPersonnesString = ligne.substr(curseur + 1); 
					nbPersonnes = stoi(nbPersonnesString); 

					*this+= new Table(id, nbPersonnes); 
					nbPersonnesString = ""; 
					idString = ""; 					
					getline(file, ligne);

				} while (ligne[0] != '-' && !file.eof());
			}
		}
		file.close(); 
	}
}

// Ajoute une table aux vecteurs de tables du restaurant 
Restaurant& Restaurant::operator+=(Table* table)
{
	tables_.push_back(new Table(*table)); 
	return *this;
}

//Placer les clients a une table
void Restaurant::placerClients(Client* client)
{
	int indexTable = -1;
	int minimum = 100;

	for (unsigned i = 0; i < tables_.size(); i++) {
		if (tables_[i]->getNbPlaces() >= (client->getTailleGroupe()) && 
            !tables_[i]->estOccupee() && tables_[i]->getNbPlaces() < minimum &&
			i != INDEX_TABLE_LIVRAISON) 
		{
			indexTable = i;
			minimum = tables_[i]->getNbPlaces();
		}
	}
	if (indexTable == -1) 
	{
		cout << "Erreur : il n'y a plus/pas de table disponible pour les clients. " << endl;
	}
	else 
	{
		tables_[indexTable]->placerClients((client->getTailleGroupe())); 
		tables_[indexTable]->setClientPrincipal(client);
	}
}

// Livraison 
void Restaurant::livrerClient(Client * client, const vector<string>& commande)
{
	if (client->getStatut() == Prestige)
	{
		tables_[INDEX_TABLE_LIVRAISON]->placerClients(1);
		tables_[INDEX_TABLE_LIVRAISON]->setClientPrincipal(client);
		
		cout << "Livraison en cours..." << endl;
		
		for (size_t i = 0; i < commande.size(); i++)
			commanderPlat(commande[i], tables_[INDEX_TABLE_LIVRAISON]->getId());
		
		
		cout << "Statut de la table de livraison:(table numero "<< tables_[INDEX_TABLE_LIVRAISON]->getId() << "):" << endl << *tables_[INDEX_TABLE_LIVRAISON];
		cout << "Livraison terminee" << endl << endl;;
		libererTable(tables_[INDEX_TABLE_LIVRAISON]->getId());
	}
	else
	{
		cout << "Le client " << client->getPrenom() << " " << client->getNom() << " n est pas admissible a la livraison." << endl << endl ;
	}
}

// Methode de lecture de l'adresse d'un client a l'aide du fichier 
// fournit 
void Restaurant::lireAdresses(const string & fichier)
{
	ifstream file(fichier, ios::in);

		if (file) {
			string ligne;

			string addresseCodeStr;
			int addressCode;

			string fraisStrg;
			double frais;

			int curseur;
			while (!file.eof()) {
				getline(file, ligne);
				if (ligne == "-ADDRESSES") {
					while (!file.eof()) {
						getline(file, ligne);
						for (unsigned i = 0; i < ligne.size(); i++) {
							if (ligne[i] == ' ') {
								curseur = i;
								break;
							}
							addresseCodeStr += ligne[i];
							addressCode = stoi(addresseCodeStr);

						}


						fraisStrg = ligne.substr(curseur + 1);
						frais = stod(fraisStrg);
						fraisTransport_[addressCode] = frais;

						addresseCodeStr = "";
						fraisStrg = "";



					}

					
				}
			}
			file.close();
		}
	}

// Calcule le prix de reduction selon le statut du client
// Evalue egalement si la livraison est gratuite en fonction du 
// statut et du nombre de points pour un client prestige 
double Restaurant::calculerReduction(Client* client, double montant, bool livraison)
{
	switch (client->getStatut()) 
	{

		case Occasionnel:
				return 0.0;
			break;

		case Fidele:
			if (static_cast<ClientRegulier*>(client)->getNbPoints() > SEUIL_DEBUT_REDUCTION)
			{
				return (montant * TAUX_REDUC_REGULIER);
			}
			else
			{
				return 0.0;
			}
			break;

		case Prestige:
			if (static_cast<ClientPrestige*>(client)->getNbPoints() > SEUIL_LIVRAISON_GRATUITE && livraison)
			{
				return (getFraisTransports(static_cast<ClientPrestige*>(client)->getAddresseCode() ));
			}
			else if (static_cast<ClientPrestige*>(client)->getNbPoints() < SEUIL_LIVRAISON_GRATUITE && livraison)
			{
				return (montant * TAUX_REDUC_PRESTIGE - getFraisTransports(static_cast<ClientPrestige*>(client)->getAddresseCode()));
			}
			else
			{
				return (montant * TAUX_REDUC_PRESTIGE);
			}
			break;
	}
}
