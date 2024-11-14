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

void set_spot_hit_miss(Board *current_player_shots, Board *targeted_player_ships, Position shot, bool is_hit) {
    char symbol;
    Color foreground, background;
    ShotsInSpace hit_status;
    if (is_hit) {
        symbol = HIT_SYMBOL;
        foreground = HIT_FG_COLOR;
        background = HIT_BG_COLOR;
        hit_status = ShotHit;
    }
    else {
        symbol = MISS_SYMBOL;
        foreground = MISS_FG_COLOR;
        background = MISS_BG_COLOR;
        hit_status = ShotMiss;
    }
    current_player_shots->board[shot.row][shot.col].symbol[1] = symbol;
    current_player_shots->board[shot.row][shot.col].fg_color[1] = foreground;
    current_player_shots->board[shot.row][shot.col].fg_color[1] = foreground;
    current_player_shots->board[shot.row][shot.col].shot = hit_status;

    targeted_player_ships->board[shot.row][shot.col].symbol[1] = symbol;
    targeted_player_ships->board[shot.row][shot.col].fg_color[1] = foreground;
    targeted_player_ships->board[shot.row][shot.col].fg_color[1] = foreground;
    targeted_player_ships->board[shot.row][shot.col].shot = hit_status;
}