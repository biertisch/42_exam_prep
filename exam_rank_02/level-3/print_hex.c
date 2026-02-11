#include <unistd.h>

void put_hex(int n)
{
	char *base = "0123456789abcdef";
	int base_len = 16;

	if (n >= base_len)
		put_hex(n / base_len);
	write(1, &base[n % base_len], 1);
}

int ft_atoi(char *s)
{
	int n = 0;
	int i = 0;
	while (s[i] == 32 || (s[i] >= 9 && s[i] <= 13))
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		n = n * 10 + s[i] - '0';
		i++;
	}
	return (n);
}

int main(int argc, char **argv)
{
	if (argc == 2)
		put_hex(ft_atoi(argv[1]));
	write(1, "\n", 1);
	return (0);
}