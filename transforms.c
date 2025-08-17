#include "transforms.h"
#include <stdlib.h>
#include <stdio.h>

float random_coeff() {
    return ((float)rand() / (float)RAND_MAX) * 2.0f - 1.0f;
}

AffineTransform create_random_transform() {
    AffineTransform t;
    t.a = random_coeff();
    t.b = random_coeff();
    t.c = random_coeff();
    t.d = random_coeff();
    t.e = random_coeff();
    t.f = random_coeff();
    t.g = random_coeff();
    t.h = random_coeff();
    t.i = random_coeff();
    return t;
}

Point apply_affine_transform(Point p, AffineTransform t, int layer_id) {
    Point result;
    result.x = p.x * t.a + p.y * t.b + p.z * t.c;
    result.y = p.x * t.d + p.y * t.e + p.z * t.f;
    result.z = p.x * t.g + p.y * t.h + p.z * t.i;
    result.layer = layer_id;
    result.variant = p.variant;
    return result;
}

void print_matrix(AffineTransform* m) {
    printf("%.6f %.6f %.6f\n", m[0].a, m[0].b, m[0].c);
    printf("%.6f %.6f %.6f\n", m[0].d, m[0].e, m[0].f);
    printf("%.6f %.6f %.6f\n", m[0].g, m[0].h, m[0].i);
    printf("\n");
}