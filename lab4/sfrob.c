#include <stdio.h>
#include <stdlib.h>

int errorCheck(); // 1 if failed, 0 if not
void memoryCheck(void* memBlock);
int frobcmp(char const* s1, char const* s2);
int prefrobcmp(const void* str1, const void* str2);

int main()
{	
	char* currentString = malloc(sizeof(char));
	char** stringList = malloc(sizeof(char*));
	int stringPosition = 0;
	int listPosition = 0;
	char currentChar;

	memoryCheck(currentString);
	memoryCheck(stringList);

	while (currentChar = getchar())
	{
		if (errorCheck())
		{
			for (int i = 0; i < listPosition; i++)
			{
				free(stringList[listPosition]);
			}
			free(stringList);
			return 1;
		}

		if (currentChar != EOF && currentChar != ' ' && currentChar != '\n')
		{
			currentString[stringPosition] = currentChar;
			stringPosition++;
	
			char* temp = currentString;

			currentString = realloc(currentString,
							(stringPosition+1)*sizeof(char));

			memoryCheck(currentString);
		}

		if ((currentChar == ' '|| currentChar == EOF || currentChar == '\n')
													&& stringPosition > 0)
		{
			currentString[stringPosition] = ' ';
			stringList[listPosition] = currentString;
			listPosition++;

			stringList = realloc(stringList,(listPosition+1)*sizeof(char*));
			memoryCheck(stringList);

			stringPosition = 0;

			currentString = malloc(sizeof(char));
			memoryCheck(currentString);
		}

		if (currentChar == EOF)
		{
			break;
		}

	}

	qsort(stringList, listPosition, sizeof(char*), prefrobcmp);

	for (size_t i = 0; i < listPosition; i++)
	{
		for (size_t j = 0; stringList[i][j] != ' '; j++)
		{
			printf("%c", stringList[i][j]);
		}
		printf("%c", ' ');
	}


	for (size_t i = 0; i < listPosition; i++)
	{
		free(stringList[i]);
	}

	free(stringList);

	return 0;
}


int errorCheck()
{
	if (ferror(stdin))
	{
		fprintf(stderr, "ERROR: unable to read input");
		return 1;
	}
	else
	{
		return 0;
	}
}

void memoryCheck(void* memBlock)
{
	if (memBlock == NULL)
	{
		fprintf(stderr, "ERROR: unable to allocate sufficient memory");
		exit(1);
	}
}

int prefrobcmp(const void* str1, const void* str2)
{
	const char* string1 = *(const char**)str1;
	const char* string2 = *(const char**)str2;
	return frobcmp(string1, string2);
}

int frobcmp(char const* s1, char const* s2)	
{	
	for (;;s1++, s2++)
	{
		while (*s1 == '\0') s1++;
		while (*s2 == '\0') s2++;

		if (*s1 == ' ' && *s2 == ' ') return 0;

		if (*s1 == ' ' || (*s1^42) < (*s2^42)) return -1;

		if (*s2 == ' ' || (*s1^42) > (*s2^42)) return 1;
	}
}
