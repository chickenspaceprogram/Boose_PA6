#ifndef AI_H
#define AI_H
#include "log.h"
#include "board-spot-checking.h"

Position ai_play_turn(PlayerInfo *current_player, PlayerInfo *targeted_player, Position last_shot, ShotRecords *records, int turn_num);


#endif