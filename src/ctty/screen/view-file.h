#ifndef SCREEN_VIEW_FILE_H
#define SCREEN_VIEW_FILE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "screen.h"
#include "../ansi/cursor.h"

/**
* Function name: print_file
* Date created: 2024-09-25
* Date last modified: 2024-11-15
* Description:	Prints the contents of a file to stdout.
*				This is used to print the rules and the main menu because a bunch of printf() statements would've been extremely ugly
* Inputs:
* `filename` : The name of the file.
* `clear_screen` : Whether to clear the screen before displaying the file.
* Outputs: none
*/
void print_file(char *filename, int clear_screen);

#ifdef __cplusplus
}
#endif

#endif