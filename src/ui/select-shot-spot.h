#ifndef SELECT_SHOT_SPOT_H
#define SELECT_SHOT_SPOT_H

#include <stdio.h>

#include "board.h"
#include "../ctty/keyselect.h"
#include "../ctty/keypress-codes.h"
#include "../ctty/ansi/cursor.h"

#define CURSOR_PRINT_INFO {.bg_color = BrightCyan, .fg_color = Black, .symbol = '+', .color_all_spaces = 0}

typedef struct {
    int row;
    int col;
} ShotCoords;

typedef enum {
    Key_1 = 0,
    Key_2,
    Key_3,
    Key_4,
    Key_5,
    Key_6,
    Key_7,
    Key_8,
    Key_9,
    Key_0,
    Key_a,
    Key_b,
    Key_c,
    Key_d,
    Key_e,
    Key_f,
    Key_g,
    Key_h,
    Key_i,
    Key_j,
    ArrowUp,
    ArrowDown,
    ArrowLeft,
    ArrowRight,
    Enter,
} Keypress;

ShotCoords select_spot(Board *board);

ShotCoords normalize_spot(ShotCoords spot, int max_row, int max_col);

#endif