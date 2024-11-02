#ifndef COORD_H
#define COORD_H

#include "ctty/ansi/cursor.h"
#include "ctty/ansi/colors.h"
#include "board.h"

typedef struct coord Coord;

struct coord {
    int row;
	int col;
    Color color;
    char symbol;

    /**
     * Function name: Coord->normalize
     * Date created: 1 Nov 2024
     * Date last modified: 1 Nov 2024
     * Description: Normalizes the position of the Coord, forcing any values that are out of bounds to be in bounds.
     * Inputs:
     * `this` : The Coord you want to normalize.
     * Outputs: none
     */
    void (*normalize)(Coord *this);

    /**
     * Function name: Coord->print
     * Date created: 1 Nov 2024
     * Date last modified: 1 Nov 2024
     * Description: Moves to the location of the Coord, prints the Coord, then moves back.
     *              Presumes that the cursor is currently at position A1 (and resets the cursor to that position).
     * Inputs:
     * `this` : The Coord you want to print.
     * Outputs: none
     */
    void (*print)(Coord *this);

    /**
     * Function name: Coord->clear
     * Date created: 1 Nov 2024
     * Date last modified: 1 Nov 2024
     * Description: Moves to the location of the Coord, clears the Coord, then moves back.
     *              Presumes that the cursor is currently at position A1 (and resets the cursor to that position).
     * Inputs:
     * `this` : The Coord you want to clear.
     * Outputs: none
     */
    void (*clear)(Coord *this);
};

Coord newCoord(int row, int col, Color color, char symbol);

#endif
