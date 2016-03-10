#include "tgaimage.h"
#include "Point.h"
#include "matrice.h"
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
	cout << "Lecture des textures f... ";
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
	cout << "Lecture des textures vt... ";
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

vector<vector<double> > lectureVecteursNormauxVn(string nomFichier) {
	cout << "Lecture des vecteurs normaux... ";
	ifstream fichier(nomFichier.c_str(), ios::in);  // on ouvre en lecture

	if (fichier)  // si l'ouverture a fonctionné
	{
		string ligne;
		vector<vector<double> > vect;
		vector<double> vectLigne;
		int nbVectNorm = 0;
		//int test = 0;
		while (getline(fichier, ligne, '\n'))  // tant que l'on peut mettre la ligne dans "contenu"
		{
			/*if (test >= 5)
			break;*/
			if (ligne[0] == 'v' && ligne[1] == 'n' && ligne[2] == ' ' && ligne[3] == ' ')
			{
				//test++;
				string aux;
				for (unsigned int i = 4; i < ligne.size(); ++i)
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

				nbVectNorm++;
			}
			vectLigne.clear();
		}
		cout << "(" << nbVectNorm << " vecteurs normaux) ";
		cout << "Succes" << endl;
		return vect;
	}
	else
		cerr << "Impossible d'ouvrir le fichier !" << endl;
}

vector<vector<double> > lectureVecteursF(string nomFichier) {
	cout << "Lecture des vecteurs f... ";
	ifstream fichier(nomFichier.c_str(), ios::in);  // on ouvre en lecture

	if (fichier)  // si l'ouverture a fonctionné
	{
		string ligne;
		vector<vector<double> > vect;
		vector<double> vectLigne;
		int nbVectF = 0;
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

				double partie1 = atof(texte1.substr(posSlash2Texte1 + 1, texte1.size() - 1 - posSlash2Texte1).c_str());
				double partie2 = atof(texte2.substr(posSlash2Texte2 + 1, texte2.size() - 1 - posSlash2Texte2).c_str());
				double partie3 = atof(texte3.substr(posSlash2Texte3 + 1, texte3.size() - 1 - posSlash2Texte3).c_str());

				//cout << partie1 << " | " << partie2 << " | " << partie3 << endl;

				vectLigne.push_back(partie1);
				vectLigne.push_back(partie2);
				vectLigne.push_back(partie3);
				vect.push_back(vectLigne);

				nbVectF++;
			}
			vectLigne.clear();
		}
		cout << "(" << nbVectF << " vecteurs f) ";
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

