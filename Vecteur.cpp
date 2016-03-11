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

void Vecteur::setX(double x)
{
	this->x = x;
}

void Vecteur::setY(double y)
{
	this->y = y;
}

void Vecteur::setZ(double z)
{
	this->z = z;
}

void Vecteur::setNom(string nom)
{
	this->nom = nom;
}

double Vecteur::getX() const
{
	return this->x;
}

double Vecteur::getY() const
{
	return this->y;
}

double Vecteur::getZ() const
{
	return this->z;
}

string Vecteur::getNom()
{
	return this->nom;
}

void Vecteur::normaliser(Vecteur &V) const
{
	double tmp = sqrt(V.x*V.x + V.y*V.y + V.z*V.z);
	V.x /= tmp;
	V.y /= tmp;
	V.z /= tmp;
}

void Vecteur::afficher() const
{
	cout << this->nom << "(" << this->x << "," << this->y << "," << this->z << ")" << endl;
}
