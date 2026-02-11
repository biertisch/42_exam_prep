#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		int n = atoi(argv[1]);
		int i = 2;
		if (n < 2)
			printf("%d", n);
		while (n > 1)
		{
			while (n % i == 0)
			{
				printf("%d", i);
				if (n != i)
					printf("*");
				n /= i;
			}
			i++;
		}
	}
	printf("\n");
	return (0);
}
