    /*
    *File: game_of_life.c
    *Description: A module implementing the core functionality for Conway's
    *Game of Life, including memory allocation, user input handling, game field updates,
    *cell state evaluation, and memory deallocation.
    *
    *Author: Adam Pettersson
    *CS username: hed21apn
    *Date: 16/6/2023
    *Limitations: Assumes correct memory allocation and proper game field initialization.
    */

   //gcc -I "C:\Users\adamf\OneDrive - Umeå universitet\DOA\OU4\GIT EXEMPEL" -o game game_of_life.c mp10.c game_of_life_handler.c

    #include "game_of_life.h"

    // Rest of the code remains unchanged

    void allocate_cell_memory(field *fp)
    {
        fp->cells = malloc(fp->rows * sizeof(cell *));

        for (int r = 0; r < (fp->rows); r++)
        {
            fp->cells[r] = malloc(fp->cols * sizeof(cell));
        }
    }

    int choice(void)
    {
        if (getchar() == '\n')
        {
            return 1;
        }

        return 0;
    }

    void print_the_menu(void)
    {
        printf("Select one of the following options:\n");
        printf("        (enter) Step\n");
        printf("        (any)   Save and exit\n");
    }

    void live_or_die_status(field *game_field, int r, int c, int neighbors)
    {
        switch (game_field->cells[r][c].current)
        {
        case ALIVE:
            if (neighbors < 2 || neighbors > 3)
            {
                game_field->cells[r][c].next = DEAD;
            }
            else
            {
                game_field->cells[r][c].next = ALIVE;
            }
            break;
        case DEAD:
            if (neighbors == 3)
            {
                game_field->cells[r][c].next = ALIVE;
            }
            else
            {
                game_field->cells[r][c].next = DEAD;
            }
            break;
        default:
            game_field->cells[r][c].next = game_field->cells[r][c].current;
            break;
        }
    }

    void neighbor_count_and_status(field *game_field, const int r, const int c)
    {
        int neighbor_counter = 0;

        for (int i = r - 1; i <= r + 1; i++)
        {
            for (int j = c - 1; j <= c + 1; j++)
            {
                // Makes sure that our program doesn't count positions out of our field
                if (i >= 0 && i < (game_field->rows) && j >= 0 && j < (game_field->cols) && (i != r || j != c))
                {
                    if (game_field->cells[i][j].current == ALIVE)
                    {
                        neighbor_counter++;
                    }
                }
            }
        }

        live_or_die_status(game_field, r, c, neighbor_counter);
    }

    void print_game_field(field *game_field)
    {
        for (int r = 0; r < (game_field->rows); r++)
        {
            for (int c = 0; c < (game_field->cols); c++)
            {
                printf("%c ", game_field->cells[r][c].current);
            }
            printf("\n");
        }
    }

    void update_field(field *game_field)
    {
        for (int r = 0; r < (game_field->rows); r++)
        {
            for (int c = 0; c < (game_field->cols); c++)
            {
                game_field->cells[r][c].current = game_field->cells[r][c].next;
            }
        }
    }

    void update_game(field *game_field)
    {
        for (int r = 0; r < (game_field->rows); r++)
        {
            for (int c = 0; c < (game_field->cols); c++)
            {
                neighbor_count_and_status(game_field, r, c);
            }
        }
        update_field(game_field);
    }

    void deallocate_cell_memory(field fp)
    {
        for (int r = 0; r < (fp.rows); r++)
        {
            free(fp.cells[r]);
        }
        free(fp.cells);
    }
