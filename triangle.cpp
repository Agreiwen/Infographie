#include "tgaimage.h"
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

double matriceA[2][2];
double matriceB[1][2];
double matriceUV[1][2];

void inverseMatrice(double matrice[2][2], double matriceInversse[2][2]) {
	double determinant = 1/(matrice[1][1] * matrice[2][2] - matrice[1][2] * matrice[2][1]);
	matriceInversse[1][1] = matrice[2][2] * determinant;
	matriceInversse[2][2] = matrice[1][1] * determinant;
	matriceInversse[1][2] = -matrice[1][2] * determinant;
	matriceInversse[2][1] = -matrice[2][1] * determinant;
}

void produitMatrice(double matriceA[2][2], double matriceB[1][2], double produit[1][2]) {
	produit[1][1] = matriceA[1][1] * matriceB[1][1] + matriceA[1][2] * matriceB[1][2];
	produit[1][2] = matriceA[2][1] * matriceB[1][1] + matriceA[2][2] * matriceB[1][2];
}

bool appartientTriangle(double Px, double Py, double Ax, double Ay, double Bx, double By, double Cx, double Cy) {
	//Remplissage Matrice A
	matriceA[1][1] = Bx - Ax;
	matriceA[1][2] = Cx - Ax;
	matriceA[2][1] = By - Ay;
	matriceA[2][2] = Cy - Ay;

	//Remplissage matrice N=B
	matriceB[1][1] = Px - Ax;
	matriceB[1][2] = Py - Ay;

	double inverseA[2][2];
	inverseMatrice(matriceA, inverseA);

	produitMatrice(inverseA, matriceB, matriceUV);

	if (matriceUV[1][1] >= 0 && matriceUV[1][2] >= 0) {
		return true;
	}
	else {
		return false;
	}

}


/*
int main(int argc, char** argv) {
	appartientTriangle(5, 3, 3, 5, 8, 4, 4, 1);
	return 0;
}
*/
