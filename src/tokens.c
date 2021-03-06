/*
 * ============================================================================
 *
 *       Filename:  tokens.c
 *
 *    Description:  Functions that controls the token
 *
 *        Version:  1.0
 *        Created:  09/27/2015 02:23:31 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Gustavo Pantuza
 *   Organization:  Software Community
 *
 * ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>

#include "tokens.h"
#include "colors.h"
#include "string.h"



/*
 * Increment the token line
 */
void
inc_line(struct token *token, int inc_size)
{
    token->line += (inc_size) ? inc_size : 0;
}



/*
 * Increment the token column
 */
void
inc_column (struct token *token, int inc_size)
{
    token->column += (inc_size) ? inc_size : 0;
}



/*
 * Sets the token value color
 */
void
set_color (struct token *token, char color[COLOR_STR_SIZE])
{
    strncpy(token->color, color, COLOR_STR_SIZE);
}



/*
 * Sets the token value
 */
void
set_value (struct token *token, char value[])
{
    unsigned int str_len = strlen(value) + 1;  // For null termination '\n'
    token->value = malloc(str_len);
    strncpy(token->value, value, str_len);
}



/*
 * Update current token
 */
void
update_token (struct token *token, int type, char color[COLOR_STR_SIZE],
              char value[], int inc_l, int inc_c)
{
    token->type = type;

    inc_line(token, inc_l);
    inc_column(token, inc_c);

    set_color(token, color);

    free(token->value);
    set_value(token, value);
}



/*
 * Prints the json until the error and exits
 */
void
print_json_error (char json[])
{
    fprintf(stdout, "%s", json);
    exit(EXIT_FAILURE);
}



/*
 * Prints token value into the result json
 */
void
add_token (struct token *token, options_t *options)
{
    /* There are 2 colors in the string: token->color and NO_COLOR */
    int colors_size = 2 * COLOR_STR_SIZE;

    int size = strlen(token->value) + colors_size;
    char* value = malloc(size);

    if(options->use_colors) {

        snprintf(value, size, "%s%s%s", token->color, token->value, NO_COLOR);
        fprintf(stdout, "%s", value);
    } else {

        fprintf(stdout, "%s", token->value);
    }

    if(token->type == TOKEN_ERROR) {
        print_json_error(value);
    }
    free(value);
}


/*
 * Expand tabs with spaces
 */
void
expandtab (char tab_str[EXPANDTAB_SIZE], int n_tabs, unsigned int tabstop)
{
    int tabs_no = n_tabs * tabstop;
    snprintf(tab_str, EXPANDTAB_SIZE, "%*s", tabs_no, EXPANDTAB);
}
