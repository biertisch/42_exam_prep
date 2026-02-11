#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_rectangle
{
	int x;
	int y;
	int size;
} t_rectangle;

typedef struct s_map
{
	char** grid;
	int height;
	int width;
	char empty;
	char obstacle;
	char full;
	t_rectangle bsq;
} t_map;