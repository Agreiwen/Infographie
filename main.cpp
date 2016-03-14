#include "tgaimage.h"
#include "Point.h"
#include "Matrice.h"
#include "Vecteur.h"
#include <iostream>
#include <vector>
#include <limits>
#include <sstream>
#include <cmath>
#include <algorithm>

# define PI           3.14159265358979323846  /* pi */

using namespace std;

double zbuffer[1000][1000];
int tailleImage = 1000;
int tailleImageSurDeux = tailleImage / 2;
TGAImage imageTexture(tailleImage, tailleImage, TGAImage::RGB);

vector<vector<double> > lectureSommets(string nomFichier) {
	cout << "Lecture des sommets... ";
	ifstream fichier(nomFichier.c_str(), ios::in);  // on ouvre en lecture

	if (fichier)  // si l'ouverture a fonctionné
	{
		string ligne;
		vector<vector<double> > vect;
		vector<double> vectLigne;
		int nbSommets = 0;
		while (getline(fichier, ligne, '\n'))  // tant que l'on peut mettre la ligne dans "contenu"
		{
			if (ligne[0] == 'v' && ligne[1] == ' ' && ligne[2] == ' ')
			{
				string aux;
				for (unsigned int i = 3; i < ligne.size(); ++i)
				{
					aux.push_back(ligne[i]);
				}

				stringstream ss;
				ss.str(aux);
				double partie1, partie2, partie3;
				ss >> partie1 >> partie2 >> partie3;

				vectLigne.push_back(partie1);
				vectLigne.push_back(partie2);
				vectLigne.push_back(partie3);
				vect.push_back(vectLigne);

				nbSommets++;
			}
			vectLigne.clear();
		}
		cout << "(" << nbSommets << " sommets) ";
		cout << "Succes" << endl;
		return vect;
	}
	else
		cerr << "Impossible d'ouvrir le fichier !" << endl;
}

vector<vector<double> > lectureTriangles(string nomFichier) {
	cout << "Lecture des triangles... ";
	ifstream fichier(nomFichier.c_str(), ios::in);  // on ouvre en lecture

	if (fichier)  // si l'ouverture a fonctionné
	{
		string ligne;
		vector<vector<double> > vect;
		vector<double> vectLigne;
		int nbTriangle = 0;;
		while (getline(fichier, ligne, '\n'))  // tant que l'on peut mettre la ligne dans "contenu"
		{
			if (ligne[0] == 'f' && ligne[1] == ' ')
			{
				string aux;
				for (unsigned int i = 2; i < ligne.size(); ++i)
				{
					aux.push_back(ligne[i]);
				}

				int posEspace1 = aux.find(' ', 0);
				int posEspace2 = aux.find(' ', posEspace1 + 1);

				string texte1 = aux.substr(0, posEspace1);
				string texte2 = aux.substr(posEspace1 + 1, posEspace2 - (posEspace1 + 1));
				string texte3 = aux.substr(posEspace2 + 1, aux.size() - (posEspace2 + 1));

				int posSlashTexte1 = texte1.find('/', 0);
				int posSlashTexte2 = texte2.find('/', 0);
				int posSlashTexte3 = texte3.find('/', 0);

				double partie1 = atof(texte1.substr(0, posSlashTexte1).c_str());
				double partie2 = atof(texte2.substr(0, posSlashTexte2).c_str());
				double partie3 = atof(texte3.substr(0, posSlashTexte3).c_str());

				vectLigne.push_back(partie1);
				vectLigne.push_back(partie2);
				vectLigne.push_back(partie3);
				vect.push_back(vectLigne);

				nbTriangle++;
			}
			vectLigne.clear();
		}
		cout << "(" << nbTriangle << " triangles) ";
		cout << "Succes" << endl;
		return vect;
	}
	else
		cerr << "Impossible d'ouvrir le fichier !" << endl;
}

