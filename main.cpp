#include "tgaimage.h"
#include "Point.h"
#include "matrice.h"
#include <iostream>
#include <vector>
#include <limits>
#include <sstream>
#include <cmath>
#include <algorithm>

using namespace std;

double zbuffer[1000][1000];
int tailleImage = 1000;
int tailleImageSurDeux = tailleImage / 2;

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

vector<vector<double> > lectureTexturesF(string nomFichier) {
	cout << "Lecture des textures f (partie 1)... ";
	ifstream fichier(nomFichier.c_str(), ios::in);  // on ouvre en lecture

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

				int posSlash2Texte1 = texte1.find('/', posSlash1Texte1 + 1);
				int posSlash2Texte2 = texte2.find('/', posSlash1Texte2 + 1);
				int posSlash2Texte3 = texte3.find('/', posSlash1Texte3 + 1);

				double partie1 = atof(texte1.substr(posSlash1Texte1 + 1, posSlash2Texte1 - 1 - posSlash1Texte1).c_str());
				double partie2 = atof(texte2.substr(posSlash1Texte2 + 1, posSlash2Texte2 - 1 - posSlash1Texte2).c_str());
				double partie3 = atof(texte3.substr(posSlash1Texte3 + 1, posSlash2Texte3 - 1 - posSlash1Texte3).c_str());

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
	ifstream fichier(nomFichier.c_str(), ios::in);  // on ouvre en lecture

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

void faceTexture(vector<vector<double> > &vectPoints, vector<vector<double> > &vectTriangles, vector<vector<double> > &vectTexturesF, vector<vector<double> > &vectTexturesVt, Matrice &viewPort) {
	cout << "Creation image texture... ";
	TGAImage image(tailleImage, tailleImage, TGAImage::RGB);

	TGAImage africanDiffuse;
	africanDiffuse.read_tga_file("african_head_diffuse.tga");
	africanDiffuse.flip_vertically();
	
	TGAImage imageTexture(tailleImage, tailleImage, TGAImage::RGB);

	double ligne1, ligne2, ligne3, Ax, Ay, Az, Bx, By, Bz, Cx, Cy, Cz, maxAbs, minAbs, maxOrd, minOrd, fA, fB, fC;
	int pix_x, pix_y;
	double vtAx, vtAy, vtBx, vtBy, vtCx, vtCy;
	TGAColor colorPix;
	TGAColor color;

	double xLumiere = 0;
	double yLumiere = 0;
	double zLumiere = 1;

	Matrice A(4, 1);
	Matrice B(4, 1);
	Matrice C(4, 1);
	Matrice res(4, 1);

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
		A(0, 0) = vectPoints[ligne1 - 1][0];
		A(1, 0) = vectPoints[ligne1 - 1][1];
		A(2, 0) = vectPoints[ligne1 - 1][2];
		A(3, 0) = 1;

		res = viewPort.operator*(A);
		Ax = res(0,0);
		Ay = res(1,0);
		Az = res(2,0);

		fA = vectTexturesF[i][0];
		vtAx = vectTexturesVt[fA - 1][0];
		vtAy = vectTexturesVt[fA - 1][1];
		TGAColor colorA = africanDiffuse.get(vtAx, vtAy);

		ligne2 = vectTriangles[i][1];
		B(0, 0) = vectPoints[ligne2 - 1][0];
		B(1, 0) = vectPoints[ligne2 - 1][1];
		B(2, 0) = vectPoints[ligne2 - 1][2];
		B(3, 0) = 1;

		res = viewPort.operator*(B);
		Bx = res(0, 0);
		By = res(1, 0);
		Bz = res(2, 0);

		fB = vectTexturesF[i][1];
		vtBx = vectTexturesVt[fB - 1][0];
		vtBy = vectTexturesVt[fB - 1][1];
		TGAColor colorB = africanDiffuse.get(vtBx, vtBy);

		ligne3 = vectTriangles[i][2];
		C(0, 0) = vectPoints[ligne3 - 1][0];
		C(1, 0) = vectPoints[ligne3 - 1][1];
		C(2, 0) = vectPoints[ligne3 - 1][2];
		C(3, 0) = 1;

		res = viewPort.operator*(C);
		Cx = res(0, 0);
		Cy = res(1, 0);
		Cz = res(2, 0);

		fC = vectTexturesF[i][2];
		vtCx = vectTexturesVt[fC - 1][0];
		vtCy = vectTexturesVt[fC - 1][1];
		TGAColor colorC = africanDiffuse.get(vtCx, vtCy);

		//cout << "f : " << fA << "|" << fB << "|" << fC << endl;
		//cout << "vtA : " << vtAx << "|" << vtAy << endl;
		//cout << "vtB : " << vtBx << "|" << vtBy << endl;
		//cout << "vtC : " << vtCx << "|" << vtCy << endl;

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
					double Pz = w*Az + u*Bz + v*Cz;
					if (zbuffer[Px][Py] > Pz) {
						continue;
					}
					else {
						zbuffer[Px][Py] = Pz;
						pix_x = (vtAx*w + vtBx*u + vtCx*v) * africanDiffuse.get_width();
						pix_y = (vtAy*w + vtBy*u + vtCy*v) * africanDiffuse.get_height();
						colorPix = africanDiffuse.get(pix_x, pix_y);

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
						double intensity = abs(xNormal*xLumiere + yNormal*yLumiere + zNormal*zLumiere);
						color = TGAColor(colorPix.r*intensity, colorPix.g* intensity, colorPix.b* intensity, colorPix.a * intensity);
						imageTexture.set(Px, Py, color);
					}
				}
			}
		}
	}

	imageTexture.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	imageTexture.write_tga_file("imageTexture.tga");

	cout << "Succes" << endl;
}

int main(int argc, char** argv) {
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
	viewPort(2, 2) = 500;
	viewPort(2, 3) = 500;
	viewPort(3, 3) = 1;
	//cout << viewPort << endl;

	/* On dessine l'image */
	faceTexture(vectPoints, vectTriangles, vectTexturesF, vectTexturesVt, viewPort);
	return 0;
}
