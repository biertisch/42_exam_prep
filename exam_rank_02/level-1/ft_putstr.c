#include <unistd.h>

void	ft_putstr(char *str)
{
	while (*str)
	{
		write(1, str, 1);
		str++;
	}
}

/* int main(void)
{
	ft_putstr("hello\n");
	ft_putstr("");
	ft_putstr("\n");
	return (0);
} */