vector<vector<double> > lectureTexturesF(string nomFichier) {
	cout << "Lecture des textures f... ";
	ifstream fichier(nomFichier.c_str(), ios::in);  // on ouvre en lecture

	if (fichier)  // si l'ouverture a fonctionné
	{
		string ligne;
		vector<vector<double> > vect;
		vector<double> vectLigne;
		int nbTexture = 0;
		while (getline(fichier, ligne, '\n'))  // tant que l'on peut mettre la ligne dans "contenu"
		{
			if (ligne[0] == 'f' && ligne[1] == ' ')
			{
				string aux;
				for (unsigned int i = 2; i < ligne.size(); ++i)
				{
					aux.push_back(ligne[i]);
				}

				int posEspace1 = aux.find(' ', 0);
				int posEspace2 = aux.find(' ', posEspace1 + 1);

				string texte1 = aux.substr(0, posEspace1);
				string texte2 = aux.substr(posEspace1 + 1, posEspace2 - (posEspace1 + 1));
				string texte3 = aux.substr(posEspace2 + 1, aux.size() - (posEspace2 + 1));

				int posSlash1Texte1 = texte1.find('/', 0);
				int posSlash1Texte2 = texte2.find('/', 0);
				int posSlash1Texte3 = texte3.find('/', 0);

				int posSlash2Texte1 = texte1.find('/', posSlash1Texte1 + 1);
				int posSlash2Texte2 = texte2.find('/', posSlash1Texte2 + 1);
				int posSlash2Texte3 = texte3.find('/', posSlash1Texte3 + 1);

				double partie1 = atof(texte1.substr(posSlash1Texte1 + 1, posSlash2Texte1 - 1 - posSlash1Texte1).c_str());
				double partie2 = atof(texte2.substr(posSlash1Texte2 + 1, posSlash2Texte2 - 1 - posSlash1Texte2).c_str());
				double partie3 = atof(texte3.substr(posSlash1Texte3 + 1, posSlash2Texte3 - 1 - posSlash1Texte3).c_str());

				vectLigne.push_back(partie1);
				vectLigne.push_back(partie2);
				vectLigne.push_back(partie3);
				vect.push_back(vectLigne);

				nbTexture++;
			}
			vectLigne.clear();
		}
		cout << "(" << nbTexture << " textures f) ";
		cout << "Succes" << endl;
		return vect;
	}
	else
		cerr << "Impossible d'ouvrir le fichier !" << endl;
}

vector<vector<double> > lectureTexturesVt(string nomFichier) {
	cout << "Lecture des textures vt... ";
	ifstream fichier(nomFichier.c_str(), ios::in);  // on ouvre en lecture

	if (fichier)  // si l'ouverture a fonctionné
	{
		string ligne;
		vector<vector<double> > vect;
		vector<double> vectLigne;
		int nbTexture = 0;
		while (getline(fichier, ligne, '\n'))  // tant que l'on peut mettre la ligne dans "contenu"
		{
			if (ligne[0] == 'v' && ligne[1] == 't' && ligne[2] == ' ' && ligne[3] == ' ')
			{
				string aux;
				for (unsigned int i = 4; i < ligne.size(); ++i)
				{
					aux.push_back(ligne[i]);
				}

				stringstream ss;
				ss.str(aux);
				double partie1, partie2;
				ss >> partie1 >> partie2;

				vectLigne.push_back(partie1);
				vectLigne.push_back(partie2);
				vect.push_back(vectLigne);

				nbTexture++;
			}
			vectLigne.clear();
		}
		cout << "(" << nbTexture << " textures vt) ";
		cout << "Succes" << endl;
		return vect;
	}
	else
		cerr << "Impossible d'ouvrir le fichier !" << endl;
}

int maxDeux(int a, int b) {
	if (a >= b) {
		return a;
	}
	else {
		return b;
	}
}

int maxTrois(int a, int b, int c) {
	return maxDeux(maxDeux(a, b), c);
}

int minDeux(int a, int b) {
	if (a <= b) {
		return a;
	}
	else {
		return b;
	}
}

int minTrois(int a, int b, int c) {
	return minDeux(minDeux(a, b), c);
}

void initialisationZBuffer() {
	for (int i = 0; i<1000; i++) {
		for (int j = 0; j<1000; j++) {
			zbuffer[i][j] = std::numeric_limits<int>::min();
		}
	}
}

