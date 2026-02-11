#include <unistd.h>

int main(int argc, char **argv)
{
	if (argc == 3)
	{
		int len = 0;
		int i = 0;
		int j = 0;

		while (argv[1][len])
			len++;
		while (argv[1][i] && argv[2][j])
		{
			if (argv[1][i] == argv[2][j])
				i++;
			j++;
		}
		if (i == len)
			write(1, argv[1], len);
	}
	write(1, "\n", 1);
	return (0);
}