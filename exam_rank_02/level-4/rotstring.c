#include <unistd.h>

int ft_isspace(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	main(int argc, char **argv)
{
	if (argc > 1)
	{
		int i;
		int j;

		i = 0;
		while (argv[1][i] && ft_isspace(argv[1][i]))
			i++;
		j = i;
		while (argv[1][i] && !ft_isspace(argv[1][i]))
			i++;
		while (argv[1][i])
		{
			while (argv[1][i] && ft_isspace(argv[1][i]))
				i++;
			while (argv[1][i] && !ft_isspace(argv[1][i]))
			{
				write(1, &argv[1][i], 1);
				i++;
			}
			write(1, " ", 1);
		}
		while (argv[1][j] && !ft_isspace(argv[1][j]))
		{
			write(1, &argv[1][j], 1);
			j++;
		}	
	}
	write(1, "\n", 1);
	return (0);
}
