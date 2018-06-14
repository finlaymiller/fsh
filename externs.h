/*
    FILE:       externs.h
    PURPOSE:    headerfile for external program functions
    AUTHOR:     Finlay Miller B00675696
    DATE:       13 June 2018
*/

#ifndef EXTERNS_H
#define EXTERNS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include "fsh.h"

#define MAX_LINE_LEN 80

void print_history(char *array[], int count);
char *run_last_cmd(char *array[], int count);
char *run_specific_cmd(char *array[], int count, int index);
void print_help(void);
void joke(void);

#endif