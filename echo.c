#include "header.h"
void echo(char token[])
{
	char *buf;
	buf = strtok (token, " \n\t");
	buf = strtok (NULL, " \n\t");

	while (buf != NULL)
	{
		printf("%s ",buf);
		buf = strtok (NULL, " \n\t");
	}
	printf("\n");
	return;
}
