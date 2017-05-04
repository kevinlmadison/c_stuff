#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define KEVSH_RL_BUFSIZE 1024
#define KEVSH_TOK_BUFSIZE 64
#define KEVSH_TOK_DELIM " \t\r\n\a"

/*
 * Function Declarations for built-in shell commands:
 */

int kevsh_cd(char **args);
int kevsh_help(char **args);
int kevsh_exit(char **args);

/*
 * List of built-in commands, followed by their corresponding functions:
 */

char *builtin_str[] = {
    "cd",
    "help",
    "exit"
};

int (*builtin_func[]) (char **) = {
    &kevsh_cd,
    &kevsh_help,
    &kevsh_exit
};

int kevsh_num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

/*
 * Built-in function implementations:
 */

int kevsh_cd(char **args)
{
    if (args[1] == NULL) {
        fprintf(stderr, "kevsh: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("kevsh");
        }
    }
    return 1;
}

int kevsh_help(char **args)
{
    int i;
    printf("Kevin Madison's KEVSH\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for (i = 0; i < kevsh_num_builtins(); i++) {
        printf("  %s\n", builtin_str[i]);
    }

    printf("Use the man command for information on other programs.\n");
    return 1;
}

int kevsh_exit(char **args)
{
    return 0;
}

int kevsh_execute(char **args)
{
    int i;
    if (args[0] == NULL) {
        // An empty command was entered
        return 1;
    }

    for (i = 0; i < kevsh_num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }

    return kevsh_launch(args);
}

int kevsh_launch(char **args)
{
    pid_t pid, wpid;
    int status;

    pid = fork();

    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            perror("kevsh");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Error forking
        perror("kevsh");
    } else {
        // Parent process
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

char **kevsh_split_line(char *line)
{
    int bufsize = KEVSH_TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens) {
        fprintf(stderr, "kevsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, KEVSH_TOK_DELIM);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += KEVSH_TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "kevsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, KEVSH_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

char *kevsh_read_line(void)
{
    int bufsize = KEVSH_RL_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer) {
        fprintf(stderr, "kevsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while(1) {
        // Read a character
        c = getchar();

        //if we hit EOF, replace it with a null character and return.
        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;

        // If we have exceeded the buffer, reallocate.
        if (position >= bufsize) {
            bufsize += KEVSH_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer) {
                fprintf(stderr, "kevsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

void kevsh_loop(void)
{
    char *line;
    char **args;
    int status;

    do {
        printf("> ");
        line = kevsh_read_line();
        args = kevsh_split_line(line);
        status = kevsh_execute(args);

        free(line);
        free(args);
    } while (status);
}

int main(int argc, char **argv)
{
    kevsh_loop();

    return EXIT_SUCCESS;
}


