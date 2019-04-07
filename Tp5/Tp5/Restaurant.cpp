/*
* Date : 25 f�vrier 2019
* Auteur : AbdeB
*/

#include "Restaurant.h"
#include "LectureFichierEnSections.h"
#include "debogageMemoire.hpp"
#include <cassert>


//constructeurs 
Restaurant::Restaurant() :
	Restaurant{"menu.txt", "Inconnu", TypeMenu::Matin}
{
}

//constructeur utilisant un fichier texte pour initialiser les menus, les frais de livraison et les tables
Restaurant::Restaurant(const string& nomFichier, string_view nom, TypeMenu moment) :
	nom_{nom},
	momentJournee_{moment},
	chiffreAffaire_{0},
	menuMatin_{new GestionnairePlats{nomFichier, TypeMenu::Matin}},
	menuMidi_ {new GestionnairePlats{nomFichier, TypeMenu::Midi }},
	menuSoir_ {new GestionnairePlats{nomFichier, TypeMenu::Soir }},
	fraisLivraison_{},
    tables_{new GestionnaireTables}
{
    tables_->lireTables(nomFichier);
	lireAdresses(nomFichier);
}

// Destructeur.
Restaurant::~Restaurant()
{
	delete menuMatin_;
	delete menuMidi_;
	delete menuSoir_;
    delete tables_;
}


// Setters.

//changer le moment de la journee
void Restaurant::setMoment(TypeMenu moment)
{
	momentJournee_ = moment; 
}

//changer le nom du restaurant
void Restaurant::setNom(string_view nom)
{
	nom_ = nom;
}

//changer le chiffre d'affaire du resto
 void  Restaurant::setChiffreAffaire( double chiffre)
{
    chiffreAffaire_ = chiffre;
}

// Getters.

//retourne le nom du restaurant
string Restaurant::getNom() const
{
	return nom_; 
}

//retourne le moment de la journee
TypeMenu Restaurant::getMoment() const
{
	return momentJournee_; 
}

//retourne un pointeur vers le gestionnaire de table
GestionnaireTables* Restaurant::getTables() const
{
    return tables_;
}

//retourne les frais de livraison selon la zone
double Restaurant::getFraisLivraison(ZoneHabitation zone) const
{
    return fraisLivraison_[static_cast<int>(zone)];
}

//retourne le chiffre d'affaire actuel du restaurant
double Restaurant::getChiffreAffaire() const
{
    return chiffreAffaire_;
}

// Autres methodes.

//Libere la table correspondant au id et ajoute son chiffre d'affaire a celui du restaurant.
void Restaurant::libererTable(int id)
{
    Table* tableALiberer = tables_->getTable(id);
	if (tableALiberer != nullptr)
    {
		chiffreAffaire_ += tableALiberer->getChiffreAffaire();
        chiffreAffaire_ += calculerReduction(tableALiberer->getClientPrincipal(), tableALiberer->getChiffreAffaire(), id == ID_TABLE_LIVRAISON);
		
        tableALiberer->libererTable();
	}
}

//surcharge d'operateur qui permet d'afficher un restaurant
ostream& operator<<(ostream& os, const Restaurant& restaurant)
{
   os << "Le restaurant " << restaurant.getNom();
   if (restaurant.chiffreAffaire_ != 0)
       os << " a fait un chiffre d'affaire de : " << restaurant.chiffreAffaire_ << "$" << endl;
   else
       os << " n'a pas fait de benefice ou le chiffre n'est pas encore calcule." << endl;

   os << "-Voici les tables : " << endl;

   restaurant.tables_->afficherTables(os);
   os << endl;
    
   os << "-Voici son menu : " << endl;
   for (TypeMenu typeMenu : { TypeMenu::Matin, TypeMenu::Midi, TypeMenu::Soir })
   {
       GestionnairePlats* menuResto = restaurant.getMenu(typeMenu);
       os << restaurant.getNomTypeMenu(typeMenu) << " : " << endl;
       restaurant.getMenu(typeMenu)->afficherPlats(os);
       os << endl << "Le plat le moins cher est : ";
       menuResto->trouverPlatMoinsCher()->afficherPlat(os);
       os << endl;
   }
	return os;
}

