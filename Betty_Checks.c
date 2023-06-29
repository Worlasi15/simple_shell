#include "shell.h"
#include <stdio.h>
#include <unistd.h>

/**
  * print_sen - function that
  * prints a sentence
  *
  */

void print_sen(void)
{
	char display[] = "Beginning of a new shell creation.\n";

	write(STDOUT_FILENO, display, sizeof(display));
}
