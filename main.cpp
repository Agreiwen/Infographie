#include "tgaimage.h"
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

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

void affichageVector(vector<vector<double> > vect) {
	for (unsigned int i = 0; i < vect.size(); ++i) {
		for (unsigned int j = 0; j < vect[i].size(); ++j) {
			cout << "Vect[" << i << "," << j << "] = " << vect[i][j] << endl;
		}
	}
	cout << "\n" << endl;
}

void dessinePoint(vector<vector<double> > vect) {
	cout << "Creation de l'image nuage de point ... ";
	int tailleImage = 1000;
	int moitierTailleImage = tailleImage / 2;
	TGAImage image(tailleImage, tailleImage, TGAImage::RGB);
	for (unsigned int i = 0; i < vect.size(); ++i) {
		double x = vect[i][0]+ moitierTailleImage;
		double y = vect[i][1]+ moitierTailleImage;
		image.set(x, y, white);
	}
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("nuage_de_point.tga");
	cout << "Succes" << endl;
}

void dessineFilDeFer(vector<vector<double> > vectPoints, vector<vector<double> > vectTriangles) {
	cout << "Creation image fil de fer ... ";
	int tailleImage = 1000;
	int tailleImageSurDeux = tailleImage / 2;
	int tailleImagesurQuatre = tailleImage / 4;
	TGAImage image(tailleImage, tailleImage, TGAImage::RGB);
	for (unsigned int i = 0; i < vectPoints.size(); ++i) {
		double x = vectPoints[i][0] + tailleImagesurQuatre;
		double y = vectPoints[i][1] + tailleImagesurQuatre;
		image.set(x, y, white);
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

		line(x1, y1, x2, y2, image, white);
		line(x1, y1, x3, y3, image, white);
		line(x2, y2, x3, y3, image, white);
	}

	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("fil_de_fer.tga");
	cout << "Succes" << endl;
}

vector<vector<double> > lectureSommets(string nomFichier) {
	ifstream fichier(nomFichier, ios::in);  // on ouvre en lecture

	if (fichier)  // si l'ouverture a fonctionné
	{
		string ligne;
		vector<vector<double> > vect;
		vector<double> vectLigne;
		int nbLigne = 0;
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

				nbLigne++;
			}
			vectLigne.clear();
		}
		cout << "\nNombre de point  : " << nbLigne << "\n" << endl;
		return vect;
	}
	else
		cerr << "Impossible d'ouvrir le fichier !" << endl;
}

vector<vector<double> > lectureTriangles(string nomFichier) {
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
		cout << "\nNombre de triangle  : " << nbTriangle << "\n" << endl;
		return vect;
	}
	else
		cerr << "Impossible d'ouvrir le fichier !" << endl;
}

int main(int argc, char** argv) {

	//intro();
	vector<vector<double> > vectPoints = lectureSommets("african_head.obj");
	vector<vector<double> > vectTriangles = lectureTriangles("african_head.obj");
	//affichageVector(vectPoints);
	//affichageVector(vectTriangles);
	//dessinePoint(vectPoints);
	dessineFilDeFer(vectPoints,vectTriangles);
	
	return 0;
}