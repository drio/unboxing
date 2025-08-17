#ifndef COLOR_H
#define COLOR_H

#include "raylib.h"

typedef enum {
    PALETTE_RED_TO_PINK,
    PALETTE_BLUE_OCEAN,
    PALETTE_GREEN_FOREST,
    PALETTE_PURPLE_DREAM,
    PALETTE_RAINBOW,
    PALETTE_R_DEFAULT,
    PALETTE_GREY,
    PALETTE_EXPERIMENT, 
} PaletteType;

// Color functions
Color lerp_color(Color a, Color b, float t);
Color palette_3color(float t, Color c1, Color c2, Color c3);
Color map_color(float layer_value, float z_value, PaletteType palette);

#endif