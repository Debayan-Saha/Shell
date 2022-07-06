#include "header.h"
void jobs(char *token)
{
	int c = 0;
	int pro[100];
	int proch[100];
	for (int i = 0; i < 100; i++)
	{
		/* code */
		pro[i]=0;
		proch[i]=0;
	}
	char *bf;
	// char *argument;
	char *a;
	bf = strtok (token, " \n\t");
	a = strtok (NULL, " \n\t");
	int check = 0;
	// printf("%sds\n", a);
	if(a == NULL)
	{
		check = 1;
	}
	else if(a[0] == '-' && a[1] == 'r') 
	{
		check = 2;
	}
	else if(a[0] == '-' && a[1] == 's') 
	{
		check = 3;
		// printf
	}
	if(check == 0)
	{
		printf("Wrong argument\n");
		return;
	}
	// printf("%d\n", check);	
	for(int i=0; i<onjobs; i++)
	{
		if (fbjobs[i].status == 1 || fbjobs[i].status == -1)
		{
			continue;
		}
		char fs[100];
		sprintf(fs, "/proc/%d/status", fbjobs[i].pid);
		int fd = open(fs, O_RDONLY);
		if(check == 1 || check == 3)
		{
			if (fd < 0 )
			{
				// printf("[%d] Stopped %s [%d]\n", c + 1, fbjobs[i].job_name, fbjobs[i].pid);
				proch[c]=3;
				pro[c]=i;
				c++;
				continue;
			}
		}
		char buf[100];
		read(fd, buf, 100);
		char * temp;
		temp = strtok(buf, " :\n\t\r");
		while (!(strcmp(temp, "State") == 0))
		{
			temp = strtok(NULL, " :\n\t\r");
		}
		temp = strtok(NULL, " :\n\t\r");
		if(check == 1)
		{
			if (!strcmp(temp, "T"))
			{
				// printf("[%d] Stopped %s [%d]\n", c + 1, fbjobs[i].job_name, fbjobs[i].pid);
				proch[c]=3;
				pro[c]=i;
				c++;
			}
			else
			{
				// printf("[%d] Running %s [%d]\n", c + 1, fbjobs[i].job_name, fbjobs[i].pid);
				proch[c]=2;
				pro[c]=i;
				c++;
			}
		}
		else if(check == 2)
		{
			if (strcmp(temp, "T"))
			{
				// printf("[%d] Running %s [%d]\n", c + 1, fbjobs[i].job_name, fbjobs[i].pid);
				proch[c]=2;
				pro[c]=i;
				c++;
			}
		}	
		else if(check == 3)
		{
			if (!strcmp(temp, "T"))
			{
				// printf("[%d] Stopped %s [%d]\n", c + 1, fbjobs[i].job_name, fbjobs[i].pid);
				proch[c]=3;
				pro[c]=i;
				c++;
			}
		}	
	}
	int alpha;
	for(int i=0;i<c;i++)
	{
   		for(int j=i+1;j<c;j++)
   		{
      		if(strcmp(fbjobs[pro[i]].job_name, fbjobs[pro[j]].job_name)>0)
      		{
         		alpha = pro[i];
         		pro[i] = pro[j];
         		pro[j] = alpha;

         		alpha = proch[i];
         		proch[i] = proch[j];
         		proch[j] = alpha;
      		}
   		}
	}
	for(int i =0 ;i<c;i++)
	{
		if (proch[i] == 3)
		{
			printf("[%d] Stopped %s [%d]\n", pro[i] + 1, fbjobs[pro[i]].job_name, fbjobs[pro[i]].pid);
		}
		else if (proch[i] == 2)
		{
			printf("[%d] Running %s [%d]\n", pro[i] + 1, fbjobs[pro[i]].job_name, fbjobs[pro[i]].pid);
		}
	}
}