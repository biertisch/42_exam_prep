int ischarset(char c, const char *s2)
{
	int i = 0;
	while (s2[i])
	{
		if (s2[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char *ft_strpbrk(const char *s1, const char *s2)
{
	int i = 0;
	while (s1[i])
	{
		if (ischarset(s1[i], s2))
			return (s1[i]);
		i++;
	}
	return (NULL);
}