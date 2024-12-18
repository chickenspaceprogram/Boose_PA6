#include "battleship.h"

static void print_turn_welcome(PlayerInfo *player, Position last_shot, int turn_num);

static void print_ship_status(Board *board, ShipInfo ship_info);

void play_battleship(void) {
    CLEAR_SCREEN();
    FILE *log = fopen("battleship.log", "w");
    if (log == NULL) {
        puts("Error 0x01: Log file could not be opened.\nPlease report this error to the developer of this application.\nPress any key to return to the main menu. . .\n");
        PAUSE();
        return;
    }

    PlayerInfo players[2] = {
        {.shots = newBoard(ShotMsg), .name = {0}},
        {.shots = newBoard(ShotMsg), .name = {0}},
    };

    Position player1_pos = {0, 0}, player2_pos = {0, 0};

    int player_1_first = randint(0, 1);

    if (player_1_first) {
        init_player_info(&(players[0]), 1, false);
        init_player_info(&(players[1]), 2, true);
    }
    else {
        init_player_info(&(players[0]), 2, true);
        init_player_info(&(players[1]), 1, false);
    }
    Position shot_pos[2] = {
        {-1, -1},
        {-1, -1},
    };
    players[0].ships.set_print_message(&(players[0].ships), ShipView);
    players[1].ships.set_print_message(&(players[1].ships), ShipView);

    ShotRecords recs[2] = {
        {0, 0},
        {0, 0},
    };

    for (int num_turns = 1; !check_all_ship_sunk(players[0].ship_info) && !check_all_ship_sunk(players[1].ship_info); ++num_turns) {
        if (players[0].is_ai) {
            shot_pos[0] = ai_play_turn(&(players[0]), &(players[1]), &(recs[0]));
        }
        else {
            shot_pos[0] = play_turn(&(players[0]), &(players[1]), shot_pos[1], &(recs[0]), num_turns);
        }
        print_turn_log(log, &(players[0]), shot_pos[0]);

        if (players[1].is_ai) {
            shot_pos[1] = ai_play_turn(&(players[1]), &(players[0]), &(recs[1]));
        }
        else {
            shot_pos[1] = play_turn(&(players[1]), &(players[0]), shot_pos[0], &(recs[1]), num_turns);
        }
        print_turn_log(log, &(players[1]), shot_pos[1]);
        fflush(log);
    }
    if (check_all_ship_sunk(players[0].ship_info)) {
        print_win_lose(log, players[1].name, players[0].name);
    }
    else {
        print_win_lose(log, players[0].name, players[1].name);
    }
    print_end_game_log(log, players[0].name, recs[0].hits, recs[0].misses);
    print_end_game_log(log, players[1].name, recs[1].hits, recs[1].misses);
    fclose(log);
    CLEAR_SCREEN();
}

