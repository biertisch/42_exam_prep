#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <float.h>

// compute the distance between two points
float    distance(float a[2], float b[2])
{
    return sqrtf((b[0] - a[0]) * (b[0] - a[0]) + (b[1] - a[1]) * (b[1] - a[1]));
}

void ft_swap(float (*a)[2], float (*b)[2])
{
	float tmp[2];
	memcpy(tmp, *a, sizeof(float) * 2);
	memcpy(*a, *b, sizeof(float) * 2);
	memcpy(*b, tmp, sizeof(float) * 2);
}

void	permute(float (*array)[2], int start, int size, float *best)
{
	if (start == size)
	{
		float len = 0;
		for (int i = 0; i < size - 1; i++)
			len += distance(array[i], array[i + 1]);
		len += distance(array[size - 1], array[0]);
		if (len < *best)
			*best = len;
		return;
	}
	for (int i = start; i < size; i++)
	{
		ft_swap(&array[start], &array[i]);
		permute(array, start + 1, size, best);
		ft_swap(&array[start], &array[i]);
	}
}

float tsp(float (*array)[2], ssize_t size)
{
    float best = FLT_MAX;
	permute(array, 0, size, &best);
	return (best);
}

ssize_t    file_size(FILE *file)
{
    char    *buffer = NULL;
    size_t    n = 0;
    ssize_t ret;

    errno = 0;

    for (ret = 0; getline(&buffer, &n, file) != -1; ret++);

    free(buffer);
    if (errno || fseek(file, 0, SEEK_SET))
        return -1;
    return ret;
}

int        retrieve_file(float (*array)[2], FILE *file)
{
    int tmp;
    for (size_t i = 0; (tmp = fscanf(file, "%f, %f\n", array[i] + 0, array[i] + 1)) != EOF; i++)
        if (tmp != 2)
        {
            errno = EINVAL;
            return -1;
        }
    if (ferror(file))
        return -1;
    return 0;
}

int        main(int ac, char **av)
{
    char *filename = "stdin";
    FILE *file = stdin;
    if (ac > 1)
    {
        filename = av[1];
        file = fopen(filename, "r");
    }

    if (!file)
    {
        fprintf(stderr, "Error opening %s: %m\n", filename);
        return 1;
    }

    ssize_t size = file_size(file);
    if (size == -1)
    {
        fprintf(stderr, "Error reading %s: %m\n", filename);
        fclose(file);
        return 1;
    }

    float (*array)[2] = calloc(size, sizeof (float [2]));
    if (!array)
    {
        fprintf(stderr, "Error: %m\n");
        fclose(file);
        return 1;
    }

    if (retrieve_file(array, file) == -1)
    {
        fprintf(stderr, "Error reading %s: %m\n", av[1]);
        fclose(file);
        free(array);
        return 1;
    }
    if (ac > 1)
        fclose(file);

    printf("%.2f\n", tsp(array, size));
    free(array);
    return (0);
}
