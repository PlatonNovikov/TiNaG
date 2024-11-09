#include <math.h>
#include "random.hpp"

typedef struct {
    int y;
    int x;
    int y_e;
    int x_e;
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

    int randx = rand() % width;
    int randy = rand() % height;

    for (int i = 0; i < log2(width * height); i++) {
        if (MAP_RIVER[randy][randx] != 0) {
            i++;
            continue;
        }

        Coordinate dir[4];
        int dir_q = 0;

        // Check all four directions and add valid moves to `dir`
        if (randy > 0 && MAP_RIVER[randy - 1][randx] == 0) {
            dir[dir_q++] = (Coordinate){randy - 1, randx, randy - 1 + randint(0, width), randx};
        }
        if (randx > 0 && MAP_RIVER[randy][randx - 1] == 0) {
            dir[dir_q++] = (Coordinate){randy, randx - 1};
        }
        if (randy < height - 1 && MAP_RIVER[randy + 1][randx] == 0) {
            dir[dir_q++] = (Coordinate){randy + 1, randx};
        }
        if (randx < width - 1 && MAP_RIVER[randy][randx + 1] == 0) {
            dir[dir_q++] = (Coordinate){randy, randx + 1};
        }

        if (dir_q > 0) {
            int choice = rand() % dir_q;
            randy = dir[choice].y;
            randx = dir[choice].x;
            MAP_RIVER[randy][randx] = 1; 
        }
    }
}