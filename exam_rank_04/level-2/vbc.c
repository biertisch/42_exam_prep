//given
#include <stdio.h>
#include <malloc.h>
#include <ctype.h>

typedef struct node {
    enum {
        ADD,
        MULTI,
        VAL
    }   type;
    int val;
    struct node *l;
    struct node *r;
}   node;

node    *new_node(node n)
{
    node *ret = calloc(1, sizeof(n));
    if (!ret)
        return (NULL);
    *ret = n;
    return (ret);
}

void    destroy_tree(node *n)
{
    if (!n)
        return ;
    if (n->type != VAL)
    {
        destroy_tree(n->l);
        destroy_tree(n->r);
    }
    free(n);
}

void    unexpected(char c)
{
    if (c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpected end of input\n"); //modified
}

int accept(char **s, char c)
{
    if (**s == c) // modified
    {
        (*s)++;
        return (1);
    }
    return (0);
}

int expect(char **s, char c)
{
    if (accept(s, c))
        return (1);
    unexpected(**s);
    return (0);
}

//mine
static node *parse_add(char **s);
static node *parse_mult(char **s);
static node *parse_value(char **s);

node    *parse_expr(char *s)
{
	if (!s)
		return (NULL);

	node *ret = parse_add(&s);
	if (!ret)
		return (NULL);

    if (*s)
    {
		unexpected(*s);
        destroy_tree(ret);
        return (NULL);
    }

    return (ret);
}

static node *parse_add(char **s)
{
	node *left = NULL;
	node *right = NULL;
	node *new;

	left = parse_mult(s);
	if (!left)
		return (NULL);
	while (accept(s, '+'))
	{
		right = parse_mult(s);
		if (!right)
		{
			destroy_tree(left);
			return (NULL);
		}

		new = malloc(sizeof(*new));
		if (!new)
		{
			destroy_tree(left);
			destroy_tree(right);
			return (NULL);
		}
		new->type = ADD;
		new->val = 0;
		new->l = left;
		new->r = right;
		left = new;
	}
	return (left);
}

static node *parse_mult(char **s)
{
	node *left = NULL;
	node *right = NULL;
	node *new;

	left = parse_value(s);
	if (!left)
		return (NULL);

	while (accept(s, '*'))
	{
		right = parse_value(s);
		if (!right)
		{
			destroy_tree(left);
			return (NULL);
		}

		new = malloc(sizeof(*new));
		if (!new)
		{
			destroy_tree(left);
			destroy_tree(right);
			return (NULL);
		}
		new->type = MULTI;
		new->val = 0;
		new->l = left;
		new->r = right;
		left = new;
	}
	return (left);
}

static node *parse_value(char **s)
{
	if (!(*s) || (!isdigit(**s) && **s != '('))
	{
		unexpected(**s);
		return (NULL);
	}

	node *new;
	if (accept(s, '('))
	{
		new = parse_add(s);
		if (!new)
			return (NULL);
		if (expect(s, ')'))
		{
			destroy_tree(new);
			return (NULL);
		}
		return (new);
	}

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->type = VAL;
	new->val = int(**s - '0');
	new->l = NULL;
	new->r = NULL;
	(*s)++;
	return (new);
}

//given
int eval_tree(node *tree)
{
    switch (tree->type)
    {
        case ADD:
            return (eval_tree(tree->l) + eval_tree(tree->r));
        case MULTI:
            return (eval_tree(tree->l) * eval_tree(tree->r));
        case VAL:
            return (tree->val);
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (1);
    node *tree = parse_expr(argv[1]);
    if (!tree)
        return (1);
    printf("%d\n", eval_tree(tree));
    destroy_tree(tree);
}