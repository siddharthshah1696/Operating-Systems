#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <fcntl.h> 
#include<sys/wait.h>
#include <sys/types.h>

int main()
{
	int file_desc = open("file_desc.txt", O_CREAT|O_RDWR|O_APPEND);
	dup2(file_desc,1);
	printf("Hello dosto  \n");
	printf(" Hello fraands! chai peelo \n");
	return 0;
}