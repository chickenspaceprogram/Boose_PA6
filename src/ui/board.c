#include "board.h"


typedef enum row_types {
    Top,
    Middle,
    Bottom,
} RowTypes;

/* Public Method Declarations */

/**
 * Function name: 
 * Date created: 1 Nov 2024
 * Date last modified: 1 Nov 2024
 * Description: 
 * Inputs: 
 * Outputs: 
 */
void print_board(Board *board);

/**
 * Function name: Board->print_symbols
 * Date created: 31 Oct 2024
 * Date last modified: 1 Nov 2024
 * Description: Prints the symbols and colors to go on the board.
 * Inputs:
 * `Board *` : The `Board` struct you want to print
 * Outputs: none
 */
void print_symbols(const Board *board);

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
void reprint_symbol(const Board *board, int row, int col);

/**
 * Function name: set_print_message
 * Date created: 12 Nov 2024
 * Date last modified: 12 Nov 2024
 * Description: Sets print_message to the appropriate message.
 * Inputs: 
 * `Board *` : The `Board` struct you want to print.
 * `BoardMsg` : An enum representing the message you want printed alongside the board.
 * Outputs: none
 */
void set_print_message(Board *board, BoardMsg msg);

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

Board newBoard(BoardMsg msg) {
    Board board;
    PrintInfo blank_info = BLANK_PRINT_INFO;

    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board.board[i][j] = blank_info;
        }
    }

    board.start_position = cursor_get_position();
    board.print_board = &print_board;
    board.print_symbols = &print_symbols;
    board.reprint_symbol = &reprint_symbol;
    board.set_print_message = &set_print_message;
    printf("%p", board.set_print_message);
    board.set_print_message(&board, msg);
    return board;
}

