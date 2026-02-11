#include <stdio.h>

int	check(char *s)
{
	int open = 0;
	int close = 0;	
	for (int i = 0; s[i]; i++)
	{
		if (s[i] == '(')
			open++;
		else if (s[i] == ')')
		{
			if (open)
				open--;
			else
				close++;
		}
	}
	return (open + close);
}

void rip(char *s, int offset, int i)
{
	if (!s[i])
	{
		if (!offset && !check(s))
			puts(s);
		return;
	}
	if ((s[i] == '(' || s[i] == ')') && offset)
	{
		char tmp = s[i];
		s[i] = ' ';
		rip(s, offset - 1, i + 1);
		s[i] = tmp;
	}
	rip(s, offset, i + 1);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	rip(argv[1], check(argv[1]), 0);
	return (0);
}