Matrice boiteEnglobante(Point a, Point b, Point c) {
	Matrice boite = Matrice(4, 1);
	/* Boite englobante minAbs, minOrd, maxAbs, maxOrd */	
	boite(0, 0) = minTrois(a.x, b.x, c.x);
	boite(1, 0) = minTrois(a.y, b.y, c.y);
	boite(2, 0) = maxTrois(a.x, b.x, c.x);
	boite(3, 0) = maxTrois(a.y, b.y, c.y);

	/* Pour ne pas être out of map */
	boite(0,0) = max(0., boite(0,0));
	boite(1,0) = max(0., boite(1,0));
	boite(2,0) = min(boite(2,0), (double)tailleImage);
	boite(3,0) = min(boite(3,0), (double)tailleImage);
	return boite;
}

void recuperationTriangle(vector<vector<double> > &vectPoints, int ligne1, int ligne2, int ligne3, Matrice transformation, Point &a, Point &b, Point &c) {
	
	Matrice A(4, 1);
	Matrice B(4, 1);
	Matrice C(4, 1);
	Matrice aux(4, 1);

	A(0, 0) = vectPoints[ligne1 - 1][0];
	A(1, 0) = vectPoints[ligne1 - 1][1];
	A(2, 0) = vectPoints[ligne1 - 1][2];
	A(3, 0) = 1;
	aux = transformation*A;
	a = Point(aux(0, 0) / aux(3, 0), aux(1, 0) / aux(3, 0), aux(2, 0) / aux(3, 0));

	B(0, 0) = vectPoints[ligne2 - 1][0];
	B(1, 0) = vectPoints[ligne2 - 1][1];
	B(2, 0) = vectPoints[ligne2 - 1][2];
	B(3, 0) = 1;
	aux = transformation*B;
	b = Point(aux(0, 0) / aux(3, 0), aux(1, 0) / aux(3, 0), aux(2, 0) / aux(3, 0));

	C(0, 0) = vectPoints[ligne3 - 1][0];
	C(1, 0) = vectPoints[ligne3 - 1][1];
	C(2, 0) = vectPoints[ligne3 - 1][2];
	C(3, 0) = 1;
	aux = transformation*C;
	c = Point(aux(0, 0) / aux(3, 0), aux(1, 0) / aux(3, 0), aux(2, 0) / aux(3, 0));
}

void recuperationTexture(vector<vector<double> > &vectTexturesVt, double fTextureA, double fTextureB, double fTextureC, double &vtAx, double &vtAy, double &vtBx, double &vtBy, double &vtCx, double &vtCy) {
	vtAx = vectTexturesVt[fTextureA - 1][0];
	vtAy = vectTexturesVt[fTextureA - 1][1];
	vtBx = vectTexturesVt[fTextureB - 1][0];
	vtBy = vectTexturesVt[fTextureB - 1][1];
	vtCx = vectTexturesVt[fTextureC - 1][0];
	vtCy = vectTexturesVt[fTextureC - 1][1];
}

double calculCoefficiant(Point a, Point b, Point c) {
	double denominateur = (((b.x - a.x)*(c.y - a.y)) - ((c.x - a.x)*(b.y - a.y)));
	double coeff = 1. / denominateur;
	return coeff;
}

bool appartientTriangle(Point &a, Point &b, Point &c, Point &p, double coeff, double &u, double &v, double &w) {
	u = (coeff*(c.y - a.y))*(p.x - a.x) + (coeff*(a.x - c.x))*(p.y - a.y);
	v = (coeff*(a.y - b.y))*(p.x - a.x) + (coeff*(b.x - a.x))*(p.y - a.y);
	w = 1 - u - v;
	if (u < -1e-5 || v < -1e-5 || w < -1e-5) {
		return false;
	}
	else {
		return true;
	}
}

