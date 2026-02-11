#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	if (n < 0)
	{
		ft_putchar('-');
		n *= -1;
	}
	if (n >= 10)
		ft_putnbr(n / 10);
	ft_putchar(n % 10 + '0');
}

int ft_isprime(int n)
{
	int i = 2;

	if (n < 2)
		return (0);
	while (i < n)
	{
		if (n % i == 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(char *s)
{
	int i = 0;
	int sign = 1;
	long int n = 0;	

	while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		n = n * 10 + s[i] - '0';
		i++;
	}
	return (n * sign);
}

int	main(int argc, char **argv)
{
	int n; 
	int sum = 0;
	
	if (argc == 2)
	{
		n = ft_atoi(argv[1]);
		while (n > 1)
		{
			if (ft_isprime(n))
				sum += n;
			n--;
		}		
	}
	ft_putnbr(sum);
	ft_putchar('\n');
	return (0);	
}