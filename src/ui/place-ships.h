#ifndef UI_PLACE_SHIPS_H
#define UI_PLACE_SHIPS_H

#include "../ctty/ansi/cursor.h"
#include "../ctty/keyselect.h"
#include "../ctty/keypress-codes.h"
#include "board.h"

typedef enum {
    Destroyer,
    Submarine,
    Cruiser,
    Battleship,
    Carrier,
} Ship;

#define NUM_SHIPS               5

#define DESTROYER_PRINT_INFO    {.bg_color = BrightGreen, .fg_color = BrightWhite, .symbol = 'd', .color_all_spaces = 1}
#define SUBMARINE_PRINT_INFO    {.bg_color = Yellow, .fg_color = BrightWhite, .symbol = 's', .color_all_spaces = 1}
#define CRUISER_PRINT_INFO      {.bg_color = BrightBlue, .fg_color = BrightWhite, .symbol = 'r', .color_all_spaces = 1}
#define BATTLESHIP_PRINT_INFO   {.bg_color = Magenta, .fg_color = BrightWhite, .symbol = 'b', .color_all_spaces = 1}
#define CARRIER_PRINT_INFO      {.bg_color = Cyan, .fg_color = BrightWhite, .symbol = 'c', .color_all_spaces = 1}

typedef enum {
    Horizontal,
    Vertical,
} Orientation;

typedef struct {
    Position position;
    Ship ship;
    Orientation orientation;
    int ship_is_hit;
} ShipInfo;

/**
 * Function name: place_ships
 * Date created: 3 Nov 2024
 * Date last modified: 3 Nov 2024
 * Description: Prompts the user to place their ships on the board.
 *              Stores the ships placed to `ships`.
 *              `ships` must have a length greater than or equal to `NUM_SHIPS`, otherwise the behavior of this function is undefined.
 * Inputs: 
 * `board` : The game board
 * `ships` : The array to store the ship positions in.
 * Outputs: none
 */
void place_ships(Board *board, ShipInfo *ships);

/**
 * Function name: place_single_ship
 * Date created: 3 Nov 2024
 * Date last modified: 3 Nov 2024
 * Description: Allows the user to place a single ship on the board.
 * Inputs: 
 * `board` : The game board.
 * `ship_info` : The current status of the ship.
 * Outputs: The ShipInfo of the ship that was placed.
 */
ShipInfo place_single_ship(Board *board, ShipInfo ship_info);

/**
 * Function name: spot_is_valid
 * Date created: 3 Nov 2024
 * Date last modified: 3 Nov 2024
 * Description: Checks if the spot where the ship described by `ship_info` overlaps any other ships.
 * Inputs: 
 * `board` : The game board.
 * `ship_info` : The current status of the ship.
 * Outputs: 0 if the spot is invalid, 1 if the spot is valid.
 */
int spot_is_valid(Board *board, ShipInfo ship_info);

/**
 * Function name: process_user_input
 * Date created: 3 Nov 2024
 * Date last modified: 3 Nov 2024
 * Description: Gets input from the user, and moves the ship if necessary
 * Inputs: 
 * `ship_info` : The current status of the ship.
 * Outputs: 0 if the user has not pressed enter, 1 if they have.
 */
int process_user_input(ShipInfo *ship_info);

/**
 * Function name: normalize_ship_position
 * Date created: 3 Nov 2024
 * Date last modified: 3 Nov 2024
 * Description: Checks if `position` is a valid grid position, and if it isn't, sets its values such that it is.
 * Inputs: 
 * `ship_info` : The current status of the ship.
 * Outputs: The normalized position
 */
Position normalize_ship_position(ShipInfo ship_info);

/**
 * Function name: print_ship
 * Date created: 3 Nov 2024
 * Date last modified: 3 Nov 2024
 * Description: Prints the ship given at the position and orientation given.
 *              Assumes that the ship is in a valid position.
 * Inputs: 
 * `board` : The game board.
 * `ship_info` : The current status of the ship.
 * `ship_print_info` : An array containing information about how each space that makes up the ship is printed to the board.
 * Outputs: none
 */
void print_ship(Board *board, ShipInfo ship_info, PrintInfo *ship_print_info);

/**
 * Function name: save_ship
 * Date created: 3 Nov 2024
 * Date last modified: 3 Nov 2024
 * Description: Saves the print info of the ship to `ship_print_info`.
 * Inputs: 
 * `board` : The game board.
 * `ship_info` : The current status of the ship.
 * `ship_print_info` : An array containing information about how each space that makes up the ship is printed to the board.
 * Outputs: none
 */
void save_ship(Board *board, ShipInfo ship_info, PrintInfo *ship_print_info);

/**
 * Function name: get_ship_len
 * Date created: 3 Nov 2024
 * Date last modified: 3 Nov 2024
 * Description: Finds the length of a type of ship.
 * Inputs:
 * `ship` : The ship type.
 * Outputs: The ship's length.
 */
int get_ship_len(Ship ship);

/**
 * Function name: set_max_row_col
 * Date created: 3 Nov 2024
 * Date last modified: 3 Nov 2024
 * Description: Finds the maximum row and column that the top left of the ship described in `ship_info` can be located.
 * Inputs: 
 * `ship_info` : The current status of the ship.
 * `row` : Output parameter containing the maximum row in which the ship can be located.
 * `col` : Output parameter containing the maximum column in which the ship can be located.
 * Outputs: none
 */
void set_max_row_col(ShipInfo ship_info, int *row, int *col);

#endif