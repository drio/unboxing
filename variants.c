#include "variants.h"
#include <math.h>

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
    result.z = p.z + s;
    return result;
}

VariantFunction variant_functions[] = {
    {rescaling_variant, "rescaling", "point + (sum(point^2))^(1/3)"},
    {sine_variant, "sine", "sin(point)"},
    {double_sine_variant, "double_sine", "2 * sin(point)"},  
};
const int num_variant_functions = 3;