#include "board.h"

// basically just a magic macro to make some functions here less ugly
#define CURSOR_TO_MSG_POS(row_offset)   CURSOR_TO_POSITION(board->start_position.row + MSG_START_ROW + row_offset, board->start_position.col + MSG_START_COL);

typedef enum row_types {
    Top,
    Middle,
    Bottom,
} RowTypes;

/* Public Method Declarations */

static void print_board(Board *board);

/**
 * Function name: Board->print_symbols
 * Date created: 31 Oct 2024
 * Date last modified: 1 Nov 2024
 * Description: Prints the symbols and colors to go on the board.
 * Inputs:
 * `Board *` : The `Board` struct you want to print
 * Outputs: none
 */
static void print_symbols(const Board *board);

/**
 * Function name: Board->reprint_symbol
 * Date created: 31 Oct 2024
 * Date last modified: 1 Nov 2024
 * Description: Reprints the symbol at a specific location.
 * Inputs:
 * `Board *` : Reprints the symbol at a specific location.
 * `row` : The row of the symbol you want to reprint.
 * `col` : The column of the symbol you want to reprint.
 * Outputs: none
 */
static void reprint_symbol(const Board *board, int row, int col);

/**
 * Function name: print_shot_message
 * Date created: 2 Nov 2024
 * Date last modified: 2 Nov 2024
 * Description: Prints the message that accompanies the board where the user picks a space to shoot at.
 * Inputs: none
 * Outputs: none
 */
static void print_shot_message(Board *board);

/**
 * Function name: print_ship_message
 * Date created: 2 Nov 2024
 * Date last modified: 2 Nov 2024
 * Description: Prints the message that accompanies the board where the user picks locations for their ships.
 * Inputs: none
 * Outputs: none
 */
static void print_ship_message(Board *board);


/* Private Method Declarations */

/**
 * Function name: print_board
 * Date created: 31 Oct 2024
 * Date last modified: 1 Nov 2024
 * Description: Prints the board, except for the symbols and colors.
 * Inputs:
 * `Board *` : The `Board` struct you want to print
 * Outputs: none
 */
static void print_board_outline(Board *board);

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

Board newBoard(BoardType type) {
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
    board.reprint_symbol = &reprint_symbol;
    switch (type) {
        case Ships:
            board.print_message = &print_ship_message;
            break;
        case Shots:
            board.print_message = &print_shot_message;
            break;
    }
    return board;
}

static void print_board(Board *board) {
    print_board_outline(board);
    board->print_symbols(board);
    board->print_message(board);
}

void print_board_outline(Board *board) {
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
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            reprint_symbol(board, i, j);
        }
    }
}

static void reprint_symbol(const Board *board, const int row, const int col) {
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
    CURSOR_TO_POSITION(board->start_position.row + (row + 1) * (CELL_HEIGHT + 1) + 1, board->start_position.col + (col + 1) * (CELL_WIDTH + 1) + 1);
    printf("%s", bg_colors[(int) board->board[row][col].bg_color]);
    printf("%s", fg_colors[(int) board->board[row][col].fg_color]);
    putchar(board->board[row][col].symbol);
    printf(BG_DEFAULT FG_DEFAULT); // C concatenates string literals automatically
}

void print_shot_message(Board *board) {
    // this is pretty cursed and messy. however, it does work!

    // printing text
    CURSOR_TO_MSG_POS(0);
    printf("Select a spot you haven't fired");
    CURSOR_TO_MSG_POS(1);
    printf("at before using either the");
    CURSOR_TO_MSG_POS(2);
    printf("arrow keys or keys 1-0 and a-j,");
    CURSOR_TO_MSG_POS(3);
    printf("then press [Enter].");
    CURSOR_TO_MSG_POS(5);
    printf("Key:");

    // printing "Hit" box
    CURSOR_TO_MSG_POS(7);
    printf(MODE_DRAW"lqqqk");
    CURSOR_TO_MSG_POS(8);
    printf("x"MODE_DRAW_RESET" * "MODE_DRAW"x"MODE_DRAW_RESET" : Hit");
    CURSOR_TO_MSG_POS(9);
    printf(MODE_DRAW"mqqqj");

    // printing "Miss" box
    CURSOR_TO_MSG_POS(11);
    printf(MODE_DRAW"lqqqk");
    CURSOR_TO_MSG_POS(12);
    printf("x"MODE_DRAW_RESET" m "MODE_DRAW"x"MODE_DRAW_RESET" : Miss");
    CURSOR_TO_MSG_POS(13);
    printf(MODE_DRAW"mqqqj");

    CURSOR_TO_MSG_POS(15);
    printf(MODE_DRAW"lqqqk");
    CURSOR_TO_MSG_POS(16);
    printf("x"MODE_DRAW_RESET"   "MODE_DRAW"x"MODE_DRAW_RESET" : No shot made");
    CURSOR_TO_MSG_POS(17);
    printf(MODE_DRAW"mqqqj"MODE_DRAW_RESET);

}

void print_ship_message(Board *board) {}

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