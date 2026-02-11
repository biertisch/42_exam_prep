#include <unistd.h>

int	main(int argc, char **argv)
{
	if (argc == 4)
	{
		int i = 0;
		int j = 0;
		while (argv[2][i])
			i++;
		while (argv[3][j])
			j++;
		if (i > 1 || j > 1)
		{
			write(1, "\n", 1);
			return (1);
		}
		
		i = 0;
		while (argv[1][i])
		{
			if (argv[1][i] == argv[2][0])
				argv[1][i] = argv[3][0];
			write(1, &argv[1][i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}