void faceTexture(vector<vector<double> > &vectPoints, vector<vector<double> > &vectTriangles, vector<vector<double> > &vectTexturesF, vector<vector<double> > &vectTexturesVt, vector<vector<double> > &vectNormauxVn, vector<vector<double> > &vectNormauxF, Matrice &viewPort, Matrice &perspective, Matrice &rotation) {
	cout << "Creation image texture... ";
	TGAImage image(tailleImage, tailleImage, TGAImage::RGB);

	TGAImage africanDiffuse;
	africanDiffuse.read_tga_file("african_head_diffuse.tga");
	africanDiffuse.flip_vertically();

	TGAImage africanNM;
	africanNM.read_tga_file("african_head_nm.tga");
	africanNM.flip_vertically();

	TGAImage africanSpecular;
	africanSpecular.read_tga_file("african_head_spec.tga");
	africanSpecular.flip_vertically();
	
	TGAImage imageTexture(tailleImage, tailleImage, TGAImage::RGB);

	double ligne1, ligne2, ligne3, fTextureA, fTextureB, fTextureC, fVectA, fVectB, fVectC, xLumiere, yLumiere, zLumiere;
	double Ax, Ay, Az, Bx, By, Bz, Cx, Cy, Cz;
	double maxAbs, minAbs, maxOrd, minOrd;
	double pix_x, pix_y;
	double vtAx, vtAy, vtBx, vtBy, vtCx, vtCy;
	double vnAx, vnAy, vnAz, vnBx, vnBy, vnBz, vnCx, vnCy, vnCz;
	double intensity, xNormal, yNormal, zNormal, produitScalaire, xR, yR, zR, spec;
	TGAColor colorPix, color, colorNm, colorSpec;

	Matrice lumiere = Matrice(3, 1);
	lumiere(0, 0) = 1;
	lumiere(1, 0) = 1;
	lumiere(2, 0) = 0;

	xLumiere = lumiere(0, 0);
	yLumiere = lumiere(1, 0);
	zLumiere = lumiere(2, 0);

	Matrice A(4, 1);
	Matrice B(4, 1);
	Matrice C(4, 1);
	Matrice res(4, 1);
	Matrice aux(4, 1);

	res = viewPort*perspective*rotation;

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

		aux = res*A;
		Ax = aux(0,0) / aux(3, 0);
		Ay = aux(1,0) / aux(3, 0);
		Az = aux(2,0) / aux(3, 0);

		fTextureA = vectTexturesF[i][0];
		vtAx = vectTexturesVt[fTextureA - 1][0];
		vtAy = vectTexturesVt[fTextureA - 1][1];
		TGAColor colorA = africanDiffuse.get(vtAx, vtAy);

		fVectA = vectNormauxF[i][0];
		vnAx = vectNormauxVn[fVectA - 1][0];
		vnAy = vectNormauxVn[fVectA - 1][1];
		vnAz = vectNormauxVn[fVectA - 1][2];

		ligne2 = vectTriangles[i][1];
		B(0, 0) = vectPoints[ligne2 - 1][0];
		B(1, 0) = vectPoints[ligne2 - 1][1];
		B(2, 0) = vectPoints[ligne2 - 1][2];
		B(3, 0) = 1;

		aux = res*B;
		Bx = aux(0, 0) / aux(3, 0);
		By = aux(1, 0) / aux(3, 0);
		Bz = aux(2, 0) / aux(3, 0);

		fTextureB = vectTexturesF[i][1];
		vtBx = vectTexturesVt[fTextureB - 1][0];
		vtBy = vectTexturesVt[fTextureB - 1][1];
		TGAColor colorB = africanDiffuse.get(vtBx, vtBy);

		fVectB = vectNormauxF[i][1];
		vnBx = vectNormauxVn[fVectB - 1][0];
		vnBy = vectNormauxVn[fVectB - 1][1];
		vnBz = vectNormauxVn[fVectB - 1][2];

		ligne3 = vectTriangles[i][2];
		C(0, 0) = vectPoints[ligne3 - 1][0];
		C(1, 0) = vectPoints[ligne3 - 1][1];
		C(2, 0) = vectPoints[ligne3 - 1][2];
		C(3, 0) = 1;

		aux = res*C;
		Cx = aux(0, 0) / aux(3, 0);
		Cy = aux(1, 0) / aux(3, 0);
		Cz = aux(2, 0) / aux(3, 0);

		fTextureC = vectTexturesF[i][2];
		vtCx = vectTexturesVt[fTextureC - 1][0];
		vtCy = vectTexturesVt[fTextureC - 1][1];
		TGAColor colorC = africanDiffuse.get(vtCx, vtCy);

		fVectC = vectNormauxF[i][2];
		vnCx = vectNormauxVn[fVectC - 1][0];
		vnCy = vectNormauxVn[fVectC - 1][1];
		vnCz = vectNormauxVn[fVectC - 1][2];

		//cout << "f : " << fTextureA << "|" << fTextureB << "|" << fTextureC << endl;
		//cout << "vtA : " << vtAx << "|" << vtAy << endl;
		//cout << "vtB : " << vtBx << "|" << vtBy << endl;
		//cout << "vtC : " << vtCx << "|" << vtCy << endl;
		//cout << "fVect : " << fVectA << "|" << fVectB << "|" << fVectC << endl;
		//cout << "vnA : " << vnAx << "|" << vnAy << "|" << vnAz << endl;
		//cout << "vnB : " << vnBx << "|" << vnBy << "|" << vnBz << endl;
		//cout << "vnC : " << vnCx << "|" << vnCy << "|" << vnCz << endl;

		/* Boite englobante */
		maxAbs = maxTrois(Ax, Bx, Cx);
		minAbs = minTrois(Ax, Bx, Cx);
		maxOrd = maxTrois(Ay, By, Cy);
		minOrd = minTrois(Ay, By, Cy);

		/* Pour ne pas être out of map */
		minAbs = max(0., minAbs);
		minOrd = max(0., minOrd);
		maxAbs = min(maxAbs, (double)tailleImage);
		maxOrd = min(maxOrd, (double)tailleImage);

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

						colorNm = africanNM.get(pix_x, pix_y);
						xNormal = colorNm.r;
						yNormal = colorNm.g;
						zNormal = colorNm.b;

						double tmp = sqrt(xNormal*xNormal + yNormal*yNormal + zNormal*zNormal);
						xNormal /= tmp;
						yNormal /= tmp;
						zNormal /= tmp;

						produitScalaire = 2*(xNormal*xLumiere + yNormal*yLumiere + zNormal*zLumiere);
						xR = xNormal * produitScalaire;
						yR = yNormal * produitScalaire;
						zR = zNormal * produitScalaire;
						xR -= xLumiere;
						yR -= yLumiere;
						zR -= zLumiere;

						double tmp1 = sqrt(xR*xR + yR*yR + zR*zR);
						xR /= tmp1;
						yR /= tmp1;
						zR /= tmp1;

						colorSpec = africanSpecular.get(pix_x, pix_y);
						spec = pow(max(zR, 0.), colorSpec.b);

						intensity = max(0.,xNormal*xLumiere + yNormal*yLumiere + zNormal*zLumiere);
						color = TGAColor(min(5+colorPix.r*(intensity+0.6*spec),255.), min(5+colorPix.g*(intensity+0.6*spec),255.), min(5+colorPix.b*(intensity+0.6*spec),255.), min(5+colorPix.a*(intensity+0.6*spec),255.));
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

int main(int argc, char** argv)
{
	cout << "Projet d'infographie - M1 Informatique" << endl;
	/* Parse du fichier obj */
	vector<vector<double> > vectPoints = lectureSommets("african_head.obj");
	vector<vector<double> > vectTriangles = lectureTriangles("african_head.obj");
	vector<vector<double> > vectTexturesF = lectureTexturesF("african_head.obj");
	vector<vector<double> > vectTexturesVt = lectureTexturesVt("african_head.obj");
	vector<vector<double> > vectNormauxVn = lectureVecteursNormauxVn("african_head.obj");
	vector<vector<double> > vectNormauxF = lectureVecteursF("african_head.obj");

	/* Creation du Viewport */
	Matrice viewPort = Matrice(4, 4);
	viewPort(0, 0) = tailleImageSurDeux;
	viewPort(0, 3) = tailleImageSurDeux;
	viewPort(1, 1) = tailleImageSurDeux;
	viewPort(1, 3) = tailleImageSurDeux;
	viewPort(2, 2) = 500;
	viewPort(2, 3) = 500;
	viewPort(3, 3) = 1;

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
	double angleX = 25 *(PI) / 180;
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

	/* Creation de la rotation complete */
	Matrice rotation = Matrice(4, 4);
	rotation = rotationX*rotationY*rotationZ;

	/* On dessine l'image */
	faceTexture(vectPoints, vectTriangles, vectTexturesF, vectTexturesVt, vectNormauxVn, vectNormauxF, viewPort, perspective, rotation);
	return 0;
}