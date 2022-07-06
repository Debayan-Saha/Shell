#include "header.h"
void cd(char *token)
{
	char *buf;
	char *argument;
	char *argument1;
	buf = strtok (token, " \n\t");
	argument = strtok (NULL, " \n\t");
	argument1 = strtok (NULL, " \n\t");
	if(argument1!=NULL)
	{
		printf("Error: Too many arguments\n");
		return;
	}
	else
	{
		int d;
		if (argument == NULL)
		{
			chdir(root);
			return;
		}
		else if (strcmp(argument, "..") == 0)
		{
			chdir(argument);
			getcwd(cwd, 1024);
			return;
		}
		else if (strcmp(argument, "~") == 0)
		{
			chdir(root);
			return;
		}
		else if (strcmp(argument, "-") == 0)
		{
			pwd();
			return;
		}
		else if (strcmp(argument, ".") == 0)
		{
			return;
		}
		else
		{
			d = chdir(argument);
			if (d == -1)
			{
				printf("Error: No such file or directory\n");
				return;
			}
		}
	}
}
