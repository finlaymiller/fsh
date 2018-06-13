#ifndef FSH_H
#define FSH_H
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <string.h>
#include <sys/types.h>
#define MAX_LINE_LEN 80 /* The maximum length of command */

void print_history(char *array[], int count);
char *run_last_cmd(char *array[], int count);
char *run_specific_cmd(char *array[], int count, int index);
#endif