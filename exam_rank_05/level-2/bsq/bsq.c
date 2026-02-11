#include "bsq.h"

static void free_matrix(int** matrix, int height)
{
	if (!matrix)
		return;

	for (int i = 0; i < height; i++)
		free(matrix[i]);
	free(matrix);
}

static void free_string_array(char** array)
{
	if (!array)
		return;

	for(int i = 0; array[i]; i++)
		free(array[i]);
	free(array);
}

static char* ft_strdup(char* src, int len)
{
	if (!src || len < 1)
		return NULL;

	char* dest = calloc(len + 1, sizeof(char));
	if (!dest)
		return NULL;

	int i;
	for (i = 0; i < len && src[i]; i++)
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

static int validate_line(char* line, t_map* map)
{
	if (!line || !map)
		return 0;

	for (int i = 0; line[i]; i++)
	{
		if (line[i] != map->empty && line[i] != map->obstacle)
			return 0;
	}
	return 1;
}

static int validate_parameters(FILE* file, t_map* map)
{
	if (fscanf(file, "%d %c %c %c", &map->height, &map->empty, &map->obstacle, &map->full) != 4)
		return 0;

	if (map->height < 1)
		return 0;
	if (map->empty < 32 || map->empty > 126)
		return 0;
	if (map->obstacle < 32 || map->obstacle > 126)
		return 0;
	if (map->full < 32 || map->full > 126)
		return 0;
	if (map->empty == map->obstacle || map->empty == map->full || map->obstacle == map->full)
		return 0;

	return 1;
}

static int validate_map(FILE* file, t_map* map)
{
	if (!file || !map || !validate_parameters(file, map))
		return 0;

	char* line = NULL;
	size_t len = 0;
	if (getline(&line, &len, file) == -1 || !line || line[0] != '\n')
		return 0;

	map->grid = calloc(map->height + 1, sizeof(char*));
	if (!map->grid)
		return 0;

	for (int i = 0; i < map->height; i++)
	{
		free(line);
		line = NULL;
		len = 0;
		int read = getline(&line, &len, file);
		if (read < 1)
		{
			free(line);
			free_string_array(map->grid);
			return 0;
		}

		if (line[read - 1] == '\n')
			read--;

		map->grid[i] = ft_strdup(line, read);
		if (!map->grid[i])
		{
			free(line);
			free_string_array(map->grid);
			return 0;
		}

		if (i == 0)
			map->width = read;
		if (read != map->width || !validate_line(map->grid[i], map))
		{
			free(line);
			free_string_array(map->grid);
			return 0;
		}
	}

	free(line);
	return 1;
}

static int find_biggest_square(t_map* map)
{
	map->bsq.size = 0;
	int** matrix = malloc(map->height * sizeof(int*));
	if (!matrix)
		return 0;

	for (int i = 0; i < map->height; i++)
	{
		matrix[i] = malloc(map->width * sizeof(int));
		if (!matrix[i])
		{
			free_matrix(matrix, map->height);
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
					matrix[i - 1][j - 1],
					matrix[i - 1][j],
					matrix[i][j - 1]
				);

			if (matrix[i][j] > map->bsq.size)
			{
				map->bsq.size = matrix[i][j];
				map->bsq.x = i - map->bsq.size + 1;
				map->bsq.y = j - map->bsq.size + 1;
			}
		}
	}

	free_matrix(matrix, map->height);
	return 1;
}

void print_map(t_map* map)
{
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

int bsq(FILE* file)
{
	if (!file)
	{
		printf("map error\n");
		return 1;
	}

	t_map map;
	if (!validate_map(file, &map))
	{
		printf("map error\n");
		return 1;
	}

	if (!find_biggest_square(&map))
	{
		printf("memory allocation failed\n");
		return 1;
	};
	print_map(&map);
	free_string_array(map.grid);
	return 0;
}

int main(int argc, char** argv)
{
	if (argc > 2)
	{
		printf("invalid number of arguments\n");
		return 1;
	}

	if (argc == 1)
		return bsq(stdin);

	FILE* file = fopen(argv[1], "r");
	if (!file)
	{
		printf("map error\n");
		return 1;
	}
	int ret = bsq(file);
	if (ret)
		printf("map error\n");
	fclose(file);

	return ret;
}