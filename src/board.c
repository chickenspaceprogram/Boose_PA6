#include "board.h"

typedef enum row_types {
    Top,
    Middle,
    Bottom,
} RowTypes;

/**
 * Function name: print_shots_board
 * Date created: 31 Oct 2024
 * Date last modified: 31 Oct 2024
 * Description: Prints a ShotsBoard.
 * Inputs: The board to be printed.
 * Outputs: none
 */
static void print_shots_board(Board *board);

/**
 * Function name: print_ships_board
 * Date created: 31 Oct 2024
 * Date last modified: 31 Oct 2024
 * Description: Prints a ShipsBoard.
 * Inputs: The board to be printed.
 * Outputs: none
 */
static void print_ships_board(Board *board);

/**
 * Function name: print_board_skeleton
 * Date created: 31 Oct 2024
 * Date last modified: 31 Oct 2024
 * Description: Prints the outline of a board.
 * Inputs: none
 * Outputs: none
 */
static void print_board_skeleton(void);

/**
 * Function name: 
 * Date created: 31 Oct 2024
 * Date last modified: 31 Oct 2024
 * Description: Prints a solid, horizontal row. Assumes the terminal is already in draw mode.
 * Inputs: none
 * Outputs: none
 */
static void print_solid_row(RowTypes type);

/**
 * Function name: 
 * Date created: 31 Oct 2024
 * Date last modified: 31 Oct 2024
 * Description: 
 * Inputs: 
 * Outputs: 
 */
static void print_dashed_row(void);

/* Public methods */

void BoardFactory(Board *board_ptr, BoardType type) {
    
    board_ptr->type = type;

    switch (type) {
        case ShotsBoard:
            board_ptr->print_board = (void (*)(Board *)) &print_shots_board;
            for (int i = 0; i < BOARD_SIZE; ++i) {
                for (int j = 0; j < BOARD_SIZE; ++j) {
                    board_ptr->board[i][j] = (int) (Shots) NoShot;
                }
            }
            break;
        case ShipsBoard:
            board_ptr->print_board = (void (*)(Board *)) &print_ships_board;
            for (int i = 0; i < BOARD_SIZE; ++i) {
                for (int j = 0; j < BOARD_SIZE; ++j) {
                    board_ptr->board[i][j] = (int) (Ships) NoShip;
                }
            }
            break;
    }
}


void print_shots_board(Board *board) {
    print_board_skeleton();
}

void print_ships_board(Board *board) {
    print_board_skeleton();
}

/* Private methods */

void print_board_skeleton(void) {
    printf(MODE_DRAW);
    CURSOR_DOWN_LINE_START(CELL_HEIGHT + 1);
    print_solid_row(Top);
    for (int i = 0; i < BOARD_SIZE - 1; ++i) {
        print_dashed_row();
        print_solid_row(Middle);
    }
    print_dashed_row();
    print_solid_row(Bottom);
    printf(MODE_DRAW_RESET);
}

void print_solid_row(RowTypes type) {
    CURSOR_TO_COL(CELL_WIDTH + 2);

    char left_side_char, middle_char, right_side_char;
    switch(type) {
        case Top:
            left_side_char = 'l';
            middle_char = 'w';
            right_side_char = 'k';
            break;
        case Middle:
            left_side_char = 't';
            middle_char = 'n';
            right_side_char = 'u';
            break;
        case Bottom:
            left_side_char = 'm';
            middle_char = 'v';
            right_side_char = 'j';
            break;
    }
    putchar(left_side_char);
    for (int i = 0; i < BOARD_SIZE - 1; ++i) { // don't want to print the last cell so that we can print a corner character
        for (int j = 0; j < CELL_WIDTH; ++j) {
            putchar('q');
        }
        putchar(middle_char);
    }
    for (int j = 0; j < CELL_WIDTH; ++j) {
        putchar('q');
    }
    putchar(right_side_char);
    putchar('\n');
}

void print_dashed_row(void) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        CURSOR_TO_COL((CELL_WIDTH + 1) * (i + 1) + 1);
        putchar('x');
    }
    CURSOR_TO_COL((CELL_WIDTH + 1) * (BOARD_SIZE + 1) + 1);
    putchar('x');
    putchar('\n');
}