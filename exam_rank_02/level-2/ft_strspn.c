int	isaccept(char c, const char *accept)
{
	int i = 0;
	while (accept[i])
	{
		if (accept[i] == c)
			return (1);
		i++;
	}
	return (0);
}

size_t ft_strspn(const char *s, const char *accept)
{
	size_t i = 0;
	while (s[i] && isaccept(s[i], accept))
		i++;
	return (i);
}