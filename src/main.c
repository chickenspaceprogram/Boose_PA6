#include <stdlib.h>
#include <stdbool.h>
#include "ui/board.h"
#include "ui/place-ships.h"
#include "ctty/screen/screen.h"
#include "ctty/ansi/cursor.h"
#include "ctty/screen/view-file.h"
#include "rand.h"
#include "ctty/menu/menu.h"
#include "ui/select-shot-spot.h"
#include "battleship.h"

void printship(ShipInfo ship);

typedef enum {
    PlayGame = 0,
    ViewLog,
    Exit,
} MainMenu;

int main(void) {
    seed_rand();
    CLEAR_SCREEN();
    Option main_menu_opts[] = {
        {.msg = (unsigned char *)"1. Play Game", .sequence = (unsigned char *)"1"},
        {.msg = (unsigned char *)"2. View log", .sequence = (unsigned char *)"2"},
        {.msg = (unsigned char *)"3. Exit", .sequence = (unsigned char *)"3"},
    };
    int selection = 0;
    do {
        selection = menu(main_menu_opts, "Battleship Main Menu", 3);
        CLEAR_SCREEN();

        switch (selection) {
            case 0:
                play_battleship();
                break;
            case 1:
                fputs(CURSOR_OFF, stdout);
                FILE *log = fopen("battleship.log", "r");
                if (log == NULL) {
                    fputs("Sorry, it doesn't look like a log file has been created yet.\nTry playing a game of battleship first!\n\nPress any key to continue . . .", stdout);
                }
                else {
                    fclose(log);
                    print_file("battleship.log", false);
                }
                PAUSE();
                CLEAR_SCREEN();
                fputs(CURSOR_ON, stdout);
                break;
            default:
                break;
        }
    }
    while ((selection != Exit));

    CLEAR_SCREEN();
    fputs("\nThanks for playing Battleship!\n\n", stdout);
}

/*void current(void) {
    Board bored = newBoard(Ships);
    ShipInfo ships[5];
    printf(CURSOR_OFF);
    place_ships(&bored, ships);
    CLEAR_SCREEN();
    Board twobored = newBoard(Shots);
    twobored.board[2][2] = set_hit_print_info(twobored.board[2][2]);
    select_spot(&twobored);
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
    printf("Orientation: ");
    if (ship.orientation == Horizontal) {
        printf("Horizontal\n");
    }
    else {
        printf("Vertical\n");
    }
    
}