#include <stdio.h>
#include <stdlib.h>

#include "image.h"

const double a = 0.299;
const double b = 0.587;
const double c = 0.114;
const double alpha = 0.2;


int main(int argc , char** argv){
  struct image* image = PPM_convertor("../../Exemples/image2.ppm");
  if (image){
    affiche_PPM(image);
  }
  struct image* image_gris = Niveau_gris(image,a,b,c);
  if (image_gris){
    printf("\n\n");
    affiche_Niveau_Gris(image_gris);
  }

	struct image* image_noir_et_blanc = noir_et_blanc(image,alpha);
  if (image_noir_et_blanc){
    printf("\n\n");
    affiche_noir_et_blanc(image_noir_et_blanc);
  }


}
