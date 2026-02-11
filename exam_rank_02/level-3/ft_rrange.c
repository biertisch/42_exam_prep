#include <stdlib.h>
#include <stdio.h>

int	*ft_rrange(int start, int end)
{
	int size;
	int i;
	int *arr;

	size = end - start; 
	if (size < 0)
		size *= -1;
	size++;
	arr = malloc(sizeof(int) * size);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < size)
	{
		if (start <= end)
			arr[i] = end - i;
		else
			arr[i] = end + i;
		i++;
	}
	return (arr);
}

/* int main(void)
{
	int *arr;
	int i = 0;
	
	arr = ft_rrange(1, 3);
	while (i < 3)
	{
		printf("%d ", arr[i]);
		i++;
	}
	printf("\n");
	free (arr);

	arr = ft_rrange(-1, 2);
	i = 0;
	while (i < 4)
	{
		printf("%d ", arr[i]);
		i++;
	}
	printf("\n");
	free (arr);

	arr = ft_rrange(0, 0);
	i = 0;
	while (i < 1)
	{
		printf("%d ", arr[i]);
		i++;
	}
	printf("\n");
	free (arr);

	arr = ft_rrange(0, -3);
	i = 0;
	while (i < 4)
	{
		printf("%d ", arr[i]);
		i++;
	}
	printf("\n");
	free (arr);
} */