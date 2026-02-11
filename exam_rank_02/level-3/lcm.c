#include <stdio.h>

unsigned int	lcm(unsigned int a, unsigned int b)
{
	int hcf;
	int res;
	if (a == 0 || b == 0)
		return (0);
	if (a < b)
		hcf = a;
	else
		hcf = b;
	while (a % hcf != 0 || b % hcf != 0)
		hcf--;
	res = a * b / hcf;
	return (res);
}

/* int main(void)
{
	printf("%d\n", lcm(5, 4));
	printf("%d\n", lcm(3, 12));
	printf("%d\n", lcm(12, 15));
	printf("%d\n", lcm(12, 30));
	return (0);
} */