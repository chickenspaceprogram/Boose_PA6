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
#include "log.h"
#include "board-spot-checking.h"

void init_player_info(PlayerInfo *info, int player_num, bool is_ai);

/**
 * Function name: play_battleship
 * Date created: 2024-11-12
 * Date last modified: 2024-11-15
 * Description: Plays a game of Battleship.
 * Inputs: none
 * Outputs: none
 */
void play_battleship(void);

/**
 * Function name: play_turn
 * Date created: 2024-11-13
 * Date last modified: 2024-11-14
 * Description: Plays through a single turn of Battleship.
 * Inputs: 
 * `current_player` : The current player
 * `targeted_player` : The targeted player
 * `last_shot` : The position that the opponent last shot at.
 * `turn_num` : The number of the current turn.
 * Outputs: 
 * Returns: The position at which the player decided to shoot
 * `records` : A struct containing the number of hits and misses the player has made
 */
Position play_turn(PlayerInfo *current_player, PlayerInfo *targeted_player, Position last_shot, ShotRecords *records, int turn_num);

/**
 * Function name: is_rand_placing_ships
 * Date created: 2024-11-12
 * Date last modified: 2024-11-12
 * Description: Checks if the player wants to place ships down manually.
 * Inputs: none
 * Outputs: `true` if the ships are to be placed randomly, `false` otherwise
 */
bool is_rand_placing_ships(void);

/**
 * Function name: init_ships_board
 * Date created: 2024-11-12
 * Date last modified: 2024-11-13
 * Description: Creates a ships board with its ships placed down.
 * Inputs: none
 * Outputs: Returns a ships board with the correct message.
 */
Board init_ships_board(bool rand_ships);

#endif