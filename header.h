#include<stdio.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/utsname.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/sysmacros.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>
typedef struct {
	char job_name[1024];
	pid_t pid;
	int status;
} job;
job fbjobs[100];
int onjobs;
char cwd[1024];
char root[1024];
char hist[20][1024];
int his_count;
char add_his[1024];
char infile[1024];
char outfile[1024];
void exitout();
void handlecommand(char []);
void dir();
void pwd();
void cd(char *);
void echo(char *);
void repeat(char *);
void ls(char *);
void history(char *);
int sq(int);
void initialise_history();
void appendtofile(char *);
void execute(char *);
void pinfo(char *);
void execpipe(char []);
void jobs(char []);
