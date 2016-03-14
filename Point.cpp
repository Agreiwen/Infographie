#include "Point.h"
#include <cmath>
#include <string>
#include <iostream>
using namespace std;

Point::Point() : x(0), y(0)
{}

Point::Point(double x, double y, double z) : x(x), y(y), z(z)
{}

Point::Point(string nom) : x(0), y(0), z(0), nom(nom)
{}

Point::Point(string nom, double x, double y, double z) : x(x), y(y), z(z), nom(nom)
{}

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
