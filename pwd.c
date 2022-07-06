#include "header.h"
void pwd()
{
	getcwd(cwd, 1024);
	printf("%s\n", cwd);
	return;
}