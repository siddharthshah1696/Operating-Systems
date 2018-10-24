#include <stdio.h>
#include <stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include <pthread.h>
#define MAX 100000
int arr[MAX];
int n;
unsigned long long odd_sum,even_sum;

void *find_sum(void *var){
    int val = *((int *)var);
    if(!val){
        even_sum=0;
        for(int i=0; i<n; i+=2){
            even_sum+=arr[i];
        }
        printf("\nSum of elements at even positions : %lld \n",even_sum);
    }
    else{
        odd_sum=0;
        for(int i=1; i<n; i+=2){
            odd_sum+=arr[i];
        }
        printf("\nSum of elements at odd positions : %lld \n",odd_sum);
    }
}

void print_arrary(){
    printf("\n Initial array is : \n");
    for(int i=0; i<n; i++){
        printf("%d ",arr[i]);
    }
    printf("\n");
}
int main(){
		scanf("%d",&n);
        for(int i=0; i<n; i++){
            scanf("%d",&arr[i]);
        }
        print_arrary();
        pthread_t t_odd,t_even;
        int odd=1,even=0;
        pthread_create(&t_odd,NULL,find_sum,(void *)&odd);
        pthread_create(&t_even,NULL,find_sum,(void *)&even);
        pthread_join(t_odd,NULL);
        pthread_join(t_even,NULL);
       
	return 0;
}
