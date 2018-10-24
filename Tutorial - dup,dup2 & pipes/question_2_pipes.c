#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h> 
#include<fcntl.h> 
#define MSIZE 10000

int main()
{
	 int fd[2];
	 pipe(fd);
	 int pid = fork();
	 if(pid>0)
	 {
	 	 wait(NULL);
	 	 char *str = (char *)malloc(MSIZE);
	 	 close(fd[1]);
	 	 read(fd[0],str,MSIZE);
	 	 int x = open("example_copy4.txt", O_WRONLY | O_CREAT);
	 	 write(x,str,MSIZE);
	 }
	 else
	 {	
	 	dup2(fd[1],1);
	 	close(fd[0]);
	 	char *cmd1={"cat example.txt"};
	 	system(cmd1);	
	 }
    
	return 0;
}