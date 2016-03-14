#ifndef POINT_H
#define POINT_H

#include <string>
#include <iostream>
using namespace std;

class Point
{
public:
	// Constructeurs
	Point();
	Point(double x, double y, double z);
	Point(string nom);
	Point(string nom, double x, double y, double z);

	// Autres méthodes
	double distance(const Point &P) const;
	Point milieu(const Point &P) const;

	void saisir();
	void afficher() const;

public:
	double x, y, z;
	string nom;
};

#endif