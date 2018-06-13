#include "fsh.h"

int main(void)
{
    char *args[MAX_LINE_LEN / 2 + 1];   // an array of arguments
    char command[MAX_LINE_LEN];         // the input command
    char *history[MAX_LINE_LEN / 2 + 1];// an array of saved commands
    char *current_cmd;                  // the command currently being worked with
    char *tmp_command;                  // a temporary command holder used when handling '!!' or '!'
    char *tkn;                          // a pointer to the first token of the command
    int should_run = 1;                 // flag for controlling whether or not the program should run
    int i;                              // the counter for the args array
    int j;                              // the counter used to initially clear args array
    int amperflag;                      // flag set when '&' character is detected
    int count = 0;                      // the number of commands in history
    pid_t pid;                          // the process identification number
    size_t size;                        // the size of the history array
    int k = 0;

    //lsta
    //lstb
    //con-ptr-500
    //rcl
    printf("\n\nfsh shell interface - Version %s (%s)\n", CURRENT_VERSION, UPDATE_DATE);
	printf("Written by Finlay Miller (B00675696) for CSCI3120 Assignment #1\n");
    printf("Enter 'fhelp' for help.\n\n\n");

    while (should_run)
    {
        // initialize values
        i = 0;
        amperflag = 0;
        fflush(stdin);
        fflush(stdout);
        command[0] = '\0';
        memset(command, 0, MAX_LINE_LEN);
        for (j = 0; j < (MAX_LINE_LEN / 2 + 1); j++)
        {
            args[j] = '\0';
            history[j] = NULL;
        } 

        printf("fsh> ");

        // get input and check for exit command
        fgets(command, MAX_LINE_LEN, stdin);
        strtok(command, "\n");
        if (strcmp(command, "exit") == 0)
        {
            should_run = 0;
            break;
        }

        // set command pointer to preserve original string
        current_cmd = command;

        // check for 'fhelp' command
        if (strcmp(current_cmd, "fhelp") == 0)
        {
            if(!print_help())
                printf("Failed to print help.\n");
        }

        if ((strcmp(current_cmd, "history") != 0) && (current_cmd[0] != '!'))
        {
            history[count++] = strdup(current_cmd);
        }
        // check for 'history' command
        else if (strcmp(current_cmd, "history") == 0)
        {
            if (count == 0)
            {
                printf("No commands in history\n");
                continue;
            }
            
            k = 0;
            while(history[k] != NULL) 
            {
                printf("history[k] is %s\n", history[k]);
                k++;
            }
            size = k;

            print_history(history, count, size);
            continue;
        }

        // check for '!!' command
        if ((strcmp(current_cmd, "!!") == 0))
        {
            if (count == 0)
            {
                printf("No commands in history\n");
                continue;
            }
            
            // run last command
            tmp_command = strdup(run_last_cmd(history, count));
            history[count++] = strdup(tmp_command);
            strcpy(command, tmp_command);
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
            
            // run specified command
            tmp_command = strdup(run_specific_cmd(history, count, index));
            history[count++] = strdup(tmp_command);
            strcpy(command, tmp_command);
        }

        if(strcmp(current_cmd, "joke") == 0)
            joke();

        // once specific commands are checked for, tokenize the command string
        tkn = strtok(command, " ");
        while (tkn != NULL)
        {
            args[i++] = tkn;
            tkn = strtok(NULL, " ");
        }

        // add null terminator
        args[i] = NULL;

        // check for ampersand
        if ((strcmp(args[i - 1], "&") == 0))
        {
            amperflag = 1;
            args[i - 1] = NULL;
        }

        // handle fork
        pid = fork();

        if (pid < 0)
        {
            fprintf(stderr, "Fork failed.\n");
            return 1;
        }
        else if (pid == 0)
        {
            // child
            if (strcmp(current_cmd, "exit") == 0)
                break;

            if (strcmp(current_cmd, "history") == 0 || strcmp(current_cmd, "!!") == 0 || (current_cmd[0] == '!'))
            {
                printf("/n/n/t/tHERE/n/n");
                while(history[k] != '\0') k++;
                size = k;
                print_history(history, count, size);
            }
            else
            {
                // add command to history
                execvp(args[0], args);
            }
        }
        else
        {
            // parent
            if (strcmp(current_cmd, "exit") == 0)
                break;

            if (amperflag)
            {
                // sleep until seconds have elapsed
                sleep(1);
                printf("\tDone.\n");
            }
            // wait for child processes to complete
            else wait(NULL);
        }
    }
    return 0;
}