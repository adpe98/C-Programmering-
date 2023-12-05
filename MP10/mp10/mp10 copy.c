/*
 * Imperativ programmering i C
 * Spring 23
 * Mastery test 10
 *
 * File:         mp10.c
 * Description:   An implementation of Conway's Game of Life using dynamic 
 * memory allocation and file handling. The game reads the initial
 * configuration from an input file and saves the final state to an output file.
 * 
 * Author:       Adam Pettersson
 * CS username:  hed21apn
 * Date:         13/4/2023
 * 
 * Input:        .txt and .gol file for outputs and configurations, and 
 * keyboard inputs from the user. 
 * 
 * Output:       configurations to an ouput file and prints a game field.
 *               
 * Limitations:  The input file must be correctly formated
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game_of_life.h"
#include "game_of_life_file_handler.h"

void write_to_file(FILE* out_file_p, field game_field);
int check_prog_params(int argc, const char *argv[],
                      FILE **in_file_p, FILE **out_file_p);

int main(int argc, const char *argv[])
{
   FILE *in_file_p = NULL; // File pointer for input file
   FILE *out_file_p = NULL; // File pointer for output file

   int decision; // User's menu choice
   field game_field; // The game field

   // starts the random number generator
   srand(time(NULL));

   // check program parameters
   if (check_prog_params(argc, argv, &in_file_p, &out_file_p) != 0)
   {
      return 0;
   }

   // load configuration from file
   if (load_config_from_file(&game_field, in_file_p) != 0)
   {
      fclose(in_file_p);
      fclose(out_file_p);
      return 0;
   }

   // Start game loop
   do
   {
      // display game and menu
      print_game_field(&game_field);
      print_the_menu();
      decision = choice();

      // If the user chooses to step, update the game field
      if (decision == 1)
      {
         update_game(&game_field);
      }

   } while (decision == 1);

   // Call the write_to_file function instead of writing directly to the file
   write_to_file(out_file_p, game_field);

   // cleanup and exit
   deallocate_cell_memory(game_field);
   
   return 0;
}


void write_to_file(FILE* out_file_p, field game_field) {
    fprintf(out_file_p, "%d,%d\n", game_field.rows, game_field.cols);
    int result = save_config_to_file(game_field, out_file_p);
    if (result != 0) {
        fprintf(stderr, "Could not save configuration to output file");
    }
}


/* Description: Checks the parameters to the program. Checks if the
* call to the program has the right number of
* parameters. Open the input and output files.
* Input: The parameters to the program and two pointers to file
* pointers.
* Output: Returns 0 when the files are correctly opened.
* Returns a non-zero value on failure.
*/
int check_prog_params(int argc, const char *argv[],
                      FILE **in_file_p, FILE **out_file_p)
{

   // Check that the program was called with the right number of parameters
   if (argc < 3 || argc > 3)
   {
      fprintf(stderr, "Usage: %s <input configuration file> <output configuration file>\n", argv[0]);
      return 1;
   }

   // Open the input file  
   *in_file_p = fopen(argv[1], "r");
   if (*in_file_p == NULL)
   {
      fprintf(stderr, "Could not open the file: %s", argv[1]);
      return 1;
   }

   // Open the output file 
   *out_file_p = fopen(argv[2], "w");
   if (*out_file_p == NULL)
   {
      fprintf(stderr, "Could not open the file: %s", argv[2]);
      return 1;
   }

   return 0;
}

