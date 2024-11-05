#include "select-shot-spot.h"

static ShotCoords move_cursor(ShotCoords cursor_pos, Keypress keypress);

ShotCoords select_spot(Board *board) {
    ShotCoords current_coords = {.row = 4, .col = 4};
    ShotCoords next_coords;
    PrintInfo spot_print_info = board->board[current_coords.row][current_coords.col];
    PrintInfo cursor_print_info = CURSOR_PRINT_INFO;

    sequence valid_keypresses[] = {
        CTTY_1,
        CTTY_2,
        CTTY_3,
        CTTY_4,
        CTTY_5,
        CTTY_6,
        CTTY_7,
        CTTY_8,
        CTTY_9,
        CTTY_0,
        CTTY_a,
        CTTY_b,
        CTTY_c,
        CTTY_d,
        CTTY_e,
        CTTY_f,
        CTTY_g,
        CTTY_h,
        CTTY_i,
        CTTY_j,
     	CTTY_UP,
        CTTY_DOWN,
        CTTY_LEFT,
        CTTY_RIGHT,
        CTTY_ENTER,
    };
    Keypress keypress = -1;
    board->print_board(board);

    printf(CURSOR_OFF);
    board->board[current_coords.row][current_coords.col] = cursor_print_info;
    board->reprint_symbol(board, current_coords.row, current_coords.col);
    do {

        // moving the cursor in the direction the user selects
        keypress = (Keypress) select_char(valid_keypresses, 25);
        next_coords = move_cursor(current_coords, keypress);

        if (next_coords.row != current_coords.row || next_coords.col != current_coords.col) {


            // resetting the formatting at the current cursor position
            board->board[current_coords.row][current_coords.col] = spot_print_info;
            board->reprint_symbol(board, current_coords.row, current_coords.col);
            current_coords = next_coords;

            // saving print info at the spot and printing the cursor there
        	spot_print_info = board->board[current_coords.row][current_coords.col];
        	board->board[current_coords.row][current_coords.col] = cursor_print_info;
        	board->reprint_symbol(board, current_coords.row, current_coords.col);
        }
    } while (!(keypress == Enter && spot_print_info.symbol == ' '));
    printf(CURSOR_ON);
    return current_coords;
}

ShotCoords normalize_spot(ShotCoords spot, int max_row, int max_col) {
    if (spot.row < 0) {
        spot.row = 0;
    }
    else if (spot.row > max_row) {
        spot.row = max_row;
    }
    if (spot.col < 0) {
        spot.col = 0;
    }
    else if (spot.col > max_col) {
        spot.col = max_col;
    }
    return spot;
}

static ShotCoords move_cursor(ShotCoords cursor_pos, Keypress keypress) {
    switch (keypress) {
        case Key_1: case Key_2: case Key_3: case Key_4: case Key_5: case Key_6: case Key_7: case Key_8: case Key_9: case Key_0:
            cursor_pos.col = (int) keypress;
            return cursor_pos;
            break;
        case Key_a: case Key_b: case Key_c: case Key_d: case Key_e: case Key_f: case Key_g: case Key_h: case Key_i: case Key_j:
            cursor_pos.row = (int) keypress - 10;
            return cursor_pos;
            break;
        case ArrowUp:
            --(cursor_pos.row);
            return normalize_spot(cursor_pos, 9, 9);
            break;
        case ArrowDown:
            ++(cursor_pos.row);
            return normalize_spot(cursor_pos, 9, 9);
            break;
        case ArrowLeft:
            --(cursor_pos.col);
            return normalize_spot(cursor_pos, 9, 9);
            break;
        case ArrowRight:
            ++(cursor_pos.col);
            return normalize_spot(cursor_pos, 9, 9);
            break;
        case Enter:
            return cursor_pos;
            break;
    }
}