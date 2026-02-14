# A simple shell in C

## Compile and run
- `make` Compiles your project and creates the ./lisp executable.
- `make test` Rebuilds the code (if needed) and runs test_shell.sh.
- `make memcheck` Runs program through Valgrind.
- `make clean`: Deletes .o files and the executable.

## Others
- In man 3p there is thorough documentation on every system call. 
- https://pubs.opengroup.org/onlinepubs/9699919799/

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

- DONE
    - Print a prompt
    - Handle invalid commands
    - Implemented a REPL
    - Implemented exit, type, cd, help