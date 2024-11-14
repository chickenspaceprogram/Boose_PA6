#include "log.h"

void print_turn_log(FILE *log, PlayerInfo *player, Position shot) {
    char *shot_type_str;
    int col = shot.col;
    ShipsInSpace hit_type = player->ships.board[shot.row][shot.col].ship;

    if (player->ships.board[shot.row][shot.col].shot == ShotHit) {
        shot_type_str = "Hit";
    }
    else {
        shot_type_str = "Miss";
    }

    if (shot.col == BOARD_SIZE - 1) {
        col = 0;
    }
    fprintf(log, "%s : %c%d : %s", player->name, shot.row + 'A', col, shot_type_str);

    if (hit_type == SpaceHasNone || !(player->ship_info[hit_type].is_sunk)) {
        putc('\n', log);
        return;
    }
    fputs("Sunk \n", log);
    print_ship_string(hit_type, log);
    fputs("!\n", log);
    
}

void print_win_lose(FILE *log, char *winner_name, char *loser_name) {
    fprintf(log, "%s won, %s lost\n\n", winner_name, loser_name);
}

void print_end_game_log(FILE *log, char *name, int num_hits, int num_misses) {
    fprintf(log, "*** %s's stats ***\nHits: %d\nMisses: %d\nTotal shots: %d\nHit percentage: %.0lf%%\n\n", name, num_hits, num_misses, num_hits + num_misses, (double)num_hits * 100 / (double)(num_hits + num_misses));
}

void print_ship_string(ShipsInSpace ship, FILE *output) {
    switch (ship) {
        case SpaceHasDestroyer:
            fputs("Destroyer", stdout);
            break;
        case SpaceHasSubmarine:
            fputs("Submarine", stdout);
            break;
        case SpaceHasCruiser:
            fputs("Cruiser", stdout);
            break;
        case SpaceHasBattleship:
            fputs("Battleship", stdout);
            break;
        case SpaceHasCarrier:
            fputs("Carrier", stdout);
            break;
        default: // should never happen!
            fputs("\n\nAn error occurred! Exiting immediately. Please report this error to the developer of this application.\nError code: `0x00` - invalid ship type\n", stdout);
            exit(1);
            break;
    }
}