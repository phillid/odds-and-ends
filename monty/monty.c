/*
 * monty - Hacked-together tool to simulate the Monty Hall problem. Still can't
 *         get my head around it ;)
 * Copyright (c) 2017 David Phillips <dbphillipsnz@gmail.com>
 * All rights reserved
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

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
	int doors = 3;

	srand(time(NULL));

	/* "stick/stay/lazy" strategy */
	wins = monty(doors, runs, STRATEGY_STICK);
	ratio = ((double)wins) / runs;
	printf("Stick : Won %d of %d (%.5f) success\n", wins, runs, ratio);

	/* "change" strategy */
	wins = monty(doors, runs, STRATEGY_CHANGE);
	ratio = ((double)wins) / runs;
	printf("Change: Won %d of %d (%.5f) success\n", wins, runs, ratio);

	return 0;
}