void init_player_info(PlayerInfo *info, int player_num, bool is_ai) {
    info->shots = newBoard(ShotMsg);
    info->is_ai = is_ai;
    if (is_ai) {
        char *str = "Computer";
        strcpy(info->name, str);
        info->ships_rand_place = true;
        info->ships = init_ships_board(info->ships_rand_place);
        rand_place_ships(&(info->ships), info->ship_info);
        return;
    }
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

Position play_turn(PlayerInfo *current_player, PlayerInfo *targeted_player, Position last_shot, ShotRecords *records, int turn_num) {
    Position current_shot;
    int hit_ship;

    print_turn_welcome(current_player, last_shot, turn_num);

    Option turn_menu[2] = {
        {.msg = (unsigned char *)"1. Shoot at opponent ships", .sequence = (unsigned char *)"1"},
        {.msg = (unsigned char *)"2. Look at your ships", .sequence = (unsigned char *)"2"},
    };
    int selection = 0;
    do {
        selection = menu(turn_menu, "What do you want to do?", 2);
        if (selection == 1) {
            CLEAR_SCREEN();
            fputs(CURSOR_OFF, stdout);
            current_player->ships.print_board(&(current_player->ships));
            PAUSE();
            fputs(CURSOR_ON, stdout);
        }
        CLEAR_SCREEN();
    } while (selection != 0);

    current_shot = select_spot(&(current_player->shots));
    fputs(CURSOR_OFF, stdout);
    hit_ship = check_for_hit(&(targeted_player->ships), current_shot);
    if (hit_ship == -1) {
        set_spot_hit_miss(&(current_player->shots), &(targeted_player->ships), current_shot, false);
        current_player->shots.reprint_symbol(&(current_player->shots), current_shot.row, current_shot.col);
        ++(records->misses);
        PAUSE();
        CLEAR_SCREEN();
        printf("\nYour shot at position "MODE_INVERSE MODE_BOLD"%c%d"MODE_INVERSE_RESET MODE_BOLD_FAINT_RESET" missed.\n\nPress any key to let %s play . . .", current_shot.row + 'A', current_shot.col + 1, targeted_player->name);
        PAUSE();
        CLEAR_SCREEN();
        fputs(CURSOR_ON, stdout);

        return current_shot;
    }

    set_spot_hit_miss(&(current_player->shots), &(targeted_player->ships), current_shot, true);
    current_player->shots.reprint_symbol(&(current_player->shots), current_shot.row, current_shot.col);
    ++(records->hits);

    PAUSE();
    CLEAR_SCREEN();
    if (check_ship_sunk(&(targeted_player->ships), targeted_player->ship_info[hit_ship])) {
        printf("\nYour shot at position "MODE_INVERSE MODE_BOLD"%c%d"MODE_INVERSE_RESET MODE_BOLD_FAINT_RESET" hit and sunk %s's "MODE_INVERSE MODE_BOLD,  current_shot.row + 'A', current_shot.col + 1, targeted_player->name);
        targeted_player->ship_info[hit_ship].is_sunk = true;
        update_ships_status(&(targeted_player->ships), targeted_player->ship_info);
    }
    else {
        printf("\nYour shot at position "MODE_INVERSE MODE_BOLD"%c%d"MODE_INVERSE_RESET MODE_BOLD_FAINT_RESET" hit %s's "MODE_INVERSE MODE_BOLD,  current_shot.row + 'A', current_shot.col + 1, targeted_player->name);
    }
    print_ship_string(targeted_player->ships.board[current_shot.row][current_shot.col].ship, stdout);
    fputs(MODE_INVERSE_RESET MODE_BOLD_FAINT_RESET".\n\nPress any key to continue...", stdout);
    PAUSE();
    CLEAR_SCREEN();
    fputs(CURSOR_ON, stdout);
    return current_shot;
}

bool is_rand_placing_ships(void) {
    Option options[] = {
        {.msg = (unsigned char *)"1. Place ships manually", .sequence = (unsigned char *)"1"},
        {.msg = (unsigned char *)"2. Place ships randomly", .sequence = (unsigned char *)"2"},
    };
    char *title = "Select Ship Placement";
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
    int col = last_shot.col + 1;
    if (last_shot.col == BOARD_SIZE - 1) {
        col = 0;
    }

    printf("Hi, %s. It is currently turn %d.\n", player->name, turn_num);

    // only want to print this if a shot has been made
    if (turn_num != 1 || last_shot.row != -1 || last_shot.col != -1) {
        printf("Your opponent shot at space "MODE_INVERSE MODE_BOLD"%c%d"MODE_INVERSE_RESET MODE_BOLD_FAINT_RESET" and "MODE_INVERSE MODE_BOLD, last_shot.row + 'A', col);
        if (player->ships.board[last_shot.row][last_shot.col].symbol[1] == 'm') {
            fputs("missed"MODE_INVERSE_RESET MODE_BOLD_FAINT_RESET".\n\n", stdout);
            fputs("Status of ships:\n\n", stdout);
            // should've been a function but I'm lazy
            for (int i = 0; i < NUM_SHIPS; ++i) {
                print_ship_status(&(player->ships), player->ship_info[i]);
            }
            return;
        }
        fputs(MODE_INVERSE_RESET MODE_BOLD_FAINT_RESET"hit your "MODE_INVERSE MODE_BOLD, stdout);
        print_ship_string(player->ships.board[last_shot.row][last_shot.col].ship, stdout);
        fputs(MODE_INVERSE_RESET MODE_BOLD_FAINT_RESET".\n\n", stdout);
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
