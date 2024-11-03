#include "place-ships.h"

typedef enum {
    Up,
    Down,
    Left,
    Right,
    Space,
    Enter,
} Keys;

void place_ships(Board *board) {
    ShipInfo current_ship_info = {
        .position = {.row = 4, .col = 4},
        .orientation = Horizontal,
    };
    board->print_board(board);
    for (int i = 0; i < NUM_SHIPS; ++i) {
        current_ship_info.ship = (Ship) i;
        place_single_ship(board, current_ship_info);
    }
}

void place_single_ship(Board *board, ShipInfo ship_info) {
    Board last_valid_board = *board;
    static const PrintInfo ships_print_info[] = {
        DESTROYER_PRINT_INFO,
        SUBMARINE_PRINT_INFO,
        CRUISER_PRINT_INFO,
        BATTLESHIP_PRINT_INFO,
        CARRIER_PRINT_INFO,
    };
    ShipInfo next_ship_info;
    int has_pressed_enter;
    PrintInfo board_print_info[5], ship_print_info[5];
    save_ship(board, ship_info, board_print_info);

    for (int i = 0; i < get_ship_len(ship_info.ship); ++i) {
        ship_print_info[i] = ships_print_info[(int)ship_info.ship];
    }

    do {
        print_ship(board, ship_info, ship_print_info);
        next_ship_info = ship_info;
        has_pressed_enter = process_user_input(&next_ship_info);
        if (!has_pressed_enter) {
            print_ship(board, ship_info, board_print_info); // clearing current location of ship, resetting it to how it was
            save_ship(board, next_ship_info, board_print_info); // saving how the next location of ship looks
            ship_info = next_ship_info;
        }
    } while (!(has_pressed_enter && spot_is_valid(&last_valid_board, ship_info)));
}

int spot_is_valid(Board *board, ShipInfo ship_info) {
    int ship_len = get_ship_len(ship_info.ship);

    if (ship_info.orientation == Horizontal) {
        for (int i = ship_info.position.col; i < ship_info.position.col + ship_len; ++i) {
            if (board->board[ship_info.position.row][i].symbol != ' ') {
                return 0;
            }
        }
    }
    else {
        for (int i = ship_info.position.row; i < ship_info.position.row + ship_len; ++i) {
            if (board->board[i][ship_info.position.col].symbol != ' ') {
                return 0;
            }
        }
    }
    return 1;
}

int process_user_input(ShipInfo *ship_info) {
    int selected_char;
    static sequence valid_keys[] = {
        CTTY_UP,
        CTTY_DOWN,
        CTTY_LEFT,
        CTTY_RIGHT,
        CTTY_SPACE,
        CTTY_ENTER,
    };

    selected_char = select_char(valid_keys, 6);
    switch ((Keys)selected_char) {
        case Up:
            --(ship_info->position.row);
            break;
        case Down:
            ++(ship_info->position.row);
            break;
        case Left:
            --(ship_info->position.col);
            break;
        case Right:
            ++(ship_info->position.col);
            break;
        case Space:
            ship_info->orientation = (Orientation) !ship_info->orientation;
            break;
        case Enter:
            return 1;
            break;
    }
    ship_info->position = normalize_ship_position(*ship_info);
    return 0;
}

Position normalize_ship_position(ShipInfo ship_info) {
    int max_row, max_col;
    set_max_row_col(ship_info, &max_row, &max_col);


    if (ship_info.position.row < 0) {
        ship_info.position.row = 0;
    }
    else if (ship_info.position.row > max_row) {
        ship_info.position.row = max_row;
    }

    if (ship_info.position.col < 0) {
        ship_info.position.col = 0;
    }
    else if (ship_info.position.col > max_col) {
        ship_info.position.col = max_col;
    }
    return ship_info.position;
}

void print_ship(Board *board, ShipInfo ship_info, PrintInfo *ship_print_info) {
    int ship_len = get_ship_len(ship_info.ship);

    if (ship_info.orientation == Horizontal) {
        for (int i = ship_info.position.col; i < ship_info.position.col + ship_len; ++i) {
            board->board[ship_info.position.row][i] = ship_print_info[i - ship_info.position.col];
            board->reprint_symbol(board, ship_info.position.row, i);
        }
    }
    else {
        for (int i = ship_info.position.row; i < ship_info.position.row + ship_len; ++i) {
            board->board[i][ship_info.position.col] = ship_print_info[i - ship_info.position.row];
            board->reprint_symbol(board, i, ship_info.position.col);
        }
    }
}

void save_ship(Board *board, ShipInfo ship_info, PrintInfo *ship_print_info) {
    int ship_len = get_ship_len(ship_info.ship);

    if (ship_info.orientation == Horizontal) {
        for (int i = ship_info.position.col; i < ship_info.position.col + ship_len; ++i) {
            ship_print_info[i - ship_info.position.col] = board->board[ship_info.position.row][i];
        }
    }
    else {
        for (int i = ship_info.position.row; i < ship_info.position.row + ship_len; ++i) {
            ship_print_info[i - ship_info.position.row] = board->board[i][ship_info.position.col];
        }
    }
}

int get_ship_len(Ship ship) {
    int ship_len;
    switch(ship) {
        case Destroyer:
            ship_len = 2;
            break;
        case Submarine: case Cruiser:
            ship_len = 3;
            break;
        case Battleship:
            ship_len = 4;
            break;
        case Carrier:
            ship_len = 5;
            break;
    }
    return ship_len;
}

void set_max_row_col(ShipInfo ship_info, int *row, int *col) {
    int ship_len = get_ship_len(ship_info.ship);

    // finding the maximum row/column the ship could be in
    switch(ship_info.orientation) {
        case Horizontal:
            *row = 9;
            *col = 10 - ship_len;
            break;
        case Vertical:
            *row = 10 - ship_len;
            *col = 9;
            break;
    }
}