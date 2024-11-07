#include "menu.h"

typedef enum {
    Up,
    Down,
    K,
    J,
    Enter,
} Keys;

/**
 * Function name: 
 * Date created: 5 Nov 2024
 * Date last modified: 5 Nov 2024
 * Description: 
 * Inputs: 
 * Outputs: 
 */
static size_t find_max_msg_len(Option *options, unsigned char *title, size_t num_msgs);

/**
 * Function name: 
 * Date created: 5 Nov 2024
 * Date last modified: 5 Nov 2024
 * Description: 
 * Inputs: 
 * Outputs: 
 */
static void print_title(unsigned char *title, size_t table_size);

/**
 * Function name: 
 * Date created: 5 Nov 2024
 * Date last modified: 5 Nov 2024
 * Description: 
 * Inputs: 
 * Outputs: 
 */
static void print_row(unsigned char *row, size_t position, size_t len);

/**
 * Function name: 
 * Date created: 5 Nov 2024
 * Date last modified: 5 Nov 2024
 * Description: 
 * Inputs: 
 * Outputs: 
 */
static void inverse_row(unsigned char *row, size_t position, size_t len);

/**
 * Function name: 
 * Date created: 5 Nov 2024
 * Date last modified: 5 Nov 2024
 * Description: 
 * Inputs: 
 * Outputs: 
 */
static void print_bottom(size_t num_rows, size_t row_len);

/**
 * Function name: 
 * Date created: 5 Nov 2024
 * Date last modified: 5 Nov 2024
 * Description: 
 * Inputs: 
 * Outputs: 
 */
static sequence *fill_sequence_array(Option *options, size_t num_options);


size_t menu(Option *options, unsigned char *title, size_t num_options) {
    sequence *seqs = fill_sequence_array(options, num_options);
    if (seqs == NULL) {
        return -1;
    }

    size_t len = find_max_msg_len(options, title, num_options);
    size_t current_row = 0, prev_row = 0;
    Keys user_selection = Enter;
    print_title(title, len);
    inverse_row(options[0].msg, 0, len);
    for (int i = 1; i < num_options; ++i) {
        print_row(options[i].msg, i, len);
    }
    print_bottom(num_options, len);
    while (1) {
        user_selection = select_char(seqs, num_options + 5);
        if (user_selection < num_options) {
            if (user_selection != current_row) {
                print_row(options[current_row].msg, current_row, len);
                current_row = user_selection;
                inverse_row(options[current_row].msg, current_row, len);
            }
        }
        else if (user_selection == (num_options) || user_selection == (num_options + 2)) {
            if (current_row > 0) {
                print_row(options[current_row].msg, current_row, len);
                --current_row;
                inverse_row(options[current_row].msg, current_row, len);
            }
        }
        else if (user_selection == (num_options + 1) || user_selection == (num_options + 3)) {
            if (current_row < (num_options - 1)) {
                print_row(options[current_row].msg, current_row, len);
                ++current_row;
                inverse_row(options[current_row].msg, current_row, len);
            }
        }
        else {
            free(seqs);
            return current_row;
        }
    }
}


size_t find_max_msg_len(Option *options, unsigned char *title, size_t num_msgs) {
    size_t longest_len = strlen((char *)title);
    size_t current_len;
    for (int i = 0; i < num_msgs; ++i) {
        if ((current_len = strlen((char *)options[i].msg)) > longest_len) {
            longest_len = current_len;
        }
    }
    return longest_len;
}

void print_title(unsigned char *title, size_t table_size) {
    size_t title_len = strlen((char *)title);

    fputs("  "MODE_DRAW"l", stdout);
    for (int i = 0; i < (table_size + 2); ++i) {
        putchar('q');
    }
    fputs("k\n  x "MODE_DRAW_RESET, stdout);

    fputs((char *)title, stdout);
    for (int i = strlen((char *)title); i < (table_size + 1); ++i) {
        putchar(' ');
    }

    fputs(MODE_DRAW"x\n  t", stdout);

    for (int i = 0; i < (table_size + 2); ++i) {
        putchar('q');
    }
    fputs("u\n"MODE_DRAW_RESET, stdout);
}

void print_row(unsigned char *row, size_t position, size_t len) {
    size_t msg_len = 0;
    if (position != 0) {
        CURSOR_DOWN_LINE_START((int)position);
    }

    fputs("  "MODE_DRAW"x "MODE_DRAW_RESET, stdout);
    fputs((char *)row, stdout);

    for (int i = strlen((char *)row); i < (len + 1); ++i) {
        putchar(' ');
    }

    fputs(MODE_DRAW"x"MODE_DRAW_RESET"  ", stdout);

    if (position != 0) {
        CURSOR_UP_LINE_START((int)position);
    }
    else {
        putchar('\r');
    }
}

void inverse_row(unsigned char *row, size_t position, size_t len) {
    size_t msg_len = 0;
    if (position != 0) {
        CURSOR_DOWN_LINE_START((int)position);
    }

    fputs("> "MODE_DRAW"x "MODE_DRAW_RESET MODE_INVERSE, stdout);
    fputs((char *)row, stdout);
    fputs(MODE_INVERSE_RESET, stdout);

    for (int i = strlen((char *)row); i < (len + 1); ++i) {
        putchar(' ');
    }

    fputs(MODE_DRAW"x"MODE_DRAW_RESET" <", stdout);

    if (position != 0) {
        CURSOR_UP_LINE_START((int)position);
    }
    else {
        putchar('\r');
    }
}

static void print_bottom(size_t num_rows, size_t row_len) {
    CURSOR_DOWN_LINE_START((int)num_rows);
    fputs("  "MODE_DRAW"m", stdout);
    for (int i = 0; i < (row_len + 2); ++i) {
        putchar('q');
    }
    fputs("j"MODE_DRAW_RESET, stdout);
    CURSOR_UP_LINE_START((int)num_rows);
}

sequence *fill_sequence_array(Option *options, size_t num_options) {
    sequence *seqs = malloc(sizeof(sequence) * (num_options + 5));
    if (seqs == NULL) {
        return NULL;
    }
    sequence default_seqs[5] = {
        CTTY_UP,
        CTTY_DOWN,
        CTTY_k,
        CTTY_j,
        CTTY_ENTER,
    };

    for (int i = 0; i < num_options; ++i) {
        seqs[i].chars = options[i].sequence;
        seqs[i].len = strlen((char *)options[i].sequence);
    }
    for (int i = num_options; i < (num_options + 5); ++i) {
        seqs[i] = default_seqs[i - num_options];
    }
    return seqs;
}