/*
 * File:         game_of_life_handler.c
 *
 * Description:   A module handling the game field for Conway's Game of Life, including
 * loading the initial configuration from an input file, updating the
 * game field based on the game rules, and saving the final state to  an output file.
 *
 * Author:       Adam Pettersson
 * CS username:  hed21apn
 * Date:         18/6/2023
 * Limitations:  Assumes correctly formatted input file and game field
 */

#include "game_of_life_file_handler.h"

// Description: Loads the game field configuration from an input file,
// initializes the game field and then closes the file pointer.
// Input: A pointer to the game field and a file pointer to the input file.
// Output: Returns 0 if the configuration is successfully loaded and initialized, 1 if there is an error.
int load_config_from_file(field *game_field, FILE *fp)
{

  int row_nr, col_nr;

  // Read the number of rows and columns from the file
  if (fscanf(fp, "%d, %d\n", &row_nr, &col_nr) != 2)
  {
    fprintf(stderr, "Incorrect configuration file format");
    return 1;
  }

  // Assign the number of rows and columns to the game field
  game_field->rows = row_nr;
  game_field->cols = col_nr;
  allocate_cell_memory(game_field);

  // Read the cell states from the input file and assign them to the game field cells
  for (int r = 0; r < row_nr; ++r)
  {
    for (int c = 0; c < col_nr; ++c)
    {
      char cell_value;
      fscanf(fp, "%c", &cell_value);
      switch (cell_value)
      {
      case '0':
        cell_value = DEAD;
        break;
      case '*':
        cell_value = ALIVE;
        break;
      }
      game_field->cells[r][c].current = cell_value;
    }
    fscanf(fp, "\n");
  }

  fclose(fp);

  return 0;
}

// Description: Saves the current game field configuration to an output file.
// Input: A field structure containing the current game field configuration and a file pointer to the output file.
// Output: Returns 0 if the configuration is successfully saved, otherwise an error code (non-zero value).
int save_config_to_file(const field game_field, FILE *fp)
{
  // Check if the file pointer is NULL.
  if (fp == NULL)
  {
    return 1; // Return 1  failure.
  }

  for (int r = 0; r < game_field.rows; r++)
  {
    for (int c = 0; c < game_field.cols; c++)
    {
      char cell_value;

      // Decides the charachter of each cell
      if (game_field.cells[r][c].current == ALIVE)
      {
        cell_value = '*';
      }
      else
      {
        cell_value = '0';
      }
      // Writes the state of the cell to char to the file and check if successful.
      if (fputc(cell_value, fp) == EOF)
      {
        fclose(fp);
        return 1; // Return 1  failure.
      }
    }
    // Starts on a new line after each row and check if successful.
    if (fputc('\n', fp) == EOF)
    {
      fclose(fp);
      return 1; // Return 1 failure.
    }
  }

  // Close the file and check if successful.
  if (fclose(fp) == EOF)
  {
    return 1; // Return 1  failure.
  }

  return 0;
}
