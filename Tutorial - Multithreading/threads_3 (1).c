#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

#define MAXSIZE 101

int arr[MAXSIZE];
bool found;
int indx;
char ans;

void initialize(){
    found=0;
    indx=-1;
    ans='X';
    for(int i=0; i<MAXSIZE; i++)
        arr[i]=i;
}

void *findFromLeft(void *var)
{
    int *ele = (int *)(var);
    for(int i=0; i<MAXSIZE; i++){
        if(found)
            break;    
        if(arr[i]==*ele){
            found=1;
            indx=i;
            ans='L';
            break;
        }
    //    printf("\n%d %d %d L",i,arr[i],*ele);
    }
}

void *findFromRight(void *var)
{
    int *ele = (int *)(var);
    for(int i=MAXSIZE-1; i>=0; i--){
        if(found)
            break;    
        if(arr[i]==*ele){
            found=1;
            indx=i;
            ans='R';
            break;
        }
    //   printf("\n%d %d %d R",i,arr[i],*ele);        
    }
}



int main(){
		int key;
		printf("\nEnter a value to find : ");
		scanf("%d",&key);
		pthread_t thread_left,thread_right;
        initialize();
      //  printf("\nStart of Search : %d %d %c\n",found,indx,ans);
		pthread_create(&thread_left, NULL, findFromLeft , (void *)&key);
        pthread_create(&thread_right, NULL, findFromRight , (void *)&key);        
        pthread_join(thread_left,NULL);
        pthread_join(thread_right,NULL);
      //  printf("\nEnd of Search : %d %d %c\n",found,indx,ans);
        if(found){
            if(ans=='L')
                printf("\nElement found at indx : %d by Left thread\n",indx);
            else
                printf("\nElement found at indx : %d by Right thread\n",indx);
        }
        else{
            printf("\nElement not found in the array");
        }
        return 0;
}
