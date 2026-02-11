#include <unistd.h>

int main(int argc, char **argv)
{
	if (argc == 3)
	{
		int i = 0;
		int j;
		int k;
		int dup = 0;
		while (argv[1][i])
		{
			j = 0;
			while (argv[2][j])
			{
				k = i - 1;
				dup = 0;
				while (k >= 0)
				{
					if (argv[1][i] == argv[1][k])
					{
						dup = 1;
						break;
					}
					k--;
				}
				if (!dup && argv[1][i] == argv[2][j])
				{
					write(1, &argv[1][i], 1);
					break;
				}
				j++;
			}
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}