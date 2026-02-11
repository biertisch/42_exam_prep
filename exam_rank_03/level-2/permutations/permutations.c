#include <stdio.h>

void ft_swap(char *a, char *b)
{
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

void sort(char *s, int len)
{
	for (int i = 0; i < len - 1; i++)
		for (int j = 0; j < len - 1 - i; j++)
			if (s[j] > s[j + 1])
				ft_swap(&s[j], &s[j + 1]);
}

void permute(char *out, char *in, int *used, int len, int i)
{
	if (i == len)
	{
		out[i] = '\0';
		puts(out);
		return;
	}
	for (int j = 0; j < len; j++)
	{
		if (!used[j])
		{
			used[j] = 1;
			out[i] = in[j];
			permute(out, in, used, len, i + 1);
			used[j] = 0;			
		}
	}
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	int len = 0;
	while (argv[1][len])
		len++;
	char in[len + 1];
	char out[len + 1];
	int	used[len];
	for (int i = 0; i < len; i++)
	{
		in[i] = argv[1][i];
		used[i] = 0;
	}
	in[len] = '\0';		
	sort(in, len);
	permute(out, in, used, len, 0);
	return (0);
}
