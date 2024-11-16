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

/**
 * Function name: print_turn_log
 * Date created: 2024-11-14
 * Date last modified: 2024-11-14
 * Description: Prints the log entry for a turn.
 * Inputs: 
 * `log` : The log file
 * `player` : The PlayerInfo struct corresponding to the player whose information we want to print.
 * `shot` : The position the player shot at.
 * Outputs: none
 */
void print_turn_log(FILE *log, PlayerInfo *player, Position shot);

/**
 * Function name: print_win_lose
 * Date created: 2024-11-14
 * Date last modified: 2024-11-14
 * Description: Prints which player won, and which player lost.
 * Inputs: 
 * `log` : The log file
 * `winner_name` : The name of the winner
 * `loser_name` : The name of the loser
 * Outputs: none
 */
void print_win_lose(FILE *log, char *winner_name, char *loser_name);

/**
 * Function name: print_end_game_log
 * Date created: 2024-11-14
 * Date last modified: 2024-11-14
 * Description: Prints the log for a player that goes at the end of the game.
 * Inputs: 
 * `log` : The log file
 * `name` : The name of the player
 * `num_hits` : The number of hits the player has made
 * `num_misses` : The number of misses the player has made
 * Outputs: none
 */
void print_end_game_log(FILE *log, char *name, int num_hits, int num_misses);

/**
 * Function name: print_ship_string
 * Date created: 2024-11-14
 * Date last modified: 2024-11-14
 * Description: Prints the string associated with each ship.
 *              Precondition: Ship is not `SpaceHasNone`
 * Inputs: 
 * `ship` : The ship to print.
 * `output` : The stream to print the ship string to.
 * Outputs: none
 */
void print_ship_string(ShipsInSpace ship, FILE *output);


#endif