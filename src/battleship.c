#include "battleship.h"

int check_ship_sunk(Board *shots_board, ShipInfo ship) {
    int ship_len = get_ship_len(ship.ship);
    switch (ship.orientation) {
        case Horizontal:
            for (int i = 0; i < ship_len; ++i) {
                if (shots_board->board[ship.position.row][ship.position.col + i].symbol != HIT_SYMBOL) {
                    return 0;
                }
            }
            break;
        case Vertical:
            for (int i = 0; i < ship_len; ++i) {
                if (shots_board->board[ship.position.row + i][ship.position.col].symbol != HIT_SYMBOL) {
                    return 0;
                }
            }
            break;
    }
    return 1;
}


int get_newly_sunk_ship(Board *shots_board, ShipInfo *ships) {
    for (int i = 0; i < NUM_SHIPS; ++i) {
        if (check_ship_sunk(shots_board, ships[i])) {
            return i;
        }
    }
    return -1;
}