#include "header.h"
void initialise_history()
{
	int fd = open(add_his, O_RDONLY);
	if (fd < 0)
	{
		perror("Unable to open file\n");
		return;
	}
	char buff[10000];
	read(fd, buff, 10000);
	char *ptr = strtok(buff, "\n");
	while (ptr != NULL)
	{
		strcpy(hist[his_count % 20], ptr);
		// hist[his_count % 20][strlen(ptr)] = '\0';
		his_count++;
		ptr = strtok(ptr + strlen(ptr) + 1, "\n");
	}
}
void appendtofile(char *input)
{
	FILE *fp;
	fp = fopen(add_his, "w+");
    int fix = 19;
	char temphis[20][1024];
	input[strlen(input) - 1] = '\0';
    if(strcmp(input, hist[0])!=0)
    {
	    strcpy(temphis[0], input);
	    for(int i=0;i<his_count;i++)
		    strcpy(temphis[i+1], hist[i]);
	    if(his_count>=fix)
	        his_count=fix;
	    else
	        his_count++;
	    for(int i=0;i<his_count;i++)
		    strcpy(hist[i], temphis[i]);
	}
	for(int i = 0; i<his_count; i++)
	{
		fprintf(fp, "%s\n", hist[i]);
	}
	fclose(fp);
}
void printhistory(int n)
{
	if(n<=his_count+1)
	{
		for(int i = n-1; i>=0; i--)
		{
			printf("%s\n", hist[i]);
		}
	}
	else
	{
		for(int i = his_count-1; i>=0; i--)
		{
			printf("%s\n", hist[i]);
		}
	}
}
void history(char *token)
{
	char *buf;
	char *argument;
	int no=0;
	int x;
	buf = strtok (token, " \t");
	argument = strtok (NULL, " \n\t");
	if (argument == NULL)
		printhistory(10);
	else
	{
		int len = strlen(argument);
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
		printhistory(no);
	}
}