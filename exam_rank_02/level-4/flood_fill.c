#include "flood_fill.h"

void	flood_fill(char **tab, t_point size, t_point begin)
{
	if (begin.x < 0 || begin.x >= size.x || begin.y < 0 || begin.y >= size.y
		|| tab[begin.x][begin.y] == '1' || tab [begin.x][begin.y] == 'F')
		return ;
	tab[begin.x][begin.y] = 'F';
	
	flood_fill(tab, size, (t_point){begin.x, begin.y + 1});
	flood_fill(tab, size, (t_point){begin.x, begin.y - 1});
	flood_fill(tab, size, (t_point){begin.x - 1, begin.y});
	flood_fill(tab, size, (t_point){begin.x + 1, begin.y});
}
