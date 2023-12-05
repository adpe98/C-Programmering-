/*
 * Programmering i C
 * Spring 23
 * Mastery test 8
 *
 * File:         mp8.c
 * Description:  A simple implementation of Conway's Game of Life.
 * Author:       Adam Pettersson
 * CS username:  hed21apn
 * Date:         2023/02/21
 * Input:        Choice of initial configuration and then instruction
 *               to step or exit.
 * Output:       Prints the game field in each step.
 * Limitations:  No validation of input.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* Constants, representation of states */
#define ALIVE 'X'
#define DEAD '.'
/* Declaration of data structure */
typedef struct
{
  char current;
  char next;
} cell;

/* Declaration of functions */
int choice(void);

void print_game_field(const int rows, const int cols,
                 const cell field[rows][cols]);

void update_game(const int rows, const int cols,
                       cell field[rows][cols]);

void init_field(const int rows, const int cols,
                 cell field[rows][cols]);

void load_glider(const int rows, const int cols,
                 cell field[rows][cols]);

void load_semaphore(const int rows, const int cols,
                 cell field[rows][cols]);

void load_random(const int rows, const int cols,
                 cell field[rows][cols]);

void load_custom(const int rows, const int cols,
                 cell field[rows][cols]);

void neighbor_count_and_status(int rows, int cols, cell field[rows][cols],
                 const int r, const int c);

void update_field(const int rows, const int cols,
                       cell field[rows][cols]);

void live_or_die_status(int rows, int cols,
                 cell field[rows][cols], int r, int c, int neighbor_counter);

void print_the_menu(void);

/* Description: Start and run games, interact with the user.
 * Input:       About what initial structure and whether to step or
 *              exit.
 * Output:      Prints information to the user, and the game field in
 *              each step.
 */
int main(void)
{
    const int rows = 20, cols = 20;
    cell field[rows][cols];
    int desicion;

    srand(time(NULL));

    init_field(rows, cols, field);

    do{
       print_game_field(rows, cols, field);
       print_the_menu();
       desicion = choice();
       if(desicion == 1)
       {
         update_game(rows, cols, field);
       }

    }while(desicion == 1);

    return 0;
}

/* Description: Checks the keyboard input from the user.
 * Input:       Input from the person using the program.
 * Output:      If the user presses enter 1 otherwise 0 the value is then user in the menu.
 */
int choice(void)
{
    if(getchar() == '\n')
    {
        return 1;
    }

    return 0;
}

/* Description: Updates the game field by calculating the next state of each cell.
 * Input: The number of rows and columns, and the size of the field.
 * Output: The game field is updated.
*/
void update_game(const int rows, const int cols,
                       cell field[rows][cols])
{
  for (int r = 0 ; r < rows ; r++)
  {
    for (int c = 0 ; c < cols ; c++)
    {
      neighbor_count_and_status(rows, cols, field, r, c);
    }
  }

   update_field(rows, cols, field);
}

/* Description: Updates the current state of each cell to the next state.
 * Input: The number of rows and columns, and the size of the field.
 * Output: The current state of each cell is updated to the next state
*/
void update_field(const int rows, const int cols,
                       cell field[rows][cols])
{
  for (int r = 0 ; r < rows ; r++)
  {
    for (int c = 0 ; c < cols ; c++)
    {
      field[r][c].current = field[r][c].next;
    }
  }
}

/* Description: Determines whether a cell should be alive or dead in the next generation.
 * Input:       The number of rows and columns, the size of the field, the row and column for the cell, and the number neighbors.
 * Output:      Updates the next field array.
 */
void live_or_die_status(int rows, int cols, cell field[rows][cols], int r, int c, int neighbors)
{
    switch (field[r][c].current) {
        case ALIVE:
            if (neighbors < 2 || neighbors > 3) {
                field[r][c].next = DEAD;
            } else {
                field[r][c].next = ALIVE;
            }
            break;
        case DEAD:
            if (neighbors == 3) {
                field[r][c].next = ALIVE;
            } else {
                field[r][c].next = DEAD;
            }
            break;
        default:
            field[r][c].next = field[r][c].current;
            break;
    }
}

/* Description: Counts the number of live neighbors for a cell and calls the function for checking if a
                certain cell should be alive or dead in the next phase of the game.
 * Input:       The number of rows and columns, and the size of the field and the row and column for the cell.
 * Output:      The number of live neighbors for the cell.
 */