//Ajoute un plat s'il a ete trouve par son nom dans la commande de la table quon trouve avec son id
void Restaurant::commanderPlat(const string& nom, int idTable) 
{
    if (Table* table = tables_->getTable(idTable); table && table->estOccupee())
		if (Plat* plat = menuActuel()->trouverPlat(nom))
        {
			table->commander(plat);
			return;
		}
	cout << "Erreur : table vide ou plat introuvable." << endl << endl;
}

//surcharge d'operateur qui compare le chiffre d'affaire de 2 restaurant et retourne si le restaurant courant a un chiffre d'affaire plus petit
bool Restaurant::operator <(const Restaurant& autre) const 
{
	return chiffreAffaire_ < autre.chiffreAffaire_;
}

//Place le client dans la meilleure table et assigne la table au client. Retourne true si le client a bient ete placer sinon retourne false.
bool Restaurant::placerClients(Client* client)
{
	const int tailleGroupe = client->getTailleGroupe();
	//trouver la table la plus adaptée pour le client.
    Table* meilleurTable = tables_->getMeilleureTable(tailleGroupe);
	//Si possible assigner la table au client sinon retourner false.
    if (meilleurTable != nullptr)
    {
        meilleurTable->placerClients(tailleGroupe);
        meilleurTable->setClientPrincipal(client);
        client->setTable(meilleurTable);
        return true;
    }
    else
    {
        return false; // si le client n'a pas pu etre placer
    }
}

//Livrer une commande a un client en utilisant la table de livraison. Retourne true si le client a bien ete livre sinon retourne false.
bool Restaurant::livrerClient(Client* client, const vector<string>& commande)
{
	if (dynamic_cast<ClientPrestige*>(client))
    {
		//Placer le client principal a la table fictive en utilisant la classe GestionnaireTables.
        Table* tableLivraison = tables_->getTable(ID_TABLE_LIVRAISON);
        
        tableLivraison->setClientPrincipal(client);
		
		//Placer client à la table fictive en utilisant la classe GestionnaireTables.
        tableLivraison->placerClients(1);
		
		// Placer la commande
		for (unsigned int i = 0; i < commande.size(); i++)
			commanderPlat(commande[i], ID_TABLE_LIVRAISON);
		// Liberer la table fictive.
		libererTable(ID_TABLE_LIVRAISON);
		return true;
	}
	else
    {
		return false;
	}
}

//Calcule la reduction a laquelle le client a droit
double Restaurant::calculerReduction(Client* client, double montant, bool estLivraison) const
{
    return client->getReduction(*this, montant, estLivraison);
}

//Retourne un nom selon le type de menu en parametre
GestionnairePlats* Restaurant::getMenu(TypeMenu typeMenu) const
{
	switch (typeMenu) {
	case TypeMenu::Matin : return menuMatin_;
	case TypeMenu::Midi  : return menuMidi_;
	case TypeMenu::Soir  : return menuSoir_;
	}
	assert(false && "Le type du menu est invalide");
	return nullptr;  // On ne devrait jamais se rendre � cette ligne.
}

//Retourne le menu correspondant au moment de la journee actuel
GestionnairePlats* Restaurant::menuActuel() const
{
	return getMenu(momentJournee_);
}

//Initialise les frais de livraison des differentes zones en lisant un fichier texte
void Restaurant::lireAdresses(const string& nomFichier)
{
	LectureFichierEnSections fichier{nomFichier};
	fichier.allerASection("-ADDRESSES");
	while (!fichier.estFinSection())
    {
		int zone; double frais;
		fichier >> zone >> frais;
		fraisLivraison_[zone] = frais;
	}
}

//Retourne un type string du type de menu (Matin, Midi, Soir)
string Restaurant::getNomTypeMenu(TypeMenu typeMenu) const
{
	return string{nomsDesTypesDeMenu[static_cast<int>(typeMenu)]};
}
