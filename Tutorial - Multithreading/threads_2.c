#include <stdio.h>
#include <stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include <pthread.h>

void *factorial_n(void *vargp)
{
    int *n = (int *)vargp;
    int no=*n;
    *n=1;
    for(int i=1; i<=no; i++){
    	(*n)*=i;
    }
    printf("\n Factorial n : %d",*n);
}

void *factorial_r(void *vargp)
{
    int *n = (int *)vargp;
    int no=*n;
    *n=1;
    for(int i=1; i<=no; i++){
    	(*n)*=i;
    }
    printf("\n Factorial r : %d",*n);
}

void *factorial_nr(void *vargp)
{
    int *n = (int *)vargp;
    int no=*n;
    *n=1;
    for(int i=1; i<=no; i++){
    	(*n)*=i;
    }
    printf("\n Factorial n-r : %d",*n);
}

int main(){
		int n,r;
		printf("\nEnter values of n and r for nCr ( n >= r) : ");
		scanf("%d %d",&n,&r);
		int a=n,b=r,c=n-r;
		pthread_t thread_n,thread_r,thread_nr;
		pthread_create(&thread_n, NULL, factorial_n, (void *)&a);
		pthread_create(&thread_r, NULL, factorial_r, (void *)&b);
		pthread_create(&thread_nr, NULL, factorial_nr, (void *)&c);
		pthread_join(thread_n, NULL);
		pthread_join(thread_r, NULL);
		pthread_join(thread_nr, NULL);
		printf("\nValue of nCr is %.3f : ",1.0*a/(1.0*b*c));

	return 0;
}
