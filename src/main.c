#include <stdlib.h>
#include "ui/board.h"
#include "ui/place-ships.h"
#include "ctty/screen.h"
#include "rand.h"
#include "ui/menu.h"
#include "ctty/ansi/text-modes.h"

void printship(ShipInfo ship);

int main(void) {
	// initializing a struct containing the options for the main menu
	option main_menu_options[] = {
		{.is_valid = 0, .msg = "\0", .selection_char = '\0'},
		{.is_valid = 1, .msg = MODE_DRAW"x"MODE_DRAW_RESET"1 : Print gamerules         "MODE_DRAW"x"MODE_DRAW_RESET"\0", .selection_char = '1'},
		{.is_valid = 1, .msg = MODE_DRAW"x"MODE_DRAW_RESET"2 : Start a game of Yahtzee "MODE_DRAW"x"MODE_DRAW_RESET"\0", .selection_char = '2'},
		{.is_valid = 1, .msg = MODE_DRAW"x"MODE_DRAW_RESET"3 : Exit                    "MODE_DRAW"x"MODE_DRAW_RESET"\0", .selection_char = '3'}
	};

	// displaying menu header
	CLEAR_SCREEN(); fputs(HIDE_CURSOR, stdout);
	printf("Please select an option by pressing the key next to it, using the arrow keys, or pressing k or j.\n\nThen, press [Enter] to save your selection.\n\n");
	printf("  "MODE_DRAW"lqqqqqqqqqqqqqqqqqqqqqqqqqqqqk\n"MODE_DRAW_RESET);
	printf("  "MODE_DRAW"x"MODE_DRAW_RESET" PA 5 - Yahtzee - Main Menu "MODE_DRAW"x\n"MODE_DRAW_RESET);
	printf("  "MODE_DRAW"tqqqqqqqqqqqqqqqqqqqqqqqqqqqqu\n"MODE_DRAW_RESET);

	// displaying menu, getting user selection
	int selection = menu(main_menu_options, MODE_DRAW"  mqqqqqqqqqqqqqqqqqqqqqqqqqqqqj"MODE_DRAW_RESET, 4);
}

/*
    seed_rand();
    system("clear");
    Board bored = newBoard(Ships);
    ShipInfo ships[5];
    printf(HIDE_CURSOR);
    rand_place_ships(&bored, ships);
    PAUSE();
    printf(SHOW_CURSOR);
    system("clear");
    for (int i = 0; i < 5; ++i) {
        printship(ships[i]);
    }
}*/

void printship(ShipInfo ship) {
    printf("Ship: ");
    switch (ship.ship) {
        case Destroyer:
            printf("Destroyer\n");
            break;
        case Submarine:
            printf("Submarine\n");
            break;
        case Cruiser:
            printf("Cruiser\n");
            break;
        case Battleship:
            printf("Battleship\n");
            break;
        case Carrier:
            printf("Carrier\n");
            break;
    }
    if (ship.position.col == 9) {
        ship.position.col = -1;
    }
    printf("Position: {%c, %c}\n", ship.position.row + 'a', ship.position.col + '1');
    printf("ship_is_hit: ");
    if (ship.ship_is_hit) {
        printf("True\n");
    }
    else {
        printf("False\n");
    }
    printf("Orientation: ");
    if (ship.orientation == Horizontal) {
        printf("Horizontal\n");
    }
    else {
        printf("Vertical\n");
    }
    
}