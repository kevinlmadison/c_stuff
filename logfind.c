#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dbg.h"

/**
 * This program searches for logfiles that contain 
 * the word given to this program as arguments
 */


const unsigned int MAX_LINES = 1024;

int scanner(const char *filename, int args_num, char *search_for[])
{

    char *lines = calloc(MAX_LINES, 1);
    FILE *file = fopen(filename, "r");
    char *found = NULL;
    int i = 0;
    
    check_mem(lines);
    check(file, "failed to open file: %s", filename);
    /**so we need to loop through each line in the file
    *  basically while !EOF
    *  I believe we use MAX_LINES - 1 to allow for the '\0' character
    *  at the end of the string??? Not entirely sure here
    */

    while (fgets(lines, MAX_LINES - 1, file) != NULL && found == NULL) {
        for (i = 0; i < args_num && found == NULL; i++) {
                found = strcasestr(lines, search_for[i]);
                //strcasestr(haystack, needle)
                //returns NULL if needle not found in haystack
                if (found) {
                    printf("%s\n",filename);
                }
        }
    }

    free(lines);
    fclose(file);
/**we can use the strcasestr() function to find the needle in the haystack
 *without caring about the case of the needle or the haystack
 */
    
    return 0;
error:
    if(lines) free(lines);
    if(file) fclose(file);
    return -1;
}

int main(int argc, char *argv[])
{
    check(argc > 2, "usage: logfind word word word");
    
    /*so this first function needs to return a list
     *of files that contain inclusively the arguments
     *given in the filename.
     */

    scanner("logfind.c",argc, argv);

    return 0;

error:
    return 1;
}
