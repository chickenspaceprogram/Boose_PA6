#include "board.h"
#include "ctty/ansi/cursor.h"

typedef enum row_types {
    Top,
    Middle,
    Bottom,
} RowTypes;

/**
 * Function name: print_board
 * Date created: 31 Oct 2024
 * Date last modified: 1 Nov 2024
 * Description: Prints the board skeleton (everything except for the symbols and colors).
 * Inputs:
 * `struct board *` : The `Board` struct you want to print
 * Outputs: none
 */
static void print_board(Board *board);

/**
 * Function name: Board->print_symbols
 * Date created: 31 Oct 2024
 * Date last modified: 1 Nov 2024
 * Description: Prints the symbols and colors to go on the board.
 * Inputs:
 * `struct board *` : The `Board` struct you want to print
 * Outputs: none
 */
static void print_symbols(const Board *board);

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
 * Function name: print_dashed_row
 * Date created: 31 Oct 2024
 * Date last modified: 31 Oct 2024
 * Description: 
 * Inputs: none
 * Outputs: none
 */
static void print_dashed_row(void);

/**
 * Function name: print_numbers
 * Date created: 1 Nov 2024
 * Date last modified: 1 Nov 2024
 * Description: expects to be on the row below the last row
 * Inputs: none
 * Outputs: none
 */
static void print_numbers(void);

/**
 * Function name: print_letters
 * Date created: 1 Nov 2024
 * Date last modified: 1 Nov 2024
 * Description: expects to be on the numbers row
 * Inputs: none
 * Outputs: none
 */
static void print_letters(void);

/* Public methods */

Board newBoard(void) {
    Board board;
    PrintInfo blank_info = {.bg_color = None, .fg_color = None, .symbol = ' '};

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board.board[i][j] = blank_info;
        }
    }

    board.start_position = cursor_get_position();
    board.print_board = &print_board;
    board.print_symbols = &print_symbols;
    return board;
}


void print_board(Board *board) {
    board->start_position = cursor_get_position();
    CURSOR_DOWN_LINE_START(1);
    print_board_skeleton();
    CURSOR_TO_POSITION(board->start_position.row, board->start_position.col);
    print_numbers();
    CURSOR_TO_POSITION(board->start_position.row, board->start_position.col);
    print_letters();
    CURSOR_TO_POSITION(board->start_position.row, board->start_position.col);
}

void print_symbols(const Board *board) {
    const char *bg_colors[] = {
        BG_DEFAULT,
        BG_BLACK,
        BG_RED,
        BG_GREEN,
        BG_BLUE,
        BG_CYAN,
        BG_MAGENTA,
        BG_WHITE,
        BG_BLACK_BRIGHT,
        BG_RED_BRIGHT,
        BG_GREEN_BRIGHT,
        BG_BLUE_BRIGHT,
        BG_CYAN_BRIGHT,
        BG_MAGENTA_BRIGHT,
        BG_WHITE_BRIGHT,
    };
    const char *fg_colors[] = {
        FG_DEFAULT,
        FG_BLACK,
        FG_RED,
        FG_GREEN,
        FG_BLUE,
        FG_CYAN,
        FG_MAGENTA,
        FG_WHITE,
        FG_BLACK_BRIGHT,
        FG_RED_BRIGHT,
        FG_GREEN_BRIGHT,
        FG_BLUE_BRIGHT,
        FG_CYAN_BRIGHT,
        FG_MAGENTA_BRIGHT,
        FG_WHITE_BRIGHT,
    };

    CURSOR_TO_POSITION(board->start_position.row, board->start_position.col);
    CURSOR_DOWN(1);
    for (int i = 0; i < BOARD_SIZE; ++i) {
        CURSOR_DOWN_LINE_START(CELL_HEIGHT);
        CURSOR_RIGHT(1);
        for (int j = 0; j < BOARD_SIZE; ++j) {
            CURSOR_RIGHT(CELL_WIDTH);
            printf("%s", bg_colors[(int) board->board[i][j].bg_color]);
            printf("%s", fg_colors[(int) board->board[i][j].fg_color]);
            putchar(board->board[i][j].symbol);
            printf(BG_DEFAULT FG_DEFAULT); // C concatenates string literals automatically
        }
    }
}

/* Private methods */

void print_board_skeleton(void) {
    printf(MODE_DRAW);
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
    CURSOR_DOWN_LINE_START(1);
    CURSOR_RIGHT(CELL_WIDTH);
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
        default:
            return;
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
}

void print_dashed_row(void) {
    CURSOR_DOWN_LINE_START(1);
    for (int i = 0; i < BOARD_SIZE; ++i) {
        CURSOR_RIGHT(CELL_WIDTH);
        putchar('x');
    }
    CURSOR_RIGHT(CELL_WIDTH);
    putchar('x');
}

void print_numbers(void) {
    CURSOR_DOWN(CELL_HEIGHT);
    CURSOR_RIGHT(NUMS_OFFSET + 1);
    for (int i = 0; i < BOARD_SIZE; ++i) {
        CURSOR_RIGHT(CELL_WIDTH);
        if (i < 9) {
            putchar(i + 1 + '0');
        }
        else {
            putchar('0');
        }
    }
}

void print_letters(void) {
    CURSOR_DOWN(CELL_HEIGHT);
    for (int i = 0; i < BOARD_SIZE; ++i) {
        CURSOR_DOWN_LINE_START(CELL_HEIGHT + 1);
        CURSOR_RIGHT(1);
        putchar(i + 'A');
    }
}