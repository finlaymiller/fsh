#include "externs.h"

int print_help(void)
{
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
	printf("What do you call a fish with no eye?\n");
	sleep(1);
	printf(".\n");
	sleep(1);
	printf(".\n");
	sleep(1);
	printf(".\n");
	sleep(1);
	printf("A fsh!\n");
}

void print_history(char *array[], int cnt, size_t size)
{
	int i = 10;
	printf("Count is %d\n", cnt);
	printf("Size is %d\n", size);

	// if less than 10 cmds are saved
	if (cnt <= 10)
	{
		while (cnt != 0)
		{
			printf("%d\t%s\n", size - cnt, array[cnt - 1]);
			i++;
			if (i == 10)
				break;
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
			if (i == 0)
				break;
			cnt--;
		}
	}
}

char *run_last_cmd(char *array[], int cnt)
{
	char *command = array[cnt - 1];
	printf("Command to execute is %s.\n", command);
	return command;
}

char *run_specific_cmd(char *array[], int cnt, int index)
{
	int i = 10;
	char *command;
	printf("count is %d\n", cnt);
	printf("Command to execute is %s.\n", command);

	if (cnt <= 10)
		command = array[index - 1];
	else
	{
		command = array[cnt + index - 11];
	}
	return command;
}