void faceTexture(vector<vector<double> > &vectPoints, vector<vector<double> > &vectTriangles, vector<vector<double> > &vectTexturesF, vector<vector<double> > &vectTexturesVt, Matrice &transformation, Matrice &sepia) {
	cout << "Creation image texture... ";

	TGAImage africanDiffuse, africanNM, africanSpecular;
	africanDiffuse.read_tga_file("african_head_diffuse.tga");
	africanDiffuse.flip_vertically();
	africanNM.read_tga_file("african_head_nm.tga");
	africanNM.flip_vertically();
	africanSpecular.read_tga_file("african_head_spec.tga");
	africanSpecular.flip_vertically();

	double ligne1, ligne2, ligne3, fTextureA, fTextureB, fTextureC;
	double pix_x, pix_y;
	double vtAx, vtAy, vtBx, vtBy, vtCx, vtCy;
	double coeff, u, v, w, intensity, produitScalaire, spec;
	TGAColor colorPix, color, colorNm, colorSpec;
	Vecteur normalPix, lumiere, r;
	Point a, b, c, p;
	Matrice aux(4, 1);
	Matrice couleur(4, 1);
	Matrice boite;
	Matrice triangle;

	lumiere = Vecteur(1, 1, 0);
	lumiere.normaliser();

	initialisationZBuffer();

	for (unsigned int i = 0; i < vectTriangles.size(); ++i) {
		ligne1 = vectTriangles[i][0];
		ligne2 = vectTriangles[i][1];
		ligne3 = vectTriangles[i][2];
		recuperationTriangle(vectPoints, ligne1, ligne2, ligne3, transformation, a, b, c);
		boite = boiteEnglobante(a, b, c);
		fTextureA = vectTexturesF[i][0];
		fTextureB = vectTexturesF[i][1];
		fTextureC = vectTexturesF[i][2];
		recuperationTexture(vectTexturesVt, fTextureA, fTextureB, fTextureC, vtAx, vtAy, vtBx, vtBy, vtCx, vtCy);

		coeff = calculCoefficiant(a, b, c);

		for (int i = boite(1,0); i <= boite(3,0); i++) {
			for (int j = boite(0,0); j <= boite(2,0); j++) {
				p.x = j;
				p.y = i;
				if (!appartientTriangle(a,b,c,p,coeff,u,v,w)) {
				}
				else {
					p.z = w*a.z + u*b.z + v*c.z;
					if (zbuffer[(int)p.x][(int)p.y] > p.z) {
						continue;
					}
					else {
						zbuffer[(int)p.x][(int)p.y] = p.z;
						pix_x = (vtAx*w + vtBx*u + vtCx*v) * africanDiffuse.get_width();
						pix_y = (vtAy*w + vtBy*u + vtCy*v) * africanDiffuse.get_height();
						colorPix = africanDiffuse.get(pix_x, pix_y);

						colorNm = africanNM.get(pix_x, pix_y);
						normalPix = Vecteur(colorNm.r, colorNm.g, colorNm.b);
						normalPix.normaliser();

						produitScalaire = 2 * (normalPix.x*lumiere.x + normalPix.y*lumiere.y + normalPix.z*lumiere.z);
						r = Vecteur((normalPix.x * produitScalaire) - lumiere.x, (normalPix.y * produitScalaire) - lumiere.y, (normalPix.z * produitScalaire) - lumiere.z);
						r.normaliser();

						colorSpec = africanSpecular.get(pix_x, pix_y);
						spec = pow(max(r.z, 0.), colorSpec.b);

						intensity = max(0., normalPix.x*lumiere.x + normalPix.y*lumiere.y + normalPix.z*lumiere.z);
						couleur(0, 0) = min(5 + colorPix.r*(intensity + 0.6*spec), 255.);
						couleur(1, 0) = min(5 + colorPix.g*(intensity + 0.6*spec), 255.);
						couleur(2, 0) = min(5 + colorPix.b*(intensity + 0.6*spec), 255.);
						couleur(3, 0) = min(5 + colorPix.a*(intensity + 0.6*spec), 255.);
						couleur = sepia*couleur;
						color = TGAColor(min(couleur(0, 0), 255.), min(couleur(1, 0), 255.), min(couleur(2, 0), 255.), min(couleur(3, 0), 255.));
						imageTexture.set(p.x, p.y, color);
					}
				}
			}
		}
	}

	imageTexture.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	imageTexture.write_tga_file("imageTexture.tga");

	cout << "Succes" << endl;
}

