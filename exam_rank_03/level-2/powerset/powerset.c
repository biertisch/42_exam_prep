#include <stdlib.h>
#include <stdio.h>

void print_arr(int *arr, int count)
{
	if (!count)
		return;
	for (int i = 0; i < count; i++)
	{
		printf("%d", arr[i]);
		if (i < count - 1)
			printf(" ");
	}
	printf("\n");
}

void powerset(int *in, int *out, int target, int size, int sum, int i, int j)
{
	if (i == size)
	{
		if (sum == target)
			print_arr(out, j);
		return;
	}
	powerset(in, out, target, size, sum, i + 1, j);
	out[j] = in[i];
	powerset(in, out, target, size, sum + in[i], i + 1, j + 1);
}

int	main(int argc, char **argv)
{
	if (argc < 3)
		return (1);
	int target = atoi(argv[1]);
	int size = argc - 2;
	int *in = calloc(sizeof(int), size);
	int *out = calloc(sizeof(int), size);
	if (!in || !out)
	{
		free(in);
		free(out);
		return (1);
	}
	for (int i = 0; i < size; i++)
		in[i] = atoi(argv[i + 2]);
	powerset(in, out, target, size, 0, 0, 0);
	free(in);
	free(out);
	return (0);
}
