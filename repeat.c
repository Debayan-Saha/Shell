#include "header.h"
int sq(int times)
{
	int x = 1;
	for(int i =0; i<times;i++)
	{
		x = x*10;
	}
	return x;
}
void repeat(char *token)
{
	char *buf;
	char *argument;
	char *argument1;
	int no=0;
	int x;
	buf = strtok (token, " \t");
	argument = strtok (NULL, " \n\t");
	if(argument==NULL)
	{
		printf("Error: Too few arguments\n");
		return;
	}
	else
	{
		int len = strlen(argument);
		// printf("%c\n",argument[1]);
		for(int i =0 ;i<len; i++)
		{
			x = (argument[i] - '0');
			// printf("as %d\n", x);
			if(x>9 || x<0)
			{
				printf("Error: Wrong argument\n");
				return;
			}
			no = no+ sq(len-i-1)*x;
		}
		argument1 = strtok (NULL, ";\n");
		if(argument1==NULL)
		{
			printf("Error: Too few arguments\n");
			return;
		}
		else
		{
			char temp[1024];
			char qwe[1024];
			strcat(argument1, "\n");
			strcpy(temp, argument1);
			for(int i =0; i<no; i++)
			{
				// printf("%s",argument1);
				strcpy(qwe, temp);
				handlecommand(qwe);
			}
		}
	}
	return;
}
