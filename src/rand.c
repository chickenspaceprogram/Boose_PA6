#include "rand.h"

void seed_rand(void) {
	srand((unsigned int) time(NULL));
}

int randint(int min, int max) {
    int diff = max - min + 1;
    return (rand() % diff) + min;
}