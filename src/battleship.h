#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include "ui/board.h"
#include "ui/place-ships.h"
#include "rand.h"
#include <stdio.h>
#include <stdbool.h>
#include "ctty/ansi/colors.h"
#include "ui/space-print-info.h"
#include "ui/select-shot-spot.h"

#define MAX_NAME_LEN 80

typedef struct {
    Board shots;
    Board ships;
    ShipInfo ship_info[NUM_SHIPS];
    bool ships_rand_place;
    char name[MAX_NAME_LEN + 1]; // must add 1 to have space for '\0' at the end
} PlayerInfo;

void init_player_info(PlayerInfo *info, int player_num);

/**
 * Function name: 
 * Date created: 12 Nov 2024
 * Date last modified: 12 Nov 2024
 * Description: 
 * Inputs: 
 * Outputs: 
 */
void play_battleship(void);

// wrote on 13th
Position play_turn(PlayerInfo *current_player, PlayerInfo *targeted_player, Position last_shot, int turn_num);


/**
 * Function name: check_ship_sunk
 * Date created: 7 Nov 2024
 * Date last modified: 7 Nov 2024
 * Description: Checks whether a ship has been sunk.
 * Inputs: 
 * `ships_board` : A pointer to the board containing the ships.
 * `ship` : A ShipInfo struct containing the ship's info
 * Outputs: 1 if the ship has been sunk, 0 otherwise.
 */
bool check_ship_sunk(Board *ships_board, ShipInfo ship);

/**
 * Function name: check_all_ship_sunk
 * Date created: 13 Nov 2024
 * Date last modified: 13 Nov 2024
 * Description: Checks whether all ships have been sunk.
 * Inputs: 
 * `ship` : An array of ShipInfo structs containing the info of the ships.
 * Outputs: `true` if any ship has been sunk, `false` otherwise.
 */
bool check_all_ship_sunk(ShipInfo *ships);

/**
 * Function name: update_ship_status
 * Date created: 13 Nov 2024
 * Date last modified: 13 Nov 2024
 * Description: Updates the status of each ship, setting it to floating or sunk if need be.
 * Inputs: 
 * `ships_board` : The board where the ships are.
 * Outputs: 
 * `ships` : ships.is_sunk set to the right value.
 */
void update_ships_status(Board *ships_board, ShipInfo *ships);

/**
 * Function name: is_new_ship_sunk
 * Date created: 13 Nov 2024
 * Date last modified: 13 Nov 2024
 * Description: Checks if a new ship has been sunk.
 *              If it has, returns the index of the ship.
 *              If not, -1 is returned.
 * Inputs: 
 * Outputs: 
 */
int is_new_ship_sunk(ShipInfo *old_ships, ShipInfo *new_ships);

/**
 * Function name: check_for_hit
 * Date created: 13 Nov 2024
 * Date last modified: 13 Nov 2024 
 * Description: Checks whether a shot in a specific position hits a ship.
 * Inputs: 
 * Outputs: The index of the ship that was hit if there was a hit, otherwise -1.
 */
int check_for_hit(Position shot, ShipInfo *other_player_ships);

/**
 * Function name: is_rand_placing_ships
 * Date created: 12 Nov 2024
 * Date last modified: 12 Nov 2024
 * Description: Checks if the player wants to place ships down manually.
 * Inputs: none
 * Outputs: `true` if the ships are to be placed randomly, `false` otherwise
 */
bool is_rand_placing_ships(void);

/**
 * Function name: init_ships_board
 * Date created: 12 Nov 2024
 * Date last modified: 13 Nov 2024
 * Description: Creates a ships board with its ships placed down.
 * Inputs: none
 * Outputs: Returns a ships board with the correct message.
 */
Board init_ships_board(bool rand_ships);

#endif