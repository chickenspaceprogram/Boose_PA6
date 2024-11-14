#include "battleship.h"

static void print_turn_welcome(PlayerInfo *player, Position last_shot, int turn_num);

static void print_ship_status(Board *board, ShipInfo ship_info);

void play_battleship(void) {
    CLEAR_SCREEN();

    PlayerInfo players[2] = {
        {.shots = newBoard(ShotMsg), .name = {0}},
        {.shots = newBoard(ShotMsg), .name = {0}},
    };

    Position player1_pos = {0, 0}, player2_pos = {0, 0};

    int player_1_first = randint(0, 1);

    if (player_1_first) {
        init_player_info(&(players[0]), 1);
        init_player_info(&(players[1]), 2);
    }
    else {
        init_player_info(&(players[1]), 2);
        init_player_info(&(players[0]), 1);
    }
    Position shot_pos[2] = {
        {0, 0},
        {0, 0},
    };
    players[0].ships.set_print_message(&(players[0].ships), ShipView);
    players[1].ships.set_print_message(&(players[1].ships), ShipView);

    // an entirely sensible for loop :)
    for (int num_turns = 1; !check_all_ship_sunk(&(players[0].shots), players[0].ship_info) && !check_all_ship_sunk(&(players[1].shots), players[1].ship_info); ++num_turns) {
        shot_pos[0] = play_turn(&(players[0]), shot_pos[0], num_turns);
        CLEAR_SCREEN();
        shot_pos[1] = play_turn(&(players[1]), shot_pos[1], num_turns);
        CLEAR_SCREEN();
    }
}

void init_player_info(PlayerInfo *info, int player_num) {
    info->shots = newBoard(ShotMsg);
    for (int i = 0; i < MAX_NAME_LEN + 1; ++i) {
        info->name[i] = '\0';
    }

    printf("Hi Player %d! Please enter your name (maximum %d characters): ", player_num, MAX_NAME_LEN);
    fgets(info->name, MAX_NAME_LEN, stdin);
    putchar('\n');

    // clearing newline at end of string
    int len = strlen(info->name);
    if (info->name[len - 1] == '\n') { // fgets also stops reading on encountering EOF and doesn't put EOF into the string
        info->name[len - 1] = '\0';
    }

    info->ships_rand_place = is_rand_placing_ships();
    info->ships = init_ships_board(info->ships_rand_place);
    place_ships(&(info->ships), info->ship_info, info->ships_rand_place);
    
}

Position play_turn(PlayerInfo *player, Position last_shot, int turn_num) {
    print_turn_welcome(player, last_shot, turn_num);

    Option turn_menu[2] = {
        {.msg = (unsigned char *)"1. Shoot at opponent ships", .sequence = (unsigned char *)"1"},
        {.msg = (unsigned char *)"2. Look at your ships", .sequence = (unsigned char *)"2"},
    };
    int selection = 0;
    do {
        selection = menu(turn_menu, "What do you want to do?", 2);
        if (selection == 1) {
            CLEAR_SCREEN();
            player->ships.print_board(&(player->ships));
            PAUSE();
        }
        CLEAR_SCREEN();
    } while (selection != 0);
    return select_spot(&(player->shots));
}

bool check_ship_sunk(Board *shots_board, ShipInfo ship) {
    int ship_len = get_ship_len(ship.ship);
    switch (ship.orientation) {
        case Horizontal:
            for (int i = 0; i < ship_len; ++i) {
                if (shots_board->board[ship.position.row][ship.position.col + i].symbol[1] != HIT_SYMBOL) {
                    return false;
                }
            }
            break;
        case Vertical:
            for (int i = 0; i < ship_len; ++i) {
                if (shots_board->board[ship.position.row + i][ship.position.col].symbol[1] != HIT_SYMBOL) {
                    return false;
                }
            }
            break;
    }
    return true;
}

bool check_all_ship_sunk(Board *shots_board, ShipInfo *ships) {
    for (int i = 0; i < NUM_SHIPS; ++i) {
        if (check_ship_sunk(shots_board, ships[i])) {
            return true;
        }
    }
    return false;
}

bool is_rand_placing_ships(void) {
    Option options[] = {
        {.msg = (unsigned char *)"1. Place ships manually", .sequence = (unsigned char *)"1"},
        {.msg = (unsigned char *)"2. Place ships randomly", .sequence = (unsigned char *)"2"},
    };
    unsigned char *title = (unsigned char *)"Select Ship Placement";
    size_t selection = menu(options, title, 2);
    CLEAR_SCREEN();
    return selection;
}

Board init_ships_board(bool rand_ships) {
    Board board;
    if (rand_ships) {
        board = newBoard(AutoPlacement);
    }
    else {
        board = newBoard(ManualPlacement);
    }
    return board;
}




/* private functions */

void print_turn_welcome(PlayerInfo *player, Position last_shot, int turn_num) {
    printf("Hi, %s. It is currently turn %d.\n", player->name, turn_num);

    // only want to print this if a shot has been made
    if (turn_num != 1) {
        printf("Your opponent shot at space %c%d and ", last_shot.row + 'A', last_shot.col + 1);
        if (player->ships.board[last_shot.row][last_shot.col].symbol[1] == 'm') {
            fputs("missed.\n\n", stdout);
            return;
        }

        switch (player->ships.board[last_shot.row][last_shot.col].bg_color[0]) {
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
        print_ship_status(&(player->ships), player->ship_info[i]);
    }
}

void print_ship_status(Board *board, ShipInfo ship_info) {
    switch (ship_info.ship) {
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

    if (check_ship_sunk(board, ship_info)) {
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
