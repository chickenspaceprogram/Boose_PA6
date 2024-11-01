#ifndef BOARD_H
#define BOARD_H

#include "ctty/ansi/colors.h"
#include "ctty/ansi/cursor.h"
#include "ctty/ansi/text-modes.h"

#define BOARD_SIZE 10
#define CELL_WIDTH 3
#define CELL_HEIGHT 1

typedef enum board_type {
    ShotsBoard,
    ShipsBoard,
} BoardType;

typedef enum ships {
    NoShip,
    Destroyer,
    Submarine,
    Cruiser,
    Battleship,
    Carrier,
} Ships;

typedef enum shots {
    NoShot,
    Miss,
    Hit,
} Shots;


typedef struct board Board;
// OOP in C is cursed but it felt very natural here
struct board {
    int board[BOARD_SIZE][BOARD_SIZE];
    BoardType type;

    /**
     * Function name: Board->print_board
     * Date created: 31 Oct 2024
     * Date last modified: 31 Oct 2024
     * Description: Prints the board.
     * Inputs: 
     * `struct board *` : The `Board` struct you want to print
     * Outputs: none
     */
    void (*print_board)(Board *);
};

/**
 * Function name: BoardFactory
 * Date created: 31 Oct 2024
 * Date last modified: 31 Oct 2024
 * Description: Instantiates a new Board of the desired BoardType.
 *              this is pretty cursed to do in C
 * Inputs: 
 * Outputs: none
 */
void BoardFactory(Board *board_ptr, BoardType type);

#endif