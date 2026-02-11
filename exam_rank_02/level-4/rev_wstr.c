#include <unistd.h>

int	ft_isspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		int i = 0;
		int start = 0;

		while (argv[1][i])
			i++;
		i--;
		while (i >= 0)
		{
			while (i >= 0 && ft_isspace(argv[1][i]))
				i--;
			start = i;
			while (start >= 0 && !ft_isspace(argv[1][start]))
				start--;
			write(1, &argv[1][start + 1], i - start);
			if (start >= 0)
				write(1, " ", 1);
			i = start;
		}
	}
	write(1, "\n", 1);	
	return (0);
}
