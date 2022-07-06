#include "header.h"
void execpipe(char arr[])
{
	int stdin = 0, stdout = 1;
	int len = strlen(arr);
	int no_pipe = 0;
	for(int i = 0; i<len; i++)
	{
		if (arr[i] == '|')
			no_pipe++;
	}
	if (no_pipe == 0)
	{
		handlecommand(arr);
		return;
	}
	char tokens[no_pipe + 1][100];
	char *ptr = strtok(arr, "|\n\t");
	for(int i=0; i<no_pipe + 1; i++)
	{
		strcpy(tokens[i], ptr);
		ptr = strtok(NULL, "|\n\t");
	}
	int fdes[20][2];
	stdin = dup(0);
	stdout = dup(1);
	for(int i=0; i<=no_pipe; i++)
	{
		if (pipe(fdes[i]) < 0) //change
		{
			perror("Pipe Failed!!\n");
			exit(0);
		}
		if (i == 0) //initial
		{
			dup2(fdes[i][1], 1);
			close(fdes[i][1]);
		}
		else if (i == no_pipe) // end
		{
			dup2(fdes[i - 1][0], 0);
			dup2(stdout, 1);
			close(fdes[i - 1][0]);
		}
		else // rest
		{
			dup2(fdes[i - 1][0], 0);
			dup2(fdes[i][1], 1);
			close(fdes[i - 1][0]);
			close(fdes[i][1]);
		}
		int pid = fork();
		if (pid < 0)
		{
			perror("fork failed");
			exit(0);
		}
		if (pid == 0)
		{
			handlecommand(tokens[i]);
			exit(0);
		}
		else
		{
			wait(NULL);
			dup2(stdin, 0);
			dup2(stdout, 1);
		}
	}
}