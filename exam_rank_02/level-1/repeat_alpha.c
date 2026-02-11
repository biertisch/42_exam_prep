#include <unistd.h>

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		char *str = argv[1];
		int i = 0;
		while (str[i])
		{
			if ((str[i] >= 'A' && str[i <= 'Z']) || (str[i] >= 'a' && str[i] <= 'z'))
			{
				int j;
				if (str[i] >= 'A' && str[i] <= 'Z') 
					j = str[i] - 64;
				else if (str[i] >= 'a' && str[i] <= 'z')
					j = str[i] - 96;
				while (j > 0)
				{
					write(1, &str[i], 1);
					j--;
				}	
			}
			else
				write(1, &str[i], 1);
			i++;
		}	
	}
	write(1, "\n", 1);
	return (0);
}