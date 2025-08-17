#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "color.h"
#include "variants.h"
#include "transforms.h"
#include "chaos.h"
#include "wasm.h"

Config cfg;

int main(void) {
#ifdef PLATFORM_WEB
    printf("WASM module loaded, ready for JS calls\n");
    return 0;
#else
    cfg = (Config){
        .mode = 2,
        .iterations = 10000000,
        .layers = 5,
        .palette = PALETTE_RAINBOW,
        .width = 4000,
        .height = 4000,
        .background = BLACK,
    };

    Point* points = malloc(cfg.iterations * sizeof(Point));

    srand(time(NULL)); 
    generate_chaos_points(points, &cfg);

    if (cfg.mode == 1) {
        run_raylib_visualization(points, cfg.iterations, &cfg);
    } else if (cfg.mode == 2) {
        save_image(points, cfg.iterations, "fractal.png", &cfg);
    } else {
        print_points(points, cfg.iterations);
    }

    free(points);
    return 0;
#endif
}
