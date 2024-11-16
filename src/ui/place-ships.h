#ifndef UI_PLACE_SHIPS_H
#define UI_PLACE_SHIPS_H

#include "../ctty/ansi/cursor.h"
#include "../ctty/keypress/keyselect.h"
#include "../ctty/keypress/keypress-codes.h"
#include "../rand.h"
#include "../ctty/screen/screen.h"
#include "../ctty/menu/menu.h"
#include "board.h"
#include "space-print-info.h"
#include <stdbool.h>

typedef enum {
    Destroyer = 0,
    Submarine,
    Cruiser,
    Battleship,
    Carrier,
} Ship;

#define NUM_SHIPS   5

typedef enum {
    Horizontal = 0,
    Vertical,
} Orientation;

typedef struct {
    Position position;
    Ship ship;
    Orientation orientation;
    bool is_sunk;
} ShipInfo;

/**
 * Function name: place_ships
 * Date created: 2024-11-05
 * Date last modified: 2024-11-12
 * Description: Places ships on the board, either manually or automatically.
 * Inputs: 
 * `board` : The board to place the ships on.
 * `ships` : An array containing the ships to place.
 * `rand_ships` : 1 if ships are to be randomly placed, 0 if not.
 * Outputs: none
 */
void place_ships(Board *board, ShipInfo *ships, int rand_ships);

/**
 * Function name: player_place_ships
 * Date created: 2024-11-03
 * Date last modified: 2024-11-03
 * Description: Prompts the user to place their ships on the board.
 *              Stores the ships placed to `ships`.
 *              `ships` must have a length greater than or equal to `NUM_SHIPS`, otherwise the behavior of this function is undefined.
 * Inputs: 
 * `board` : The game board
 * `ships` : The array to store the ship positions in.
 * Outputs: none
 */
void player_place_ships(Board *board, ShipInfo *ships);

/**
 * Function name: rand_place_ships
 * Date created: 2024-11-03
 * Date last modified: 2024-11-03
 * Description: Randomly places ships on the board.
 * Inputs: 
 * `board` : The board on which to place the ships.
 * `ships` : The ships to place on the board.
 * Outputs: none
 */
void rand_place_ships(Board *board, ShipInfo *ships);

/**
 * Function name: place_single_ship
 * Date created: 2024-11-03
 * Date last modified: 2024-11-03
 * Description: Allows the user to place a single ship on the board.
 * Inputs: 
 * `board` : The game board.
 * `ship_info` : The current status of the ship.
 * Outputs: The ShipInfo of the ship that was placed.
 */
ShipInfo place_single_ship(Board *board, ShipInfo ship_info);

/**
 * Function name: spot_is_valid
 * Date created: 2024-11-03
 * Date last modified: 2024-11-03
 * Description: Checks if the spot where the ship described by `ship_info` overlaps any other ships.
 * Inputs: 
 * `board` : The game board.
 * `ship_info` : The current status of the ship.
 * Outputs: 0 if the spot is invalid, 1 if the spot is valid.
 */
int spot_is_valid(Board *board, ShipInfo ship_info);

/**
 * Function name: process_user_input
 * Date created: 2024-11-03
 * Date last modified: 2024-11-03
 * Description: Gets input from the user, and moves the ship if necessary
 * Inputs: 
 * `ship_info` : The current status of the ship.
 * Outputs: 0 if the user has not pressed enter, 1 if they have.
 */
int process_user_input(ShipInfo *ship_info);

/**
 * Function name: normalize_ship_position
 * Date created: 2024-11-03
 * Date last modified: 2024-11-03
 * Description: Checks if `position` is a valid grid position, and if it isn't, sets its values such that it is.
 * Inputs: 
 * `ship_info` : The current status of the ship.
 * Outputs: The normalized position
 */
Position normalize_ship_position(ShipInfo ship_info);

/**
 * Function name: print_ship
 * Date created: 2024-11-03
 * Date last modified: 2024-11-03
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
 * Function name: print_ship
 * Date created: 2024-11-15
 * Date last modified: 2024-11-15
 * Description: Prints the ship given at the position and orientation given.
 *              Assumes that the ship is in a valid position.
 * Inputs: 
 * `board` : The game board.
 * `ship_info` : The current status of the ship.
 * `ship_print_info` : An array containing information about how each space that makes up the ship is printed to the board.
 * Outputs: none
 */
void place_ship_no_print(Board *board, ShipInfo ship_info, PrintInfo *ship_print_info);

/**
 * Function name: save_ship
 * Date created: 2024-11-03
 * Date last modified: 2024-11-03
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
 * Date created: 2024-11-03
 * Date last modified: 2024-11-03
 * Description: Finds the length of a type of ship.
 * Inputs:
 * `ship` : The ship type.
 * Outputs: The ship's length.
 */
int get_ship_len(Ship ship);

/**
 * Function name: set_max_row_col
 * Date created: 2024-11-03
 * Date last modified: 2024-11-03
 * Description: Finds the maximum row and column that the top left of the ship described in `ship_info` can be located.
 * Inputs: 
 * `ship_info` : The current status of the ship.
 * `row` : Output parameter containing the maximum row in which the ship can be located.
 * `col` : Output parameter containing the maximum column in which the ship can be located.
 * Outputs: none
 */
void set_max_row_col(ShipInfo ship_info, int *row, int *col);

#endif