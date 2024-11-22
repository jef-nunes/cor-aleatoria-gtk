#include <stdlib.h>
#include <time.h>

int randint(int min, int max) {
    // Se min > max, retorna um erro
    if (min > max) {
        return -1;
    }
    // Gerar um número aleatório entre min e max
    return min + rand() % (max - min + 1);
}
