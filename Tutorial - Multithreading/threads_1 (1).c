#include <stdio.h>
#include <stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include <pthread.h>

struct Sides{
	float l;
	float b;
};

void *calculateArea(void *vargp)
{
    struct Sides *myShape = (struct Sides *)vargp;
    if(myShape->l==myShape->b)
    	printf("Area of square is : %.3f units\n",myShape->l*myShape->b);
    else
    	printf("Area of rectangle is : %.3f units\n",myShape->l*myShape->b);
}

void *calculatePerimeter(void *vargp)
{
    struct Sides *myShape = (struct Sides *)vargp;
    if(myShape->l==myShape->b)
    	printf("Perimeter of square is : %.3f units\n",2*(myShape->l+myShape->b));
    else
    	printf("Perimeter of rectangle is : %.3f units\n",2*(myShape->l+myShape->b));
}	


int main(){
	struct Sides square,rectangle;
	printf("Enter length of square : ");
	scanf("%f",&square.l);
	square.b=square.l;
	printf("Enter length and breadth of rectangle : ");
	scanf("%f %f",&rectangle.l,&rectangle.b);
	pthread_t tsquare,trect;
	int pid = fork();
	if(pid){
		wait(NULL);
		pthread_create(&tsquare, NULL, calculateArea, (void *)&square);
		pthread_join(tsquare, NULL);
		pthread_create(&trect, NULL, calculateArea, (void *)&rectangle);
		pthread_join(trect, NULL);
    }
    else{    	
		pthread_create(&tsquare, NULL, calculatePerimeter, (void *)&square);
		pthread_join(tsquare, NULL);
		pthread_create(&trect, NULL, calculatePerimeter, (void *)&rectangle);
    	pthread_join(trect, NULL);
    }
	return 0;
}
