#ifndef AI_H
#define AI_H
#include "log.h"
#include "board-spot-checking.h"

/**
 * Function name: ai_play_turn
 * Date created: 2024-11-15
 * Date last modified: 2024-11-15
 * Description: Lets the computer play a turn.
 *              Analogous to `play_turn` in `battleship.c`.
 * Inputs: 
 * `current_player` : The current player's info.
 * `targeted_player` : The targeted player's info.
 * `records` : The hit/miss records.
 * Outputs: The position the computer chose to shoot at.
 */
Position ai_play_turn(PlayerInfo *current_player, PlayerInfo *targeted_player, ShotRecords *records);


#endif