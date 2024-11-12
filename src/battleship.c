#include "battleship.h"

static void print_turn_welcome(Board *board, ShipInfo *ships, char *player_name, Position last_shot, int turn_num);

static void print_ship_status(Board *board, ShipInfo ship);

void play_battleship(void) {
    CLEAR_SCREEN();

    Board player1_shots_board = newBoard(ShotMsg);
    int player1_rand_ships;
    ShipInfo player1_ships[5];
    Board player1_ships_board;

    Board player2_shots_board = newBoard(ShotMsg);
    int player2_rand_ships;
    Board player2_ships_board;
    ShipInfo player2_ships[5];

    int player_1_first = randint(0, 1);

    // a cursed way of doing this, but oh well
    if (player_1_first) {
        // placing player 1's ships
        fputs("It is player 1's turn.\n\n", stdout);
        player1_ships_board = init_ships_board(&player1_rand_ships);
        place_ships(&player1_ships_board, player1_ships, player1_rand_ships);
    }

    fputs("It is player 2's turn.\n\n", stdout);
    player2_ships_board = init_ships_board(&player2_rand_ships);
    place_ships(&player2_ships_board, player2_ships, player2_rand_ships);

    if (!player_1_first) {
        // placing player 1's ships
        fputs("It is player 1's turn.\n\n", stdout);
        player1_ships_board = init_ships_board(&player1_rand_ships);
        place_ships(&player1_ships_board, player1_ships, player1_rand_ships);
    }
    Position test = {-1, -1};

    play_turn(&player1_shots_board, &player1_ships_board, player1_ships, "Player 1", test, 69);

}

Position play_turn(Board *shots_board, Board *ships_board, ShipInfo *ships, char *player_name, Position last_shot, int turn_num) {
    print_turn_welcome(shots_board, ships, player_name, last_shot, turn_num); // this many function args is painful

    Option turn_menu[2] = {
        {.msg = (unsigned char *)"1. Shoot at opponent ships", .sequence = (unsigned char *)"1"},
        {.msg = (unsigned char *)"2. Look at your ships", .sequence = (unsigned char *)"2"},
    };
    int selection = 0;
    do {
        selection = menu(turn_menu, "What do you want to do?", 2);
        if (selection == 1) {
            CLEAR_SCREEN();
            ships_board->print_board(ships_board);
            PAUSE();
        }
        CLEAR_SCREEN();
    } while (selection != 0);
    return select_spot(shots_board);
}

int check_ship_sunk(Board *shots_board, ShipInfo ship) {
    int ship_len = get_ship_len(ship.ship);
    switch (ship.orientation) {
        case Horizontal:
            for (int i = 0; i < ship_len; ++i) {
                if (shots_board->board[ship.position.row][ship.position.col + i].symbol[1] != HIT_SYMBOL) {
                    return 0;
                }
            }
            break;
        case Vertical:
            for (int i = 0; i < ship_len; ++i) {
                if (shots_board->board[ship.position.row + i][ship.position.col].symbol[1] != HIT_SYMBOL) {
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

int check_player_placing_ships(void) {
    Option options[] = {
        {.msg = (unsigned char *)"1. Place ships manually", .sequence = (unsigned char *)"1"},
        {.msg = (unsigned char *)"2. Place ships randomly", .sequence = (unsigned char *)"2"},
    };
    unsigned char *title = (unsigned char *)"Select Ship Placement";
    size_t selection = menu(options, title, 2);
    CLEAR_SCREEN();
    return selection;
}

Board init_ships_board(int *rand_ships) {
    Board board;
    if (*rand_ships = check_player_placing_ships()) { // the assignment inside the if statement is intentional
        board = newBoard(ManualPlacement);
    }
    else {
        board = newBoard(AutoPlacement);
    }
    return board;
}




/* private functions */

void print_turn_welcome(Board *board, ShipInfo *ships, char *player_name, Position last_shot, int turn_num) {
    printf("Hi, %s. It is currently turn %d.\n", player_name);

    // only want to print this if a shot has been made
    if (last_shot.row != -1 && turn_num != 1) {
        printf("Your opponent shot at space %c%d and ", last_shot.row + 'A', last_shot.col + 1);
        if (board->board[last_shot.row][last_shot.col].symbol[1] == 'm') {
            fputs("missed.\n\n", stdout);
            return;
        }

        switch (board->board[last_shot.row][last_shot.col].bg_color[0]) {
            // switching based on the color of the space is a very cursed way to do this, but it works.
            // we can't switch based on the characters because those might be overwritten by hits
            case DESTROYER_BG_COLOR:
                fputs("hit your destroyer.\n\n", stdout);
                break;
            case SUBMARINE_BG_COLOR:
                fputs("hit your submarine.\n\n", stdout);
                break;
            case CRUISER_BG_COLOR:
                fputs("hit your cruiser.\n\n", stdout);
                break;
            case BATTLESHIP_BG_COLOR:
                fputs("hit your battleship.\n\n", stdout);
                break;
            case CARRIER_BG_COLOR:
                fputs("hit your carrier.\n\n", stdout);
                break;
            default: // should never happen!
                fputs("\n\nAn error occurred! Exiting immediately. Please report this error to the developer of this application.\n", stdout);
                exit(1);
                break;
        }
    }


    fputs("Status of ships:\n\n", stdout);
    for (int i = 0; i < NUM_SHIPS; ++i) {
        print_ship_status(board, ships[i]);
    }
}

void print_ship_status(Board *board, ShipInfo ship) {
    switch (ship.ship) {
        case Destroyer:
            fputs("Destroyer:  ", stdout);
            break;
        case Cruiser:
            fputs("Cruiser:    ", stdout);
            break;
        case Submarine:
            fputs("Submarine:  ", stdout);
            break;
        case Battleship:
            fputs("Battleship: ", stdout);
            break;
        case Carrier:
            fputs("Carrier:    ", stdout);
            break;
    }

    if (check_ship_sunk(board, ship)) {
        set_color(BrightWhite, BrightRed);
        fputs(MODE_BOLD"SUNK\n"MODE_BOLD_FAINT_RESET, stdout);
        set_color(Default, Default);
    }
    else {
        set_color(BrightWhite, BrightGreen);
        fputs(MODE_BOLD"AFLOAT\n"MODE_BOLD_FAINT_RESET, stdout);
        set_color(Default, Default);
    }
}
