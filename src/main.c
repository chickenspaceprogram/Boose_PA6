#include <stdio.h>
#include "ctty/ansi/cursor.h"

int main(void) {
    printf("Hello World\n\nshitpost");
    Position pos = CURSOR_GET_POSITION();
    printf("\n\nRow %d, Col %d\n", pos.row, pos.col);
}