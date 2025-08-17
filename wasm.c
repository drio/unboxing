#include "wasm.h"
#include "color.h"
#include "chaos.h"
#include <stdlib.h>

extern Config cfg;

int get_canvas_width() {
    return cfg.width;
}

int get_canvas_height() {
    return cfg.height;
}

unsigned char* generate_fractal_pixels(int iterations, int layers, int palette_type, int width, int height, int bg_r, int bg_g, int bg_b, int seed) {
    Config fractal_cfg = {
        .iterations = iterations,
        .layers = layers,
        .mode = 1,
        .palette = (PaletteType)palette_type,
        .width = width,
        .height = height,
        .background = (Color){bg_r, bg_g, bg_b, 255}
    };

    Point* points = malloc(fractal_cfg.iterations * sizeof(Point));
    srand(seed);
    generate_chaos_points(points, &fractal_cfg);

    size_t pixel_count = width * height * 4;
    unsigned char* pixels = malloc(pixel_count);

    for (int i = 0; i < width * height; i++) {
        pixels[i * 4 + 0] = bg_r;
        pixels[i * 4 + 1] = bg_g;
        pixels[i * 4 + 2] = bg_b;
        pixels[i * 4 + 3] = 255;
    }

    for (int i = 0; i < fractal_cfg.iterations; i++) {
        int screen_x = (int)((points[i].x + 4.0f) * width / 8.0f);
        int screen_y = height - (int)((points[i].y + 4.0f) * height / 8.0f);

        if (screen_x >= 0 && screen_x < width && screen_y >= 0 && screen_y < height) {
            Color point_color = map_color(points[i].layer, points[i].z, fractal_cfg.palette);
            int pixel_index = (screen_y * width + screen_x) * 4;
            pixels[pixel_index + 0] = point_color.r;
            pixels[pixel_index + 1] = point_color.g;
            pixels[pixel_index + 2] = point_color.b;
            pixels[pixel_index + 3] = point_color.a;
        }
    }

    free(points);
    return pixels;
}

void free_pixel_data(unsigned char* pixels) {
    free(pixels);
}