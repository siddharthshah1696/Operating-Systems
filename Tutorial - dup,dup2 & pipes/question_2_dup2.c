#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h> 
#include<fcntl.h> 


int main()
{
	 
	 int x = open("example_copy.txt", O_WRONLY | O_CREAT);
	 dup2(x,1);
	 int pid = fork();
	 if(pid>0)
	 {
	 	close(1);	
	 	wait(NULL);

	 }
	 else
	 {	
	 	char *cmd2={"cat example.txt"};
	 	system(cmd2);
	 }
    
	return 0;
}
