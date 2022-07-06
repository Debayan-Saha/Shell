#include "header.h"
void pinfo(char *token)
{
	char *buf;
	char *argument;
	buf = strtok (token, " \n\t");
	argument = strtok (NULL, " \n\t");
	char prp[100] = "/proc/";
	char exe[100];
	char pd[20];
	if (argument == NULL)
	{
		int pid = getpid();
		sprintf(pd, "%d", pid);
	}
	else
	{
	// printf("%s\n", argument);
		strcpy(pd, argument);
	}
	strcat(prp, pd); // /proc/pd
	strcpy(exe, prp); // /proc/pd
	strcat(prp, "/stat"); // /proc/pd/stat
	strcat(exe, "/exe"); //  /proc/pd/exe
	// printf("%sss\n", prp);
	char buff[10000];
	int fd = open(prp, O_RDONLY);
	if (fd < 0)
	{
		perror("Error");
	}
	else
	{
		char* arr[1000];
		read(fd, buff, 10000);
		// printf("%s\n", buff);
		char *ptr = strtok(buff, " \t");
		int count = 0;
		while (ptr != NULL)
		{
			arr[count] = ptr;
			count++;
			ptr = strtok (ptr + strlen (ptr) + 1, " \t");
		}
		printf("pid -- %s\n", pd );
		printf("Process Status -- %s\n", arr[2]);
		printf("memory -- %s    {Virtual Memory}\n", arr[22]);
		char pathexe[1000];
		for(int i=0;i<1000;i++)
			pathexe[i] = '\0';
		readlink(exe, pathexe, 1000);
		// pathexe[strlen(pathexe)] = '\0';	
		printf("Executable Path -- %s\n", pathexe);
		for(int i=0;i<1000;i++)
			pathexe[i] = '\0';
	}
}