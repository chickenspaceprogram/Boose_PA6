#ifndef BOARD_H
#define BOARD_H


/*
This is some very cursed graphics programming, sorry if it's darn near unintelligible.
*/

#include "../ctty/ansi/colors.h"
#include "../ctty/ansi/cursor.h"
#include "../ctty/ansi/text-modes.h"

#define BOARD_SIZE 10
#define CELL_WIDTH 3
#define CELL_HEIGHT 1
#define NUMS_OFFSET 1

#define MSG_START_ROW 3
#define MSG_START_COL 47

typedef enum {
    Ships,
    Shots,
} BoardType;

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

#endif