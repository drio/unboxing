#ifndef VARIANTS_H
#define VARIANTS_H

typedef struct {
    float x, y, z;
    int layer;
    int variant;
} Point;

typedef struct {
    Point (*function)(Point p);
    const char* name;
    const char* description;
} VariantFunction;

Point sine_variant(Point p);
Point double_sine_variant(Point p);
Point rescaling_variant(Point p);

extern VariantFunction variant_functions[];
extern const int num_variant_functions;

#endif