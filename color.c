#include "color.h"

const Color LIGHT_GREY = {240, 240, 240, 255};
const Color DARK_GREY = {60, 60, 60, 255};
const Color CREAM = {245, 245, 220, 255};
const Color DARK_BLUE = {25, 25, 112, 255};
const Color FOREST_GREEN = {34, 139, 34, 255};

Color map_color(float z_value, PaletteType palette) {
    float t = (z_value + 1.0f) / 3.0f;
    if (t < 0) t = 0;
    if (t > .8) t = .8;
    unsigned char intensity = (unsigned char)(t * 255);

    switch(palette) {
        case PALETTE_EXPERIMENT:
            return (Color){255, intensity, intensity, 200};
        case PALETTE_GREY:
            return DARK_GREY;
        case PALETTE_RED_TO_PINK:
            return (Color){255, intensity, intensity, 255};

        case PALETTE_BLUE_OCEAN:
            return (Color){intensity/3, intensity/2, 255, 255};

        case PALETTE_GREEN_FOREST:
            return (Color){intensity/4, 255, intensity/2, 255};

        case PALETTE_PURPLE_DREAM:
            return (Color){255, intensity/3, 255, 255};

        case PALETTE_RAINBOW:
            if (t < 0.2f) {
                return (Color){255, (unsigned char)(t * 1275), 0, 255};
            } else if (t < 0.4f) {
                return (Color){255, 255, 0, 255};
            } else if (t < 0.6f) {
                return (Color){(unsigned char)(255 * (1 - (t-0.4f)*5)), 255, 0, 255};
            } else {
                return (Color){0, (unsigned char)(255 * (1 - (t-0.6f)*5)), 255, 255};
            }

        case PALETTE_R_DEFAULT:
            {
                unsigned char darkness = (unsigned char)(t * 120);
                return (Color){darkness, darkness, darkness, 255};
            }

        default:
            return (Color){255, intensity, intensity, 255};
    }
}