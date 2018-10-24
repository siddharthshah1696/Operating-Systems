/* This program takes in an argument, a number of seconds.
It creates a copy of itself, the child waits that many seconds,
and both of them die. */
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_TIME 0

int main (int argc, char **argv) {
	int child_id;
	int seconds;

	if (argc == 1)
		seconds = DEFAULT_TIME;
	else
		seconds = atoi (argv[1]);

	printf ("Here I am in the program!  Seconds = %d\n", seconds);

	child_id = fork();

	if (child_id) {
		printf ("I'm the parent.  Bye now!\n");
		}
	else {
		sleep(seconds);
		printf ("I'm the child.  Bye now!\n");
		}
	return 0;
	}
