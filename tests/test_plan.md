# msh Test Plan

## 1. Objective

To verify that the minimal C shell correctly handles user input, command execution, built-in commands, process management, output redirection and signal handling.

## 2. Test Cases

| Test ID | Feature | Test Procedure | Expected Result | Actual Result |
|---|---|---|---|---|
| TC01 | Dynamic input | Enter a long command | Input is accepted | Pending |
| TC02 | Blank input | Press Enter | Shell continues | Pending |
| TC03 | Argument parsing | Run `echo Hello World` | Displays Hello World | Pending |
| TC04 | External execution | Run `ls` | Directory listing appears | Pending |
| TC05 | Invalid command | Run `invalidcommand` | Error and status 127 | Pending |
| TC06 | Help | Run `help` | Built-in help appears | Pending |
| TC07 | Change directory | Run `cd /tmp`, then `pwd` | Displays /tmp | Pending |
| TC08 | Exit status | Run `false` | Prompt displays status 1 | Pending |
| TC09 | Background process | Run `sleep 5 &` | Returns prompt and displays PID | Pending |
| TC10 | Output redirection | Run `echo Hello > output.txt` | File is created | Pending |
| TC11 | Redirection verification | Run `cat output.txt` | Displays Hello | Pending |
| TC12 | Ctrl-C at prompt | Press Ctrl-C | Shell remains active | Pending |
| TC13 | Ctrl-C during execution | Run `sleep 100`, then press Ctrl-C | Child terminates; shell survives | Pending |
| TC14 | EOF handling | Press Ctrl-D | Shell exits cleanly | Pending |

## 3. Additional Tests

1. Run a command with multiple spaces and tabs between arguments.
2. Run `cd` without arguments and verify that the shell returns to the home directory.
3. Overwrite an existing output file using `>` and verify that the old content is replaced.

## 4. Test Summary

**Total planned tests:** 17

**Passed:** [Update after testing]

**Failed:** [Update after testing]

**Pending:** [Update after testing]


