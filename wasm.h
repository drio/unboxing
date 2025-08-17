#ifndef WASM_H
#define WASM_H

int get_canvas_width();
int get_canvas_height();
unsigned char* generate_fractal_pixels(int iterations, int layers, int palette_type, int width, int height, int bg_r, int bg_g, int bg_b, int seed);
void free_pixel_data(unsigned char* pixels);

#endif