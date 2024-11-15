#ifndef SELECT_SHOT_SPOT_H
#define SELECT_SHOT_SPOT_H

#include <stdio.h>

#include "board.h"
#include "../ctty/keypress/keyselect.h"
#include "../ctty/keypress/keypress-codes.h"
#include "../ctty/ansi/cursor.h"
#include "../ctty/screen/screen.h"

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

/**
 * Function name: select_spot
 * Date created: 2 Nov 2024
 * Date last modified: 6 Nov 2024
 * Description: Allows the user to select a spot to shoot at on the board.
 * Inputs: 
 * `board` : The board on which to select a spot.
 * Outputs: The spot the user selected.
 */
Position select_spot(Board *board);

/**
 * Function name: normalize_spot
 * Date created: 2 Nov 2024
 * Date last modified: 2 Nov 2024
 * Description: Ensures that `spot` is within the proper bounds, and if it isn't, returns a value that is.
 * Inputs: 
 * `spot` : The position to be checked.
 * `max_row` : The maximum allowable row.
 * `max_col` : The maximum allowable column.
 * Outputs: The new position of `spot`.
 */
Position normalize_spot(Position spot, int max_row, int max_col);

/**
 * Function name: set_cursor_print_info
 * Date created: 6 Nov 2024
 * Date last modified: 6 Nov 2024
 * Description: Sets the PrintInfo struct `info` to the expected values for the cursor.
 * Inputs: none
 * Outputs:
 * `info` : The PrintInfo struct to be set
 */
void set_cursor_print_info(PrintInfo *info);

#endif