#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <fcntl.h> 
#include<sys/wait.h>
#include <sys/types.h>

int main()
{
	char command[100];
	gets(command);
	int file_desc = open("file_desc.txt", O_WRONLY|O_APPEND);
	dup2(file_desc,1);
	system(command);
	
	return 0;
}