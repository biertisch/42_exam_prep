#include "flood_fill.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void	print_tab(char **map, t_point size)
{
	int i = 0;
	int j = 0;

	while (i < size.x)
	{
		j = 0;
		while (j < size.y)
		{
			printf("%c", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

char **make_map(char **zone, t_point size)
{
	int i;
	char **map;

	map = malloc(sizeof(char *) * (size.x + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (i < size.x)
	{
		map[i] = strdup(zone[i]);
		if (!map[i])
		{
			while (--i >= 0)
				free(map[i]);
			free(map);
			return (NULL);
		}
		i++;
	}
	map[i] = NULL;
	return (map);
}

int main(void)
{
	char **map;
	t_point size = {5, 8};
	t_point begin = {1, 1};
	char *zone[] = {
		"11111111",
		"10001001",
		"10010001",
		"10110001",
		"11100001",
	};
	map = make_map(zone, size);
	print_tab(map, size);
	flood_fill(map, size, begin);
	printf("\n");
	print_tab(map, size);
	return (0);
}