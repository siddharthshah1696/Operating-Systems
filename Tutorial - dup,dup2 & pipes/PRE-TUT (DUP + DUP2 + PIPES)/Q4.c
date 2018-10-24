#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <fcntl.h> 
#include<sys/wait.h>
#include <sys/types.h>

int ncr(int n, int r)
{
	
	int k=r;
	float ans=1;
	if(r > n-r) k = n-r;
	
	for(int i=0;i<k;i++)
	{
		ans*=(n-i);
		ans/=(r-i);
	}
	return ans;

}

int main()
{
	int fd1[2],fd2[2];
	pipe(fd1);
	pipe(fd2);
	int pid = fork();
	if(pid>0)
	{
		int n=0,r=0;
		//debug stmt printf("Input n and r of nCr \n");
		scanf("%d",&n);
		scanf("%d",&r);
		char N[10],R[10];
		//int -> string
		sprintf(N,"%d",n);
		sprintf(R,"%d",r);
		//debug stmt printf("%s and %s are N and R \n",N,R );

		//Parent sending n , r to child
		close(fd1[0]);
		write(fd1[1],N,10);
		write(fd1[1],R,10);	
		close(fd1[1]);

		wait(NULL);
		// Parent recieving ncr value from child
		char ans[10];

		close(fd2[1]);
		read(fd2[0],ans,10);
		close(fd2[0]);

		printf("%s is the ans \n",ans );

	}
	else
	{
		char buffer1[10];
		char buffer2[10];

		// child recieving n and r from parent
		close(fd1[1]);
		read(fd1[0],buffer1 ,10);
		read(fd1[0],buffer2 ,10);
		close(fd1[0]);

		int n=0,r=0;
		// string -> integer
		sscanf(buffer1,"%d",&n);
		sscanf(buffer2,"%d",&r);
		
		int ans = ncr(n,r);
		char buffer3[10];
		// int -> string
		sprintf(buffer3,"%d",ans); 
		
		close(fd2[0]);
		write(fd2[1],buffer3,10);
		close(fd2[1]);

	}
	return 0;
} 
