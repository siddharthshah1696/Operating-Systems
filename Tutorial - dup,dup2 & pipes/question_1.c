#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h> 
#include<fcntl.h> 


int main()
{
	// Program to simulate working of pipe in the terminal according to question 1 - /bin/ls -al | /usr/bin/tr a-z A-Z
	 int fd[2];
	 pipe(fd);
	 int pid = fork();
	 if(pid>0)
	 {
	 	// Changing standard output to pipe
	 	dup2(fd[1],1);
	 	char *cmd1={"/bin/ls -al"};
	 	//Executing first command - output is written to pipe
	 	system(cmd1);
	 	wait(NULL);
	 }
	 else
	 {
	 	//changing standard input to pipe
	 	dup2(fd[0],0);
	 	char *cmd2={"/usr/bin/tr a-z A-Z"};
	 	//Executing second command - input is data stored in the pipe and output is written to terminal
	 	system(cmd2);
	 }
    
	return 0;
}