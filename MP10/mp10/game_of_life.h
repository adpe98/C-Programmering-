#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ALIVE 'X'
#define DEAD '.'

/* Declaration of data structure */
typedef struct
{
   char current;
   char next;
} cell;

typedef struct
{
   int rows;
   int cols;
   cell **cells;
} field;

// Description: Reads user's input and returns their choice from the menu.
// Input: None.
// Output: Returns 1 if the user presses enter (to step), 0 for any other input (save and exit).
int choice(void);

// Description: Allocates memory for the game field based on the provided number of rows and columns.
// Input: A pointer to the field structure.
// Output: No direct output, but memory is allocated for the cells in the game field.
void allocate_cell_memory(field *fp);

// Description: Updates the live or dead status of a cell in the game field based on the number of neighbors.
// Input: A pointer to the game field, row and column index of the cell, and the number of neighbors.
// Output: No direct output, but the next status of the cell is updated.
void live_or_die_status(field *game_field, int r, int c, int neighbors);

// Description: Counts the number of live neighbors for a cell and updates its status accordingly.
// Input: A pointer to the game field, row and column index of the cell.
// Output: No direct output, but the next status of the cell is updated based on the number of neighbors.
void neighbor_count_and_status(field *game_field, const int r, const int c);

// Description: Prints the current state of the game field.
// Input: A pointer to the game field.
// Output: No direct output, but the current state of the game field is printed to the console.
void print_game_field(field *game_field);

// Description: Updates the current state of the game field with the next state.
// Input: A pointer to the game field.
// Output: No direct output, but the current state of the game field is updated with the next state.
void update_game(field *game_field);

// Description: Updates the game by counting neighbors for each cell and updating their states accordingly.
// Input: A pointer to the game field.
// Output: No direct output, but the game field is updated with the new cell states.
void update_field(field *game_field);

// Description: Frees the memory allocated for the game field.
// Input: A field structure.
// Output: No direct output, but memory allocated for the game field is freed.
void deallocate_cell_memory(field fp);

// Description: Prints the menu options for the user.
// Input: None.
// Output: No direct output, but menu options are printed to the console.
void print_the_menu(void);

#endif
