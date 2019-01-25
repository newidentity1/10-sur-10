#include "Menu.h"

Menu::Menu() {
    capacite_ = MAXPLAT;
    listePlats_ = nullptr;
    nbPlats_ = 0;
    type_ = Matin;
}

Menu::Menu(string fichier, TypeMenu type ) {
    capacite_ = MAXPLAT;
    type_ = type;
    ifstream fichierPlats(fichier + ".txt");
    listePlats_ = new Plat* [capacite_];
    nbPlats_ = 0;
    
    string enteteFichierTexte[4] = {"-MATIN", "-MIDI", "-SOIR", "-TABLE"};
    
    while (!ws(fichierPlats).eof()) {
       
        string plats;
        getline(fichierPlats, plats);
        
        if (enteteFichierTexte[type] == plats){
            while(plats != enteteFichierTexte[type +1]){
               
                string nom;
                cin >> nom;

                double prix;
                cin >> prix;
                
                double cout;
                cin >> cout;
               
                listePlats_[nbPlats_] = new Plat(nom, prix,cout);
                nbPlats_++;
                
            }
        }
    }
}
//(*************ajouter un destructor!!!!!*******
int Menu::getNbPlats() {
    return nbPlats_;
}

Plat* Menu::trouverPlat(string& nom){
    
    if (nbPlats_ != 0){
        for(unsigned i =0; i < nbPlats_ ; i++){
            if (listePlats_[i]->getNom() == nom)
                return listePlats_[i];
        }
    }
    return nullptr;
}

void Menu::ajouterPlat(Plat& plat) {
    
    Plat* nouveauPlat = new Plat;
    *nouveauPlat = plat;
    
    if (capacite_ == nbPlats_){
        capacite_ *= 2;
        Plat** nouveauTableau = new Plat* [capacite_];
        
        for (unsigned i=0; i < nbPlats_; i++) {
            nouveauTableau[i] = listePlats_[i];
            
        }
        delete [] listePlats_;
        listePlats_= nouveauTableau;
        listePlats_[nbPlats_++] = nouveauPlat;
   
    } else {
        listePlats_[nbPlats_++] = nouveauPlat;
    }
}


void Menu::ajouterPlat(string& nom, double montant, double cout){
    
    Plat* nouveauPlat = new Plat(nom, montant, cout);
    ajouterPlat(*nouveauPlat);
    
}


