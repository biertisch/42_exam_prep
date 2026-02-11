#include <unistd.h>

int ft_isspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	int i;
	int space;

	if (argc == 2)
	{
		i = 0;
		space = 0;
		while (ft_isspace(argv[1][i]))
			i++;
		while (argv[1][i])
		{
			if (ft_isspace(argv[1][i]))
				space = 1;
			if (!ft_isspace(argv[1][i]))
			{
				if (space)
					write(1, " ", 1);
				space = 0;
				write(1, &argv[1][i], 1);
				
			}
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}