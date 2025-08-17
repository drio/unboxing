#include "color.h"
#include <math.h>
#include <stdint.h>
#include <stdio.h>

// Custom color constants (raylib provides basic colors like BLACK, RED, etc.)
static const Color NAVY = {0, 0, 50, 255};
static const Color DARK_GREEN = {0, 100, 0, 255};
static const Color BRIGHT_GREEN = {0, 200, 50, 255};
static const Color YELLOW_GREEN = {150, 255, 150, 255};
static const Color FIRE_YELLOW = {255, 255, 100, 255};
static const Color DARK_GREY = {60, 60, 60, 255};

// 3-color linear interpolation
Color lerp_color(Color a, Color b, float t) {
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;

    return (Color){
        (uint8_t)(a.r + t * (b.r - a.r)),
        (uint8_t)(a.g + t * (b.g - a.g)),
        (uint8_t)(a.b + t * (b.b - a.b)),
        255
    };
}

Color palette_3color(float t, Color c1, Color c2, Color c3) {
    if (t <= 0.5f) {
        return lerp_color(c1, c2, t * 2.0f);
    } else {
        return lerp_color(c2, c3, (t - 0.5f) * 2.0f);
    }
}

Color map_color(float layer_value, float z_value, float variant_value, PaletteType palette) {
    float layer_t = layer_value / 4.0f;
    float z_t = (z_value + 1.0f) / 3.0f;
    if (z_t < 0) z_t = 0;
    if (z_t > 1) z_t = 1;

    // Apply log transform to spread out clustered z values
    z_t = logf(z_t * 9.0f + 1.0f) / logf(10.0f);

    float variant_t = variant_value / 2.0f;

    // Blend: layer dominates, z adds variation, variant adds color shifts
    float t = (layer_t + z_t * 0.3f + variant_t * 0.2f) / 1.5f;
    if (t > 1.0f) t = 1.0f;


    switch(palette) {
        case PALETTE_EXPERIMENT:
            return (Color){255, (uint8_t)(255 * (1-t)), (uint8_t)(255 * t), 128};

        case PALETTE_RED_TO_PINK:
            return palette_3color(t, BLACK, RED, YELLOW);

        case PALETTE_BLUE_OCEAN:
            return palette_3color(t, NAVY, BLUE, SKYBLUE);

        case PALETTE_GREEN_FOREST:
            return palette_3color(t, DARK_GREEN, BRIGHT_GREEN, YELLOW_GREEN);

        case PALETTE_PURPLE_DREAM:
            return palette_3color(t, PURPLE, MAGENTA, ORANGE);

        case PALETTE_GREY:
            return DARK_GREY;

        case PALETTE_R_DEFAULT: {
            uint8_t darkness = (uint8_t)(t * 120);
            return (Color){darkness, darkness, darkness, 255};
        }

        default:
            return palette_3color(t, BLACK, RED, FIRE_YELLOW);
    }
}