void print_board(Board *board) {
    fputs(CURSOR_OFF, stdout);
    print_board_outline(board);
    board->print_symbols(board);
    board->print_message(board);
    fputs(CURSOR_ON, stdout);
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

void reprint_symbol(const Board *board, const int row, const int col) {
    CURSOR_TO_POSITION(board->start_position.row + (row + 1) * (CELL_HEIGHT + 1) + 1, board->start_position.col + (col + 1) * (CELL_WIDTH + 1));

    for (int i = 0; i < CELL_WIDTH; ++i) {
        set_color(board->board[row][col].fg_color[i], board->board[row][col].bg_color[i]);
        putchar(board->board[row][col].symbol[i]);
    }
    set_color(Default, Default);
    CURSOR_LEFT(1); // dont remember why this has to be here, but it breaks without it :)
}

PrintInfo set_hit_print_info(PrintInfo spot_print_info) {
    spot_print_info.bg_color[1] = HIT_BG_COLOR;
    spot_print_info.fg_color[1] = HIT_FG_COLOR;
    spot_print_info.symbol[1] = HIT_SYMBOL;
    return spot_print_info;
}

PrintInfo set_miss_print_info(PrintInfo spot_print_info) {
    spot_print_info.bg_color[1] = MISS_BG_COLOR;
    spot_print_info.fg_color[1] = MISS_FG_COLOR;
    spot_print_info.symbol[1] = MISS_SYMBOL;
    return spot_print_info;
}

void set_print_message(Board *board, BoardMsg msg) {
    switch (msg) {
        case ShotMsg:
            board->print_message = &print_shot_message;
            break;
        case ManualPlacement:
            board->print_message = &print_ship_placement_message;
            break;
        case AutoPlacement:
            board->print_message = &print_rand_ship_message;
            break;
        case ShipView:
            board->print_message = &print_ship_status_message;
            break;
    }
}


/* Private methods */

static void print_board_skeleton(void) {
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

static void print_solid_row(RowTypes type) {
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

static void print_dashed_row(void) {
    CURSOR_DOWN_LINE_START(1);
    for (int i = 0; i < BOARD_SIZE; ++i) {
        CURSOR_RIGHT(CELL_WIDTH);
        putchar('x');
    }
    CURSOR_RIGHT(CELL_WIDTH);
    putchar('x');
}

static void print_numbers(void) {
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

static void print_letters(void) {
    CURSOR_DOWN(CELL_HEIGHT);
    for (int i = 0; i < BOARD_SIZE; ++i) {
        CURSOR_DOWN_LINE_START(CELL_HEIGHT + 1);
        CURSOR_RIGHT(1);
        putchar(i + 'A');
    }
}



/* Message printing functions */

/* the code beyond this point is terrible, but i couldn't think of a better way to do it */

void print_shot_message(Board *board) {
    // printing text
    CURSOR_TO_MSG_POS(0);
    fputs("Select a spot you haven't fired", stdout);
    CURSOR_TO_MSG_POS(1);
    fputs("at before using either the", stdout);
    CURSOR_TO_MSG_POS(2);
    fputs("arrow keys or keys 1-0 and a-j,", stdout);
    CURSOR_TO_MSG_POS(3);
    fputs("then press [Enter].", stdout);
    CURSOR_TO_MSG_POS(5);
    fputs("Key:", stdout);

    // printing "Hit" box
    CURSOR_TO_MSG_POS(7);
    fputs(MODE_DRAW"lqqqk", stdout);
    CURSOR_TO_MSG_POS(8);
    fputs("x"MODE_DRAW_RESET, stdout);
    putchar(' ');
    set_color(HIT_FG_COLOR, HIT_BG_COLOR);
    putchar(HIT_SYMBOL);
    set_color(Default, Default);
    putchar(' ');
    fputs(MODE_DRAW"x"MODE_DRAW_RESET" : Hit", stdout);
    CURSOR_TO_MSG_POS(9);
    fputs(MODE_DRAW"mqqqj", stdout);

    // printing "Miss" box
    CURSOR_TO_MSG_POS(11);
    fputs(MODE_DRAW"lqqqk", stdout);
    CURSOR_TO_MSG_POS(12);
    fputs("x"MODE_DRAW_RESET, stdout);
    putchar(' ');
    set_color(MISS_FG_COLOR, MISS_BG_COLOR);
    putchar('m');
    set_color(Default, Default);
    putchar(' ');
    fputs(MODE_DRAW"x"MODE_DRAW_RESET" : Miss", stdout);
    CURSOR_TO_MSG_POS(13);
    fputs(MODE_DRAW"mqqqj", stdout);

    CURSOR_TO_MSG_POS(15);
    fputs(MODE_DRAW"lqqqk", stdout);
    CURSOR_TO_MSG_POS(16);
    fputs("x"MODE_DRAW_RESET"   "MODE_DRAW"x"MODE_DRAW_RESET" : No shot made", stdout);
    CURSOR_TO_MSG_POS(17);
    fputs(MODE_DRAW"mqqqj"MODE_DRAW_RESET, stdout);

}

void print_ship_placement_message(Board *board) {
    CURSOR_TO_MSG_POS(0);

    // printing msg txt  
    fputs("Use the arrow keys to move each", stdout);
    CURSOR_TO_MSG_POS(1);
    fputs("ship to the desired position.", stdout);
    CURSOR_TO_MSG_POS(2);
    fputs("Press [Space] to change the", stdout);
    CURSOR_TO_MSG_POS(3);
    fputs("orientation of the ship, and", stdout);
    CURSOR_TO_MSG_POS(4);
    fputs("press [Enter] to place the", stdout);
    CURSOR_TO_MSG_POS(5);
    fputs("ship at the selected location.", stdout);

    // printing ship types
    CURSOR_TO_MSG_POS(7);
    fputs("Ship types:", stdout);

    CURSOR_TO_MSG_POS(9);
    fputs(MODE_DRAW"lqqqk", stdout);
    CURSOR_TO_MSG_POS(10);

    fputs("x"MODE_DRAW_RESET, stdout);
    set_color(DESTROYER_FG_COLOR, DESTROYER_BG_COLOR);
    fputs(DESTROYER_SYMBOL, stdout);
    set_color(NO_COLOR, NO_COLOR);
    fputs(MODE_DRAW"x"MODE_DRAW_RESET" : Destroyer", stdout);
    
    CURSOR_TO_MSG_POS(11);
    fputs(MODE_DRAW"tqqqu", stdout);
    CURSOR_TO_MSG_POS(12);

    fputs("x"MODE_DRAW_RESET, stdout);
    set_color(SUBMARINE_FG_COLOR, SUBMARINE_BG_COLOR);
    fputs(SUBMARINE_SYMBOL, stdout);
    set_color(NO_COLOR, NO_COLOR);
    fputs(MODE_DRAW"x"MODE_DRAW_RESET" : Submarine", stdout);

    CURSOR_TO_MSG_POS(13);
    fputs(MODE_DRAW"tqqqu", stdout);
    CURSOR_TO_MSG_POS(14);

    fputs("x"MODE_DRAW_RESET, stdout);
    set_color(CRUISER_FG_COLOR, CRUISER_BG_COLOR);
    fputs(CRUISER_SYMBOL, stdout);
    set_color(NO_COLOR, NO_COLOR);
    fputs(MODE_DRAW"x"MODE_DRAW_RESET" : Cruiser", stdout);

    CURSOR_TO_MSG_POS(15);
    fputs(MODE_DRAW"tqqqu", stdout);
    CURSOR_TO_MSG_POS(16);

    fputs("x"MODE_DRAW_RESET, stdout);
    set_color(BATTLESHIP_FG_COLOR, BATTLESHIP_BG_COLOR);
    fputs(BATTLESHIP_SYMBOL, stdout);
    set_color(NO_COLOR, NO_COLOR);
    fputs(MODE_DRAW"x"MODE_DRAW_RESET" : Battleship", stdout);

    CURSOR_TO_MSG_POS(17);
    fputs(MODE_DRAW"tqqqu", stdout);
    CURSOR_TO_MSG_POS(18);


    fputs("x"MODE_DRAW_RESET, stdout);
    set_color(CARRIER_FG_COLOR, CARRIER_BG_COLOR);
    fputs(CARRIER_SYMBOL, stdout);
    set_color(NO_COLOR, NO_COLOR);
    fputs(MODE_DRAW"x"MODE_DRAW_RESET" : Carrier", stdout);

    CURSOR_TO_MSG_POS(19);
    fputs(MODE_DRAW"mqqqj"MODE_DRAW_RESET, stdout);

}

void print_rand_ship_message(Board *board) {
    CURSOR_TO_MSG_POS(0);

    // printing msg txt  
    fputs("Your ships have been randomly", stdout);
    CURSOR_TO_MSG_POS(1);
    fputs("placed in the locations", stdout);
    CURSOR_TO_MSG_POS(2);
    fputs("displayed here. Press any key", stdout);
    CURSOR_TO_MSG_POS(3);
    fputs("to continue . . .", stdout);

    // printing ship types
    CURSOR_TO_MSG_POS(6);
    fputs("Ship types:", stdout);

    CURSOR_TO_MSG_POS(7);
    fputs(MODE_DRAW"lqqqk", stdout);
    CURSOR_TO_MSG_POS(8);

    fputs("x"MODE_DRAW_RESET, stdout);
    set_color(DESTROYER_FG_COLOR, DESTROYER_BG_COLOR);
    fputs(DESTROYER_SYMBOL, stdout);
    set_color(NO_COLOR, NO_COLOR);
    fputs(MODE_DRAW"x"MODE_DRAW_RESET" : Destroyer", stdout);
    
    CURSOR_TO_MSG_POS(9);
    fputs(MODE_DRAW"tqqqu", stdout);
    CURSOR_TO_MSG_POS(10);

    fputs("x"MODE_DRAW_RESET, stdout);
    set_color(SUBMARINE_FG_COLOR, SUBMARINE_BG_COLOR);
    fputs(SUBMARINE_SYMBOL, stdout);
    set_color(NO_COLOR, NO_COLOR);
    fputs(MODE_DRAW"x"MODE_DRAW_RESET" : Submarine", stdout);

    CURSOR_TO_MSG_POS(11);
    fputs(MODE_DRAW"tqqqu", stdout);
    CURSOR_TO_MSG_POS(12);

    fputs("x"MODE_DRAW_RESET, stdout);
    set_color(CRUISER_FG_COLOR, CRUISER_BG_COLOR);
    fputs(CRUISER_SYMBOL, stdout);
    set_color(NO_COLOR, NO_COLOR);
    fputs(MODE_DRAW"x"MODE_DRAW_RESET" : Cruiser", stdout);

    CURSOR_TO_MSG_POS(13);
    fputs(MODE_DRAW"tqqqu", stdout);
    CURSOR_TO_MSG_POS(14);

    fputs("x"MODE_DRAW_RESET, stdout);
    set_color(BATTLESHIP_FG_COLOR, BATTLESHIP_BG_COLOR);
    fputs(BATTLESHIP_SYMBOL, stdout);
    set_color(NO_COLOR, NO_COLOR);
    fputs(MODE_DRAW"x"MODE_DRAW_RESET" : Battleship", stdout);

    CURSOR_TO_MSG_POS(15);
    fputs(MODE_DRAW"tqqqu", stdout);
    CURSOR_TO_MSG_POS(16);


    fputs("x"MODE_DRAW_RESET, stdout);
    set_color(CARRIER_FG_COLOR, CARRIER_BG_COLOR);
    fputs(CARRIER_SYMBOL, stdout);
    set_color(NO_COLOR, NO_COLOR);
    fputs(MODE_DRAW"x"MODE_DRAW_RESET" : Carrier", stdout);

    CURSOR_TO_MSG_POS(17);
    fputs(MODE_DRAW"mqqqj"MODE_DRAW_RESET, stdout);

}

void print_ship_status_message(Board *board) {

    CURSOR_TO_MSG_POS(0);

    // printing msg txt  
    fputs("Here is the current status of", stdout);
    CURSOR_TO_MSG_POS(1);
    fputs("your ships. Press any key to", stdout);
    CURSOR_TO_MSG_POS(2);
    fputs("continue . . .", stdout);

    // printing ship types
    CURSOR_TO_MSG_POS(4);
    fputs("Key:", stdout);

    CURSOR_TO_MSG_POS(5);
    fputs(MODE_DRAW"lqqqk", stdout);
    CURSOR_TO_MSG_POS(6);

    fputs("x"MODE_DRAW_RESET, stdout);
    set_color(DESTROYER_FG_COLOR, DESTROYER_BG_COLOR);
    fputs(DESTROYER_SYMBOL, stdout);
    set_color(NO_COLOR, NO_COLOR);
    fputs(MODE_DRAW"x"MODE_DRAW_RESET" : Destroyer", stdout);
    
    CURSOR_TO_MSG_POS(7);
    fputs(MODE_DRAW"tqqqu", stdout);
    CURSOR_TO_MSG_POS(8);

    fputs("x"MODE_DRAW_RESET, stdout);
    set_color(SUBMARINE_FG_COLOR, SUBMARINE_BG_COLOR);
    fputs(SUBMARINE_SYMBOL, stdout);
    set_color(NO_COLOR, NO_COLOR);
    fputs(MODE_DRAW"x"MODE_DRAW_RESET" : Submarine", stdout);

    CURSOR_TO_MSG_POS(9);
    fputs(MODE_DRAW"tqqqu", stdout);
    CURSOR_TO_MSG_POS(10);

    fputs("x"MODE_DRAW_RESET, stdout);
    set_color(CRUISER_FG_COLOR, CRUISER_BG_COLOR);
    fputs(CRUISER_SYMBOL, stdout);
    set_color(NO_COLOR, NO_COLOR);
    fputs(MODE_DRAW"x"MODE_DRAW_RESET" : Cruiser", stdout);

    CURSOR_TO_MSG_POS(11);
    fputs(MODE_DRAW"tqqqu", stdout);
    CURSOR_TO_MSG_POS(12);

    fputs("x"MODE_DRAW_RESET, stdout);
    set_color(BATTLESHIP_FG_COLOR, BATTLESHIP_BG_COLOR);
    fputs(BATTLESHIP_SYMBOL, stdout);
    set_color(NO_COLOR, NO_COLOR);
    fputs(MODE_DRAW"x"MODE_DRAW_RESET" : Battleship", stdout);

    CURSOR_TO_MSG_POS(13);
    fputs(MODE_DRAW"tqqqu", stdout);
    CURSOR_TO_MSG_POS(14);


    fputs("x"MODE_DRAW_RESET, stdout);
    set_color(CARRIER_FG_COLOR, CARRIER_BG_COLOR);
    fputs(CARRIER_SYMBOL, stdout);
    set_color(NO_COLOR, NO_COLOR);
    fputs(MODE_DRAW"x"MODE_DRAW_RESET" : Carrier", stdout);

    CURSOR_TO_MSG_POS(15);
    fputs(MODE_DRAW"mqqqj"MODE_DRAW_RESET, stdout);

    CURSOR_TO_MSG_POS(17);
    fputs(MODE_DRAW"lqqqk", stdout);
    CURSOR_TO_MSG_POS(18);

    fputs("x"MODE_DRAW_RESET, stdout);
    putchar(' ');
    set_color(HIT_FG_COLOR, HIT_BG_COLOR);
    putchar(HIT_SYMBOL);
    set_color(NO_COLOR, NO_COLOR);
    putchar(' ');
    fputs(MODE_DRAW"x"MODE_DRAW_RESET" : Hit", stdout);
    
    CURSOR_TO_MSG_POS(19);
    fputs(MODE_DRAW"tqqqu", stdout);
    CURSOR_TO_MSG_POS(20);

    fputs("x"MODE_DRAW_RESET, stdout);
    putchar(' ');
    set_color(MISS_FG_COLOR, MISS_BG_COLOR);
    putchar(MISS_SYMBOL);
    set_color(NO_COLOR, NO_COLOR);
    putchar(' ');
    fputs(MODE_DRAW"x"MODE_DRAW_RESET" : Miss", stdout);

    CURSOR_TO_MSG_POS(21);
    fputs(MODE_DRAW"mqqqj"MODE_DRAW_RESET, stdout);
}