#ifndef BOARD_H
#define BOARD_H

#include "ctty/ansi/colors.h"
#include "ctty/ansi/cursor.h"
#include "ctty/ansi/text-modes.h"

#define BOARD_SIZE 10
#define CELL_WIDTH 3
#define CELL_HEIGHT 1
#define NUMS_OFFSET 1

typedef enum {
    None = 0,
    Black,
    Red,
    Green,
    Blue,
    Cyan,
    Magenta,
    White,
    BrightBlack,
    BrightRed,
    BrightGreen,
    BrightBlue,
    BrightCyan,
    BrightMagenta,
    BrightWhite,
} Color;

typedef struct {
    Color bg_color;
    Color fg_color;
    char symbol;
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
     * Description: Prints the board skeleton (everything except for the symbols and colors).
     * Inputs: 
     * `struct board *` : The `Board` struct you want to print
     * Outputs: none
     */
    void (*print_board)(Board *);

    /**
     * Function name: Board->print_symbols
     * Date created: 31 Oct 2024
     * Date last modified: 1 Nov 2024
     * Description: Prints the symbols and colors to go on the board.
     * Inputs:
     * `struct board *` : The `Board` struct you want to print
     * Outputs: none
     */
    void (*print_symbols)(const Board *);
};

/**
 * Function name: newBoard
 * Date created: 31 Oct 2024
 * Date last modified: 1 Nov 2024
 * Description: Creates a new, empty board.
 * Inputs: none
 * Outputs: The created board.
 */
Board newBoard(void);

#endif