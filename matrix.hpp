#include <stdio.h>
#include <stdlib.h>

int** createMatrix(int height, int width) {
    int** matrix = (int**)malloc(height * sizeof(int*));
    if (matrix == NULL) {
        printf("ermemloc");
        exit(1);
    }

    // Выделяем память для каждого столбца в строках
    for (int i = 0; i < height; i++) {
        matrix[i] = (int*)malloc(width * sizeof(int));
        if (matrix[i] == NULL) {
            printf("ermemloc");
            exit(1);
        }
    }

    return matrix;
}

void freeMatrix(int** matrix, int height) {
    // Освобождаем память для каждой строки
    for (int i = 0; i < height; i++) {
        free(matrix[i]);
    }
    // Освобождаем память для массива указателей
    free(matrix);
}

void printMatrix(int** matrix, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printf("%d", matrix[i][j]);
        }
        printf("\n");
    }
}