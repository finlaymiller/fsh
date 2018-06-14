## fsh: A simple C shell
### CSCI3120 Assignment 1

Finlay Miller - B00675696 - 13 JUNE 2018

---
To compile: `gcc -g -o fsh fsh.c externs.c`

The included image _fsh.png_ shows several types of command being executed:
1. `!2` - Executing the 2nd last command executed
2. `mkdir tempfolder &` - Creation of a child process
3. `history` - Printing of the last 10 command executed