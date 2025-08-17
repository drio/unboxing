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

extern const Color LIGHT_GREY;
extern const Color DARK_GREY;
extern const Color CREAM;
extern const Color DARK_BLUE;
extern const Color FOREST_GREEN;

Color map_color(float z_value, PaletteType palette);

#endif