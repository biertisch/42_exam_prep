#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int match(char *s1, char *s2)
{
	for (int i = 0; s2[i]; i++)
		if (s1[i] != s2[i])
			return (0);
	return (1);
}

void filter(char *res, char *sep, int len)
{
	for (int i = 0; res[i]; i++)
	{
		if (match(res + i, sep))
		{
			for (int j = 0; j < len; j++)
			{
				res[i] = '*';
				if (j != len - 1)
					i++;
			}
		}
	}	
	printf("%s", res);
}

char *read_stdin(void)
{
	int size = 50;
	char *res = calloc(sizeof(char), size);
	if (!res)
	{
		perror("Error: memory allocation failed\n");
		return (NULL);
	}
	char c;
	int	bytes_read;
	int i = 0;
	while (bytes_read = read(0, &c, 1) > 0)
	{
		if (i >= size - 1)
		{
			size *= 2;
			char *tmp = realloc(res, size);
			if (!tmp)
			{
				free(res);
				perror("Error: memory allocation failed\n");
				return (NULL);
			}
			res = tmp;
		}
		res[i++] = c;
	}
	if (bytes_read == -1)
	{
		free(res);
		perror("Error: failure to read from stdin\n");
		return (NULL);
	}
	return (res);
}

int	main(int argc, char **argv)
{
	if (argc != 2 || !argv[1][0])
		return (1);
	char *res = read_stdin();
	if (!res)
		return (1);	
	filter(res, argv[1], strlen(argv[1]));
	free(res);
	return (0);
}
