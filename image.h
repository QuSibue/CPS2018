#ifndef IMAGE_H
#define IMAGE_H

#include <stdint.h>


struct image{
  enum type {1,2,3};
  enum type Pi;
  uint32_t largeur;
  uint32_t hauteur;
  int maxPixelValue;
  uint64_t* pixels[hauteur][largeur];
};


#endif
