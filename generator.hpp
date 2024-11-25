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

void begin_river(Coordinate *rand_start, int width, int height) {
    int begin_side = rand() % 4; // 0 - up, 1 - left, 2 - down, 3 - right

    switch (begin_side) {
        case 0:
            rand_start->x = rand() % width;
            rand_start->y = 0;
            break;
        
        case 1:
            rand_start->x = 0;
            rand_start->y = rand() % height;
            break;

        case 2:
            rand_start->x = rand() % width;
            rand_start->y = height - 1;
            break;

        case 3:
            rand_start->x = width - 1;
            rand_start->y = rand() % height;
            break;

        default:
            break;
    }

}

void GENERATOR_RIVER(int** MAP_RIVER, int width, int height) {
    Coordinate rand_start;

    begin_river(&rand_start, width, height);

    //printf("%d",ceil(log2(height * width)));

    int river_count = 1;
    for (int i = 0; i < ceil(log2(height * width)) + 1; i++) {
        Coordinate cont_riv_end[4];
        int cont_riv_count = 0;

        if (rand_start.x > 0 && MAP_RIVER[rand_start.y][rand_start.x - 1] == 0) {
            cont_riv_end[cont_riv_count].x = rand_start.x - rand() % rand_start.x;
            cont_riv_end[cont_riv_count].y = rand_start.y;
            cont_riv_count++;
        }

        if (rand_start.x < width - 1 && MAP_RIVER[rand_start.y][rand_start.x + 1] == 0) {
            cont_riv_end[cont_riv_count].x = rand_start.x + rand() % (width - rand_start.x);
            cont_riv_end[cont_riv_count].y = rand_start.y;
            cont_riv_count++;
        }

        if (rand_start.y > 0 && MAP_RIVER[rand_start.y - 1][rand_start.x] == 0) {
            cont_riv_end[cont_riv_count].x = rand_start.x;
            cont_riv_end[cont_riv_count].y = rand_start.y - rand() % rand_start.y;
            cont_riv_count++;
        }

        if (rand_start.y < height - 1 && MAP_RIVER[rand_start.y + 1][rand_start.x] == 0) {
            cont_riv_end[cont_riv_count].x = rand_start.x;
            cont_riv_end[cont_riv_count].y = rand_start.y + rand() % (height - rand_start.y);
            cont_riv_count++;
        }

        if (cont_riv_count == 0) {
            continue;
        }

        Coordinate rand_end = cont_riv_end[rand() % cont_riv_count];
        //printf("Start: %d %d -> End: %d %d\n", rand_start.x, rand_start.y, rand_end.x, rand_end.y);

        fillPath(MAP_RIVER, rand_start.x, rand_start.y, rand_end.x, rand_end.y);
    
        if ((rand() % river_count) == 0) {
            rand_start = rand_end;
            river_count++;
        } else {
            begin_river(&rand_start, width, height);
            river_count = 1;
        }
    }
}
