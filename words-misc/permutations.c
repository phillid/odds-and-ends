#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap_chr(char*, char*);
void p(char *, size_t, size_t);
void die_help(const char*);

int main(int argc, char **argv)
{
	if (argc != 2)
		die_help(argv[0]);

	p(argv[1], strlen(argv[1]), 0);

	return 0;
}

void die_help(const char* argv0) {
	fprintf(stderr, "Usage: %s <word>\n", argv0);
	exit(1);
}

void swap_chr(char *a, char *b) {
	char t = *a;
	*a = *b;
	*b = t;
}

void p(char *string, size_t x, size_t i) {
	size_t j = 0;

	if (i == x) {
		puts(string);
		return;
	}

	for (j = i; j < x; j++) {
		swap_chr(&string[i], &string[j]);
		p(string, x, i+1);
		swap_chr(&string[i], &string[j]);
	}
}
