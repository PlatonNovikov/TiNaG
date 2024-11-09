#include <stdlib.h>

int randint(int min, int max){
    return(rand() % (min + max) + min);
}