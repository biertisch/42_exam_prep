#include <stdlib.h>

int	count_digits(int n)
{
	int count = 0;

	if (n <= 0)
		count++;
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char *ft_itoa(int nbr)
{
	char *res;
	int count = count_digits(nbr);

	res = malloc(count + 1);
	if (!res)
		return (NULL);
	res[count] = '\0';
	if (nbr < 0)
	{
		res[0] = '-';
		nbr *= -1;
	}
	while (nbr > 9)
	{
		res[--count] = (nbr % 10) + '0';
		nbr /= 10; 
	}
	res[--count] = nbr + '0';
	return (res);
}

/* #include <stdio.h>

int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	printf("%s\n", ft_itoa(atoi(argv[1])));
	return (0);
} */