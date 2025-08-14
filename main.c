#include "raylib.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    float x, y, z;
    int layer;
    int variant;
} Point;

typedef struct {
    Point (*function)(Point p);
    const char* name;
    const char* description;
} VariantFunction;

typedef struct {
    float a, b, c;
    float d, e, f;
    float g, h, i;
} AffineTransform;

Point apply_affine_transform(Point p, AffineTransform t, int layer_id) {
    Point result;
    result.x = t.a * p.x + t.b * p.y + t.c;
    result.y = t.d * p.x + t.e * p.y + t.f;
    result.z = t.g * p.x + t.h * p.y + t.i;
    result.layer = layer_id;
    result.variant = p.variant;
    return result;
}

Point sine_variant(Point p) {
    Point result;
    result.x = sinf(p.x);
    result.y = sinf(p.y);
    result.z = sinf(p.z) + 1.0f;
    return result;
}

Point double_sine_variant(Point p) {
    Point result;
    result.x = 2.0f * sinf(p.x);
    result.y = 2.0f * sinf(p.y);
    result.z = 2.0f * (sinf(p.z) + 1.0f);
    return result;
}

Point rescaling_variant(Point p) {
    Point result;
    float s = powf(p.x*p.x + p.y*p.y + p.z*p.z, 1.0f/3.0f);
    result.x = p.x + s;
    result.y = p.y + s;
    result.z = fabsf(p.z + s); // Use absolute value
    return result;

}

VariantFunction variant_functions[] = {
    {sine_variant, "sine", "sin(point)"},
    {double_sine_variant, "double_sine", "2 * sin(point)"},  
    {rescaling_variant, "rescaling", "point + (sum(point^2))^(1/3)"}
};
const int num_variant_functions = 3;

float random_coeff() {
    return ((float)rand() / (float)RAND_MAX) * 2.0f - 1.0f; 
}

AffineTransform create_random_transform() {
    AffineTransform t;
    t.a = random_coeff();
    t.b = random_coeff();
    t.c = random_coeff();
    t.d = random_coeff();
    t.e = random_coeff();
    t.f = random_coeff();
    t.g = random_coeff();
    t.h = random_coeff();
    t.i = random_coeff();
    return t;
}

void generate_chaos_points(Point* points, int iterations, int num_layers) {
    AffineTransform* transforms = malloc(num_layers * sizeof(AffineTransform));

    for (int i = 0; i < num_layers; i++) {
        transforms[i] = create_random_transform();
    }

    Point current = {
        0.0f, 0.0f, 0.0f, 0, 0
    };

    const int settling_iterations = 10; // minimal settling, preserve structure formation

    for (int i = 0; i < iterations + settling_iterations; i++) {
        int layer_choice = rand() % num_layers;
        int variant_choice = rand() % num_variant_functions;

        float old_z = current.z;
        current.z = 1.0f; // reset z=1 before transform as in article
        current = apply_affine_transform(current, transforms[layer_choice], layer_choice);
        current = variant_functions[variant_choice].function(current);
        current.z = (current.z + old_z) / 2.0f; // blend color values as in article

        current.layer = layer_choice;
        current.variant = variant_choice;

        // only save points after settling period
        if (i >= settling_iterations) {
            points[i - settling_iterations] = current;
        }
    }

    free(transforms);
}

Color map_color(float z_value) {
    float t = (z_value + 1.0f) / 3.0f; // map to [0,1] roughly
    if (t < 0) t = 0;
    if (t > 1) t = 1;
    unsigned char intensity = (unsigned char)(t * 255);
    return (Color){255, intensity, intensity, 255}; // red=255 always, G&B increase: red->pink->white
}

void print_points(Point* points, int point_count) {
    for (int i = 0; i < point_count; i++) {
        printf("%.3f %.3f %.3f %d %d\n", 
               points[i].x, points[i].y, points[i].z, points[i].layer, points[i].variant);
    }
}

Image create_fractal_image(Point* points, int point_count, int width, int height) {
    Image fractal_image = GenImageColor(width, height, BLACK);
    
    for (int i = 0; i < point_count; i++) {
        int screen_x = (int)((points[i].x + 2.0f) * width / 4.0f);
        int screen_y = (int)((points[i].y + 2.0f) * height / 4.0f);

        if (screen_x >= 0 && screen_x < width && screen_y >= 0 && screen_y < height) {
            Color point_color = map_color(points[i].z);
            ImageDrawPixel(&fractal_image, screen_x, screen_y, point_color);
        }
    }
    
    return fractal_image;
}

void save_image(Point* points, int point_count, const char* filename) {
    Image fractal_image = create_fractal_image(points, point_count, 2000, 2000);
    ExportImage(fractal_image, filename);
    UnloadImage(fractal_image);
    printf("Image saved to %s\n", filename);
}

void run_raylib_visualization(Point* points, int point_count) {
    const int screenWidth = 2000;
    const int screenHeight = 2000;
    InitWindow(screenWidth, screenHeight, "Unboxing Algorithm");

    // Create fractal image and convert to texture
    Image fractal_image = create_fractal_image(points, point_count, screenWidth, screenHeight);
    Texture2D fractal_texture = LoadTextureFromImage(fractal_image);
    UnloadImage(fractal_image);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(BLACK);

            // Just draw the pre-rendered texture
            DrawTexture(fractal_texture, 0, 0, WHITE);

            DrawText("Unboxing Fractal", 10, 10, 20, WHITE);
            DrawText("ESC to exit", 10, 40, 16, GRAY);
            DrawFPS(screenWidth - 80, 10);

        EndDrawing();
    }

    UnloadTexture(fractal_texture);
    CloseWindow();
}

int main(void) {
    const int iterations = 1000000; // reduce for WASM compatibility
    const int layers = 7;
    const int mode = 1; // 0=print points, 1=visualization, 2=save image
    const int seed = 156;

    Point* points = malloc(iterations * sizeof(Point));

    srand(seed);
    generate_chaos_points(points, iterations, layers);

    if (mode == 1) {
        run_raylib_visualization(points, iterations);
    } else if (mode == 2) {
        save_image(points, iterations, "fractal.png");
    } else {
        print_points(points, iterations);
    }

    free(points);
    return 0;
}
