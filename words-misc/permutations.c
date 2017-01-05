#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* FIXME hacked together 6 months ago, not sure if finished */
/* FIXME does duplicates */

void swap_chr(char*, char*);
void p(char *, size_t);

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <word>\n", argv[0]);
		return EXIT_FAILURE;
	}

	p(argv[1], 0);

	return 0;
}

void swap_chr(char *a, char *b) {
	char t = *a;
	*a = *b;
	*b = t;
}

void p(char *string, size_t x)
{
	size_t i = 0;

	if (x == strlen(string)) {
		puts(string);
		return;
	}
	for (i = 0; i < strlen(string); i++) {
		swap_chr(&string[x], &string[i]);
		p(string, x + 1);
		swap_chr(&string[x], &string[i]);
	}
}
