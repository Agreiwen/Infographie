#include "tgaimage.h"
#include "point.h"
#include "matrice.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>

#define M_PI  3.14159265358979323846

using namespace std;

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor blue = TGAColor(159, 121, 238, 255);
const TGAColor purple = TGAColor(155, 48, 255, 255);
int zbuffer[1000][1000];


/* Premiere partie : Lecture du fichier OBJ puis création du TGA (affichage du portait en nuage de point et fil de fer */

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
	bool steep = false;
	if (abs(x0 - x1)<abs(y0 - y1)) {
		swap(x0, y0);
		swap(x1, y1);
		steep = true;
	}
	if (x0>x1) {
		swap(x0, x1);
		swap(y0, y1);
	}
	int dx = x1 - x0;
	int dy = y1 - y0;
	int derror2 = abs(dy) * 2;
	int error2 = 0;
	int y = y0;
	for (int x = x0; x <= x1; x++) {
		if (steep) {
			image.set(y, x, color);
		}
		else {
			image.set(x, y, color);
		}
		error2 += derror2;
		if (error2 > dx) {
			y += (y1>y0 ? 1 : -1);
			error2 -= dx * 2;
		}
	}
}

void intro() {
	int x1 = 10;
	int y1 = 10;
	int x2 = 50;
	int y2 = 50;
	TGAImage image(100, 100, TGAImage::RGB);
	image.set(x1, y1, red);
	image.set(x2, y2, red);
	line(x1, y1, x2, y2, image, white);
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("intro.tga");
}

