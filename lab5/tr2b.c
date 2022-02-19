#include <stdio.h>
#include <stdlib.h>

int in(const char ch, const char* strng, const int size);
int dup(const char* fr, const int size);

int main(int argc, char *argv[])
{
	char* from;
	char* to;
	char* output;
	void* temp0;
	void* temp1;
	void* temp2;
	int tosize = 0;
	int fromsize = 0;
	int outsize = 0;
	int found = 1;
	char c;
	int i;

	if (argc != 3)
	{
		printf("incorrect number of operands. Exiting\n");
		exit(1);
	}
	
	for (i = 0; argv[1][i] != NULL; i++)
	{
		if (fromsize == 0)
		{
			temp0 = malloc(sizeof(char));
			if (temp0 == NULL)
			{
				fprintf(stderr, "memory allocation error. exiting\n");
				exit(1);
			}
			else
			{
				from = temp0;
				from[i] = argv[1][i];
				fromsize++;
			}
		}
		else
		{
			temp0 = realloc(from, (i+2)*sizeof(char));
			if (temp0 == NULL)
			{
				fprintf(stderr, "memory allocation error. exiting\n");
				exit(1);
			}
			else
			{
				from = temp0;
				from[i] = argv[1][i];
				fromsize++;
			}
		}
	}

	for (i = 0; argv[2][i] != NULL; i++)
	{
		if (tosize == 0)
		{
			temp1 = malloc(sizeof(char));
			if (temp1 == NULL)
			{
				fprintf(stderr, "memory allocation error. exiting\n");
				exit(1);
			}
			else
			{
				to = temp1;
				to[i] = argv[2][i];
				tosize++;
			}
		}
		else
		{
			temp1 = realloc(to, (i+2)*sizeof(char));
			if (temp1 == NULL)
			{
				fprintf(stderr, "memory allocation error. exiting\n");
				exit(1);
			}
			else
			{
				to = temp1;
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

	if (dup(from, fromsize))
	{
		fprintf(stderr, "error: duplicates in first operand\n");
		exit(1);
	}

	while ((c = getchar()) != EOF)
	{
		int ind = in(c, from, fromsize);
		if (outsize == 0)
		{
			temp2 = malloc(2*sizeof(char));
		}
		else
		{
			temp2 = realloc(output, (outsize+1)*sizeof(char));
		}

		if (temp2 == NULL)
		{
			fprintf(stderr, "memory allocation error. exiting\n");
			exit(1);
		}
		else
		{
			output = temp2;
			if (ind != -1) // found it
			{
				output[outsize] = to[ind];
			}
			else // didnt find it 
			{
				output[outsize] = c;
			}
		}

		outsize++;
	}

	for (i = 0; i < outsize; i++)
	{
		putchar(output[i]);
	}
	/*if (output[outsize-1] != '\n')
		putchar('\n');*/

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

int dup(const char* fr, const int size)
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
