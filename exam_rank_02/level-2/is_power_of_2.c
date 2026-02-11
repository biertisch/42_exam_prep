#include <limits.h>
#include <stdio.h>

int is_power_of_2(unsigned int n)
{
	unsigned int check = 1;
	while (check < n)
		check *= 2;
	if (check == n)
		return (1);
	return (0);
}

/* int main(void)
{
	printf("%d\n", is_power_of_2(1));
	printf("%d\n", is_power_of_2(4));
	printf("%d\n", is_power_of_2(32));
	printf("%d\n", is_power_of_2(512));
	printf("%d\n", is_power_of_2(9));
	printf("%d\n", is_power_of_2(300));
} */