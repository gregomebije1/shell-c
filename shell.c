#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

/* 
  Forward Function Declarations for builtin shell commands:
*/
int my_exit(char **args);
int my_echo(char **args);
int my_type(char **args);
int my_cd(char **args);
int my_help(char **args);


/* 
  List of builtin commands, followed by their corresponding functions
*/
char *builtin_str[] = {
    "exit",
    "echo",
    "type",
    "cd",
    "help"
};

/* An array of function pointers  
    (that take array of strings and return an int)
*/
int (*builtin_func[]) (char **) = {
    &my_exit,
    &my_echo,
    &my_type,
    &my_cd,
    &my_help
};

/* counts the built in command*/
int my_num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

/*
  Builtin function implementations.
*/
int my_exit(char **args)
{
    return 0;
}

/*{"echo", "hello", "world", NULL}*/
int my_echo(char **args)
{
    for (int i = 1; args[i] != NULL; i++) {
        char *current = args[i];
        int len = strlen(current);

        if (len >= 2 && current[0] == '\'') {
            current++; /*Move pointer forward*/
            len--; /*shorten the perceived length */
        
            // current[len] is the existing Null Terminator!
            if (current[len - 1] == '\'') {
                current[len - 1] = '\0'; /* Remove the last quote by replacing it with a null terminator */
            } 
        }
        // Logical "AND": If next arg exists, print a space
        printf("%s%s", current, (args[i+1] != NULL) ? " " : "");
    }
    printf("\n");
    return 1;
}

int my_type(char **args)
{
    if (args[1] == NULL) {
        fprintf(stderr, "shell-c: expected argument to \"type\"\n");
    } else {
        int my_num_builtins_len = my_num_builtins();
        for (int i = 0; i < my_num_builtins_len; i++) {
            if (strcmp(args[1], builtin_str[i]) == 0) {
                printf("%s is a shell builtin\n", args[1]);
                return 1;
            }
        }
        printf("%s: not found\n", args[1]);
    }
    return 1;
}

int my_cd(char **args)
{
    if (args[1] == NULL) {
        fprintf(stderr, "mysh: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("mysh");
        }
    }
    return 1;
}

int my_help(char **args) 
{
    int i;
    printf("My Own Shell\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are builtin:\n");

    for (i = 0; i < my_num_builtins(); i++) {
        printf(".  %s\n", builtin_str[i]);
    }

    printf("Use the man command for information on other programs.\n");
    return 1;
}


int my_launch(char **args)
{
    pid_t pid, wpid;
    int status;

    pid = fork(); /*creates a new process: Parent → shell, Child → program to run */
    if (pid == 0) {
        //Child process
        if (execvp(args[0], args) == -1) { /*execvp() replaces the child with the requested program*/
            //perror("lsh");
            printf("%s: command not found\n", args[0]);
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Error forking
        perror("lsh");
    } else {
        // Parent process
        do {
            wpid = waitpid(pid, &status, WUNTRACED); /*Waits until the child finishes, Prevents zombie processes*/
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

int my_execute(char **args)
{
    int i;

    if (args[0] == NULL) {
        // An empty command was entered.
        return 1;
    }

    //launch a builtin
    for (i = 0; i < my_num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }

    //launch a process
    return my_launch(args);
}


#define MY_RL_BUFSIZE 1024
char *my_read_line(void)
{
    int bufsize = MY_RL_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while(1) {
        //read a character
        c = getchar();

        // If we hit EOF, replace it with a null character and return
        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;

        //If we have exceeed the buffer, reallocate.
        if (position >= bufsize) {
            bufsize += MY_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer) {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

#define MY_TOK_BUFSIZE 64
#define MY_TOK_DELIM " \t\r\n\a"
char **my_split_line(char *line)
{
    int bufsize = MY_TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, MY_TOK_DELIM);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += MY_TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, MY_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}


void repl(void)
{
    char *line;
    char **args;
    int status;

    do {
        printf("$ ");
        line = my_read_line();
        args = my_split_line(line);
        status = my_execute(args);

        free(line);
        free(args);
    } while (status);
}
void run_test(char *test_name, char **mock_args, int expected_status) {
    printf("Testing %s... ", test_name);
    
    // Call the execute function directly
    int status = my_execute(mock_args);
    
    if (status == expected_status) {
        printf("PASSED\n");
    } else {
        printf("FAILED (Expected %d, got %d)\n", expected_status, status);
    }
}

int main(int args, char **argv)
{
    // Load config files, if any.

    repl();

    // Perorm any shutdown/cleanup
    return EXIT_SUCCESS;
}