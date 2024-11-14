#include "board-spot-checking.h"

bool check_ship_sunk(Board *ships_board, ShipInfo ship) {
    int ship_len = get_ship_len(ship.ship);
    switch (ship.orientation) {
        case Horizontal:
            for (int i = 0; i < ship_len; ++i) {
                if (ships_board->board[ship.position.row][ship.position.col + i].shot != ShotHit) {
                    return false;
                }
            }
            break;
        case Vertical:
            for (int i = 0; i < ship_len; ++i) {
                if (ships_board->board[ship.position.row + i][ship.position.col].symbol[1] != ShotHit) {
                    return false;
                }
            }
            break;
    }
    return true;
}

bool check_all_ship_sunk(ShipInfo *ships) {
    for (int i = 0; i < NUM_SHIPS; ++i) {
        if (ships[i].is_sunk) {
            return true;
        }
    }
    return false;
}

int check_for_hit(Board *other_player_ships, Position shot) {
    if (other_player_ships->board[shot.row][shot.col].ship == SpaceHasNone) {
        return -1;
    }
    return (int) other_player_ships->board[shot.row][shot.col].ship;
}

void update_ships_status(Board *ships_board, ShipInfo *ships) {
    for (int i = 0; i < NUM_SHIPS; ++i) {
        ships[i].is_sunk = check_ship_sunk(ships_board, ships[i]);
    }
}