#include <math.h>
#include "random.hpp"

typedef struct {
    int y;
    int x;
} Coordinate;

void fillPath(int** MAP_RIVER, int start_x, int start_y, int end_x, int end_y) {
    int x = start_x;
    int y = start_y;

    while (x != end_x || y != end_y) {
        MAP_RIVER[y][x] = 1;  // Отмечаем текущую позицию как часть пути

        // Рассчитываем направление движения
        if (x < end_x) x++;         // Двигаемся вправо, если конечная точка правее
        else if (x > end_x) x--;    // Двигаемся влево, если конечная точка левее

        if (y < end_y) y++;         // Двигаемся вниз, если конечная точка ниже
        else if (y > end_y) y--;    // Двигаемся вверх, если конечная точка выше
    }

    MAP_RIVER[y][x] = 1;  // Отмечаем конечную точку
}

void GENERATOR_RIVER(int** MAP_RIVER, int width, int height) {
    Coordinate rand_start;

    int begin_side = rand() % 4; //1 - up, 2 - left, 3 - down, 4 - right

    switch (begin_side){
    case 0:
        rand_start.x = rand() % width;
        rand_start.y = 0;
        break;
    
    case 1:
        rand_start.x = 0;
        rand_start.y = rand() % height;
        break;

    case 2:
        rand_start.x = rand() % width;
        rand_start.y = height;
        break;

    case 3:
        rand_start.x = width;
        rand_start.y = rand() % height;
        break;

    default:
        break;
    }
    int cont_riv_count = 0;
    for (int i = 0; i < ceil(log2(height * width)) + 1; i++){
        Coordinate cont_riv_end[4];
        cont_riv_count = 0;

        if (rand_start.x > 0 && MAP_RIVER[rand_start.y][rand_start.x - 1] == 0){
                cont_riv_end[cont_riv_count].x = rand_start.x - rand() % rand_start.x;
                cont_riv_end[cont_riv_count].y = rand_start.y;
                cont_riv_count++;

            }

        if (rand_start.x < width - 1 && MAP_RIVER[rand_start.y][rand_start.x + 1] == 0){
                cont_riv_end[cont_riv_count].x = rand_start.x + rand() % (width - rand_start.x);
                cont_riv_end[cont_riv_count].y = rand_start.y;
                cont_riv_count++;
            }

        if (rand_start.y > 0 && MAP_RIVER[rand_start.y - 1][rand_start.x] == 0){
                cont_riv_end[cont_riv_count].x = rand_start.x;
                cont_riv_end[cont_riv_count].y = rand_start.y - rand() % rand_start.y;
                cont_riv_count++;
            }

        if (rand_start.y < height - 1 && MAP_RIVER[rand_start.y + 1][rand_start.x] == 0){
                cont_riv_end[cont_riv_count].x = rand_start.x;
                cont_riv_end[cont_riv_count].y = rand_start.y + rand() % (height - rand_start.y);
                cont_riv_count++;
            }

        if (cont_riv_count == 0){
            continue;
            }

        Coordinate rand_end = cont_riv_end[rand() % cont_riv_count];

        printf("Start: %d %d\n", rand_start.x, rand_start.y);

        fillPath(MAP_RIVER, rand_start.x, rand_start.y, rand_end.x, rand_end.y);

        rand_start = rand_end;
        }
    }  
