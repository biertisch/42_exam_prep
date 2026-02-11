#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

//given
typedef struct	json {
	enum {
		MAP,
		INTEGER,
		STRING
	} type;
	union {
		struct {
			struct pair	*data;
			size_t		size;
		} map;
		int	integer;
		char	*string;
	};
}	json;

typedef struct	pair {
	char	*key;
	json	value;
}	pair;

int	peek(FILE *stream)
{
	int	c = getc(stream);
	ungetc(c, stream);
	return c;
}

void	unexpected(FILE *stream)
{
	if (peek(stream) != EOF)
		printf("unexpected token '%c'\n", peek(stream));
	else
		printf("unexpected end of input\n");
}

int	accept(FILE *stream, char c)
{
	if (peek(stream) == c)
	{
		(void)getc(stream);
		return 1;
	}
	return 0;
}

int	expect(FILE *stream, char c)
{
	if (accept(stream, c))
		return 1;
	unexpected(stream);
	return 0;
}

void	free_json(json j)
{
	switch (j.type)
	{
		case MAP:
			for (size_t i = 0; i < j.map.size; i++)
			{
				free(j.map.data[i].key);
				free_json(j.map.data[i].value);
			}
			free(j.map.data);
			break ;
		case STRING:
			free(j.string);
			break ;
		default:
			break ;
	}
}

//mine
static int parse_value(json *dst, FILE *stream);
static int parse_number(json *dst, FILE *stream);
static int parse_string(json *dst, FILE *stream);
static int parse_map(json *dst, FILE *stream);

int argo(json *dst, FILE *stream)
{
	if (!dst || !stream)
		return (-1);

	if (parse_value(dst, stream))
		return (-1);

	if (peek(stream) != EOF)
	{
		unexpected(stream);
		return (-1);
	}

	return (1);
}

static int parse_value(json *dst, FILE *stream)
{
	dst->type = INTEGER;

	char c = peek(stream);
	if (c == '+' || c == '-' || isdigit(c))
		return (parse_number(dst, stream));
	else if (c == '"')
		return (parse_string(dst, stream));
	else if (c == '{')
		return (parse_map(dst, stream));

	unexpected(stream);
	return (-1);
}

static int parse_number(json *dst, FILE *stream)
{
	long value = 0;
	int sign = 1;
	char c;

	if (accept(stream, '-'))
		sign = -1;
	else
		accept(stream, '+');

	if (!isdigit(peek(stream)))
	{
		unexpected(stream);
		return (-1);
	}
	while (isdigit(peek(stream)))
	{
		c = getc(stream);
		value = value * 10 + c - '0';
	}
	dst->type = INTEGER;
	dst->integer = (int) (value * sign);
	return (0);
}

static int parse_string(json *dst, FILE *stream)
{
	if (!expect(stream, '"'))
		return (-1);

	int size = 50;
	char *buffer = calloc(size + 1, sizeof(char));
	if (!buffer)
		return (-1);

	int i = 0;
	char c = peek(stream);
	while (c != EOF && c != '"')
	{
		c = getc(stream);

		if (c == '\\')
		{
			c = getc(stream);
			if (c != '"' && c != '\\')
			{
				free(buffer);
				unexpected(stream);
				return (-1);
			}
		}
		if (i >= size)
		{
			size *= 2;
			char *tmp = realloc(buffer, size);
			if (!tmp)
			{
				free(buffer);
				return (-1);
			}
			buffer = tmp;
		}
		buffer[i++] = c;
		c = peek(stream);
	}

	if (!expect(stream, '"'))
	{
		free(buffer);
		return (-1);
	}

	buffer[i] = '\0';
	dst->type = STRING;
	dst->string = buffer;
	return (0);
}

static int parse_map(json *dst, FILE *stream)
{
	if (!expect(stream, '{'))
		return (-1);

	dst->type = MAP;
	if (accept(stream, '}'))
	{
		dst->map.data = NULL;
		dst->map.size = 0;
		return (0);
	}

	int count = 0;
	int size = 5 * sizeof(pair);
	pair *data = malloc(size);
	if (!data)
		return (-1);

	json tmp_key;
	json tmp_value;
	while (1)
	{
		if (count >= size)
		{
			size *= 2;
			pair *tmp = realloc(data, size);
			if (!tmp)
				return (-1);
			data = tmp;
		}

		if (parse_string(&tmp_key, stream))
			return (-1);

		if (!expect(stream, ':'))
		{
			free(tmp_key.string);
			return (-1);
		}

		if (parse_value(&tmp_value, stream))
		{
			free(tmp_key.string);
			return (-1);
		}

		data[count].key = tmp_key.string;
		data[count].value = tmp_value;
		count++;

		dst->map.data = data;
		dst->map.size = count;

		if (!accept(stream, ','))
			break;
	}

	if (!expect(stream, '}'))
		return (-1);

		return (0);
}

//given
void	serialize(json j)
{
	switch (j.type)
	{
		case INTEGER:
			printf("%d", j.integer);
			break ;
		case STRING:
			putchar('"');
			for (int i = 0; j.string[i]; i++)
			{
				if (j.string[i] == '\\' || j.string[i] == '"')
					putchar('\\');
				putchar(j.string[i]);
			}
			putchar('"');
			break ;
		case MAP:
			putchar('{');
			for (size_t i = 0; i < j.map.size; i++)
			{
				if (i != 0)
					putchar(',');
				serialize((json){.type = STRING, .string = j.map.data[i].key});
				putchar(':');
				serialize(j.map.data[i].value);
			}
			putchar('}');
			break ;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return 1;
	char *filename = argv[1];
	FILE *stream = fopen(filename, "r");
	json	file;
	if (argo (&file, stream) != 1)
	{
		free_json(file);
		return 1;
	}
	serialize(file);
	printf("\n");
}
