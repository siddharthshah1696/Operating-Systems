#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h> 
#include<fcntl.h> 
#include<sys/types.h> 

int main()
{

	int pid;
	int fd[2];
	pipe(fd);
	pid=fork();
	if(pid>0)
	{
		char front[100];
		printf(" input the head of your email : \n");
		gets(front);
		close(fd[0]);
		write(fd[1],front, strlen(front)+1);
		wait(NULL);

	}
	else
	{
		char *cmd1 = {"echo "};
		char head[10];
		char *foot = {"@goa.bits-pilani.ac.in"};
		char *cmd2 = {"| tr a-z A-Z"};
		char finalcmd[1000];
		finalcmd[0]='\0';

		close(fd[1]);
		read(fd[0],head,100);
		close(fd[0]);

		strcat(finalcmd,cmd1);
		//printf(" echo added = %s \n",finalcmd );

		strcat(finalcmd,head);
		//printf(" head added = %s \n",finalcmd );

		strcat(finalcmd,foot);
		//printf(" foot added = %s \n",finalcmd );

		strcat(finalcmd,cmd2);
		printf(" pipe added = %s \n",finalcmd );

		system(finalcmd);
		
	}
	return 0;
}