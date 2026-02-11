#include <unistd.h>

char upper(char c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}

char lower(char c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}

int is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

void capitalize(char *s)
{
	int i = 0;

	while (s[i])
	{
		if (is_alpha(s[i]))
		{
			if (i == 0 || is_space(s[i-1]))
				s[i] = upper(s[i]);
			else
				s[i] = lower(s[i]);
		}
		write(1, &s[i], 1);
		i++;
	}
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		write(1, "\n", 1);
		return (1);
	}
	int i = 1;
	while (i < argc)
	{
		capitalize(argv[i]);
		write(1, "\n", 1);
		i++;
	}
	return (0);
}