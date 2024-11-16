#include "ai.h"

Position ai_play_turn(PlayerInfo *current_player, PlayerInfo *targeted_player, ShotRecords *records) {
    Position shot_pos;
    bool is_hit;
    do {
        shot_pos.row = randint(0, 9);
        shot_pos.col = randint(0, 9);
    } while (current_player->shots.board[shot_pos.row][shot_pos.col].shot != ShotNone);
    if (check_for_hit(targeted_player, shot_pos) == -1) {
        is_hit = false;
    }
    else {
        is_hit = true;
        update_ships_status(&(targeted_player->ships), targeted_player->ship_info);
    }
    set_spot_hit_miss(&(current_player->shots), &(targeted_player->ships), shot_pos, is_hit);
}