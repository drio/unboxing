#include "raylib.h"
#include <math.h>
#include <stdlib.h>

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
    result.z = sinf(p.z);
    return result;
}

Point double_sine_variant(Point p) {
    Point result;
    result.x = 2.0f * sinf(p.x);
    result.y = 2.0f * sinf(p.y);
    result.z = 2.0f * sinf(p.z);
    return result;
}

Point rescaling_variant(Point p) {
    Point result;
    float s = powf(p.x*p.x + p.y*p.y + p.z*p.z, 1.0f/3.0f);
    result.x = p.x + s;
    result.y = p.y + s;
    result.z = p.z + s;
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
        random_coeff(), random_coeff(), random_coeff(), 0, 0
    };
    
    for (int i = 0; i < iterations; i++) {
        int layer_choice = rand() % num_layers;
        int variant_choice = rand() % num_variant_functions;
        
        current = apply_affine_transform(current, transforms[layer_choice], layer_choice);
        current = variant_functions[variant_choice].function(current);
        
        current.layer = layer_choice;
        current.variant = variant_choice;
        
        points[i] = current;
    }
    
    free(transforms);
}

int main(void)
{
    // Window initialization
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Unboxing - 2D Raylib");
    
    SetTargetFPS(60);
    
    // Main game loop
    while (!WindowShouldClose())
    {
        // Start drawing
        BeginDrawing();
            ClearBackground(DARKGRAY);
            
            // Draw a simple rectangle
            DrawRectangle(screenWidth/2 - 50, screenHeight/2 - 50, 100, 100, RAYWHITE);
            
            // Draw some text
            DrawText("Hello, Unboxing!", 10, 10, 20, LIGHTGRAY);
            DrawText("ESC to exit", 10, 40, 16, GRAY);
            
            // Draw FPS
            DrawFPS(screenWidth - 80, 10);
            
        EndDrawing();
    }
    
    // Clean up
    CloseWindow();
    
    return 0;
}
