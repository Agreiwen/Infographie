#include "Vecteur.h"
#include <cmath>
#include <string>
#include <iostream>
using namespace std;

Vecteur::Vecteur() : x(0), y(0)
{}

Vecteur::Vecteur(double x, double y, double z) : x(x), y(y), z(z)
{}

Vecteur::Vecteur(string nom) : x(0), y(0), nom(nom)
{}

Vecteur::Vecteur(string nom, double x, double y, double z) : x(x), y(y), z(z), nom(nom)
{}

void Vecteur::normaliser()
{
	double tmp = sqrt(x*x + y*y + z*z);
	x /= tmp;
	y /= tmp;
	z /= tmp;
}

void Vecteur::afficher() const
{
	cout << this->nom << "(" << this->x << "," << this->y << "," << this->z << ")" << endl;
}
