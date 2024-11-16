#ifndef SCREEN_H
#define SCREEN_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include "../keypress/keypress.h"

#ifdef _WIN32

/**
 * Macro name: CLEAR_SCREEN
 * Date created: 2024-10-19
 * Date last modified: 2024-10-25
 * Description: Clears the screen.
 * Inputs: none
 * Outputs: none
 */
#define CLEAR_SCREEN() system("cls")

#else

/**
 * Macro name: CLEAR_SCREEN
 * Date created: 2024-10-19
 * Date last modified: 2024-10-19
 * Description: Clears the screen.
 * Inputs: none
 * Outputs: none
 */
#define CLEAR_SCREEN() system("clear")

#endif

/**
 * Macro name: PAUSE
 * Date created: 2024-10-24
 * Date last modified: 2024-10-24
 * Description: Pauses the program's execution until the user presses any key.
 * Inputs: none
 * Outputs: none, typecasts to void to make it clear that this is solely for pausing
 */
#define PAUSE() (void) GETCH()

/**
 * Function name: resize_screen
 * Date created: 2024-11-07
 * Date last modified: 2024-11-07
 * Description: Resizes terminal screen to be `lines` by `cols`.
 * Inputs: 
 * `lines` : The number of lines you want the terminal to have.
 * `cols` : The number of columns you want the terminal to have.
 * Outputs: none
 */
void resize_screen(int lines, int cols);

#ifdef __cplusplus
}
#endif

#endif
