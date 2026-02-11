#include <unistd.h>

int main(int argc, char **argv)
{
	if (argc == 3)
	{
		int i = 0;
		int j = 0;
		int dup = 0;
		while (argv[1][i])
		{
			j = i - 1;
			dup = 0;
			while (j >= 0)
			{
				if (argv[1][i] == argv[1][j])
					dup = 1;
				j--;
			}
			if (!dup)
				write(1, &argv[1][i], 1);
			i++;
		}
		i = 0;
		while (argv[2][i])
		{
			j = 0; 
			dup = 0;
			while (argv[1][j])
			{
				if (argv[2][i] == argv[1][j])
					dup = 1;
				j++; 
			}
			j = i - 1;
			while (j >= 0)
			{
				if (argv[2][i] == argv[2][j])
					dup = 1;
				j--;
			}
			if (!dup)
				write(1, &argv[2][i], 1);
			i++;
		}
		
	}
	write(1, "\n", 1);
	return (0);
}