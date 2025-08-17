#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "color.h"
#include "variants.h"
#include "transforms.h"
#include "chaos.h"
#include "wasm.h"

Config cfg;

void print_usage(const char* program_name) {
    printf("Usage: %s [options]\n", program_name);
    printf("Options:\n");
    printf("  -i, --iterations <num>   Number of iterations (default: 10000000)\n");
    printf("  -l, --layers <num>       Number of layers (default: 5)\n");
    printf("  -m, --mode <num>         Mode: 1=visualize, 2=save, 3=print (default: 2)\n");
    printf("  -p, --palette <num>      Palette number (see color.h for values)\n");
    printf("  -w, --width <num>        Image width (default: 4000)\n");
    printf("  -h, --height <num>       Image height (default: 4000)\n");
    printf("  -o, --output <file>      Output filename (default: fractal.png)\n");
    printf("  --help                   Show this help\n");
}

Config parse_args(int argc, char* argv[]) {
    Config config = {
        .iterations = 10000000,
        .layers = 5,
        .mode = 2,
        .palette = PALETTE_RED_TO_PINK,
        .width = 4000,
        .height = 4000,
        .background = BLACK,
        .output_filename = "fractal.png",
    };

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            print_usage(argv[0]);
            exit(0);
        } else if ((strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--iterations") == 0) && i + 1 < argc) {
            config.iterations = atoi(argv[++i]);
        } else if ((strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--layers") == 0) && i + 1 < argc) {
            config.layers = atoi(argv[++i]);
        } else if ((strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--mode") == 0) && i + 1 < argc) {
            config.mode = atoi(argv[++i]);
        } else if ((strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--palette") == 0) && i + 1 < argc) {
            config.palette = (PaletteType)atoi(argv[++i]);
        } else if ((strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--width") == 0) && i + 1 < argc) {
            config.width = atoi(argv[++i]);
        } else if ((strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--height") == 0) && i + 1 < argc) {
            config.height = atoi(argv[++i]);
        } else if ((strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) && i + 1 < argc) {
            config.output_filename = argv[++i];
        } else {
            printf("Unknown option: %s\n", argv[i]);
            print_usage(argv[0]);
            exit(1);
        }
    }

    return config;
}

int main(int argc, char* argv[]) {
#ifdef PLATFORM_WEB
    printf("WASM module loaded, ready for JS calls\n");
    return 0;
#else
    cfg = parse_args(argc, argv);

    Point* points = malloc(cfg.iterations * sizeof(Point));

    srand(time(NULL) ^ getpid() ^ clock()); 
    generate_chaos_points(points, &cfg);

    if (cfg.mode == 1) {
        run_raylib_visualization(points, cfg.iterations, &cfg);
    } else if (cfg.mode == 2) {
        save_image(points, cfg.iterations, cfg.output_filename, &cfg);
    } else {
        print_points(points, cfg.iterations);
    }

    free(points);
    return 0;
#endif
}
