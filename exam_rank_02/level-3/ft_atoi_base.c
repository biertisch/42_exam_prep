#include <stdio.h>

int	get_digit(char c, int str_base)
{
	char *base = "0123456789ABCDEF";
	int i = 0;

	if (c >= 'a' && c <= 'f')
		c -= 32;
	while (i < str_base && base[i])
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_base(const char *str, int str_base)
{
	long int n = 0;
	int sign = 1;
	int i = 0;

	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (get_digit(str[i], str_base) >= 0)
	{
		n = n * str_base + get_digit(str[i], str_base);
		i++;
	}
	return (n * sign);
}

/* int	main(void)
{
	printf("%d\n", ft_atoi_base("42", 10));
	printf("%d\n", ft_atoi_base("2A", 16));
	printf("%d\n", ft_atoi_base("2a", 16));
	printf("%d\n", ft_atoi_base("101010", 2));
	printf("%d\n", ft_atoi_base("2A", 10));
	printf("%d\n", ft_atoi_base("GF", 16));
	return (0);
} */