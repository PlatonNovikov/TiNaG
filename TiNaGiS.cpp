#include <iostream>
#include <cstdlib>
#include <ctime>
#include "matrix.hpp"
#include "generator.hpp"

int WIDTH, HEIGHT;

void GENERATOR(){
    int** MAP_RIVER = createMatrix(HEIGHT, WIDTH);
    GENERATOR_RIVER(MAP_RIVER, WIDTH, HEIGHT);
    printMatrix(MAP_RIVER, HEIGHT, WIDTH);
}

void start(){
    printf("Enter width and height of the new world\n");
    scanf("%d %d", &WIDTH, &HEIGHT);
}

int main(){
    start();
    if (WIDTH > 0 && HEIGHT > 0) {
        GENERATOR();
    } else {
        printf("Invalid dimensions!\n");
    }

    printf("Width: %d, Height: %d\n", WIDTH, HEIGHT);
    return 0;
}
