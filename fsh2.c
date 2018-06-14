/*
    FILE:       fsh.c
    PURPOSE:    mainfile for program
    AUTHOR:     Finlay Miller B00675696
    DATE:       13 June 2018
*/

#include "fsh.h"

int main(void)
{
    /*
        PURPOSE:    Creates a simple C shell
        INPUT:      None
        OUTPUT:     0 if completion successful, 1 otherwise
    */

    // variable declaration
    char *args[MAX_LINE_LEN / 2 + 1];    // an array of arguments
    char command[MAX_LINE_LEN];          // the input command
    char *history[MAX_LINE_LEN / 2 + 1]; // an array of saved commands
    char *current_cmd;                   // the command currently being worked with
    char *tmp_cmd;                       // a temporary command holder used when handling '!!' or '!'
    char *tkn;                           // a pointer to the first token of the command
    int should_run = 1;                  // flag for controlling whether or not the program should run
    int i;                               // the counter for the args array
    int j;                               // the counter used to initially clear args array
    int amperflag;                       // flag set when '&' character is detected
    int count = 0;                       // the number of commands in history
    int index;                           // the index of the command to execute, used with '!'
    pid_t pid;                           // the process identification number
    size_t size;                         // the size of the history array

    // initial screen writes
    printf("\n\nfsh shell interface - Version %s (%s)\n", CURRENT_VERSION, UPDATE_DATE);
    printf("Written by Finlay Miller (B00675696) for CSCI3120 Assignment #1\n");
    printf("Enter 'fhelp' for help.\n\n\n");

    while (should_run) // should_run = 1
    {
        // initialize values
        fflush(stdin);
        fflush(stdout);
        i = 0;
        command[0] = '\0';
        amperflag = 0;
        memset(command, 0, MAX_LINE_LEN);
        for (j = 0; j < (MAX_LINE_LEN / 2 + 1); j++)
            args[j] = '\0';

        // print prompt
        printf("fsh>");

        // get input
        fgets(command, MAX_LINE_LEN, stdin);
        strtok(command, "\n");

        // check right away for exit command
        if (strcmp(command, "exit") == 0)
        {
            should_run = 0;
            break;
        }

        // copy command pointer to preserve original command
        current_cmd = command;

        // check for 'history' command
        if (strcmp(current_cmd, "history") == 0)
        {
            if (count == 0)
            {
                printf("No commands in history\n");
                continue;
            }
            print_history(history, count);
            continue;
        }
        // check for '!!' command
        else if ((strcmp(current_cmd, "!!") == 0))
        {
            if (count == 0)
            {
                printf("No commands in history\n");
                continue;
            }
            tmp_cmd = strdup(last_cmd(history, count));
            history[count++] = strdup(tmp_cmd);
            strcpy(command, tmp_cmd);
        }
        // check for '!' command
        else if (current_cmd[0] == '!')
        {

            int index = current_cmd[1] - '0';
            if (current_cmd[2] - '0' == 0)
                index = 10;
            if (count == 0 || index > count)
            {
                printf("No command in history\n");
                continue;
            }
            // execute selected command
            tmp_cmd = strdup(former_cmd(history, count, index));
            history[count++] = strdup(tmp_cmd);
            strcpy(command, tmp_cmd);
        }
        // check for 'fhelp' command
        else if (strcmp(current_cmd, "fhelp") == 0)
        {
            print_help();
        }
        // check for 'joke' command
        else if (strcmp(current_cmd, "joke") == 0)
        {
            joke();
        }
        // default
        else
            history[count++] = strdup(current_cmd);

        // once specific commands are checked for, tokenize the command string
        tkn = strtok(command, " ");
        while (tkn != NULL)
        {
            args[i++] = tkn;
            tkn = strtok(NULL, " ");
        }
        args[i] = NULL;

        // check for '&'
        if ((strcmp(args[i - 1], "&") == 0))
        {
            amperflag = 1;
            args[i - 1] = NULL;
        }

        // once tokenized, fork
        pid = fork();

        if (pid < 0)
        {
            fprintf(stderr, "Fork failed");
            return 1;
        }
        else if (pid == 0)
        {
            // make child
            if (strcmp(current_cmd, "exit") == 0)
            {
                should_run = 0;
                break;
            }

            // add command to history
            else
                execvp(args[0], args);
        }
        else
        {
            // make parent
            if (strcmp(current_cmd, "exit") == 0)
            {
                should_run = 0;
                break;
            }

            if (amperflag)
            {
                // sleep until 1 second has elapsed
                sleep(1);
                printf("\nDone\n");
            }
            // wait until child is complete
            else wait(NULL);
        }
    } // should_run != 1

    return 0;
}