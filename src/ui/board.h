#ifndef BOARD_H
#define BOARD_H

/*
This is some very cursed graphics programming, sorry if it's darn near unintelligible.
*/

#include "../ctty/ansi/colors.h"
#include "../ctty/ansi/cursor.h"
#include "../ctty/ansi/text-modes.h"

#include "../ctty/screen/screen.h"

#include "space-print-info.h"

#define BOARD_SIZE 10
#define CELL_WIDTH 3
#define CELL_HEIGHT 1
#define NUMS_OFFSET 1

#define MSG_START_ROW 3
#define MSG_START_COL 47

// a magic macro to make some functions here less ugly
#define CURSOR_TO_MSG_POS(row_offset)   CURSOR_TO_POSITION(board->start_position.row + MSG_START_ROW + row_offset, board->start_position.col + MSG_START_COL);

typedef enum {
    Ships,
    Shots,
} BoardType;

typedef struct {
    Color bg_color[3];
    Color fg_color[3];
    char symbol[3];
} PrintInfo;



typedef struct board Board;
// OOP in C is cursed but it felt natural here
struct board {
    PrintInfo board[BOARD_SIZE][BOARD_SIZE];
    Position start_position;

    /**
     * Function name: Board->print_board
     * Date created: 31 Oct 2024
     * Date last modified: 1 Nov 2024
     * Description: 
     * Inputs: 
     * `Board *` : The `Board` struct you want to print
     * Outputs: none
     */
    void (*print_board)(Board *);

    /**
     * Function name: Board->print_symbols
     * Date created: 31 Oct 2024
     * Date last modified: 1 Nov 2024
     * Description: Prints the symbols and colors to go on the board.
     * Inputs:
     * `Board *` : The `Board` struct you want to print
     * Outputs: none
     */
    void (*print_symbols)(const Board *);

    /**
     * Function name: Board->reprint_symbol
     * Date created: 31 Oct 2024
     * Date last modified: 1 Nov 2024
     * Description: Reprints the symbol at a specific location.
     * Inputs:
     * `Board *` : The `Board` struct you want to print
     *
     * Outputs: none
     */
    void (*reprint_symbol)(const Board *, const int, const int);

    void (*print_message)(Board *);
};

/**
 * Function name: newBoard
 * Date created: 31 Oct 2024
 * Date last modified: 1 Nov 2024
 * Description: Creates a new, empty board.
 * Inputs: none
 * Outputs: The created board.
 */
Board newBoard(BoardType type);

/**
 * Function name: 
 * Date created: 6 Nov 2024
 * Date last modified: 6 Nov 2024
 * Description: 
 * Inputs: 
 * Outputs: 
 */
PrintInfo set_hit_print_info(PrintInfo spot_print_info);

/**
 * Function name: 
 * Date created: 6 Nov 2024
 * Date last modified: 6 Nov 2024
 * Description: 
 * Inputs: 
 * Outputs: 
 */
PrintInfo set_miss_print_info(PrintInfo spot_print_info);


/**
 * Function name: print_shot_message
 * Date created: 2 Nov 2024
 * Date last modified: 2 Nov 2024
 * Description: Prints the message that accompanies the board where the user picks a space to shoot at.
 * Inputs: none
 * Outputs: none
 */
void print_shot_message(Board *board);

/**
 * Function name: print_ship_placement_message
 * Date created: 2 Nov 2024
 * Date last modified: 2 Nov 2024
 * Description: Prints the message that accompanies the board where the user picks locations for their ships.
 * Inputs: none
 * Outputs: none
 */
void print_ship_placement_message(Board *board);

/**
 * Function name: print_rand_ship_message
 * Date created: 7 Nov 2024
 * Date last modified: 7 Nov 2024
 * Description: Prints the message that accompanies the board where the user picks locations for their ships.
 * Inputs: none
 * Outputs: none
 */
void print_rand_ship_message(Board *board);

#endif