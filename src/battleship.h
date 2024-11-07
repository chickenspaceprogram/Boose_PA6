#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include "ui/board.h"
#include "ui/place-ships.h"

/**
 * Function name: check_ship_sunk
 * Date created: 7 Nov 2024
 * Date last modified: 7 Nov 2024
 * Description: Checks whether a ship has been sunk
 * Inputs: 
 * `shots_board` : A pointer to the board containing the shots.
 * `ship` : A pointer to a ShipInfo struct containing the ship's info
 * Outputs: 1 if the ship has been sunk, 0 otherwise.
 */
int check_ship_sunk(Board *shots_board, ShipInfo ship);

/**
 * Function name: get_newly_sunk_ship
 * Date created: 7 Nov 2024
 * Date last modified: 7 Nov 2024
 * Description: 
 * Inputs: 
 * Outputs: Returns the index of the ship that was sunk, or -1 if none were.
 */
Ship get_newly_sunk_ship(ShipInfo *ships);

#endif