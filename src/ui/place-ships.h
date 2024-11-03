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
} ShipInfo;

void place_ships(Board *board);

void place_single_ship(Board *board, ShipInfo ship_info);

int spot_is_valid(Board *board, ShipInfo ship_info);

/**
 * Function name: process_user_input
 * Date created: 3 Nov 2024
 * Date last modified: 3 Nov 2024
 * Description: 
 * Inputs: 
 * Outputs: 0 if the user has not pressed enter, 1 if they have.
 */
int process_user_input(ShipInfo *ship_info);

/**
 * Function name: normalize_ship_position
 * Date created: 3 Nov 2024
 * Date last modified: 3 Nov 2024
 * Description: Checks if `position` is a valid grid position, and if it isn't, sets its values such that it is.
 * Inputs: 
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
 * Outputs: none
 */
void print_ship(Board *board, ShipInfo ship_info, PrintInfo *ship_print_info);

/**
 * Function name: save_ship
 * Date created: 3 Nov 2024
 * Date last modified: 3 Nov 2024
 * Description: Saves the print info of the ship to `ship_print_info`.
 * Inputs: 
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

void set_max_row_col(ShipInfo ship_info, int *row, int *col);

#endif