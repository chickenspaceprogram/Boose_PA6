#ifndef MENU_MENU_H
#define MENU_MENU_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <string.h>
#include "../ansi/text-modes.h"
#include "../ansi/cursor.h"
#include "../keypress/keyselect.h"
#include "../keypress/keypress-codes.h"
#include <stdio.h>

typedef struct {
    unsigned char *msg;
    unsigned char *sequence;
} Option;

/**
 * Function name: 
 * Date created: 2024-11-05
 * Date last modified: 2024-11-05
 * Description: 
 * Inputs: 
 * Outputs: 
 */
size_t menu(Option *options, char *title, size_t num_options);

#ifdef __cplusplus
}
#endif

#endif