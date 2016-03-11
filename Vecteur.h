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

	//Accesseurs et mutateurs
	void setX(double x);
	void setY(double y);
	void setZ(double z);
	void setNom(string nom);
	double getX() const;
	double getY() const;
	double getZ() const;
	string getNom();

	// Autres méthodes
	void normaliser();
	void afficher() const;

private:
	double x, y, z;
	string nom;
};

#endif