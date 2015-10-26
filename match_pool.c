#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	int i = 0;
	char buffer[1024];
	char *res = NULL;
	char *pool = NULL;
	char *local_pool = NULL;
	size_t pool_size = 0;


	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <character pool>\n", argv[0]);
		return EXIT_FAILURE;
	}

	pool = argv[1];
	pool_size = strlen(pool);

	local_pool = malloc(pool_size);
	if (local_pool == NULL)
	{
		fprintf(stderr, "%s: malloc for local pool failed\n", argv[0]);
		return EXIT_FAILURE;
	}

	while (fgets(buffer, sizeof(buffer), stdin))
	{
		buffer[strcspn(buffer, "\r\n")] = '\0'; /* chomp */

		if (strlen(buffer) == 0)
			continue;

		strcpy(local_pool, pool);
		for (i = strlen(buffer)-1; i >= 0; i--)
		{
			if ((res = memchr(local_pool, buffer[i], pool_size)) != NULL)
				*res = '\0';
			else
				break;
		}
		printf("%s %s\n", buffer, i < 0? "matches" : "doesn't match" );
	}
	return 0;
}
