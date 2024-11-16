#ifndef BOARD_SPOT_CHECKING_H
#define BOARD_SPOT_CHECKING_H

#include "ui/board.h"
#include "ui/place-ships.h"
#include <stdbool.h>

/**
 * Function name: check_ship_sunk
 * Date created: 2024-11-7
 * Date last modified: 2024-11-14
 * Description: Checks whether a ship has been sunk.
 * Inputs: 
 * `ships_board` : A pointer to the board containing the ships.
 * `ship` : A ShipInfo struct containing the ship's info
 * Outputs: 1 if the ship has been sunk, 0 otherwise.
 */
bool check_ship_sunk(Board *ships_board, ShipInfo ship);

/**
 * Function name: check_all_ship_sunk
 * Date created: 2024-11-13
 * Date last modified: 2024-11-13
 * Description: Checks whether all ships have been sunk.
 * Inputs: 
 * `ship` : An array of ShipInfo structs containing the info of the ships.
 * Outputs: `true` if any ship has been sunk, `false` otherwise.
 */
bool check_all_ship_sunk(ShipInfo *ships);

/**
 * Function name: check_for_hit
 * Date created: 2024-11-13
 * Date last modified: 2024-11-14
 * Description: Checks whether a shot in a specific position hits a ship.
 * Inputs: 
 * `other_player_ships` : The other player's ships board.
 * `shot` : The position of the shot.
 * Outputs: The index of the ship that was hit if there was a hit, otherwise -1.
 */
int check_for_hit(Board *other_player_ships, Position shot);

/**
 * Function name: update_ship_status
 * Date created: 2024-11-13
 * Date last modified: 2024-11-14
 * Description: Updates the status of each ship, setting it to floating or sunk if need be.
 * Inputs: 
 * `ships_board` : The board where the ships are.
 * Outputs: 
 * `ships` : ships.is_sunk set to the right value.
 */
void update_ships_status(Board *ships_board, ShipInfo *ships);

/**
 * Function name: set_spot_hit_miss
 * Date created: 2024-11-14
 * Date last modified: 2024-11-14
 * Description: Sets the spot to either a hit or a miss.
 * Inputs: 
 * `current_player_shots` : The shots-board of the current player
 * `targeted_player_ships` : The ships-board of the targeted player
 * `shot` : The position of the shot
 * `is_hit` : Whether the shot is a hit or a miss
 * Outputs: none
 */
void set_spot_hit_miss(Board *current_player_shots, Board *targeted_player_ships, Position shot, bool is_hit);

#endif