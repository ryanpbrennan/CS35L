#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int in(const char ch, const char* strng, const int size);
int searchdup(const char* fr, const int size);

int main(int argc, char *argv[])
{
	char* from;
	char* to;
	char* output = malloc(sizeof(char));
	char* c = malloc(sizeof(char));
	int tosize = 0;
	int fromsize = 0;
	int outsize = 0;
	int found = 1;
	int i;

	if (output == NULL || c == NULL)
	{
		fprintf(stderr, "memory allocation error. exiting.\n");
		printf("initial\n");
		exit(1);
	}

	if (argc != 3)
	{
		printf("incorrect number of operands. Exiting\n");
		exit(1);
	}
	
	for (i = 0; argv[1][i] != NULL; i++)
	{
		if (fromsize == 0)
		{
			from = malloc(2*sizeof(char));
			if (from == NULL)
			{
				fprintf(stderr, "memory allocation error. exiting\n");
				printf("in from malloc\n");
				exit(1);
			}
			else
			{
				from[i] = argv[1][i];
				fromsize++;
			}
		}
		else
		{
			from = realloc(from, (i+2)*sizeof(char));
			if (from == NULL)
			{
				fprintf(stderr, "memory allocation error. exiting\n");
				printf("in from realloc\n");
				exit(1);
			}
			else
			{
				from[i] = argv[1][i];
				fromsize++;
			}
		}
	}

	for (i = 0; argv[2][i] != NULL; i++)
	{
		if (tosize == 0)
		{
			to = malloc(2*sizeof(char));
			if (to == NULL)
			{
				fprintf(stderr, "memory allocation error. exiting\n");
				printf("in to malloc\n");
				exit(1);
			}
			else
			{
				to[i] = argv[2][i];
				tosize++;
			}
		}
		else
		{
			to = realloc(to, (i+2)*sizeof(char));
			if (to == NULL)
			{
				fprintf(stderr, "memory allocation error. exiting\n");
				printf("in to realloc\n");
				exit(1);
			}
			else
			{
				to[i] = argv[2][i];
				tosize++;
			}
		}
	}

	if (fromsize != tosize)
	{
		fprintf(stderr, "error: two sets different sizes\n");
		exit(1);
	}

	if (searchdup(from, fromsize))
	{
		fprintf(stderr, "error: duplicates in first operand\n");
		exit(1);
	}

	while (read(0,c,1) != 0)
	{
		int ind = in(*c, from, fromsize);
		if (ind != -1)
		{
			output = realloc(output, (outsize+2)*sizeof(char));
			if (output == NULL)
			{
				fprintf(stderr, "memory allocation error. exiting\n");
				printf("in out realloc\n");
				exit(1);
			}
			else
			{
				output[outsize] = to[ind];
				outsize++;
			}
		}
		else
		{
			output = realloc(output, (outsize+2)*sizeof(char));
			if (output == NULL)
			{
				fprintf(stderr, "memory allocation error. exiting\n");
				printf("in out realloc\n");
				exit(1);
			}
			else
			{
				output[outsize] = *c;
				outsize++;
			}

		}
	}

	void* curChar;
	if (found)
	{
		for (i = 0; i < outsize; i++)
		{
			curChar = &output[i];
			write(1, curChar, 1);
		}
		/*if (*(char*)curChar != '\n')
			putchar('\n');*/
	}
	else
	{
		printf("not found\n");
	}

	free(c);
	free(to);
	free(from);
	free(output);

	return 0;
}

int in(const char ch, const char* strng, const int size)
{
	int i;
	int index = -1;
	for (i = 0; i < size; i++)
	{
		if (ch == strng[i])
			index = i;
	}

	return index;
}

int searchdup(const char* fr, const int size)
{
	int i, j;
	for (i = 0; i < ((size/2) + 1); i++)
	{
		for (j = i+1; j < size; j++)
		{
			if (fr[i] == fr[j])
				return 1;
		}
	}
	return 0;
}