int main(int argc, char** argv)
{
	cout << "Projet d'infographie - M1 Informatique" << endl;
	/* Parse du fichier obj */
	vector<vector<double> > vectPoints = lectureSommets("african_head.obj");
	vector<vector<double> > vectTriangles = lectureTriangles("african_head.obj");
	vector<vector<double> > vectTexturesF = lectureTexturesF("african_head.obj");
	vector<vector<double> > vectTexturesVt = lectureTexturesVt("african_head.obj");

	/* Creation du Viewport */
	Matrice viewPort = Matrice(4, 4);
	viewPort(0, 0) = tailleImageSurDeux;
	viewPort(0, 3) = tailleImageSurDeux;
	viewPort(1, 1) = tailleImageSurDeux;
	viewPort(1, 3) = tailleImageSurDeux;
	viewPort(2, 2) = tailleImageSurDeux;
	viewPort(2, 3) = tailleImageSurDeux;
	viewPort(3, 3) = 1;

	/* Création du zoom */
	Matrice zoom = Matrice(4, 4);
	double zoomAction = 0.8;
	zoom(0, 0) = zoomAction;
	zoom(1, 1) = zoomAction;
	zoom(2, 2) = zoomAction;
	zoom(3, 3) = 1;

	/* Création de la Persective */
	double c = 10000;
	Matrice perspective = Matrice(4, 4);
	perspective(0, 0) = 1;
	perspective(1, 1) = 1;
	perspective(2, 2) = 1;
	perspective(3, 3) = 1;
	perspective(3, 2) = -1 / c;

	/* Création de la Rotation autour de l'axe y */
	double angleY = -25 * (PI) / 180;
	Matrice rotationY = Matrice(4, 4);
	rotationY(0, 0) = cos(angleY);
	rotationY(0, 2) = sin(angleY);
	rotationY(1, 1) = 1;
	rotationY(2, 0) = -sin(angleY);
	rotationY(2, 2) = cos(angleY);
	rotationY(3, 3) = 1;

	/* Création de la rotation autour de l'axe x */
	double angleX = 25 * (PI) / 180;
	Matrice rotationX = Matrice(4, 4);
	rotationX(0, 0) = 1;
	rotationX(1, 1) = cos(angleX);
	rotationX(1, 2) = -sin(angleX);
	rotationX(2, 1) = sin(angleX);
	rotationX(2, 2) = cos(angleX);
	rotationX(3, 3) = 1;

	/* Création de la rotation autour de l'axe z */
	double angleZ = 0 * (PI) / 180;
	Matrice rotationZ = Matrice(4, 4);
	rotationZ(0, 0) = cos(angleZ);
	rotationZ(0, 1) = -sin(angleZ);
	rotationZ(1, 0) = sin(angleZ);
	rotationZ(1, 1) = cos(angleZ);
	rotationZ(2, 2) = 1;
	rotationZ(3, 3) = 1;

	/* Creation matrice couleur */
	Matrice sepia = Matrice(4, 4);
	sepia(0, 0) = .393;
	sepia(0, 1) = .769;
	sepia(0, 2) = .189;
	sepia(1, 0) = .349;
	sepia(1, 1) = .686;
	sepia(1, 2) = .168;
	sepia(2, 0) = .272;
	sepia(2, 1) = .534;
	sepia(2, 2) = .131;
	sepia(3, 3) = 1;

	/* Creation matrice nuance de gris */
	Matrice nuanceGris = Matrice(4, 4);
	nuanceGris(0, 0) = nuanceGris(0, 1) = nuanceGris(0, 2) = nuanceGris(1, 0) = nuanceGris(1, 1) = nuanceGris(1, 2) = nuanceGris(2, 0) = nuanceGris(2, 1) = nuanceGris(2, 2) = 1 / 3.;
	nuanceGris(3, 3) = 1;

	/* Creation matrice identite */
	Matrice identite = Matrice(4, 4);
	identite(0, 0) = identite(1, 1) = identite(2, 2) = identite(3, 3) = 1;

	/* Creation matrice miroir */
	Matrice miroir = Matrice(identite);
	miroir(0, 0) = -1;

	/* Creation de la rotation complete */
	Matrice transformation = Matrice(4, 4);
	transformation = viewPort*perspective*rotationX*rotationY*rotationZ*zoom;

	/* On dessine l'image */
	faceTexture(vectPoints, vectTriangles, vectTexturesF, vectTexturesVt, transformation, identite);
	return 0;
}