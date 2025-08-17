#ifndef CHAOS_H
#define CHAOS_H

#include "raylib.h"
#include "color.h"
#include "variants.h"

typedef struct {
    int iterations;
    int layers;
    int mode;
    PaletteType palette;
    int width;
    int height;
    Color background;
} Config;

void generate_chaos_points(Point* points, Config* cfg);
void print_points(Point* points, int point_count);
Image create_fractal_image(Point* points, int point_count, Config* cfg);
void save_image(Point* points, int point_count, const char* filename, Config* cfg);
void run_raylib_visualization(Point* points, int point_count, Config* cfg);

#endif