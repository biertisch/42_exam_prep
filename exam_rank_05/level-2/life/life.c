#include "life.h"

static void free_board(char** board)
{
	if (!board)
		return;
	for (int i = 0; board[i]; i++)
		free(board[i]);
	free(board);
}

static void print_board(t_game* game)
{
	for (int row = 0; row < game->height; row++)
	{
		for (int col = 0; col < game->width; col++)
		{
			putchar(game->board[row][col]);
		}
		putchar('\n');
	}
}

static int init_board(t_game* game, char*** board)
{
	if (!game || !board)
		return -1;

	(*board) = calloc(game->height + 1, sizeof(char*));
	if (!(*board))
		return -1;

	for (int i = 0; i < game->height; i++)
	{
		(*board)[i] = calloc(game->width + 1, sizeof(char));
		if (!(*board)[i])
		{
			free_board((*board));
			return -1;
		}
		for (int j = 0; j < game->width; j++)
			(*board)[i][j] = game->dead;
	}

	return 0;
}

static int count_neighbours(t_game* game, int x, int y)
{
	int count = 0;

	for (int row = x - 1; row <= x + 1; row++)
	{
		for (int col = y - 1; col <= y + 1; col++)
		{
			if (row == x && col == y)
				continue;

			if (row >= 0 && row < game->height
				&& col >= 0 && col < game->width
				&& game->board[row][col] == game->alive)
				count++;
		}
	}
	return count;
}

static int play(t_game* game)
{
	char** temp;
	if (init_board(game, &temp))
	{
		free_board(game->board);
		return -1;
	}

	for (int row = 0; row < game->height; row++)
	{
		for (int col = 0; col < game->width; col++)
		{
			int neighbours = count_neighbours(game, row, col);
			if (game->board[row][col] == game->alive && (neighbours < 2 || neighbours > 3))
				temp[row][col] = game->dead;
			else if (game->board[row][col] == game->dead && neighbours == 3)
				temp[row][col] = game->alive;
			else
				temp[row][col] = game->board[row][col];
		}
	}

	free_board(game->board);
	game->board = temp;
	return 0;
}

static int draw_board(t_game* game)
{
	int ret = 0;
	char buffer;
	ret = read(STDIN_FILENO, &buffer, 1);
	while (ret > 0)
	{
		switch (buffer)
		{
			case 'w':
				if (game->x > 0)
					game->x--;
				break;

			case 'a':
				if (game->y > 0)
					game->y--;
				break;

			case 's':
				if (game->x < game->height - 1)
					game->x++;
				break;

			case 'd':
				if (game->y < game->width - 1)
					game->y++;
				break;

			case 'x':
				game->drawing = !(game->drawing);
				break;

			default:
				break;
		}

		if (game->drawing
			&& game->x >= 0 && game->x < game->height
			&& game->y >= 0 && game->y < game->width)
			game->board[game->x][game->y] = game->alive;

		ret = read(STDIN_FILENO, &buffer, 1);
	}

	if (ret == -1)
	{
		free_board(game->board);
		return -1;
	}

	return 0;
}

static int init_game(char** argv, t_game* game)
{
	game->width = atoi(argv[1]);
	game->height = atoi(argv[2]);
	game->iterations = atoi(argv[3]);
	game->drawing = 0;
	game->x = 0;
	game->y = 0;
	game->alive = '0';
	game->dead = '.';

	if (init_board(game, &game->board))
		return -1;

	return 0;
}

int main(int argc, char** argv)
{
	if (argc != 4)
		return 1;

	t_game game;
	if (init_game(argv, &game) == -1)
		return 1;

	if (draw_board(&game) == -1)
		return 1;

	for (int i = 0; i < game.iterations; i++)
		if (play(&game) == -1)
			return 1;

	print_board(&game);
	free_board(game.board);
	return 0;
}