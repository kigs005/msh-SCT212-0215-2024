# Minimal C Shell (msh)

**Course:** Systems Programming
**Student Name:** Watiki John Kigotho
**Registration Number:** SCT212-0215/2024  
**Language:** C  

## 1. Project Overview

This project implements a minimal Unix-like command-line shell in C. The shell, named `msh`, accepts user commands, parses command-line arguments and executes external programs using Linux process-management system calls.

The implementation demonstrates fundamental operating-system concepts, including process creation, program execution, process synchronization, background processing, file descriptor manipulation and signal handling.

## 2. Features Implemented

The shell supports the following features:

- Dynamic command input using `getline()`.
- Command parsing using `strtok()`.
- External command execution using `fork()` and `execvp()`.
- Child-process synchronization using `waitpid()`.
- Built-in commands: `cd`, `help` and `exit`.
- Display of the previous command's exit status.
- Background execution using `&`.
- Background child-process reaping using `waitpid()` with `WNOHANG`.
- Output redirection using `>`, `open()` and `dup2()`.
- Ctrl-C handling using `SIGINT`.

## 3. Requirements and Implementation Checklist

| Task | Requirement | Status |
|---|---|---|
| 1 | Prompt and dynamic input | Complete |
| 2 | Command argument parsing | Complete |
| 3 | External command execution | Complete |
| 4 | Built-in commands | Complete |
| 5 | Exit-status tracking | Complete |
| 6 | Background execution | Partial |
| 7 | Output redirection | Complete |
| 8 | Ctrl-C handling | Complete |

*Note: Task 6 has a limitation: completed background processes are reaped at prompt-loop boundaries rather than immediately while the shell is blocked waiting for input.*

## 4. Compilation and Execution

### Requirements

- Linux operating system
- GCC compiler
- Standard C library

### Compile

```bash
gcc -Wall -Wextra -std=c11 msh.c -o msh
```

### Run

```bash
./msh
```

## 5. Example Commands

```bash
# Display help
help

# List files
ls -l

# Display text
echo Hello World

# Change directory
cd /tmp

# Display current directory
pwd

# Execute a command in the background
sleep 10 &

# Redirect output to a file
echo Hello > output.txt

# Display the file contents
cat output.txt

# Exit the shell
exit
```

## 6. Design Explanation

The shell operates through a continuous input-processing-execution loop. It displays a prompt, reads user input using `getline()` and separates the command into arguments using `strtok()`. Empty commands are ignored.

For external commands, the shell creates a child process using `fork()`. The child executes the requested program through `execvp()`, which searches for the executable using the system's command search path. If execution fails, the child reports the error and terminates using `_exit()`. The parent uses `waitpid()` to wait for foreground processes and obtain their exit status.

Built-in commands are handled directly by the shell process. This is necessary for `cd` because changing the working directory inside a child process would not change the shell's own directory. The `help` command displays available built-ins, while `exit` terminates the shell.

Background commands are identified by a trailing `&`. The shell starts these processes without waiting for their completion. It uses `waitpid()` with `WNOHANG` to check for completed background processes and reap them.

Output redirection is implemented in the child process. The `open()` system call creates or truncates the destination file, while `dup2()` redirects standard output to that file.

For signal handling, the shell ignores `SIGINT`, while child processes restore its default behaviour before executing external programs. This allows Ctrl-C to terminate a foreground command without terminating the shell itself.

## 7. Limitations

- Command parsing does not support quoted arguments or escaped spaces.
- Pipes, input redirection and output append operations are not implemented.
- Background processes are reaped when the shell returns to its prompt loop, not immediately while waiting for input.
- Full job control and separate process groups are not implemented.
- Built-in command output redirection is not supported.

## 8. Testing

Testing covers command parsing, external command execution, built-in commands, exit-status reporting, background execution, output redirection and Ctrl-C handling.

Detailed test cases and their actual results are documented in `tests/test_plan.md`.

## 9. Sources and Acknowledgements

Implementation references include:

- Linux manual pages: `fork(2)`, `execvp(3)`, `waitpid(2)`, `getline(3)`, `open(2)`, `dup2(2)` and `signal(2)`.
- GNU C Library documentation.
- Course materials for ICS 2300.

**AI Assistance Declaration:** AI assistance was used for programming guidance, debugging and explanations during development. The implementation was reviewed and tested.
