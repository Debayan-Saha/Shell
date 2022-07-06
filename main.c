#include "header.h"
void sigintHandler (int sig_num)
{
	if (onjobs == 0)
	{
		return;
	}
	kill(fbjobs[onjobs - 1].pid, SIGKILL);
}
int main()
{
	signal(SIGINT, sigintHandler);
	printf("\033[H\033[J");
	getcwd(root, 1024);
	open("history.txt", O_CREAT, 0644);
	strcpy(add_his, root);
	strcat(add_his, "/history.txt");
	initialise_history();
	char * user = getenv("USER");
	char host[1024];
	gethostname(host, 1024);
	char buf[1024];
	while (1)
	{
		char *msg = NULL;
		char input[1024];
		char buf[1024];

		getcwd(cwd, 1024);
		dir();
		printf("<%s@%s:%s> ", user, host, cwd);
		// int x = fgets(input, 1024, stdin);
		if (fgets(input, 1024, stdin) == NULL)
		{
			printf("\n");
			exitout();
		}
		if (strlen(input) > 1)
		{	
			appendtofile(input);
			msg = strtok (input, ";\n");
			while (1)
			{
				strcpy(buf, msg);
				
				execpipe(buf);
				msg = strtok (msg + strlen (msg) + 1, ";\n");
				// printf("%s",msg);
				if(msg==NULL)
					break;
			}
		}
	}
}
