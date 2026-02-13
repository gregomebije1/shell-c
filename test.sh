#!/bin/bash

# Set to true to see detailed output
VERBOSE=true

run_test() {
    DESC=$1
    INPUT=$2
    EXPECTED=$3

    # Capture output and clean it up
    # sed removes the prompt "$ " from the start of lines
    ACTUAL=$(echo -e "$INPUT\nexit" | ./shell-c | sed 's/^\$ //g' | sed '/^$/d' | head -n 1)

    if [ "$ACTUAL" == "$EXPECTED" ]; then
        echo -e "PASS: $DESC"
    else
        echo -e "FAIL: $DESC"
        if [ "$VERBOSE" = true ]; then
            # 'cat -e' shows line endings ($) and hidden characters
            echo -n "   Expected: "
            echo "$EXPECTED" | cat -e
            echo -n "   Got     : "
            echo "$ACTUAL" | cat -e
        fi
    fi
}

# --- TEST CASES ---

# Command Not Found
run_test "Invalid Command" "fakecmd" "fakecmd: command not found"

# exit
run_test "Exit command" "exit" "" 

# Basic Echo
run_test "Simple Echo" "echo hello world" "hello world"

# Echo with Quotes (Testing your quote logic)
run_test "Quoted Echo" "echo 'hello'" "hello"

# Empty Echo
run_test "Empty Echo" "echo" ""

# Type builtin
run_test "Type builtin", "type echo" "echo is a shell builtin"

# Type invalid command
run_test "Type command", "type invalid_command" "invalid_command: not found"

# External Command
run_test "External Command" "whoami" "$(whoami)"

