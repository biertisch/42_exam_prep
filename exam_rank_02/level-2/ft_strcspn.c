#include <string.h>
#include <stdio.h>

int	isreject(char c, const char *reject)
{
	int i = 0;
	while (reject[i])
	{
		if (reject[i] == c)
			return (1);
		i++;
	}
	return (0);
}

size_t ft_strcspn(const char *s, const char *reject)
{
	size_t i = 0;
	while (s[i] && !isreject(s[i], reject))
		i++;
	return (i);
}

/* int main(void)
{
	printf("%ld", ft_strcspn("hello", "o"));
	printf("\n");
	printf("%ld", strcspn("hello", "o"));
	printf("\n\n");
	printf("%ld", ft_strcspn("hello world", "aw"));
	printf("\n");
	printf("%ld", strcspn("hello world", "aw"));
	printf("\n\n");
	printf("%ld", ft_strcspn("monkey", "aw"));
	printf("\n");
	printf("%ld", strcspn("monkey", "aw"));
	printf("\n");
} */