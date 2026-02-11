#include <unistd.h>

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		int i = 0;
		while (argv[1][i])
		{
			char c = argv[1][i];
			int j = 0;
			if (c >= 'A' && c <= 'Z' )
			{
				while (c < 'Z' && j < 13)
				{
					c++;
					j++;
				}
				if (j < 13)
					c = 'A' + 12 - j;
			}
			if (c >= 'a' && c <= 'z' )
			{
				while (c < 'z' && j < 13)
				{
					c++;
					j++;
				}
				if (j < 13)
					c = 'a' + 12 - j;
			}
			write(1, &c, 1);
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}