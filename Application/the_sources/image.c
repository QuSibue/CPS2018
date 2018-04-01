#include "image.h"

const uint64_t M_MASK = 65535;

void affiche_PPM(const struct image* image){
  uint64_t p1,p2,p3;                                                            //on déclare les 3 valeur d'un pixel
  printf("%d %d\n",image->largeur,image->hauteur);                              //on affiche la largeur et la hauteur de l'image
  printf("%d\n", image->maxPixelValue);

  for (int i = 0; i < image->hauteur; i++) {                                    //on parcours l'image en intégralité
    for (int j = 0; j < image->largeur; j++) {
      p1=((image->pixels[i][j] >> 32));                                        //la partie p1 du pixel est égale au bits 32 à 47 (d'ou le décalage de 32)
      p2=( (image->pixels[i][j] >> 16) & M_MASK);                               //la partie p2 du pixel est égale au bits 16 à 31 (d'ou le décalage de 16 et la comparaison avec le masque pour ne guarder que ces bits la)
      p3=( image->pixels[i][j] & M_MASK);                                       //la partie p3 du pixel est égale aux bits 0 à 15 (comparaison avec le masque pour ne prendre que ces bits)
      printf("%" SCNu64" ", p1);                                                //on affiche chaque valeur du pixel
      printf("%" SCNu64" ", p2);
      printf("%" SCNu64" ", p3);
      printf("\t");
    }
    printf("\n");
  }
}

const char *getExt (const char *fspec) {                                        //fonction qui va permettre de récuperer l'extension d'un fichier
    char *e = strrchr (fspec, '.');                                             //pointeur qui pointe sur la derniere occurence de '.' pour prendre uniquement l'extension
    if (e == NULL){                                                             //si e est NULL
        e = "";                                                                 //on lui affecte le caractère vide
    }
    return e;
}


struct image*  PPM_convertor(const char *path){                                 //fonction qui lit un fichier ppm et le transforme en image
  FILE *file;                                                                   //on déclare notre fichier
  file = fopen(path,"r");                                                       //on l'ouvre en mode lecture à l'aide du path passé en paramètre

  if (file == NULL){                                                            //si file est null
    printf("le fichier %s est inconnue\n",path);                                //erreur
    return NULL;
  }else if(strcmp(getExt(path),".ppm" ) != 0 ){                                 //sinon si son extension n'est pas .ppm
    printf("le fichier %s n'est pas au format PPM\n",path);                     //erreur
    return NULL;
  }else{                                                                        //sinon
    struct image* image = malloc(sizeof(struct image));                         //on affecte l'espace mémoire nécessaire pour une image
    char entete[3];                                                             //on déclare un tableau de char
    fscanf(file,"%s",entete);                                                   //on lit l'entete dans le fichier
    printf("%s\n",entete);
    if (strcmp(entete,"P3") != 0){                                              //si ce n'est pas P3 (pour PPM)
      printf("le fichier %s est corrompue\n",path);                             //probleme dans le fichier PPM
      free(image);
      return NULL;
    }else{                                                                      //sinon
      image->Pi = P3;                                                           //on affecte a notre struct image comme nombre magique P3
      fscanf( file,"%" SCNu32,&(image->largeur) );                              //on lit la largeur qu'on affecte à l'image
      fscanf( file,"%" SCNu32,&(image->hauteur) );                              //on lit la hauteur qu'on affecte à l'image
      fscanf( file,"%" SCNu32,&(image->maxPixelValue) );                         //on lit la valeur maximal des pixel qu'on affecte à l'image

      image->pixels = malloc(sizeof(uint64_t)*image->hauteur);                  //on allou la mémoire pour le grand tableau de pixel
      for (int z = 0; z < image->hauteur; z++) {                                //pour chaque élement de la hauteur
        image->pixels[z] = malloc(sizeof(uint64_t)*image->largeur);             //on allou la mémoire pour le sous tableau de la largeur
      }

      uint64_t p1,p2,p3;
      for (int i = 0 ;  i < image->hauteur; i++) {                              //on parcours tout les pixel
        for (int j = 0; j < image->largeur; j++) {

          fscanf( file,"%" SCNu64,&(p1) );                                      //on lit p1
          fscanf( file,"%" SCNu64,&(p2) );                                      //on lit p2
          fscanf( file,"%" SCNu64,&(p3) );                                      //on lit p3

          p2 = p2 << 16;                                                        //on décale p2 de 16
          p1 = p1 << 32;                                                        //on décale p3 de 32

          image->pixels[i][j] = p1+p2+p3;                                       //on affecte au pixel en cours la somme des p pour ne faire qu'un seul uint64_t
        }
      }
      return image;
    }
  }
}


struct image* Niveau_gris(const struct image* source, const double a, const double b, const double c){
  if(source != NULL){

    struct image* image = malloc(sizeof(struct image));                         //on affecte l'espace mémoire nécessaire pour une image

    image->Pi = P2;                                                             //on affecte P2 à notre image de niveau de gris
    image->largeur = source->largeur;                                           //on affecte la meme largeur que la source
    image->hauteur = source->hauteur;                                           //on affecte la meme hauteur que la source
    image->maxPixelValue = source->maxPixelValue;                                //UTILE ??

    image->pixels = malloc(sizeof(uint64_t)*image->hauteur);                    //on allou la mémoire pour le grand tableau de pixel

    for (int z = 0; z < image->hauteur; z++) {                                  //pour chaque élement de la hauteur
      image->pixels[z] = malloc(sizeof(uint64_t)*image->largeur);               //on allou la mémoire pour le sous tableau de la largeur
    }

    uint64_t p1,p2,p3;
    printf("\n");
    for (int i = 0 ;  i < image->hauteur; i++) {                                //on parcours tout les pixel
      for (int j = 0; j < image->largeur; j++) {

        p1 = a * (source->pixels[i][j] >> 32);
        p2 = b * ((source->pixels[i][j] >> 16) & M_MASK);
        p3 = c * (source->pixels[i][j] & M_MASK);
      
        image->pixels[i][j] = p1+p2+p3;                                         //on affecte au pixel en cours la somme des p pour ne faire qu'un seul uint64_t
      }
    }
    return image;
  }
  else{
    printf("Erreur, l'image source n'existe pas\n");
    return NULL;
  }
}

void affiche_Niveau_Gris(const struct image* image){
  if(image->Pi == 2){
    printf("P2\n");
    printf("%d %d\n",image->largeur,image->hauteur);                              //on affiche la largeur et la hauteur de l'image
    printf("%d\n", image->maxPixelValue);

    for (int i = 0; i < image->hauteur; i++) {                                    //on parcours l'image en intégralité
      for (int j = 0; j < image->largeur; j++) {
        printf("%" SCNu64" ", image->pixels[i][j]);                               //on affiche chaque valeur du pixel
        printf("\t");
      }
      printf("\n");
    }
  }
  else{
    printf("fonction affiche_Niveau_Gris appelée sur une image du mauvais format\n");
  }

}
