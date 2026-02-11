#include <unistd.h>

void	print_nbr(unsigned int n)
{
	char c;
	if (n >= 10)
		print_nbr(n / 10);
	c = n % 10 + 48;
	write(1, &c, 1);
}

int	main(void)
{
	unsigned int i = 1;

	while (i <= 100)
	{
		if (i % 3 == 0 && i % 5 == 0)
			write(1, "fizzbuzz", 8);
		else if (i % 3 == 0)
			write(1, "fizz", 4);
		else if (i % 5 == 0)
			write(1, "buzz", 4);
		else
			print_nbr(i);
		write (1, "\n", 1);
		i++;
	}
	return (0);
}