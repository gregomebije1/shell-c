# A simple shell in C

- `gcc -o shell shell.c to compile it, and then ./shell to run it.`
- In man 3p there is thorough documentation on every system call. 
- https://pubs.opengroup.org/onlinepubs/9699919799/

```c

    #include <sys/wait.h>
        waitpid() and associated macros
    #include <unistd.h>
        chdir()
        fork()
        exec()
        pid_t
    #include <stdlib.h>
        malloc()
        realloc()
        free()
        exit()
        execvp()
        EXIT_SUCCESS, EXIT_FAILURE
    #include <stdio.h>
        fprintf()
        printf()
        stderr
        getchar()
        perror()
    #include <string.h>
        strcmp()
        strtok()
```

- Key Concepts You Learn from This Program
    - Processes (fork, exec, wait)
    - Dynamic memory (malloc, realloc, free)
    - Function pointers
    - Command parsing
    - Basic shell design
    - Unix system calls


- TODO
    - Only whitespace separating arguments, no quoting or backslash escaping.
    - No piping or redirection.
    - Few standard builtins.
    - No globbing.

- `char` A char stores one character e.g., 'a', 'b', 'x'
- `char *` (pointer to char)
    - A char * usually represents a string
    - A string in C is an array of characters ending with '\0'
    - `char *word = "hello";` means 'h e l l o \0'
- `char **` → pointer to a pointer to char, many strings (array of strings)
    - "ls -l /home" => args[0] => "ls", args[1] => "-l", args[2] => "/home", args[3] => NULL
    - `char *args[] = {"ls", "-l", "/home", NULL};`
    - Since args is an array of char * (strings), its type is: `char **args`

    ```sql
    args
    |
    v
    +--------+--------+--------+--------+
    |  *     |   *    |   *    |  NULL  |
    +--------+--------+--------+--------+
    |        |        |
    v        v        v
    "ls"     "-l"    "/home"
    ```# shell-c
