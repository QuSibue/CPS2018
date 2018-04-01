#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum type {P1=1,P2=2,P3=3};
extern const uint64_t M_MASK;
extern const double a;
extern const double b;
extern const double c;



struct image{
  enum type Pi;
  uint32_t largeur;
  uint32_t hauteur;
  int maxPixelValue;
  uint64_t** pixels;
};

const char *getExt (const char *fspec);

struct image*  PPM_convertor(const char *path);

struct image* Niveau_gris(const struct image* source, double a, double b, double c);

void affiche_PPM(const struct image* image);

void affiche_Niveau_Gris(const struct image* image);

#endif
