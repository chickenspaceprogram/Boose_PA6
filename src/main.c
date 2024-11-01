#include <stdio.h>
#include "ctty/ansi/cursor.h"

int main(void) {
    printf("Hello World\n\nshitpost");
    Position pos = cursor_get_position();
    printf("\n\nRow %d, Col %d\n", pos.row, pos.col);
}