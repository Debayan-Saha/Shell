#include "header.h"
void month(int x)
{
	switch (x)
	{
	case 0: printf(" Jan "); break;
	case 1: printf(" Feb "); break;
	case 2: printf(" Mar "); break;
	case 3: printf(" Apr "); break;
	case 4: printf(" May "); break;
	case 5: printf(" Jun "); break;
	case 6: printf(" Jul "); break;
	case 7: printf(" Aug "); break;
	case 8: printf(" Sep "); break;
	case 9: printf(" Oct "); break;
	case 10: printf(" Nov "); break;
	case 11: printf(" Dec "); break;
	}
}
void ls(char *token)
{
	char *buf;
    char temp[1024];
	buf = strtok (token, " \n\t");
	char* argument[100];
	int count = 0;
	buf = strtok (NULL, " \n\t");
	while (buf != NULL)
	{
		argument[count] = buf;
		count++;
		buf = strtok (NULL, " \n\t");
	}
    // printf("count %d",count);
	struct dirent *de;  // Pointer for directory entry 
	struct passwd *pd;
	struct group *gp;
    struct stat tp;
	stat("main.c", &tp);
	mode_t val;
	val=(tp.st_mode & S_IFMT);
    DIR *dr = opendir(".");
    if(count == 0) // ls
    {
	    // printf(" %s ",argument[0]);
    	while ((de = readdir(dr)) != NULL)
        {
        	strncpy(temp, de->d_name, 254);
	        temp[254] = '\0';
	        if(temp[0]!='.')
	            printf("%s ", de->d_name);	
	    }
	    printf("\n");
	    closedir(dr);
    }
    else if(count == 1) // ls + flag or file
    {
	    // printf("%s",argument[0]);
    	if(strcmp(argument[count-1], "-a") == 0)
    	{
    		while ((de = readdir(dr)) != NULL)
	            printf("%s ", de->d_name);
		    closedir(dr);
		    printf("\n");
    	}
    	else if(strcmp(argument[count-1], "~") == 0 )
    	{
    		dr = opendir(root);
    		while ((de = readdir(dr)) != NULL)
	        {
	        	strncpy(temp, de->d_name, 254);
		        temp[254] = '\0';
		        if(temp[0]!='.')
		            printf("%s ", de->d_name);	
		    }
		    closedir(dr);
		    printf("\n");
    	}
    	else if(strcmp(argument[count-1], "-la") == 0 || strcmp(argument[count-1], "-al") == 0 || strcmp(argument[count-1], "-l") == 0)
    	{
    		while ((de = readdir(dr)) != NULL)
	        {
	    		strncpy(temp, de->d_name, 254);
		        temp[254] = '\0';
		        if(temp[0] =='.' && strcmp(argument[count-1], "-l") == 0)
		        	continue;
	    		
	    		stat(de->d_name, &tp);
	    		mode_t val;
	    		val=(tp.st_mode & S_IFMT);
				if(val == S_IFBLK)
					printf("b");
				else if(val == S_IFCHR)
					printf("c");
				else if(val == S_IFDIR)
					printf("d");
				else if(val == S_IFIFO)
					printf("p");
				else if(val == S_IFLNK)
					printf("l");
				else if(val == S_IFSOCK)
					printf("s");
				else
					printf("-");
	    		val=(tp.st_mode & ~S_IFMT);
				(val & S_IRUSR) ? printf("r") : printf("-");
		        (val & S_IWUSR) ? printf("w") : printf("-");    
		        (val & S_IXUSR) ? printf("x") : printf("-");
		        (val & S_IRGRP) ? printf("r") : printf("-");
		        (val & S_IWGRP) ? printf("w") : printf("-");
		        (val & S_IXGRP) ? printf("x") : printf("-");
		        (val & S_IROTH) ? printf("r") : printf("-");
		        (val & S_IWOTH) ? printf("w") : printf("-");
		        (val & S_IXOTH) ? printf("x") : printf("-");
				printf(" %ld", tp.st_nlink);
				pd = getpwuid(tp.st_uid);
				gp = getgrgid(tp.st_gid);
				printf(" %10s", pd->pw_name);
				printf(" %10s", gp->gr_name );
				printf(" %9ld", tp.st_size);
				// printf(" %s", de->d_name);
				struct tm *changetime;
				changetime = localtime(&tp.st_mtime);
				month(changetime->tm_mon);
				printf("%2d ", changetime->tm_mday);
				printf("%2d:", changetime->tm_hour);
				if ((changetime->tm_min / 10) > 0)
				{
					printf("%2d ", changetime->tm_min);
				}
				else
				{
					printf("0%1d ", changetime->tm_min);
				}
				printf("%s\n", de->d_name);
		    }
		    closedir(dr);
    	}
    	else
    	{
    		dr = opendir(argument[0]);
		    if (dr == NULL)  
		    {
	    		int exist = stat(argument[0], &tp);
			    if(exist == 0)
			        printf("%s ", argument[0]);
			    else  
			        printf("Could not open directory\n");
		    }
		    else
		    {
		    	while ((de = readdir(dr)) != NULL)
		        {
		        	strncpy(temp, de->d_name, 254);
			        temp[254] = '\0';
			        if(temp[0]!='.')
			            printf("%s ", de->d_name);	
			    }
			    closedir(dr);
			    printf("\n");
		    }
    	}
    }
    else if(count >= 2) // ls + flag + file + files 
    {
    	int flag_a = 0;
    	int flag_l = 0;
    	int flagdir = 0;
    	if(strcmp(argument[0], "-a") == 0 || strcmp(argument[1], "-a") == 0)
    		flag_a =1;
    	if(strcmp(argument[0], "-al") == 0 || strcmp(argument[1], "-al") == 0 || strcmp(argument[0], "-la") == 0 || strcmp(argument[1], "-la") == 0)
    	{
			flag_a =1;
			flag_l =1;
    	}
    	if(strcmp(argument[0], "-l") == 0 || strcmp(argument[1], "-l") == 0)
    		flag_l =1;

		if(strcmp(argument[1], "-a") == 0 || strcmp(argument[1], "-l") == 0 || strcmp(argument[1], "-al") == 0 || strcmp(argument[1], "-la") == 0)
			flagdir++;
		if(strcmp(argument[0], "-a") == 0 || strcmp(argument[0], "-l") == 0 || strcmp(argument[0], "-al") == 0 || strcmp(argument[0], "-la") == 0)
			flagdir++;
		if(flagdir==2)
		{
			if(count == 2)
			{
				while ((de = readdir(dr)) != NULL)
		        {		    		
		    		stat(de->d_name, &tp);
		    		mode_t val;
		    		val=(tp.st_mode & S_IFMT);
					if(val == S_IFBLK)
						printf("b");
					else if(val == S_IFCHR)
						printf("c");
					else if(val == S_IFDIR)
						printf("d");
					else if(val == S_IFIFO)
						printf("p");
					else if(val == S_IFLNK)
						printf("l");
					else if(val == S_IFSOCK)
						printf("s");
					else
						printf("-");
		    		val=(tp.st_mode & ~S_IFMT);
					(val & S_IRUSR) ? printf("r") : printf("-");
			        (val & S_IWUSR) ? printf("w") : printf("-");    
			        (val & S_IXUSR) ? printf("x") : printf("-");
			        (val & S_IRGRP) ? printf("r") : printf("-");
			        (val & S_IWGRP) ? printf("w") : printf("-");
			        (val & S_IXGRP) ? printf("x") : printf("-");
			        (val & S_IROTH) ? printf("r") : printf("-");
			        (val & S_IWOTH) ? printf("w") : printf("-");
			        (val & S_IXOTH) ? printf("x") : printf("-");
					printf(" %ld", tp.st_nlink);
					pd = getpwuid(tp.st_uid);
					gp = getgrgid(tp.st_gid);
					printf(" %10s", pd->pw_name);
					printf(" %10s", gp->gr_name );
					printf(" %9ld", tp.st_size);
					// printf(" %s", de->d_name);
					struct tm *changetime;
					changetime = localtime(&tp.st_mtime);
					month(changetime->tm_mon);
					printf("%2d ", changetime->tm_mday);
					printf("%2d:", changetime->tm_hour);
					if ((changetime->tm_min / 10) > 0)
					{
						printf("%2d ", changetime->tm_min);
					}
					else
					{
						printf("0%1d ", changetime->tm_min);
					}
					printf("%s\n", de->d_name);
			    }
			    closedir(dr);
			}
			else
			{
				for(int i=2; i<count; i++)
				{
					dr = opendir(argument[i]);
					if (dr == NULL)  
				    {
			    		int exist = stat(argument[i], &tp);
					    if(exist == 0)
					    {
					        if(flag_l)
					        {
					        	stat(argument[i], &tp);
					    		mode_t val;
					    		val=(tp.st_mode & S_IFMT);
								if(val == S_IFBLK)
									printf("b");
								else if(val == S_IFCHR)
									printf("c");
								else if(val == S_IFDIR)
									printf("d");
								else if(val == S_IFIFO)
									printf("p");
								else if(val == S_IFLNK)
									printf("l");
								else if(val == S_IFSOCK)
									printf("s");
								else
									printf("-");
					    		val=(tp.st_mode & ~S_IFMT);
								(val & S_IRUSR) ? printf("r") : printf("-");
						        (val & S_IWUSR) ? printf("w") : printf("-");    
						        (val & S_IXUSR) ? printf("x") : printf("-");
						        (val & S_IRGRP) ? printf("r") : printf("-");
						        (val & S_IWGRP) ? printf("w") : printf("-");
						        (val & S_IXGRP) ? printf("x") : printf("-");
						        (val & S_IROTH) ? printf("r") : printf("-");
						        (val & S_IWOTH) ? printf("w") : printf("-");
						        (val & S_IXOTH) ? printf("x") : printf("-");
								printf(" %ld", tp.st_nlink);
								pd = getpwuid(tp.st_uid);
								gp = getgrgid(tp.st_gid);
								printf(" %10s", pd->pw_name);
								printf(" %10s", gp->gr_name );
								printf(" %9ld", tp.st_size);
								// printf(" %s", de->d_name);
								struct tm *changetime;
								changetime = localtime(&tp.st_mtime);
								month(changetime->tm_mon);
								printf("%2d ", changetime->tm_mday);
								printf("%2d:", changetime->tm_hour);
								if ((changetime->tm_min / 10) > 0)
								{
									printf("%2d ", changetime->tm_min);
								}
								else
								{
									printf("0%1d ", changetime->tm_min);
								}
								printf("%s\n", argument[i]);
					        }
					        else
					        {
						        printf("%s ", argument[i]);
							    printf("\n");

					        }
					    }
					    else  
					        printf("Could not open directory\n");
				    }
				    else if(flag_l)
				    {
			    		printf("%s:\n", argument[i]);
				    	while ((de = readdir(dr)) != NULL)
				        {
				    		strncpy(temp, de->d_name, 254);
					        temp[254] = '\0';
					        if(temp[0] =='.' && flag_a == 0)
					        	continue;
				    		stat(de->d_name, &tp);
				    		mode_t val;
				    		val=(tp.st_mode & S_IFMT);
							if(val == S_IFBLK)
								printf("b");
							else if(val == S_IFCHR)
								printf("c");
							else if(val == S_IFDIR)
								printf("d");
							else if(val == S_IFIFO)
								printf("p");
							else if(val == S_IFLNK)
								printf("l");
							else if(val == S_IFSOCK)
								printf("s");
							else
								printf("-");
				    		val=(tp.st_mode & ~S_IFMT);
							(val & S_IRUSR) ? printf("r") : printf("-");
					        (val & S_IWUSR) ? printf("w") : printf("-");    
					        (val & S_IXUSR) ? printf("x") : printf("-");
					        (val & S_IRGRP) ? printf("r") : printf("-");
					        (val & S_IWGRP) ? printf("w") : printf("-");
					        (val & S_IXGRP) ? printf("x") : printf("-");
					        (val & S_IROTH) ? printf("r") : printf("-");
					        (val & S_IWOTH) ? printf("w") : printf("-");
					        (val & S_IXOTH) ? printf("x") : printf("-");
							printf(" %ld", tp.st_nlink);
							pd = getpwuid(tp.st_uid);
							gp = getgrgid(tp.st_gid);
							printf(" %10s", pd->pw_name);
							printf(" %10s", gp->gr_name );
							printf(" %9ld", tp.st_size);
							// printf(" %s", de->d_name);
							struct tm *changetime;
							changetime = localtime(&tp.st_mtime);
							month(changetime->tm_mon);
							printf("%2d ", changetime->tm_mday);
							printf("%2d:", changetime->tm_hour);
							if ((changetime->tm_min / 10) > 0)
							{
								printf("%2d ", changetime->tm_min);
							}
							else
							{
								printf("0%1d ", changetime->tm_min);
							}
							printf("%s\n", de->d_name);
					    }
					    closedir(dr);
				    }
				    else
				    {
			    		printf("%s:\n", argument[i]);
				    	while ((de = readdir(dr)) != NULL)
				        {
				        	strncpy(temp, de->d_name, 254);
					        temp[254] = '\0';
					        if(temp[0]=='.')
					        {
					        	if(flag_a == 0)
						        	continue;
						        else
						            printf("%s ", de->d_name);

					        }
				            else	
					            printf("%s ", de->d_name);
					            
					    }
					    closedir(dr);
					    printf("\n");
				    }
				}
			}
		}
		else if (flagdir ==1)
		{	
			for(int i=1; i< count; i++)
			{
				dr = opendir(argument[i]);
				if (dr == NULL)  
				{
		    		int exist = stat(argument[i], &tp);
				    if(exist == 0)
				    {
				        if(flag_l)
				        {
				        	stat(argument[i], &tp);
				    		mode_t val;
				    		val=(tp.st_mode & S_IFMT);
							if(val == S_IFBLK)
								printf("b");
							else if(val == S_IFCHR)
								printf("c");
							else if(val == S_IFDIR)
								printf("d");
							else if(val == S_IFIFO)
								printf("p");
							else if(val == S_IFLNK)
								printf("l");
							else if(val == S_IFSOCK)
								printf("s");
							else
								printf("-");
				    		val=(tp.st_mode & ~S_IFMT);
							(val & S_IRUSR) ? printf("r") : printf("-");
					        (val & S_IWUSR) ? printf("w") : printf("-");    
					        (val & S_IXUSR) ? printf("x") : printf("-");
					        (val & S_IRGRP) ? printf("r") : printf("-");
					        (val & S_IWGRP) ? printf("w") : printf("-");
					        (val & S_IXGRP) ? printf("x") : printf("-");
					        (val & S_IROTH) ? printf("r") : printf("-");
					        (val & S_IWOTH) ? printf("w") : printf("-");
					        (val & S_IXOTH) ? printf("x") : printf("-");
							printf(" %ld", tp.st_nlink);
							pd = getpwuid(tp.st_uid);
							gp = getgrgid(tp.st_gid);
							printf(" %10s", pd->pw_name);
							printf(" %10s", gp->gr_name );
							printf(" %9ld", tp.st_size);
							// printf(" %s", de->d_name);
							struct tm *changetime;
							changetime = localtime(&tp.st_mtime);
							month(changetime->tm_mon);
							printf("%2d ", changetime->tm_mday);
							printf("%2d:", changetime->tm_hour);
							if ((changetime->tm_min / 10) > 0)
							{
								printf("%2d ", changetime->tm_min);
							}
							else
							{
								printf("0%1d ", changetime->tm_min);
							}
							printf("%s\n", argument[i]);
				        }
				        else
					    {   
					    	printf("%s ", argument[i]);
					    	printf("\n");
					    }

				    }
				    else
				        printf("Could not open directory\n");

			    }
			    else if(flag_l)
			    {
		    		printf("%s:\n", argument[i]);
			    	while ((de = readdir(dr)) != NULL)
			        {
			    		strncpy(temp, de->d_name, 254);
				        temp[254] = '\0';
				        if(temp[0] =='.' && flag_a == 0)
				        	continue;
			    		
			    		stat(de->d_name, &tp);
			    		mode_t val;
			    		val=(tp.st_mode & S_IFMT);
						if(val == S_IFBLK)
							printf("b");
						else if(val == S_IFCHR)
							printf("c");
						else if(val == S_IFDIR)
							printf("d");
						else if(val == S_IFIFO)
							printf("p");
						else if(val == S_IFLNK)
							printf("l");
						else if(val == S_IFSOCK)
							printf("s");
						else
							printf("-");
			    		val=(tp.st_mode & ~S_IFMT);
						(val & S_IRUSR) ? printf("r") : printf("-");
				        (val & S_IWUSR) ? printf("w") : printf("-");    
				        (val & S_IXUSR) ? printf("x") : printf("-");
				        (val & S_IRGRP) ? printf("r") : printf("-");
				        (val & S_IWGRP) ? printf("w") : printf("-");
				        (val & S_IXGRP) ? printf("x") : printf("-");
				        (val & S_IROTH) ? printf("r") : printf("-");
				        (val & S_IWOTH) ? printf("w") : printf("-");
				        (val & S_IXOTH) ? printf("x") : printf("-");
						printf(" %ld", tp.st_nlink);
						pd = getpwuid(tp.st_uid);
						gp = getgrgid(tp.st_gid);
						printf(" %10s", pd->pw_name);
						printf(" %10s", gp->gr_name );
						printf(" %9ld", tp.st_size);
						// printf(" %s", de->d_name);
						struct tm *changetime;
						changetime = localtime(&tp.st_mtime);
						month(changetime->tm_mon);
						printf("%2d ", changetime->tm_mday);
						printf("%2d:", changetime->tm_hour);
						if ((changetime->tm_min / 10) > 0)
						{
							printf("%2d ", changetime->tm_min);
						}
						else
						{
							printf("0%1d ", changetime->tm_min);
						}
						printf("%s\n", de->d_name);
				    }
				    closedir(dr);
			    }
			    else
			    {
		    		printf("%s:\n", argument[i]);
			    	while ((de = readdir(dr)) != NULL)
			        {
			        	strncpy(temp, de->d_name, 254);
				        temp[254] = '\0';
				        if(temp[0]=='.')
				        {
				        	if(flag_a == 0)
					        	continue;
					        else
					            printf("%s ", de->d_name);

				        }
			            else	
				            printf("%s ", de->d_name);
				    }
				    closedir(dr);
				    printf("\n");        
			    }
			}
		}
		else
		{	
			for(int i=0; i< count; i++)
			{
				dr = opendir(argument[i]);
				if (dr == NULL)  
				{
		    		int exist = stat(argument[i], &tp);
				    if(exist == 0)
				    {
				           
						printf("%s ", argument[i]);
				    	printf("\n");
				    }
				    else
				        printf("Could not open directory\n");

			    }
			    else
			    {
		    		printf("%s:\n", argument[i]);
			    	while ((de = readdir(dr)) != NULL)
			        {
			        	strncpy(temp, de->d_name, 254);
				        temp[254] = '\0';
				        if(temp[0]=='.')
				        {
				        	if(flag_a == 0)
					        	continue;
					        else
					            printf("%s ", de->d_name);

				        }
			            else	
				            printf("%s ", de->d_name);
				    }
				    closedir(dr);
				    printf("\n");        
			    }
			}
	    
    	}
    }
	return;
}
