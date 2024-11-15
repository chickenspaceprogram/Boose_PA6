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
    SpaceHasDestroyer = 0,
    SpaceHasSubmarine,
    SpaceHasCruiser,
    SpaceHasBattleship,
    SpaceHasCarrier,
    SpaceHasNone,
} ShipsInSpace;

typedef enum {
    ShotNone = 0,
    ShotHit,
    ShotMiss,
} ShotsInSpace;

typedef struct {
    Color bg_color[3];
    Color fg_color[3];
    char symbol[3];
    ShipsInSpace ship;
    ShotsInSpace shot;
} PrintInfo;

typedef enum {
    ShotMsg,
    ManualPlacement,
    AutoPlacement,
    ShipView,
} BoardMsg;


typedef struct board Board;

// doing OOP in regular C was a bad idea but is very funny
struct board {
    PrintInfo board[BOARD_SIZE][BOARD_SIZE];
    Position start_position;

    /**
     * Function name: Board->print_board
     * Date created: 31 Oct 2024
     * Date last modified: 1 Nov 2024
     * Description: Prints the board.
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

    /**
     * Function name: print_message
     * Date created: 31 Oct 2024
     * Date last modified: 31 Oct 2024
     * Description: Prints a message to accompany the board.
     * Inputs: 
     * `Board *` : The `Board` struct you want to print
     * Outputs: none
     */
    void (*print_message)(Board *);

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
    void (*set_print_message)(Board *, BoardMsg);
};

/**
 * Function name: newBoard
 * Date created: 31 Oct 2024
 * Date last modified: 12 Nov 2024
 * Description: Creates a new, empty board.
 * Inputs: 
 * `msg` : An enum containing the message that should be printed with the board.
 * Outputs: The created board.
 */
Board newBoard(BoardMsg msg);

/**
 * Function name: set_hit_print_info
 * Date created: 6 Nov 2024
 * Date last modified: 14 Nov 2024
 * Description: Sets the values of a PrintInfo struct such that it is a hit.
 * Inputs: 
 * `spot_print_info` : The PrintInfo struct whose values you want to set.
 * Outputs: The PrintInfo struct with its values set such that it is a hit.
 */
PrintInfo set_hit_print_info(PrintInfo spot_print_info);

/**
 * Function name: set_miss_print_info
 * Date created: 6 Nov 2024
 * Date last modified: 14 Nov 2024
 * Description: Sets the values of a PrintInfo struct such that it is a miss.
 * Inputs: 
 * `spot_print_info` : The PrintInfo struct whose values you want to set.
 * Outputs: The PrintInfo struct with its values set such that it is a miss.
 */
PrintInfo set_miss_print_info(PrintInfo spot_print_info);

/**
 * Function name: print_shot_message
 * Date created: 2 Nov 2024
 * Date last modified: 2 Nov 2024
 * Description: Prints the message that accompanies the board where the user picks a space to shoot at.
 * Inputs:
 * `board` : The board whose shot message you want to print.
 * Outputs: none
 */
void print_shot_message(Board *board);

/**
 * Function name: print_ship_placement_message
 * Date created: 2 Nov 2024
 * Date last modified: 2 Nov 2024
 * Description: Prints the message that accompanies the board where the user picks locations for their ships.
 * Inputs: 
 * `board` : The board accompanying the message.
 * Outputs: none
 */
void print_ship_placement_message(Board *board);

/**
 * Function name: print_rand_ship_message
 * Date created: 7 Nov 2024
 * Date last modified: 7 Nov 2024
 * Description: Prints the message that accompanies the board where the user picks locations for their ships.
 * Inputs:
 * `board` : The board accompanying the message.
 * Outputs: none
 */
void print_rand_ship_message(Board *board);

/**
 * Function name: print_board_disp_message
 * Date created: 7 Nov 2024
 * Date last modified: 7 Nov 2024
 * Description: Prints the message that accompanies the board where the user picks locations for their ships.
 * Inputs: 
 * `board` : The board accompanying the message.
 * Outputs: none
 */
void print_board_disp_message(Board *board);

/**
 * Function name: print_ship_status_message
 * Date created: 12 Nov 2024
 * Date last modified: 12 Nov 2024
 * Description: Prints the message that accompanies the board when the user is viewing the status of their ships.
 * Inputs: 
 * `board` : The board accompanying the message.
 * Outputs: none
 */
void print_ship_status_message(Board *board);

#endif