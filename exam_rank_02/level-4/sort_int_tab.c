void	sort_int_tab(int *tab, unsigned int size)
{
	int	i; 
	int j;
	int tmp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - 1 - i)
		{
			if (tab[j] > tab[j + 1])
			{
				tmp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = tmp;
			} 
			j++;
		}
		i++;
	}
}
