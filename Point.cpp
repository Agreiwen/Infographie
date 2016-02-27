#include "point.h"
#include <cmath>
#include <string>
#include <iostream>
using namespace std;

Point::Point() : x(0), y(0)
{}

Point::Point(double x, double y) : x(x), y(y)
{}

Point::Point(string nom) : x(0), y(0), nom(nom)
{}

Point::Point(string nom, double x, double y) : x(x), y(y), nom(nom)
{}

void Point::setX(double x)
{
	this->x = x;
}

void Point::setY(double y)
{
	this->y = y;
}

void Point::setNom(string nom)
{
	this->nom = nom;
}

double Point::getX() const
{
	return this->x;
}

double Point::getY() const
{
	return this->y;
}

string Point::getNom()
{
	return this->nom;
}

double Point::distance(const Point &P) const
{
	double dx = this->x - P.x;
	double dy = this->y - P.y;
	return sqrt(dx*dx + dy*dy);
}

Point Point::milieu(const Point &P) const
{
	Point result;
	result.x = (P.x + this->x) / 2;
	result.y = (P.y + this->y) / 2;
	return result;
}

void Point::saisir()
{
	cout << "Tapez l'abscisse : ";  cin >> this->x;
	cout << "Tapez l'ordonnée : ";  cin >> this->y;
}

void Point::afficher() const
{
	cout << this->nom <<"(" << this->x << "," << this->y << ")" << endl;
}