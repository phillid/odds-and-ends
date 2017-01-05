

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


enum Strategy {
	STRATEGY_STICK,
	STRATEGY_CHANGE
};


unsigned int monty(int door_count, unsigned long plays, enum Strategy strategy)
{
	unsigned int i = 0;
	int door = 0;
	unsigned int wins = 0;
	int prize = -1;
	int choice = -1;
	int remain = -1;

	for (i = 0; i < plays; i++) {
		prize = rand() % door_count;
		choice = rand() % door_count;

		/* Monty shall open all doors except two; the contestant's choice
		 * and pick one door to not open */
		if (choice == prize) {
			/* contestant was originally correct? Pick any other door aside
			 * from their choice to remain. Crude loop strategy, but pseudo-
			 * randomness should help ensure quick termination */
			do {
				remain = rand() % door_count;
			} while (remain == choice);
		} else {
			/* contestant never originally picked prize door; the prize door
			 * remains */
			remain = prize;
		}

		switch (strategy) {
		case STRATEGY_STICK:
			/* stick with current door */
			break;
		case STRATEGY_CHANGE:
			/* `change` strategy: switch to remaining door */
			choice = remain;
			break;
		default:
			return -1;
		}
		if (choice == prize)
			wins++;
	}
	return wins;
}


int main()
{
	double ratio = 0;
	int runs = 1000000;
	int wins = 0;

	srand(time(NULL));

	/* "stick/stay/lazy" strategy */
	wins = monty(3, runs, STRATEGY_STICK);
	ratio = ((double)wins) / runs;
	printf("Stick : Won %d of %d (%.5f) success\n", wins, runs, ratio);

	/* "change" strategy */
	wins = monty(3, runs, STRATEGY_CHANGE);
	ratio = ((double)wins) / runs;
	printf("Change: Won %d of %d (%.5f) success\n", wins, runs, ratio);

	return 0;
}
