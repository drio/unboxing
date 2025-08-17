#include "chaos.h"
#include "transforms.h"
#include "variants.h"
#include <stdlib.h>
#include <stdio.h>

void generate_chaos_points(Point* points, Config* cfg) {
    AffineTransform* transforms = malloc(cfg->layers * sizeof(AffineTransform));

    for (int i = 0; i < cfg->layers; i++) {
        transforms[i] = create_random_transform();
    }

    Point current = {
        random_coeff(), 
        random_coeff(), 
        random_coeff(), 
        0, 0
    };

    for (int i = 0; i < cfg->iterations; i++) {
        int layer_choice = rand() % cfg->layers;
        int variant_choice = rand() % num_variant_functions;

        float old_z = current.z;
        current.z = 1.0f;
        current = apply_affine_transform(current, transforms[layer_choice], layer_choice);
        current = variant_functions[variant_choice].function(current);
        current.z = (current.z + old_z) / 2.0f;

        current.layer = layer_choice;
        current.variant = variant_choice;

        points[i] = current;
    }

    free(transforms);
}

void print_points(Point* points, int point_count) {
    for (int i = 0; i < point_count; i++) {
        printf("%.3f %.3f %.3f %d %d\n", 
               points[i].x, points[i].y, points[i].z, points[i].layer, points[i].variant);
    }
}

Image create_fractal_image(Point* points, int point_count, Config* cfg) {
    Image fractal_image = GenImageColor(cfg->width, cfg->height, cfg->background);

    int out = 0;
    for (int i = 0; i < point_count; i++) {
        int screen_x = (int)((points[i].x + 4.0f) * cfg->width / 8.0f);
        int screen_y = cfg->height - (int)((points[i].y + 4.0f) * cfg->height / 8.0f);

        if (screen_x >= 0 && screen_x < cfg->width && screen_y >= 0 && screen_y < cfg->height) {
            Color point_color = map_color(points[i].layer, points[i].z, points[i].variant, cfg->palette);
            ImageDrawPixel(&fractal_image, screen_x, screen_y, point_color);
        } else {
            out += 1;
        }
    }
    printf("create_fractal_image(): out screen points = %d\n", out);

    return fractal_image;
}

void save_image(Point* points, int point_count, const char* filename, Config* cfg) {
    Image fractal_image = create_fractal_image(points, point_count, cfg);
    ExportImage(fractal_image, filename);
    UnloadImage(fractal_image);
    printf("Image saved to %s\n", filename);
}

void run_raylib_visualization(Point* points, int point_count, Config* cfg) {
    InitWindow(cfg->width, cfg->height, "Unboxing Algorithm");

    Image fractal_image = create_fractal_image(points, point_count, cfg);
    Texture2D fractal_texture = LoadTextureFromImage(fractal_image);
    UnloadImage(fractal_image);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(BLACK);

            DrawTexture(fractal_texture, 0, 0, WHITE);

            DrawText("Unboxing Fractal", 10, 10, 20, WHITE);
            DrawText("ESC to exit", 10, 40, 16, GRAY);
            DrawFPS(cfg->width - 80, 10);

        EndDrawing();
    }

    UnloadTexture(fractal_texture);
    CloseWindow();
}