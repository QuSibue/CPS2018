#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "image.h"

const double a = 0.299;
const double b = 0.587;
const double c = 0.114;
const double alpha = 0.2;


int main(int argc , char** argv){

  char path [160];
  char* option;

  if(argc == 3){
    char path [160]="../../Exemples/";
    strcat(path,argv[2]);
  }

  if(argc == 3 && (access(path,F_OK) != -1)){


    struct image* image = PPM_convertor(path);
    option = argv[1];
    while(strcmp(option,"-g") != 0 && strcmp(option,"-b") != 0 ){
          printf("option :%s\n",option );
          printf("option entrée incorrect, saisir -g (Niveau_gris) ou -b (noir_et_blanc) \n");
          scanf("%s",option);

    }
    if(strcmp(option,"-g") == 0){
      struct image* image_gris = Niveau_gris(image,a,b,c);
      PPM_to_file("test.pgm",image_gris);
    }
    else if(strcmp(option,"-b") == 0){
      struct image* image_noir_et_blanc = noir_et_blanc(image,alpha);
      PPM_to_file("test.pbm",image_noir_et_blanc);
    }
  }
  else if ((argc == 2)){
    option = argv[1];
    while(strcmp(option,"-g") != 0 && strcmp(option,"-b") != 0 ){
          printf("option :%s\n",option );
          printf("option entrée incorrect, saisir -g (Niveau_gris) ou -b (noir_et_blanc) \n");
          scanf("%s",option);
          printf("\n");

    }
    printf("Aucun fichier saisi ou incorrect, entrer l'image depuis l'invite de commande\n");
    
  }
  else{
    printf("Paramètres entrés dans le mauvais sens ou absent : ./traitement_image OPTION [NOM_IMAGE]\n");
  }
}


  /*if (image){
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

	PPM_to_file("test.pbm",image_noir_et_blanc);
  PPM_to_file("test.pgm",image_gris);*/
