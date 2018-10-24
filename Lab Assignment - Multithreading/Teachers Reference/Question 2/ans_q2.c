#include <stdio.h>
#include <stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include <pthread.h>

int mat[100][100];
float mat_median[100];
int n,m;

void *sort_row(void *var)
{
    int r=*((int *)var);
    //printf("\n R value is : %d \n ",r);
        for(int i=0; i<m; i++){
            int ind=i;
            for(int j=i+1; j<m; j++){
                //printf("\n Processing : %d %d %d \n",r,i,j);
                if(mat[r][j]<mat[r][ind]){
                    ind=j;
                }
            }
            int temp=mat[r][i];
            mat[r][i]=mat[r][ind];
            mat[r][ind]=temp;
        }
   // printf("\n Sorted Row no %d",r);
}

void *find_medians(void *var){
    for(int i=0; i<n; i++){
        if(m%2==0)
            mat_median[i]=(mat[i][m/2-1]+mat[i][m/2])/2.0;
        else
            mat_median[i]=mat[i][m/2];
    }
}

void print_mat(){
    printf("\n Printing matrix \n");
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            printf(" %d ",mat[i][j]);
        }
        printf("\n");
    }
}

void print_mat_median(){
    printf("\n Printing medians of each row\n");
    for(int i=0; i<n; i++){
        printf(" %.3f ",mat_median[i]);
    }
}


void initialize(){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            // int x = rand()%100;
            // if(!x) 
            // mat[i][j]=11;
            // else
            //     mat[i][j] =  (x >= 10) ? x : 10*x + 1 ;

            scanf("%d",&mat[i][j]);
        }
    }
}
int main(){
		scanf("%d %d",&n,&m);
        initialize();
        printf("Before");
        print_mat();
        printf("\n");
		pthread_t thread_arr[n],median_ans;
        int row_no[n];

        for(int i=0; i<n; i++){
          row_no[i]=i;
		  pthread_create(&thread_arr[i], NULL, sort_row, (void *)&row_no[i]);
		}

        for(int i=0; i<n; i++){
          pthread_join(thread_arr[i], NULL);
        }

        pthread_create(&median_ans,NULL,find_medians,(void *)NULL);
        pthread_join(median_ans,NULL);
        printf("After ");
        print_mat();
        print_mat_median();

	return 0;
}
