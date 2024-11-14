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

void init_player_info(PlayerInfo *info, int player_num);

/**
 * Function name: 
 * Date created: 12 Nov 2024
 * Date last modified: 14 Nov 2024
 * Description: 
 * Inputs: 
 * Outputs: 
 */
void play_battleship(void);

/**
 * Function name: play_turn
 * Date created: 13 Nov 2024
 * Date last modified: 14 Nov 2024
 * Description: 
 * Inputs: 
 * Outputs: 
 */
Position play_turn(PlayerInfo *current_player, PlayerInfo *targeted_player, Position last_shot, ShotRecords *records, int turn_num);

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