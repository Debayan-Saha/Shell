#include "header.h"
void schandler(int sig)
{
	pid_t pidn;
	int status;
	pidn = waitpid(-1, &status, WNOHANG);
	if (pidn > 0)
	{
		int j = -1;
		for(int i = 0; i<onjobs; i++)
		{
			if (fbjobs[i].pid == pidn)
			{
				j = i;
				fbjobs[i].status = 0;
				break;
			}
		}
		if (WEXITSTATUS(status) == 0 && WIFEXITED(status) && (j != -1))
		{
			printf("\n%s with pid %d exited normally\n", fbjobs[j].job_name, fbjobs[j].pid);
			fbjobs[j].status = -1;
		}
		else if (j != -1)
		{
			printf("\n%s with pid %d failed to exit normally\n", fbjobs[j].job_name, fbjobs[j].pid);
			fbjobs[j].status = -1;
		}
	}
}
void execute(char *token)
{
	pid_t pid;
	int status;
	char* arg[100];
	int count = 0;
	char *buf;
	// printf(" %sdebayan\n",token);
	buf = strtok (token, " \n\t");
	// buf = strtok (NULL, " \n\t");
	while (buf != NULL)
	{
		// printf("%s ",buf);
		arg[count]= buf;
		count++;
		buf = strtok (NULL, " \n\t");
	}
	arg[count] = NULL;
	int isbg = 0;
	if (strcmp(arg[count - 1], "&") == 0)
	{
		// printf("312\n");
		isbg = 1;
		signal(SIGCHLD, schandler);
	}
	// for (int i = 0; i < count+1; ++i)
	// {
	// 	 // code 
	// 	printf("%s %d\n", arg[i], i);
	// }
	// printf(" %sadsf",arg[count -1]);
	pid = fork();
	if (pid == 0)
	{
		if (strcmp(arg[count - 1], "&") == 0)
		{
			setpgid(0, 0);
			arg[count - 1] = NULL;
		}
		int exec = execvp(arg[0], arg);
		if (exec < 0)
		{
			printf("Error! Execution failed\n");
		}
		// exit(1);
		// printf("asd\n");
	}
	else if (pid > 0)
	{
		if (!isbg)
		{
			fbjobs[onjobs].pid = pid;
			strcpy(fbjobs[onjobs].job_name, arg[0]);
			fbjobs[onjobs].status = 1;
			onjobs++;
			waitpid(pid, &status, 0); //wait till the child process is terminated
			if (WIFSTOPPED(status))
			{
				// printf("wad\n");
				fbjobs[onjobs - 1].status = 0;
			}
		}
		if(isbg)
		{
			fbjobs[onjobs].pid = pid;
			strcpy(fbjobs[onjobs].job_name, arg[0]);
			fbjobs[onjobs].status = 0;
			onjobs++;
			printf("%d\n", fbjobs[onjobs - 1].pid);
		}

	}
	// return;
}