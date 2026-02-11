#include <stdlib.h>
#include <unistd.h>
#include <stdio.h> //TESTING
#include <fcntl.h> //TESTING

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 50
#endif

char *get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	static int i;
	static int len;
	char *line = malloc(10000);
	int j = 0;

	if (fd < 0 || BUFFER_SIZE < 1 || !line)
	{
		free(line);
		return (NULL);
	}
	while (1)
	{
		if (i >= len)
		{
			i = 0;
			len = read(fd, buffer, BUFFER_SIZE);
			if (len <= 0)
				break ;
		}
		line[j++] = buffer[i++];
		if (line[j - 1] == '\n')
			break ;
	}
	if (j == 0)
	{
		free(line);
		return (NULL);
	}
	line[j] = '\0';
	return (line);
}

//TESTING
int main(void)
{
	char	*line;
	int fd = open("test.txt", O_RDONLY);
	for (int i = 0; line = get_next_line(fd); i++)
	{
		printf("LINE %d: %s", i, line);
		free(line);
	}
	printf("\n");
	close(fd);
}
