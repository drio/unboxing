#ifndef TRANSFORMS_H
#define TRANSFORMS_H

#include "variants.h"

typedef struct {
    float a, b, c;
    float d, e, f;
    float g, h, i;
} AffineTransform;

float random_coeff();
AffineTransform create_random_transform();
Point apply_affine_transform(Point p, AffineTransform t, int layer_id);
void print_matrix(AffineTransform* m);

#endif