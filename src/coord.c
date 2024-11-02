#include "coord.h"

/* Public Functions */

static void normalize(Coord *coord);
static void print(Coord *coord);
static void clear(Coord *coord);

/* Private Functions */

// 1 NOV
static int normalize_int(int num);
static void set_bg_color(Color color);
static void set_fg_color(Color color);

/* Declarations */

Coord newCoord(int row, int col, Color color, char symbol) {
    Coord coord;
    coord.row = row;
    coord.col = col;
    coord.color = color;
    coord.symbol = symbol;

    coord.normalize = &normalize;
    coord.print = &print;
    coord.clear = &clear;
    return coord;
}

void normalize(Coord *coord) {
    coord->row = normalize_int(coord->row);
    coord->col = normalize_int(coord->col);
}

void print(Coord *coord) {
    CURSOR_RIGHT((coord->row - 1) * (BOARD_SIZE + 1));
    CURSOR_DOWN((coord->col - 1) * (BOARD_SIZE + 1));
    set_bg_color(coord->color);
    set_fg_color(coord->color);
    putchar(coord->symbol);
    printf(BG_DEFAULT);
    printf(FG_DEFAULT);
    CURSOR_LEFT((coord->row - 1) * (BOARD_SIZE + 1));
    CURSOR_UP((coord->col - 1) * (BOARD_SIZE + 1));
}

void clear(Coord *coord) {
    CURSOR_RIGHT((coord->row - 1) * (BOARD_SIZE + 1));
    CURSOR_DOWN((coord->col - 1) * (BOARD_SIZE + 1));
    putchar(' ');
    CURSOR_LEFT((coord->row - 1) * (BOARD_SIZE + 1));
    CURSOR_UP((coord->col - 1) * (BOARD_SIZE + 1));
}

static int normalize_int(int num) {
    if (num < 1) {
        return 1;
    }
    if (num > 10) {
        return 10;
    }
    return num;
}

void set_bg_color(Color color) {
    switch(color) {
        case None:
            break;
        case Black:
            printf(BG_BLACK);
            break;
        case Red:
            printf(BG_RED);
            break;
        case Green:
            printf(BG_GREEN);
            break;
        case Blue:
            printf(BG_BLUE);
            break;
        case Cyan:
            printf(BG_CYAN);
            break;
        case Magenta:
            printf(BG_MAGENTA);
            break;
        case White:
            printf(BG_WHITE);
            break;
        case BrightBlack:
            printf(BG_BLACK_BRIGHT);
            break;
        case BrightRed:
            printf(BG_RED_BRIGHT);
            break;
        case BrightGreen:
            printf(BG_GREEN_BRIGHT);
            break;
        case BrightBlue:
            printf(BG_BLUE_BRIGHT);
            break;
        case BrightCyan:
            printf(BG_CYAN_BRIGHT);
            break;
        case BrightMagenta:
            printf(BG_MAGENTA_BRIGHT);
            break;
        case BrightWhite:
            printf(BG_WHITE_BRIGHT);
            break;
    }
}

void set_fg_color(Color color) {
    switch(color) {
        case None:
            break;
        case Black:
            printf(FG_BLACK);
            break;
        case Red:
            printf(FG_RED);
            break;
        case Green:
            printf(FG_GREEN);
            break;
        case Blue:
            printf(FG_BLUE);
            break;
        case Cyan:
            printf(FG_CYAN);
            break;
        case Magenta:
            printf(FG_MAGENTA);
            break;
        case White:
            printf(FG_WHITE);
            break;
        case BrightBlack:
            printf(FG_BLACK_BRIGHT);
            break;
        case BrightRed:
            printf(FG_RED_BRIGHT);
            break;
        case BrightGreen:
            printf(FG_GREEN_BRIGHT);
            break;
        case BrightBlue:
            printf(FG_BLUE_BRIGHT);
            break;
        case BrightCyan:
            printf(FG_CYAN_BRIGHT);
            break;
        case BrightMagenta:
            printf(FG_MAGENTA_BRIGHT);
            break;
        case BrightWhite:
            printf(FG_WHITE_BRIGHT);
            break;
    }
}