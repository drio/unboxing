#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main() {
    srand(time(NULL));  // Use current time as seed
    float x = ((float)rand() / (float)RAND_MAX) * 2.0f - 1.0f; 
    printf("%f\n", x);
    return 0;
}


