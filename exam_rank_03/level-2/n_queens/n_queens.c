#include <stdio.h>
#include <stdlib.h>

void print_solution(int *board, int size)
{
	for (int i = 0; i < size; i++)
	{
		fprintf(stdout, "%d", board[i]);
		if (i < size - 1)
			fprintf(stdout, " ");
	}
	fprintf(stdout, "\n");
}

int check(int *board, int row, int col)
{
	for (int i = 0; i < row; i++)
	{
		if (board[i] == col || board[i] - i == col - row
			|| board[i] + i == col + row)
			return (0);
	}
	return (1);
}

void solve(int *board, int size, int row)
{	
	if (row == size) 
	{
		print_solution(board, size);
		return;
	}
    for (int col = 0; col < size; col++)
	{
		if (check(board, row, col))
		{
            board[row] = col;
			solve(board, size, row + 1);
        }
    }
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	int size = atoi(argv[1]);
	if (size < 4)
		return (0);
	int board[size];
	solve(board, size, 0);
	return (0);
}
