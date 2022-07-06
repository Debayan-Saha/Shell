#include "header.h"
void in_out_file(char charr[])
{
	char * tok;
	tok = strtok(charr, " \n\t");
	while (tok != NULL)
	{
		// printf("%s\n", tok);
		if (!strcmp(tok, "<"))
		{
			tok = strtok(NULL, " \n\t");
			strcpy(infile, tok);
		}
		if (!strcmp(tok, ">") || !(strcmp(tok, ">>")))
		{
			tok = strtok(NULL, " \n\t");
			// printf("%s\n", tok);
			strcpy(outfile, tok);
		}
		tok = strtok(NULL, " \n\t");
	}
}
void handlecommand(char buf[])
{
	char* token;
	for(int i =0; i<1024; i++)
	{
		infile[i] = '\0';
		outfile[i] = '\0';
	}
	char charr[1024];
	strcpy(charr, buf);
	int j = 2000;
	int k = strlen(buf);
	int isappend = 0;
	for(int i =0; i<k; i++)
	{
		if (buf[i] == '>' || buf[i] == '<')
		{
			j = i;
			break;
		}
	}
	for(int i =0; i<k; i++)
	{
		if (buf[i] == '>')
		{
			if (buf[i + 1] == '>')
			{
				isappend = 1;
			}
		}
	}

	int bin, bout, in, out;
	if(j<1024)
	{
		for(int i=j; i<k; i++)
		{
			buf[i] = '\0';
		}
		
		in_out_file(charr);
		bin = dup(0);
		bout = dup(1);
		if (strlen(infile) > 0)
		{
			in = open(infile, O_RDONLY);
			if (in < 0)
			{
				printf("Input File Invalid\n");
				return;
			}
			dup2(in, STDIN_FILENO);
			close(in);
		}
		if (strlen(outfile) > 0)
		{
			if (isappend)
			{
				out = open(outfile, O_APPEND |  O_WRONLY , 0644);
				if (out < 0)
				{
					printf("Output File Invalid\n");
					return;
				}
			}
			else
			{
				// printf("awd\n");
				out = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			}
			dup2(out, STDOUT_FILENO);
			close(out);
		}
	}
	char temp[1024];
	strcpy(temp, buf);
	token = strtok(buf, " \n\t");

	// printf("%s toke %ld\n", temp,strlen(temp));
	if ((strcmp(token, "cd") == 0))
	{
		cd(temp);
	}
	else if (strcmp(token, "ls") == 0)
	{
		ls(temp);
	}
	else if (strcmp(token, "echo") == 0)
	{
		if(j>1024)
			echo(temp);
		else
		{
			// printf("adsf");
			int f;
			token = strtok (NULL, "\"");
			if (isappend)
			{
				f = open(outfile, O_APPEND |  O_WRONLY , 0644);
				if (f < 0)
				{
					printf("Output File Invalid\n");
					return;
				}
			}
			else
			{
				// printf("awd\n");
				f = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			}
			write(f, &token[0], strlen(token));
			close(out);
			// printf("%ld", strlen(token));
		}
	}
	else if (strcmp(token, "pwd") == 0)
	{
		pwd();
	}
	else if (strcmp(token, "pinfo") == 0)
	{
		pinfo(temp);
	}
	else if (strcmp(token, "repeat") == 0)
	{
		repeat(temp);
	}
	else if (strcmp(token, "history") == 0)
	{
		history(temp);
	}
	else if (strcmp(token, "jobs") == 0)
	{
		jobs(temp);
	}
	else if (strcmp(token, "exit") == 0)
	{
		exitout();
	}
	else
	{
		execute(temp);
	}
	if(j<1024)
	{
		if (strlen(infile) > 0)
		{
			dup2(bin, 0);
			close(bin);
		}
		if (strlen(outfile) > 0)
		{
			dup2(bout, 1);
			close(bout);
		}
	}

	return;
}
void dir()
{
	char path[1024];
	if(strlen(root)<=strlen(cwd))
	{
		for(int i=strlen(root); i<strlen(cwd)+1;i++)
		{
			cwd[i-strlen(root)]=cwd[i];
		}
		strcpy(path, cwd);
		cwd[0] = '~';
		for(int i=0; i<strlen(path)+1;i++)
		{
			cwd[i+1]=path[i];
		}
	}
}