#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_game
{
	char** board;
	int width;
	int height;
	int iterations;
	int drawing;
	int x;
	int y;
	char alive;
	char dead;
} t_game;