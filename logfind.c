#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glob.h>
#include "dbg.h"

const unsigned int MAX_LINES = 1024;
/**
 * This program searches for logfiles that contain 
 * the word given to this program as arguments
 */

/**
 * So here is where I learn what glob does, basically
 * its a structure that contains the numbers of finds
 * and paths to those finds
 */

int list_files(glob_t *pglob){
    char *lines = callac(MAX_LINES, 1);
    FILE *file = fopen(".logfind", "r");
    int glob_flags = GLOB_TILDE;
    int i = 0;
    int rc = -1;

    check(pglob != NULL, "Incorrect glob_t given.");
    check_mem(lines);
    check(file, "Failed to open .logfind file.");

    while(fgets(lines, MAX_LINES - 1, file) != NULL) {
        lines[strlen(lines) - 1] = '\0';
        debug("Globbing %s", lines);
        rc = glob(lines, glob_flags, NULL, pglob);
        check(rc == 0 || rc == GLOB_NOMATCH, "Failed to glob");
        
        //Interesting way to now add GLOB_APPEND since we can't
        //have it as a flag upon instantiation
        if (glob_flags == GLOB_TILDE) glob_flags |= GLOB_APPEND;
    }

    for (i = 0; i < pglob->gl_pathc; i++) {
        debug("Matched file: %s\n", pglob->gl_pathv[i]);
    }
    rc = 0;

    free(lines);
    fclose(file);
    return 0;

error:
    if(lines) free(lines);
    if(file) fclose(file);
    return rc;
}

int found_it(int use_or, int found_count, int search_len)
{
    debug("use_or: %d, found_count: %d, search_len: %d", use_or, found_count, search_len);

    if(use_or && found_count > 0) {
        return 1;
    } else if(!use_or && found_count == search_len) {
        return 1;
    } else {
        return 0;
    }
}

//This function will parse our arguments and check for the -o flag
int parse_args(int *use_or, int *argc, char **argv[])
{
    //We want to skip the first argument because thats "./logfind"
    (*argc)--;
    (*argv)++;

    if(strcpr((*argv)[0], "-o") == 0) {
        *use_or = 1;
        (*argc)--;
        (*argv)++;
        check(*argc > 1, "You need words after -o");
    } else {
        *use_or = 0;
    }
    return 0;

error:
    return -1;

}
int scanner(const char *filename, int args_num, char *search_for[])
{

    char *lines = calloc(MAX_LINES, 1);
    FILE *file = fopen(filename, "r");
    int found_count = 0;
    int i = 0;
    
    check_mem(lines);
    check(file, "failed to open file: %s", filename);
    /**so we need to loop through each line in the file
    *  basically while !EOF
    *  I believe we use MAX_LINES - 1 to allow for the '\0' character
    *  at the end of the string??? Not entirely sure here
    */

    while (fgets(lines, MAX_LINES - 1, file) != NULL)
    {
        for (i = 0; i < args_num; i++) {
                if(strcasestr(lines, search_for[i]) != NULL) {
                    debug("file: %s, line: %s, search: %s", filename, lines, search_for[i]);
                    found_count++;
                //strcasestr(haystack, needle)
                //returns NULL if needle not found in haystack
                if (found_it(use_or, found_count, args_num)) {
                    printf("%s\n",filename);
                    break;
                } else {
                    found_count = 0;
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
    int i = 0;
    int use_or = 0;

    glob_t matched_files;
    check(parse_args(&use_or, &argc, &argv) == 0, "Usage: logfind [-o] words");
    check(list_files(&matched_files) == 0, "Failed to list files.");
    check(argc > 1, "usage: logfind [-o] word");
    for (i = 0; i < matched_files.gl_pathc; i++) {
        scanner(matched_files.gl_pathv[i], use_or, argc, argv);
    }
    /*so this first function needs to return a list
     *of files that contain inclusively the arguments
     *given in the filename.
     */
    globfree(&files_found);
    

    return 0;

error:
    return 1;
}
