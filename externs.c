/*
    FILE:       externs.c
    PURPOSE:    file for external program functions including
				print_help, joke, print_history, last_cmd, and former_cmd
    AUTHOR:     Finlay Miller B00675696
    DATE:       13 June 2018
*/

#include "externs.h"

void print_help(void)
{
	/*
        PURPOSE:    Print help information
        INPUT:      None
        OUTPUT:     Text to screen
    */

	printf("Currently supported commands:\n");
	printf("exit\t\tExits the shell.\n");
	printf("help\t\tBrings up this text.\n");
	printf("history\t\tBrings up a list of the last 10 commands entered.\n");
	printf("joke\t\tPrints a joke.\n");
	printf("!!\t\tExecutes the last command entered.\n");
	printf("!N\t\tExecutes the Nth last command entered.\n");
}

void joke()
{
	/*
        PURPOSE:    Prints a joke
        INPUT:      None
        OUTPUT:     A joke
    */

	printf("What do you call a fish with no eye?\n");
	sleep(1);
	printf(".\n");
	sleep(1);
	printf(".\n");
	sleep(1);
	printf(".\n");
	sleep(1);
	printf("A fsh!\n");
	sleep(1);
}

void print_history(char *array[], int cnt)
{
	/*
        PURPOSE:    Prints command history to screen
        INPUT:      Array of command previoulsy executed, amount of commands saved
        OUTPUT:     None
    */

	int i = 10;

	// if less than 10 cmds are saved
	if (cnt <= 10)
	{
		while (cnt != 0)
		{
			printf("%d\t%s\n", cnt, array[cnt - 1]);

			i++;
			if (i == 10) break;

			cnt--;
		}
	}
	// if more than 10 cmds are saved
	else
	{
		while (cnt != 0)
		{
			printf("%d\t%s\n", cnt, array[cnt - 1]);

			i--;
			if (i == 0) break;

			cnt--;
		}
	}
}

char *last_cmd(char *array[], int cnt)
{
	/*
        PURPOSE:    Executes the last executed command
        INPUT:      Array of command previoulsy executed, amount of commands saved
        OUTPUT:     Last command executed
    */

	char *command = array[cnt - 1];
	return command;
}

char *former_cmd(char *array[], int cnt, int index)
{
	/*
        PURPOSE:    Executes an old command
        INPUT:      Array of command previoulsy executed, amount of commands saved,
					index of command to execute
        OUTPUT:     Command to execute
    */

	int i = 10;
	char *command;

	if (cnt <= 10) command = array[index - 1];
	else command = array[cnt + index - 11];

	return command;
}