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
	Point(double x, double y);
	Point(string nom);
	Point(string nom, double x, double y);

	//Accesseurs et mutateurs
	void setX(double x);
	void setY(double y);
	void setNom(string nom);
	double getX() const;
	double getY() const;
	string getNom();

	// Autres méthodes
	double distance(const Point &P) const;
	Point milieu(const Point &P) const;

	void saisir();
	void afficher() const;

private:
	double x, y;
	string nom;
};

#endif