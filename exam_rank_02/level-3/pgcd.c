#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	if (argc == 3)
	{
		int a = atoi(argv[1]);
		int b = atoi(argv[2]);
		int res;

		if (a < b)
			res = a;
		else
			res = b;
		while (a % res != 0 || b % res != 0)
			res--;
		printf("%d", res);
	}
	printf("\n");
	return (0);
}