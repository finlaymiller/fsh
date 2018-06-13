#include "fsh.h"

int main(void)
{
    char *args[MAX_LINE_LEN / 2 + 1]; /* command line arguments */
    int should_run = 1;               /* flag to determine when to exit program */
    int i = 0;
    char command[MAX_LINE_LEN];
    pid_t pid;
    int amperflag = 0;
    int check = 0;
    int j;
    int count = 0;
    char *save[MAX_LINE_LEN / 2 + 1];
    char *save_command;
    char *res_command;
    char *tkn;

    while (should_run)
    {
        i = 0;
        amperflag = 0;
        check = 0;
        fflush(stdout);
        fflush(stdin);

        // initialize values
        command[0] = '\0';
        memset(command, 0, MAX_LINE_LEN);
        for (j = 0; j < (MAX_LINE_LEN / 2 + 1); j++)
            args[j] = '\0';
        printf("osh>");

        fgets(command, MAX_LINE_LEN, stdin);
        strtok(command, "\n");
        printf("%c %c %c %c %c %c %c \n", command[0], command[1], command[2], command[3], command[4], command[5], command[6]);
        if (strcmp(command, "exit") == 0)
            should_run = 0;

        // count the number of commands
        save_command = command;
        if (strcmp(save_command, "exit") == 0)
            break;

        // check for 'history' command
        if (strcmp(save_command, "history") != 0 && (save_command[0] != '!'))
        {
            save[count++] = strdup(save_command);
        }
        else if (strcmp(save_command, "history") == 0)
        {
            if (count == 0)
            {
                printf("No commands in history\n");
                continue;
            }
            print_history(save, count);
            continue;
        }
        // check for '!!' command
        if ((strcmp(save_command, "!!") == 0))
        {
            if (count == 0)
            {
                printf("No commands in history\n");
                continue;
            }
            res_command = strdup(run_last_cmd(save, count));
            save[count++] = strdup(res_command);
            strcpy(command, res_command);
        }
        // check for '!' command
        else if (save_command[0] == '!')
        {

            int index = save_command[1] - '0';
            if (save_command[2] - '0' == 0)
                index = 10;
            if (count == 0 || index > count)
            {
                printf("No command in history\n");
                continue;
            }
            res_command = strdup(run_specific_cmd(save, count, index));
            printf(">>>>%s\n", res_command);
            save[count++] = strdup(res_command);
            strcpy(command, res_command);
        }

        tkn = strtok(command, " ");
        while (tkn != NULL)
        {
            args[i++] = tkn;
            tkn = strtok(NULL, " ");
        }
        args[i] = NULL;
        // check the tail of &
        // You can't (usefully) compare strings using != or ==, you need to use strcmp:
        if ((strcmp(args[i - 1], "&") == 0))
        {
            amperflag = 1;
            args[i - 1] = NULL;
        }
        // create a process
        // exit
        if ((strcmp(args[0], "exit") == 0))
            break;

        // handle fork
        pid = fork();

        if (pid < 0)
        {
            fprintf(stderr, "Frok failed");
            return 1;
        }
        else if (pid == 0)
        {
            // child
            if (strcmp(save_command, "exit") == 0)
                break;

            if (strcmp(save_command, "history") == 0 || strcmp(save_command, "!!") == 0 || (save_command[0] == '!'))
            {
                print_history(save, count);
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
            if (strcmp(save_command, "exit") == 0)
                break;

            if (amperflag)
            {
                // sleep until seconds seconds have elapsed
                sleep(1);
                printf("&\tDone.\n");
            }
            else
            {
                wait(NULL);
                printf(">>>Wait Until Child Complete.\n");
            }
        }
    }
    return 0;
}