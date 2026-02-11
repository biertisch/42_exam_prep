#include <stdio.h>

char *ft_strrev(char *str)
{
	int i = 0;
	int j = 0;
	char temp;

	while (str[i])
		i++;
	while (j < i - 1)
	{
		temp = str[j];
		str[j] = str[i - 1];
		str[i - 1] = temp; 
		j++;
		i--;
	}
	return (str);
}

/* int	main(void)
{
	char s[] = "Hello World";
	ft_strrev(s);
	printf("%s\n", s);
	return (0);
} */