#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	void *s = malloc(4*sizeof(char));
	void *frob = malloc(4*sizeof(char));
	s = argv[1];
	int length = strlen(s);

	memfrob(s, length);
	printf("%s\n", s);
	return 0;
}
