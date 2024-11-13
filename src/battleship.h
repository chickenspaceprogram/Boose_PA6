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

PlayerInfo init_player_info(int player_num);

/**
 * Function name: 
 * Date created: 12 Nov 2024
 * Date last modified: 12 Nov 2024
 * Description: 
 * Inputs: 
 * Outputs: 
 */
void play_battleship(void);

Position play_turn(PlayerInfo *player, Position last_shot, int turn_num);


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
bool check_ship_sunk(Board *shots_board, ShipInfo ship);

/**
 * Function name: check_all_ship_sunk
 * Date created: 13 Nov 2024
 * Date last modified: 13 Nov 2024
 * Description: Checks whether all ships have been sunk
 * Inputs: 
 * `shots_board` : A pointer to the board containing the shots.
 * `ship` : A pointer to a ShipInfo struct containing the ship's info
 * Outputs: 1 if any ship has been sunk, 0 otherwise.
 */
bool check_all_ship_sunk(Board *shots_board, ShipInfo *ships);

/**
 * Function name: is_rand_placing_ships
 * Date created: 12 Nov 2024
 * Date last modified: 12 Nov 2024
 * Description: Checks if the player wants to place ships down manually.
 * Inputs: none
 * Outputs: 1 if the
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