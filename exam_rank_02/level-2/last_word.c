#include <unistd.h>

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		char *last_word = argv[1];
		int i = 0;
		while (argv[1][i])
		{
			if ((i == 0 || argv[1][i - 1] == 9 || argv[1][i - 1] ==  32) && argv[1][i] != 9 && argv[1][i] != 32)
				last_word = argv[1] + i;
			i++;
		}
		i = 0;
		while (last_word[i] && last_word[i] != 9 && last_word[i] != 32)
		{
			write(1, &last_word[i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}