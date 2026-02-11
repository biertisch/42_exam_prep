#include <stdlib.h>

int ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_isspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

char *build_arr(char *str)
{
	int i = 0;
	int len = 0;
	char *s;

	while (str[len] && !ft_isspace(str[len]))
		len++;
	s = malloc(len + 1);
	if (!s)
		return (NULL);
	while (i < len)
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char **ft_split(char *str)
{
	char **arr;
	int i = 0;
	int j = 0;
	int	count = 0;

	while (str[i])
	{
		if (!ft_isspace(str[i]) && (i == 0 || ft_isspace(str[i - 1])))
			count++;
		i++;
	}

	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	
	i = 0;
	while (j < count && str[i])
	{
		if (!ft_isspace(str[i]) && (i == 0 || ft_isspace(str[i - 1])))
		{
			arr[j] = build_arr(str + i);
			if (!arr[j])
			{
				while (j)
					free(arr[--j]);
				free (arr);
				return (NULL);
			}
			j++;
		}
		i++;
	}
	arr[j] = NULL;
	return (arr);
}

/* #include <stdio.h>

int main(void)
{
	char **arr;
	int i = 0;

	arr = ft_split(" apple banana cherry ");
	while (arr[i])
		printf("%s\n", arr[i++]);
	free(arr);

	i = 0;
	arr = ft_split("hello world");
	while (arr[i])
		printf("%s\n", arr[i++]);
	free(arr);
} */