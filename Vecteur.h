#ifndef VECTEUR_H
#define VECTEUR_H

#include <string>
#include <iostream>
using namespace std;

class Vecteur
{
public:
	// Constructeurs
	Vecteur();
	Vecteur(double x, double y, double z);
	Vecteur(string nom);
	Vecteur(string nom, double x, double y, double z);

	// Autres méthodes
	void normaliser();
	void afficher() const;

public:
	double x, y, z;
	string nom;
};

#endif