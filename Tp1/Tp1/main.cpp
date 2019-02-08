/*
* Titre : main.cpp - Travail Pratique #1
 * Date : 01 Fevrier 2019
 * Auteur : Yanis Toubal et Estefan Vega Calcada
*/

#include "Restaurant.h"

using namespace std; 

int main() {
    
	//creation du restaurant - avec le fichier donne - le nom : PolyFood - moment de la journee : soir. 
    string nomfichier = "polyFood.txt";
    string nomResto = "Polyfood";
    Restaurant poly(nomfichier, nomResto, Soir);
    
	//creer plusieurs clients -- des entiers 

	int client1 = 1; 
	int client2 = 5; 
	int client3 = 15; 
	int client4 = 3; 
	int client5 = 2; 
    
	//placer les clients
    poly.placerClients(client1);
    poly.placerClients(client2);
    poly.placerClients(client3);
    poly.placerClients(client4);
    poly.placerClients(client5);

	// commander des plats
	//Poisson - Table 1 
	//Poulet - Table 2 
	//Pizza - Table 2 
	//Poulet - Table 4
	//Muffin - Table 4 
	//Oeud - Table 4
    string commande1 = "Poisson";
    string commande2 = "Poulet";
    string commande3 = "Pizza";
    string commande4 = "Poulet";
    string commande5 = "Muffin";
    string commande6 = "Oeuf";
    
    poly.commanderPlat(commande1, 1);
    poly.commanderPlat(commande2, 2);
    poly.commanderPlat(commande3, 2);
    poly.commanderPlat(commande4, 4);
    poly.commanderPlat(commande5, 4);
    poly.commanderPlat(commande6, 4);
	

	//afficher le restaurant
	poly.afficher();

	cout << "-------------------------------------------------" << endl; 

	//liberer les tables
    poly.libererTable(1);
    poly.libererTable(2);
    poly.libererTable(3);
    poly.libererTable(4);

	//afficher le restaurant 
	poly.afficher();
	
    return 0;

}
