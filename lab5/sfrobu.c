#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>

int errorCheck(); // 1 if failed, 0 if not
void memoryCheck(void* memBlock);
int frobcmp(char const* s1, char const* s2);
int prefrobcmp(const void* str1, const void* str2);
int frobcmpUpper(char const* s1, char const* s2);
int prefrobcmpUpper(const void* str1, const void* str2);

int main(int argc, char** argv)
{	
	struct stat Data;
	char* currentString;
	char** stringList = malloc(sizeof(char*));
	char* currentChar = malloc(sizeof(char));
	char* tempFile;
	void* temp;
	void* temp2;
	const char* option = argv[1];
	int fflag = 0;
	int numBytes = 0;
	int stringPosition = 0;
	int listPosition = 0;

	memoryCheck(currentChar);
	memoryCheck(stringList);

	if (argc > 2)
	{
		fprintf(stderr, "Exiting. Incorrect number of arguments\n");
		exit(1);
	}
	else if (argc == 2 && !strcmp(option, "-f"))
	{
		fflag = 1;
	}
	else if (argc == 2 && strcmp(option, "-f"))
	{
		fprintf(stderr, "Incorrect argument. Options are:\n-f\nExiting\n");
		exit(1);
	}

	if (fstat(0, &Data) < 0)
	{
		fprintf(stderr, "fstat memory allocation error\nExiting\n");
		exit(1);
	}


	if (S_ISREG(Data.st_mode))
	{
		tempFile = malloc((Data.st_size+1)*sizeof(char));
		memoryCheck(tempFile);

		while (read(0, currentChar, 1))
		{
			if (numBytes > 0 && Data.st_size <= numBytes+1)
			{
				temp2 = realloc(tempFile ,(numBytes+2)*sizeof(char));
				memoryCheck(temp2);
				tempFile = temp2;
			}

			tempFile[numBytes] = *currentChar;
			numBytes++;
		} // end while

		int i;
		for (i = 0; i < numBytes; i++)
		{
			*currentChar = tempFile[i];
			if (*currentChar != EOF && *currentChar != ' ' &&
													*currentChar != '\n')
			{
				if (stringPosition == 0)
				{
					temp = malloc(2*sizeof(char));
				}
				else
				{
					temp = realloc(currentString,
									(stringPosition+2)*sizeof(char));
				}

				memoryCheck(temp);
				currentString = temp;
				currentString[stringPosition] = *currentChar;
				stringPosition++;
			} // end if

			else
			{
				if (stringPosition == 0)
				{
					temp = malloc(2*sizeof(char));
				}
				else
				{
					temp = realloc(currentString,
									(stringPosition+2)*sizeof(char));
				}

				memoryCheck(temp);
				currentString = temp;

				if (*currentChar == EOF)
					currentString[stringPosition] = ' ';
				else
					currentString[stringPosition] = *currentChar;

				currentString[stringPosition+1] = '\0';

				stringList[listPosition] = currentString;

				temp = realloc(stringList,(listPosition+2)*sizeof(char*));
				memoryCheck(temp);

				stringList = temp;
				stringPosition = 0;
				listPosition++; 
			} // end else
		} // end for
		free(tempFile);
	} // end if
	else
	{
		int res = read(0, currentChar, 1);
		while (res > 0)
		{
			if (errorCheck())
			{
				for (int i = 0; i < listPosition; i++)
				{
					free(stringList[listPosition]);
				}
				free(stringList);
				return 1;
			} // end if
			if (*currentChar != EOF && *currentChar != ' ' &&
													*currentChar != '\n')
			{
				if (stringPosition == 0)
				{
					temp = malloc(2*sizeof(char));
				}
				else
				{
					temp = realloc(currentString,
									(stringPosition+2)*sizeof(char));
				}
    
				memoryCheck(temp);
				currentString = temp;
				currentString[stringPosition] = *currentChar;
				stringPosition++;
			} // end if 
			else
			{
				if (stringPosition == 0)
				{
					temp = malloc(2*sizeof(char));
				}
				else
				{
					temp = realloc(currentString,
									(stringPosition+2)*sizeof(char));
				}

				memoryCheck(temp);
				currentString = temp;

				currentString[stringPosition] = *currentChar;
				currentString[stringPosition+1] = '\0';
				stringList[listPosition] = currentString;
    
				temp = realloc(stringList,(listPosition+2)*sizeof(char*));
				memoryCheck(temp);
    
				stringList = temp;
				stringPosition = 0;
				listPosition++; 
			} // end else
			
			res = read(0, currentChar, 1);
			if (!res)
			{
				if (stringPosition == 0)
				{
					temp = malloc(2*sizeof(char));
				}
				else
				{
					temp = realloc(currentString,
									(stringPosition+2)*sizeof(char));
				}

				memoryCheck(temp);
				currentString = temp;
				currentString[stringPosition] = ' ';
				currentString[stringPosition+1] = '\0';
				stringList[listPosition] = currentString;
    
				stringPosition = 0;
				listPosition++; 
			}
		} // end while
	} // end else

	if (fflag)
	{
		qsort(stringList, listPosition, sizeof(char*), prefrobcmpUpper);
	}
	else
	{
		qsort(stringList, listPosition, sizeof(char*), prefrobcmp);
	}

	void* curchar;
	for (size_t i = 0; i < listPosition; i++)
	{
		for (size_t j = 0; stringList[i][j] != '\0' ; j++)
		{
			curchar = &stringList[i][j];
			write(1, curchar, 1);
		}
	}

	free(currentChar);
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

int prefrobcmpUpper(const void* str1, const void* str2)
{
	const char* string1 = *(const char**)str1;
	const char* string2 = *(const char**)str2;
	return frobcmpUpper(string1, string2);
}

int frobcmpUpper(char const* s1, char const* s2)
{	
	for (;;s1++, s2++)
	{
		while (*s1 == '\0') s1++;
		while (*s2 == '\0') s2++;

		if (*s1 == ' ' && *s2 == ' ') return 0;

		if (*s1 == ' ' || (toupper(*s1^42)) < (toupper(*s2^42))) return -1;

		if (*s2 == ' ' || (toupper(*s1^42)) > (toupper(*s2^42))) return 1;
	}
}
