#include <stdio.h>

int max(int *tab, unsigned int len)
{
	int res = 0;
	unsigned int i = 0;
	if (len > 0)
		res = tab[0];
	while (i < len)
	{
		if (res < tab[i])
			res = tab[i];
		i++;
	}
	return (res);
}

/* int main(void)
{
	int tab0[] = {4, 8, 10, 3, 1};
	printf("%d\n", max(tab0, 5));

	int tab1[] = {-4, -8, -10, -3, -1};
	printf("%d\n", max(tab1, 5));

	int tab2[] = {4, 8, 10, 3, 1, 20};
	printf("%d\n", max(tab2, 6));

	int tab3[] = {20, 4, 8, 10, 3, 1};
	printf("%d\n", max(tab3, 6));

	int tab4[] = {};
	printf("%d\n", max(tab4, 0));
} */