vector<vector<double> > lectureSommets(string nomFichier) {
	cout << "Lecture des sommets... ";
	ifstream fichier(nomFichier, ios::in);  // on ouvre en lecture

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

				//cout << partie1 << " | " << partie2 << " | " << partie3 << endl;

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

void dessinePoint(vector<vector<double> > &vect) {
	cout << "Creation de l'image nuage de point ... ";
	int tailleImage = 1000;
	int moitierTailleImage = tailleImage / 2;
	TGAImage image(tailleImage, tailleImage, TGAImage::RGB);
	for (unsigned int i = 0; i < vect.size(); ++i) {
		double x = vect[i][0] + moitierTailleImage;
		double y = vect[i][1] + moitierTailleImage;
		image.set(x, y, white);
	}
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("nuage_de_point.tga");
	cout << "Succes" << endl;
}

vector<vector<double> > lectureTriangles(string nomFichier) {
	cout << "Lecture des triangles... ";
	ifstream fichier(nomFichier, ios::in);  // on ouvre en lecture

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

				//cout << partie1 << " | " << partie2 << " | " << partie3 << endl;

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

void dessineFilDeFer(vector<vector<double> > &vectPoints, vector<vector<double> > &vectTriangles) {
	cout << "Creation image fil de fer ... ";
	int tailleImage = 1000;
	int tailleImageSurDeux = tailleImage / 2;
	int tailleImagesurQuatre = tailleImage / 4;
	TGAImage image(tailleImage, tailleImage, TGAImage::RGB);
	for (unsigned int i = 0; i < vectPoints.size(); ++i) {
		double x = vectPoints[i][0] + tailleImagesurQuatre;
		double y = vectPoints[i][1] + tailleImagesurQuatre;
		image.set(x, y, purple);
	}
	for (unsigned int i = 0; i < vectTriangles.size(); ++i) {
		int ligne1 = vectTriangles[i][0];
		int x1 = vectPoints[ligne1 - 1][0] + tailleImageSurDeux;
		int y1 = vectPoints[ligne1 - 1][1] + tailleImageSurDeux;

		int ligne2 = vectTriangles[i][1];
		int x2 = vectPoints[ligne2 - 1][0] + tailleImageSurDeux;
		int y2 = vectPoints[ligne2 - 1][1] + tailleImageSurDeux;

		int ligne3 = vectTriangles[i][2];
		int x3 = vectPoints[ligne3 - 1][0] + tailleImageSurDeux;
		int y3 = vectPoints[ligne3 - 1][1] + tailleImageSurDeux;

		/*cout << "\n" << ligne1 << " | " << ligne2 << " | " << ligne3 << endl;
		cout << "X1 = " << x1 << " Y1 = " << y1 << endl;
		cout << "X2 = " << x2 << " Y2 = " << y2 << endl;
		cout << "X3 = " << x3 << " Y3 = " << y3 << endl;*/

		line(x1, y1, x2, y2, image, purple);
		line(x1, y1, x3, y3, image, purple);
		line(x2, y2, x3, y3, image, purple);
	}

	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("fil_de_fer.tga");
	cout << "Succes" << endl;
}

void affichageVector(vector<vector<double> > &vect) {
	for (unsigned int i = 0; i < vect.size(); ++i) {
		for (unsigned int j = 0; j < vect[i].size(); ++j) {
			cout << "Vect[" << i << "," << j << "] = " << vect[i][j] << endl;
		}
	}
	cout << "\n" << endl;
}

/* Deuxieme partie : Remplissage des triangles du fichier TGA */

vector<vector<double> > inverseMatrice(vector<vector<double> > &matrice) {
	vector<vector<double> > matriceInverse = vector<vector<double> >(2, vector<double>(2, 0));
	double determinant = (matrice[0][0] * matrice[1][1] - matrice[0][1] * matrice[1][0]);
	
	matriceInverse[0][0] = (matrice[1][1] / determinant);
	matriceInverse[0][1] = (-matrice[0][1] / determinant);

	matriceInverse[1][0] = (-matrice[1][0] / determinant);
	matriceInverse[1][1] = (matrice[0][0] / determinant);

	return matriceInverse;
}

vector<double> produitMatrice(vector<vector<double> > &matriceA, vector<double> &matriceB) {
	vector<double> matriceUV = vector<double> (2, 0);
	
	matriceUV[0] = (matriceA[0][0] * matriceB[0] + matriceA[0][1] * matriceB[1]);
	
	matriceUV[1] = (matriceA[1][0] * matriceB[0] + matriceA[1][1] * matriceB[1]);
	return matriceUV;
}

bool appartientTriangle(double Px, double Py, double Ax, double Ay, double Bx, double By, double Cx, double Cy, vector<vector<double> > &inverseMatriceA) {

	//Remplissage matrice N=B
	vector<double> matriceB = vector<double> (2, 0);
	matriceB[0] = (Px - Ax);
	matriceB[1] = (Py - Ay);

	vector<double> matriceUV = produitMatrice(inverseMatriceA, matriceB);

	double u = matriceUV[0];
	double v = matriceUV[1];
	double w = 1 - u - v;

	if (u >= -1e-5 && v >= -1e-5 && w >= -1e-5) {
		return true;
	}
	else {
		return false;
	}
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

void dessineTriangle(vector<vector<double> > &vectPoints, vector<vector<double> > &vectTriangles) {
	cout << "Creation image triangle ... ";
	int tailleImage = 1000;
	int tailleImageSurDeux = tailleImage / 2;
	TGAImage image(tailleImage, tailleImage, TGAImage::RGB);

	int ligne1, ligne2, ligne3;
	int x1, x2, y1, y2, x3, y3, maxAbs, minAbs, maxOrd, minOrd;

	for (unsigned int i = 0; i < vectTriangles.size(); ++i) {
		ligne1 = vectTriangles[i][0];
		x1 = vectPoints[ligne1 - 1][0] + tailleImageSurDeux;
		y1 = vectPoints[ligne1 - 1][1] + tailleImageSurDeux;

		ligne2 = vectTriangles[i][1];
		x2 = vectPoints[ligne2 - 1][0] + tailleImageSurDeux;
		y2 = vectPoints[ligne2 - 1][1] + tailleImageSurDeux;

		ligne3 = vectTriangles[i][2];
		x3 = vectPoints[ligne3 - 1][0] + tailleImageSurDeux;
		y3 = vectPoints[ligne3 - 1][1] + tailleImageSurDeux;

		maxAbs = maxTrois(x1, x2, x3);
		minAbs = minTrois(x1, x2, x3);
		maxOrd = maxTrois(y1, y2, y3);
		minOrd = minTrois(y1, y2, y3);

		//Remplissage Matrice A
		vector<vector<double> > matriceA;
		vector<double> vectLigne;
		vectLigne.push_back(x2 - x1);
		vectLigne.push_back(x3 - x1);
		matriceA.push_back(vectLigne);
		vectLigne.clear();

		vectLigne.push_back(y2 - y1);
		vectLigne.push_back(y3 - y1);
		matriceA.push_back(vectLigne);
		vectLigne.clear();

		vector<vector<double> > inverseMatriceA = inverseMatrice(matriceA);

		TGAColor rndcolor = TGAColor(rand() % 255, rand() % 255, rand() % 255, 255);
		for (int i = minAbs; i <= maxAbs; ++i) {
			for (int j = minOrd; j <= maxOrd; ++j) {
	//			std::cerr << appartientTriangle(x1, y1, x1, y1, x2, y2, x3, y3, inverseMatriceA) << " " << appartientTriangle(x2, y2, x1, y1, x2, y2, x3, y3, inverseMatriceA) << " " << appartientTriangle(x3, y3, x1, y1, x2, y2, x3, y3, inverseMatriceA) << std::endl;
				if (appartientTriangle(i, j, x1, y1, x2, y2, x3, y3, inverseMatriceA)) {
						image.set(i, j, purple);
				}
			}
		}
	}

	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("triangle.tga");
	cout << "Succes" << endl;
}

void affichageVectorPoint(vector<Point> &vectPoint) {
	for (unsigned int i = 0; i < vectPoint.size(); ++i) {
		vectPoint[i].afficher();
		}
}

void triangle(Point t0, Point t1, Point t2, TGAImage &image, TGAColor color) {
	Point A = Point();
	Point B = Point();
	if (t0.getY() == t1.getY() && t0.getY() == t2.getY()) {
		return;
	}
	if (t0.getY() > t1.getY()) {
		swap(t0, t1);
	}
	if (t0.getY() > t2.getY()) {
		swap(t0, t2);
	}
	if (t1.getY() > t2.getY()) {
		swap(t1, t2);
	}
	int totalHeight = t2.getY() - t0.getY();
	for (int i = 0; i<totalHeight; i++) {
		bool second_half = i>t1.getY() - t0.getY() || t1.getY() == t0.getY();
		int segment_height = second_half ? t2.getY() - t1.getY() : t1.getY() - t0.getY();
		float alpha = (float)i / totalHeight;
		float beta = (float)(i - (second_half ? t1.getY() - t0.getY() : 0)) / segment_height;
		int Ax = t0.getX() + (t2.getX() - t0.getX())*alpha;
		int Bx = second_half ? t1.getX() + (t2.getX() - t1.getX())*beta : t0.getX() + (t1.getX() - t0.getX())*beta;
		int Ay = t0.getY() + (t2.getY() - t0.getY())*alpha;
		int By = second_half ? t1.getY() + (t2.getY() - t1.getY())*beta : t0.getY() + (t1.getY() - t0.getY())*beta;
		A.setX(Ax);
		A.setY(Ay);
		B.setX(Bx);
		B.setY(By);
		if (Ax>Bx) std::swap(A, B);
		for (int j = A.getX(); j <= B.getX(); j++) {
			image.set(j, t0.getY() + i, color);
		}
	}
}

void lineSweeping(vector<vector<double> > &vectPoints, vector<vector<double> > &vectTriangles) {
	cout << "Creation image triangle (lineSweeping) ... ";
	int tailleImage = 1000;
	int tailleImageSurDeux = tailleImage / 2;
	TGAImage image(tailleImage, tailleImage, TGAImage::RGB);
	Point A = Point();
	Point B = Point();
	Point C = Point();

	for (unsigned int i = 0; i < vectTriangles.size(); ++i) {
		int ligne1 = vectTriangles[i][0];
		int x1 = vectPoints[ligne1 - 1][0] + tailleImageSurDeux;
		int y1 = vectPoints[ligne1 - 1][1] + tailleImageSurDeux;
		A.setX(x1);
		A.setY(y1);

		int ligne2 = vectTriangles[i][1];
		int x2 = vectPoints[ligne2 - 1][0] + tailleImageSurDeux;
		int y2 = vectPoints[ligne2 - 1][1] + tailleImageSurDeux;
		B.setX(x2);
		B.setY(y2);

		int ligne3 = vectTriangles[i][2];
		int x3 = vectPoints[ligne3 - 1][0] + tailleImageSurDeux;
		int y3 = vectPoints[ligne3 - 1][1] + tailleImageSurDeux;
		C.setX(x3);
		C.setY(y3);

		triangle(A, B, C, image, TGAColor(rand() % 255, rand() % 255, rand() % 255, 255));
	}

	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("lineSweeping.tga");
	cout << "Succes" << endl;
}

/* Troisieme partie : On dessine que les triangles de devant et on ajoute une teinte */

void faceLumiere(vector<vector<double> > &vectPoints, vector<vector<double> > &vectTriangles){
	cout << "Creation image triangle (face visible seulement)... ";
	int tailleImage = 1000;
	int tailleImageSurDeux = tailleImage / 2;
	TGAImage image(tailleImage, tailleImage, TGAImage::RGB);

	int ligne1, ligne2, ligne3;
	int Ax, Ay, Az, Bx, By, Bz, Cx, Cy, Cz, maxAbs, minAbs, maxOrd, minOrd;
	double xLumiere = 0;
	double yLumiere = 0;
	double zLumiere = 1;
	double tmp = sqrt(xLumiere*xLumiere + yLumiere*yLumiere + zLumiere*zLumiere);
	xLumiere /= tmp;
	yLumiere /= tmp;
	zLumiere /= tmp;


	for (int i = 0; i<1000; i++) {
		for (int j = 0; j<1000; j++) {
			zbuffer[i][j] = std::numeric_limits<int>::min();
		}
	}

	for (unsigned int i = 0; i < vectTriangles.size(); ++i) {
		ligne1 = vectTriangles[i][0];
		Ax = vectPoints[ligne1 - 1][0] + tailleImageSurDeux;
		Ay = vectPoints[ligne1 - 1][1] + tailleImageSurDeux;
		Az = vectPoints[ligne1 - 1][2] + tailleImageSurDeux;

		ligne2 = vectTriangles[i][1];
		Bx = vectPoints[ligne2 - 1][0] + tailleImageSurDeux;
		By = vectPoints[ligne2 - 1][1] + tailleImageSurDeux;
		Bz = vectPoints[ligne2 - 1][2] + tailleImageSurDeux;

		ligne3 = vectTriangles[i][2];
		Cx = vectPoints[ligne3 - 1][0] + tailleImageSurDeux;
		Cy = vectPoints[ligne3 - 1][1] + tailleImageSurDeux;
		Cz = vectPoints[ligne3 - 1][2] + tailleImageSurDeux;

		maxAbs = maxTrois(Ax, Bx, Cx);
		minAbs = minTrois(Ax, Bx, Cx);
		maxOrd = maxTrois(Ay, By, Cy);
		minOrd = minTrois(Ay, By, Cy);

		int xAB = Bx - Ax;
		int yAB = By - Ay;
		int zAB = Bz - Az;

		int xAC = Cx - Ax;
		int yAC = Cy - Ay;
		int zAC = Cz - Az;

		double xNormal = yAB*zAC - zAB*yAC;
		double yNormal = zAB*xAC - xAB*zAC;
		double zNormal = xAB*yAC - yAB*xAC;

		double tmp = sqrt(xNormal*xNormal + yNormal*yNormal + zNormal*zNormal);
		xNormal /= tmp;
		yNormal /= tmp;
		zNormal /= tmp;

		float denominateur = (((Bx - Ax)*(Cy - Ay)) - ((Cx - Ax)*(By - Ay)));


		float coeff = 1. / denominateur;

		//cout << xNormal << " " << yNormal << " " << zNormal << " light: " << xLumiere << " " << yLumiere << " " << zLumiere << endl;

		double intensity = max(0., xNormal*xLumiere + yNormal*yLumiere + zNormal*zLumiere);
		
		//cout << intensity << endl;
		TGAColor color = TGAColor(intensity * 255, intensity * 255, intensity* 255, 255);
		for (int i = minOrd; i <= maxOrd; i++) {
			for (int j = minAbs; j <= maxAbs; j++) {
				int Px = j;
				int Py = i;
				float u = (coeff*(Cy - Ay))*(Px - Ax) + (coeff*(Ax - Cx))*(Py - Ay);
				float v = (coeff*(Ay - By))*(Px - Ax) + (coeff*(Bx - Ax))*(Py - Ay);
				float w = 1 - u - v;
				if (u < -1e-5 || v < -1e-5 || w < -1e-5) {
				}
				else {
					int Pz = u*Az + v*Bz + w*Cz;
					if (zbuffer[Px][Py] > Pz) {
						continue;
					}
					else {
						zbuffer[Px][Py] = Pz;
						image.set(Px, Py, color);
					}
				}
			}
		}
	}
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("lineFace.tga");
	cout << "Succes" << endl;
}

vector<vector<double> > lectureTexturesF(string nomFichier) {
	cout << "Lecture des textures f (partie 1)... ";
	ifstream fichier(nomFichier, ios::in);  // on ouvre en lecture

	if (fichier)  // si l'ouverture a fonctionné
	{
		string ligne;
		vector<vector<double> > vect;
		vector<double> vectLigne;
		int nbTexture = 0;
		//int test = 0;
		while (getline(fichier, ligne, '\n'))  // tant que l'on peut mettre la ligne dans "contenu"
		{
			/*if (test >= 5)
				break;*/
			if (ligne[0] == 'f' && ligne[1] == ' ')
			{
				//test++;
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

				double partie1 = atof(texte1.substr(posSlash1Texte1+1, posSlash1Texte1).c_str());
				double partie2 = atof(texte2.substr(posSlash1Texte2+1, posSlash1Texte2).c_str());
				double partie3 = atof(texte3.substr(posSlash1Texte3+1, posSlash1Texte3).c_str());

				//cout << partie1 << " | " << partie2 << " | " << partie3 << endl;

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
	cout << "Lecture des textures vt (partie 2)... ";
	ifstream fichier(nomFichier, ios::in);  // on ouvre en lecture

	if (fichier)  // si l'ouverture a fonctionné
	{
		string ligne;
		vector<vector<double> > vect;
		vector<double> vectLigne;
		int nbTexture = 0;
		//int test = 0;
		while (getline(fichier, ligne, '\n'))  // tant que l'on peut mettre la ligne dans "contenu"
		{
			/*if (test >= 5)
				break;*/
			if (ligne[0] == 'v' && ligne[1] == 't' && ligne[2] == ' ' && ligne[3] == ' ')
			{
				//test++;
				string aux;
				for (unsigned int i = 4; i < ligne.size(); ++i)
				{
					aux.push_back(ligne[i]);
				}

				stringstream ss;
				ss.str(aux);
				double partie1, partie2;
				ss >> partie1 >> partie2;

				//cout << partie1 << " | " << partie2 << endl;

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

void faceTexture(vector<vector<double> > &vectPoints, vector<vector<double> > &vectTriangles, vector<vector<double> > &vectTexturesF, vector<vector<double> > &vectTexturesVt) {
	cout << "Creation image texture... ";
	int tailleImage = 1000;
	int tailleImageSurDeux = tailleImage / 2;
	TGAImage image(tailleImage, tailleImage, TGAImage::RGB);

	TGAImage africanDiffuse;
	africanDiffuse.read_tga_file("african_head_diffuse.tga");
	africanDiffuse.flip_vertically();
	
	TGAImage test(tailleImage, tailleImage, TGAImage::RGB);

	double ligne1, ligne2, ligne3, Ax, Ay, Az, Bx, By, Bz, Cx, Cy, Cz, maxAbs, minAbs, maxOrd, minOrd, fA, fB, fC;
	int pix_x, pix_y;
	double vtAx, vtAy, vtBx, vtBy, vtCx, vtCy;
	TGAColor colorPix;

	for (int i = 0; i<1000; i++) {
		for (int j = 0; j<1000; j++) {
			zbuffer[i][j] = std::numeric_limits<int>::min();
		}
	}
	
	for (unsigned int i = 0; i < 2; ++i) {
		ligne1 = vectTriangles[i][0];
		Ax = vectPoints[ligne1 - 1][0] + tailleImageSurDeux;
		Ay = vectPoints[ligne1 - 1][1] + tailleImageSurDeux;
		Az = vectPoints[ligne1 - 1][2] + tailleImageSurDeux;
		fA = vectTexturesF[i][0];
		vtAx = vectTexturesVt[fA - 1][0];
		vtAy = vectTexturesVt[fA - 1][1];
		TGAColor colorA = africanDiffuse.get(vtAx, vtAy);

		ligne2 = vectTriangles[i][1];
		Bx = vectPoints[ligne2 - 1][0] + tailleImageSurDeux;
		By = vectPoints[ligne2 - 1][1] + tailleImageSurDeux;
		Bz = vectPoints[ligne2 - 1][2] + tailleImageSurDeux;
		fB = vectTexturesF[i][1];
		vtBx = vectTexturesVt[fB - 1][0];
		vtBy = vectTexturesVt[fB - 1][1];
		TGAColor colorB = africanDiffuse.get(vtBx, vtBy);

		ligne3 = vectTriangles[i][2];
		Cx = vectPoints[ligne3 - 1][0] + tailleImageSurDeux;
		Cy = vectPoints[ligne3 - 1][1] + tailleImageSurDeux;
		Cz = vectPoints[ligne3 - 1][2] + tailleImageSurDeux;
		fC = vectTexturesF[i][2];
		vtCx = vectTexturesVt[fC - 1][0];
		vtCy = vectTexturesVt[fC - 1][1];
		TGAColor colorC = africanDiffuse.get(vtCx, vtCy);

		cout << "f : " << fA << "|" << fB << "|" << fC << endl;
		cout << "vtA : " << vtAx << "|" << vtAy << endl;
		cout << "vtB : " << vtBx << "|" << vtBy << endl;
		cout << "vtC : " << vtCx << "|" << vtCy << endl;
		test.set(Ax, Ay, colorA);
		test.set(Bx, By, colorB);
		test.set(Cx, Cy, colorC);


		maxAbs = maxTrois(Ax, Bx, Cx);
		minAbs = minTrois(Ax, Bx, Cx);
		maxOrd = maxTrois(Ay, By, Cy);
		minOrd = minTrois(Ay, By, Cy);

		double denominateur = (((Bx - Ax)*(Cy - Ay)) - ((Cx - Ax)*(By - Ay)));
		double coeff = 1. / denominateur;

		for (int i = minOrd; i <= maxOrd; i++) {
			for (int j = minAbs; j <= maxAbs; j++) {
				int Px = j;
				int Py = i;
				double u = (coeff*(Cy - Ay))*(Px - Ax) + (coeff*(Ax - Cx))*(Py - Ay);
				double v = (coeff*(Ay - By))*(Px - Ax) + (coeff*(Bx - Ax))*(Py - Ay);
				double w = 1 - u - v;
				if (u < -1e-5 || v < -1e-5 || w < -1e-5) {
				}
				else {
					double Pz = u*Az + v*Bz + w*Cz;
					if (zbuffer[Px][Py] > Pz) {
						continue;
					}
					else {
						zbuffer[Px][Py] = Pz;
						pix_x = (vtAx*u + vtBx*v + vtCx*w) * 1024;
						pix_y = (vtAy*u + vtBy*v + vtCy*w) * 1024;
						colorPix = africanDiffuse.get(pix_x, pix_y);
						test.set(Px, Py, colorPix);
					}
				}
			}
		}
	}

	test.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	test.write_tga_file("test.tga");

	cout << "Succes" << endl;
}

int main(int argc, char** argv) {
	cout << "Projet d'infographie - M1 Informatique" << endl;
	vector<vector<double> > vectPoints = lectureSommets("african_head.obj");
	vector<vector<double> > vectTriangles = lectureTriangles("african_head.obj");
	vector<vector<double> > vectTexturesF = lectureTexturesF("african_head.obj");
	vector<vector<double> > vectTexturesVt = lectureTexturesVt("african_head.obj");
	//dessinePoint(vectPoints);
	//dessineFilDeFer(vectPoints,vectTriangles);
	//testTriangle();
	//dessineTriangle(vectPoints, vectTriangles);
	//lineSweeping(vectPoints, vectTriangles);
	//faceLumiere(vectPoints, vectTriangles);
	faceTexture(vectPoints, vectTriangles, vectTexturesF, vectTexturesVt);
	return 0;
}