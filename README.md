# A simple shell in C

- `gcc -o shell-c shell.c` to compile it, and then `./shell-c` to run it.
- `gcc -o shell-c shell.c; chmod +x test.sh; ./test.sh`
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