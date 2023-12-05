#ifndef GAME_OF_LIFE_FILE_HANDLER_C
#define GAME_OF_LIFE_FILE_HANDLER_C

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game_of_life.h"

/* Description: Saves the current configuration of the field to a
* specified file. The file pointed to by fp is closed.
* Input: The field structure and a file pointer to the file
* where the final configuration should be saved.
* Output: Returns 0 on success, the current configuration in the
* field is written to the file.
* Returns a non-zero value on failure.
*/
int save_config_to_file(const field game_field, FILE *fp);

/* Description: Loads a configuration to the field structure from a
 *              file. It is the responsiblity of the caller to
 *              deallocate the dynamically allocated memory in the field
 *              structure through a call to the function destroy_field.
 *              The file pointed to by fp is closed.
 * Input:       A pointer to where the created field structure should be
 *              assigned and a file pointer to the file with the initial
 *              configuration.
 * Output:      Returns 0 on success, the field structure is created
 *              with the configuration from the file.
 *              Returns a non-zero value on failure.
 */
 int load_config_from_file(field *game_field, FILE *fp);

#endif
