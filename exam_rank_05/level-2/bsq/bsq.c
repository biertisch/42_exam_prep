#include "bsq.h"

static int ft_isprint(char c)
{
	return c >= 32 && c <= 126;
}

static char* ft_strdup(char* src, int len)
{
	if (!src)
		return NULL;

	char* dest = malloc(len + 1);
	if (!dest)
		return NULL;

	int i = 0;
	for (; i < len && src[i]; i++)
		dest[i] = src[i];

	dest[i] = '\0';
	return dest;
}

static int ft_min(int a, int b, int c)
{
	int min = a;
	if (min > b)
		min = b;
	if (min > c)
		min = c;
	return min;
}

static void free_map(char** grid)
{
	if (!grid)
		return;

	for (int i = 0; grid[i]; i++)
		free(grid[i]);
	free(grid);
}

static void free_matrix(int** array, int size)
{
	if (!array)
		return;

	for (int i = 0; i < size && array[i]; i++)
		free(array[i]);
	free(array);
}

static int parse_parameters(FILE* file, t_map* map)
{
	if (fscanf(file, "%d %c %c %c", &map->height, &map->empty, &map->obstacle, &map->full) != 4)
		return 0;

	if (map->height < 1)
		return 0;
	if (!ft_isprint(map->empty) || !ft_isprint(map->obstacle) || !ft_isprint(map->full))
		return 0;
	if (map->empty == map->obstacle || map->empty == map->full || map->obstacle == map->full)
		return 0;

	char* line = NULL;
	size_t len = 0;
	if (getline(&line, &len, file) != 1 || !line || line[0] != '\n')
	{
		free(line);
		return 0;
	}
	free(line);
	return 1;
}

static int validate_row(char* row, int width, t_map* map)
{
	if (!row || !map)
		return 0;

	if (width != map->width)
		return 0;

	for (int i = 0; row[i]; i++)
		if (row[i] != map->empty && row[i] != map->obstacle)
			return 0;

	return 1;
}

static int parse_rows(FILE* file, t_map* map)
{
	for (int i = 0; i < map->height; i++)
	{
		char* line = NULL;
		size_t len = 0;
		int read = getline(&line, &len, file);
		if (read < 1)
		{
			free(line);
			free_map(map->grid);
			return 0;
		}

		if (line[read - 1] == '\n')
			read--;

		map->grid[i] = ft_strdup(line, read);
		if (!map->grid[i])
		{
			free(line);
			free_map(map->grid);
			return 0;
		}

		if (i == 0)
			map->width = read;
		if (!validate_row(map->grid[i], read, map))
		{
			free(line);
			free_map(map->grid);
			return 0;
		}
		free(line);
	}
	return 1;
}

static int parse_map(FILE* file, t_map* map)
{
	if (!file || !map)
		return 0;

	if (!parse_parameters(file, map))
		return 0;

	map->grid = calloc(map->height + 1, sizeof(char*));
	if (!map->grid)
		return 0;

	return parse_rows(file, map);
}

static int find_biggest_square(t_map* map)
{
	int** matrix = calloc(map->height, sizeof(int*));
	if (!matrix)
		return 0;

	map->bsq.x = 0;
	map->bsq.y = 0;
	map->bsq.size = 0;
	for (int i = 0; i < map->height; i++)
	{
		matrix[i] = calloc(map->width, sizeof(int));
		if (!matrix[i])
		{
			free_matrix(matrix, i);
			return 0;
		}
		for (int j = 0; j < map->width; j++)
		{
			if (map->grid[i][j] == map->obstacle)
				matrix[i][j] = 0;
			else if (i == 0 || j == 0)
				matrix[i][j] = 1;
			else
				matrix[i][j] = 1 + ft_min(
					matrix[i - 1][j],
					matrix[i][j - 1],
					matrix[i - 1][j - 1]
				);

			if (matrix[i][j] > map->bsq.size)
			{
				map->bsq.x = i - matrix[i][j] + 1;
				map->bsq.y = j - matrix[i][j] + 1;
				map->bsq.size = matrix[i][j];
			}
		}
	}

	free_matrix(matrix, map->height);
	return 1;
}

static void print_map(t_map* map)
{
	if (!map)
		return;

	for (int i = 0; i < map->height; i++)
	{
		for (int j = 0; j < map->width; j++)
		{
			if (i >= map->bsq.x && i < map->bsq.x + map->bsq.size
				&& j >= map->bsq.y && j < map->bsq.y + map->bsq.size)
				printf("%c", map->full);
			else
				printf("%c", map->grid[i][j]);
		}
		printf("\n");
	}
}

static int bsq(FILE* file)
{
	if (!file)
	{
		printf("map error\n");
		return 1;
	}

	t_map map;
	if (!parse_map(file, &map))
	{
		printf("map error\n");
		return 1;
	}

	if (!find_biggest_square(&map))
	{
		free_map(map.grid);
		printf("memory allocation failed\n");
		return 1;
	}

	print_map(&map);
	free_map(map.grid);
	return 0;
}

int main(int argc, char** argv)
{
	if (argc > 2)
		return 1;

	if (argc == 1)
		return bsq(stdin);

	FILE* file = fopen(argv[1], "r");
	if (!file)
	{
		printf("map error\n");
		return 1;
	}
	int ret = bsq(file);
	fclose(file);
	return ret;
}