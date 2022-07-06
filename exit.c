#include "header.h"
void exitout()
{
	for(int i = 0; i < onjobs; i++)
	{
		if (fbjobs[i].status == 0)
		{
			kill(fbjobs[i].pid, SIGKILL);
		}
	}
	printf("Terminated\n");
	exit(1);
}