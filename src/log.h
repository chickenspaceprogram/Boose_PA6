#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include "ctty/ansi/cursor.h"
#include "ui/board.h"
#include "ui/place-ships.h"
#define MAX_NAME_LEN 80

typedef struct {
    int hits;
    int misses;
} ShotRecords;

typedef struct {
    Board shots;
    Board ships;
    ShipInfo ship_info[NUM_SHIPS];
    bool ships_rand_place;
    char name[MAX_NAME_LEN + 1]; // must add 1 to have space for '\0' at the end
} PlayerInfo;

void print_turn_log(FILE *log, PlayerInfo *player, Position shot);

void print_win_lose(FILE *log, char *winner_name, char *loser_name);

void print_end_game_log(FILE *log, char *name, int num_hits, int num_misses);

// prints the string assoc'd with each ship
// precondition: ship is not `SpaceHasNone`
void print_ship_string(ShipsInSpace ship, FILE *output);


#endif