void neighbor_count_and_status(int rows, int cols, cell field[rows][cols], const int r, const int c)
{
    int neighbor_counter = 0;

    for (int i = r - 1; i <= r + 1; i++)
    {
        for (int j = c - 1; j <= c + 1; j++)
        {
            // Makes sure that our program doesn't count positions out of our field
            if (i >= 0 && i < rows && j >= 0 && j < cols && (i != r || j != c))
            {
                if (field[i][j].current == ALIVE)
                {
                    neighbor_counter++;
                }
            }
        }
    }

    live_or_die_status(rows, cols, field, r, c, neighbor_counter);
}

/* Description: Prints the current game field.
 * Input:       The number of rows and columns, and the size of the field.
 * Output:      The current game field is printed.
 */
void print_game_field(const int rows, const int cols,
                 const cell field[rows][cols])
{
    for (int r = 0 ; r < rows ; r++)
    {
        for (int c = 0 ; c < cols ; c++)
        {
           printf("%c ", field[r][c].current);
        }
      printf("\n");
    }
}

/* Description: Prints the menu with the users options.
 * Input:       no input.
 * Output:      the menu has been printed.
 */
void print_the_menu(void)
{
    printf("Select one of the following options:\n");
    printf("        (enter) Step\n");
    printf("        (any)   Exit\n");
}

/* Description: Initialize all the cells to dead, then asks the user
 *              about which structure to load, and finally load the
 *              structure.
 * Input:       The number of rows and columns, and the size of the field.
 * Output:      The field array is updated.
 */
void init_field(const int rows, const int cols,
                cell field[rows][cols])
{
    for (int r = 0 ; r < rows ; r++)
    {
        for (int c = 0 ; c < cols ; c++)
        {
            field[r][c].current = DEAD;
        }
    }

    printf("Select field spec to load ");
    printf("([G]lider, [S]emaphore, ");
    printf("[R]andom or [C]ustom): ");

    int ch = getchar();

    /* Ignore following newline */
    if (ch != '\n')
    {
        getchar();
    }

    switch (ch)
    {
        case 'g':
        case 'G':
            load_glider(rows, cols, field);
            break;
        case 's':
        case 'S':
            load_semaphore(rows, cols, field);
            break;
        case 'r':
        case 'R':
            load_random(rows, cols, field);
            break;
        case 'c':
        case 'C':
        default:
            load_custom(rows, cols, field);
      }
}

/* Description: Inserts a glider into the field.
 * Input:       The field array and its size.
 * Output:      The field array is updated.
 */

void load_glider(const int rows, const int cols,
                 cell field[rows][cols])
{
    field[0][1].current = ALIVE;
    field[1][2].current = ALIVE;
    field[2][0].current = ALIVE;
    field[2][1].current = ALIVE;
    field[2][2].current = ALIVE;
}

/* Description: Inserts a semaphore into the field.
 * Input:       The field array and its size.
 * Output:      The field array is updated.
 */
void load_semaphore(const int rows, const int cols,
                    cell field[rows][cols])
{
    field[8][1].current = ALIVE;
    field[8][2].current = ALIVE;
    field[8][3].current = ALIVE;
}

/* Description: Inserts a random structure into the field.
 * Input:       The field array and its size.
 * Output:      The field array is updated. There is a 50 % chance
 *              that a cell is alive.
 */


void load_random(const int rows, const int cols,
                 cell field[rows][cols])
{
	for (int r = 0 ; r < rows ; r++)
  {
		for (int c = 0 ; c < cols ; c++)
    {
			int random = rand()%3;

      if(random == 1)
      {
          field[r][c].current = ALIVE;
      }
			else
      {
          field[r][c].current = DEAD;
      }
		}
	}
}

/* Description: Lets the user specify a structure that then
 *              is inserted into the field.
 * Input:       The field array and its size.
 * Output:      The field array is updated.
 */
void load_custom(const int rows, const int cols,
                 cell field[rows][cols])
{
    printf("Give custom format string: ");
    do
    {
          int r, c;
          scanf("%d,%d", &r, &c);
          field[r][c].current = ALIVE;
    } while (getchar() != '\n');
}
