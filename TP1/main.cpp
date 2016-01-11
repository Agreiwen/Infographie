#include "tgaimage.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

using namespace std;

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) { 
    bool steep = false; 
    if (abs(x0-x1)<abs(y0-y1)) { 
        swap(x0, y0); 
        swap(x1, y1); 
        steep = true; 
    } 
    if (x0>x1) { 
        swap(x0, x1); 
        swap(y0, y1); 
    } 
    int dx = x1-x0; 
    int dy = y1-y0; 
    int derror2 = abs(dy)*2; 
    int error2 = 0; 
    int y = y0; 
    for (int x=x0; x<=x1; x++) { 
        if (steep) { 
            image.set(y, x, color); 
        } else { 
            image.set(x, y, color); 
        } 
        error2 += derror2; 
        if (error2 > dx) { 
            y += (y1>y0?1:-1); 
            error2 -= dx*2; 
        } 
    } 
}

//void parseFile(ifstream myFile){
//  string word, line;
//  myFile.open("african_head.obj");
//  string data[][];
//  while(!myFile.eof()){
//   getline(myFile, line, '\n');
//    for(unsigned int i = 0; i < line.size(); ++i){
//      char c = line[i];
//      if( c == '\n'){
//	if(!word.empty()){
//	  data[i] = word;
//	  word.clear();
//	}
//      }
//      else{
//	word += c;
//      }
//      if(!word.empty()){
//	cout << word << endl;
//      }
//    }
//  }
//}

int main(int argc, char** argv) {
  //int x1 = 10;
  //int y1 = 10;
  //int x2 = 50;
  //int y2 = 50;
  //TGAImage image(100, 100, TGAImage::RGB);
  //image.set(x1, y1, red);
  //image.set(x2, y2, red);
  //line(x1, y1, x2, y2, image, white);
  //image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
  //image.write_tga_file("output.tga");

  ifstream fichier("african_head.obj", ios::in);  // on ouvre en lecture
 
  if(fichier)  // si l'ouverture a fonctionné
    {
      string ligne;
      vector<vector<double> > vect;
      vector<double> vectLigne;
      int nbLigne = 0;
      int indiceLigne = 0;
      // int indiceColonne = 0;
      while(getline(fichier, ligne, '\n'))  // tant que l'on peut mettre la ligne dans "contenu"
        {
	  if(ligne[0] == 'v' && ligne[1] == ' ' && ligne[2] == ' ')
	    {
	      for(unsigned int i = 4; i < ligne.size(); ++i)
		{
		  if(ligne[i] != ' '){
		    vectLigne.push_back(ligne[i]);
		    vect.push_back(vectLigne);
		  }
		  //vect[indiceLigne].push_back[indiceColonne].push_back(ligne[i]);
		  //else
		    // indiceColonne++;gg
		}
	      indiceLigne ++;
	      //indiceColonne = 0;
	      nbLigne ++;
	    }
        }
	  
      cout << "Lignes : " << nbLigne << endl;
    }
  else
    cerr << "Impossible d'ouvrir le fichier !" << endl;
  return 0;
}

