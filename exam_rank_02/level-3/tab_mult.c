#include <unistd.h>

void ft_put_nbr(int n)
{
	if (n >= 10)
		ft_put_nbr(n / 10);
	char c = n % 10 + '0';
	write(1, &c, 1);
}

int ft_atoi(char *s)
{
	int i = 0;
	int n = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		n = n * 10 + s[i] - '0';
		i++;
	}
	return (n);
}

int main(int argc, char **argv)
{
	int n;
	int i;

	if (argc < 2)
	{
		write(1, "\n", 1);
		return (1);
	}

	n = ft_atoi(argv[1]);
	i = 1;
	while (i < 10)
	{
		ft_put_nbr(i);
		write(1, " x ", 3);
		ft_put_nbr(n);
		write(1, " = ", 3);
		ft_put_nbr(i * n);
		write(1, "\n", 1);
		i++;
	}
	return (0);
}
