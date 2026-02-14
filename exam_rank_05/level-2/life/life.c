#include "life.h"

static void print_board(t_game* game)
{
	for (int i = 0; i < game->height; i++)
	{
		for (int j = 0; j < game->width; j++)
			putchar(game->board[i][j]);
		putchar('\n');
	}
}

static void free_board(char** board)
{
	if (!board)
		return;

	for (int i = 0; board[i]; i++)
		free(board[i]);
	free(board);
}

static int init_board(t_game* game, char*** board)
{
	if (!game || !board)
		return 0;

	*board = calloc(game->height + 1, sizeof(char*));
	if (!*board)
		return 0;

	for (int i = 0; i < game->height; i++)
	{
		(*board)[i] = calloc(game->width + 1, sizeof(char));
		if (!(*board)[i])
		{
			free_board(*board);
			return 0;
		}
		for (int j = 0; j < game->width; j++)
			(*board)[i][j] = game->dead;
	}
	return 1;
}

static int count_neighbours(t_game* game, int x, int y)
{
	int count = 0;
	for (int i = x - 1; i <= x + 1; i++)
	{
		for (int j = y - 1; j <= y + 1; j++)
		{
			if (i == x && j == y)
				continue;
			if (i >= 0 && i < game->height
				&& j >= 0 && j < game->width
				&& game->board[i][j] == game->alive)
				++count;
		}
	}
	return count;
}

static int play(t_game* game)
{
	if (!game)
		return 0;

	char** temp;
	if (!init_board(game, &temp))
		return 0;

	for (int i = 0; i < game->height; i++)
	{
		for (int j = 0; j < game->width; j++)
		{
			int neighbours = count_neighbours(game, i, j);
			if (game->board[i][j] == game->alive && (neighbours < 2 || neighbours > 3))
				temp[i][j] = game->dead;
			else if (game->board[i][j] == game->dead && neighbours == 3)
				temp[i][j] = game->alive;
			else
				temp[i][j] = game->board[i][j];
		}
	}

	free_board(game->board);
	game->board = temp;
	return 1;
}

static int draw(t_game* game)
{
	if (!game)
		return 0;

	int len;
	char c;
	int count = 1;

	len = read(STDIN_FILENO, &c, count);
	while (len > 0)
	{
		switch (c)
		{
			case 'w':
				if (game->x > 0)
					--game->x;
				break;
			case 'a':
				if (game->y > 0)
					--game->y;
				break;
			case 's':
				if (game->x < game->height - 1)
					++game->x;
				break;
			case 'd':
				if (game->y < game->width - 1)
					++game->y;
				break;
			case 'x':
				game->drawing = !(game->drawing);
				break;
			default:
				break;
		}

		if (game->drawing && game->x >= 0 && game->x < game->height
			&& game->y >= 0 && game->y < game->width)
			game->board[game->x][game->y] = game->alive;

		len = read(STDIN_FILENO, &c, count);
	}
	return len == 0;
}

static int init_game(int argc, char**argv, t_game* game)
{
	if (!argv || !game || argc != 4)
		return 0;

	game->width = atoi(argv[1]);
	game->height = atoi(argv[2]);
	game->iterations = atoi(argv[3]);
	if (game->width < 1 || game->height < 1 || game->iterations < 0)
		return 0;

	game->x = 0;
	game->y = 0;
	game->drawing = 0;
	game->alive = 'O';
	game->dead = '.';

	return init_board(game, &game->board);
}

int main(int argc, char** argv)
{
	t_game game;
	if (!init_game(argc, argv, &game))
		return 1;

	if (!draw(&game))
	{
		free_board(game.board);
		return 1;
	}

	for (int i = 0; i < game.iterations; i++)
	{
		if (!play(&game))
		{
			free_board(game.board);
			return 1;
		}
	}

	print_board(&game);
	free_board(game.board);
	return 0;
}