#include "list.h"
#include <stddef.h>

t_list	*sort_list(t_list *lst, int (*cmp)(int, int))
{
	t_list *curr = lst;
	int tmp;
	int count;
	int i;

	if (!lst)
		return (NULL);
	count = 0;	
	while (curr)
	{
		curr = curr->next;
		count++;
	}
	i = 0;
	while (i < count - 1)
	{
		curr = lst;
		while (curr->next)
		{
			if ((*cmp)(curr->data, curr->next->data) == 0)
			{
				tmp = curr->data;
				curr->data = curr->next->data;
				curr->next->data = tmp;
			}
			curr = curr->next;
		}
		i++;
	}
	return (lst);
}

/* //TO TEST
#include <stdio.h>
#include <stdlib.h>

// Helper to create a new list node
t_list *create_node(int data)
{
	t_list *new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->data = data;
	new->next = NULL;
	return new;
}

// Helper to print the list
void print_list(t_list *lst)
{
	while (lst)
	{
		printf("%d ", lst->data);
		lst = lst->next;
	}
	printf("\n");
}

// Comparison function for ascending order
int ascending(int a, int b)
{
	return (a <= b); // returns non-zero if a is correctly before b
}

int main(void)
{
	// Create list: 4 -> 2 -> 5 -> 3 -> 1
	t_list *n1 = create_node(4);
	t_list *n2 = create_node(2);
	t_list *n3 = create_node(5);
	t_list *n4 = create_node(3);
	t_list *n5 = create_node(1);

	n1->next = n2;
	n2->next = n3;
	n3->next = n4;
	n4->next = n5;

	printf("Before sorting:\n");
	print_list(n1);

	t_list *sorted = sort_list(n1, ascending);

	printf("After sorting:\n");
	print_list(sorted);

	// Free the list
	t_list *tmp;
	while (sorted)
	{
		tmp = sorted;
		sorted = sorted->next;
		free(tmp);
	}

	return 0;
} */