#ifndef SPACE_PRINT_INFO_H
#define SPACE_PRINT_INFO_H

// sorry for so many #define macros, they were really convenient.

#define DESTROYER_SYMBOL        " d "
#define SUBMARINE_SYMBOL        " s "
#define CRUISER_SYMBOL          " r "
#define BATTLESHIP_SYMBOL       " b "
#define CARRIER_SYMBOL          " c "
#define NO_SYMBOL               "   "

#define DESTROYER_BG_COLOR      BrightGreen
#define SUBMARINE_BG_COLOR      Yellow
#define CRUISER_BG_COLOR        BrightBlue
#define BATTLESHIP_BG_COLOR     Magenta
#define CARRIER_BG_COLOR        Cyan

#define DESTROYER_FG_COLOR      BrightWhite
#define SUBMARINE_FG_COLOR      BrightWhite
#define CRUISER_FG_COLOR        BrightWhite
#define BATTLESHIP_FG_COLOR     BrightWhite
#define CARRIER_FG_COLOR        BrightWhite

#define NO_COLOR                Default

#define DESTROYER_PRINT_INFO    {.bg_color = {DESTROYER_BG_COLOR, DESTROYER_BG_COLOR, DESTROYER_BG_COLOR}, .fg_color = {DESTROYER_FG_COLOR, DESTROYER_FG_COLOR, DESTROYER_FG_COLOR}, .symbol = DESTROYER_SYMBOL, .ship = SpaceHasDestroyer, .shot = ShotNone}
#define SUBMARINE_PRINT_INFO    {.bg_color = {SUBMARINE_BG_COLOR, SUBMARINE_BG_COLOR, SUBMARINE_BG_COLOR}, .fg_color = {SUBMARINE_FG_COLOR, SUBMARINE_FG_COLOR, SUBMARINE_FG_COLOR}, .symbol = SUBMARINE_SYMBOL, .ship = SpaceHasSubmarine, .shot = ShotNone}
#define CRUISER_PRINT_INFO      {.bg_color = {CRUISER_BG_COLOR, CRUISER_BG_COLOR, CRUISER_BG_COLOR}, .fg_color = {CRUISER_FG_COLOR, CRUISER_FG_COLOR, CRUISER_FG_COLOR}, .symbol = CRUISER_SYMBOL, .ship = SpaceHasCruiser, .shot = ShotNone}
#define BATTLESHIP_PRINT_INFO   {.bg_color = {BATTLESHIP_BG_COLOR, BATTLESHIP_BG_COLOR, BATTLESHIP_BG_COLOR}, .fg_color = {BATTLESHIP_FG_COLOR, BATTLESHIP_FG_COLOR, BATTLESHIP_FG_COLOR}, .symbol = BATTLESHIP_SYMBOL, .ship = SpaceHasBattleship, .shot = ShotNone}
#define CARRIER_PRINT_INFO      {.bg_color = {CARRIER_BG_COLOR, CARRIER_BG_COLOR, CARRIER_BG_COLOR}, .fg_color = {CARRIER_FG_COLOR, CARRIER_FG_COLOR, CARRIER_FG_COLOR}, .symbol = CARRIER_SYMBOL, .ship = SpaceHasCarrier, .shot = ShotNone}

#define BLANK_PRINT_INFO        {.bg_color = {NO_COLOR, NO_COLOR, NO_COLOR}, .fg_color = {NO_COLOR, NO_COLOR, NO_COLOR}, .symbol = NO_SYMBOL, .ship = SpaceHasNone, .shot = ShotNone}

#define HIT_SYMBOL '*'
#define HIT_BG_COLOR BrightRed
#define HIT_FG_COLOR BrightWhite

#define MISS_SYMBOL 'm'
#define MISS_BG_COLOR BrightWhite
#define MISS_FG_COLOR Black

#endif