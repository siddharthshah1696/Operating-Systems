
// Semaphore solution for Roller Coaster Problem - Single Car

// Semaphore solution for Roller Coaster Problem

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#define N 10  //Number of passengers
#define C 2  //Capacity of car

int boarded_passengers=0;
int unboarded_passengers=0;
int trip_no=0;
sem_t board_queue,leave_queue,all_aboard,all_unboard,mutex;

void load(){
    printf("\n/////////////////////////////////////////////////////////////////////\n");
    printf("\nLoading -> Trip no %d \n",++trip_no);
}

void unload(){
    printf("\nUnloading -> Trip_no %d \n",trip_no);
}

void run(){
    printf("\nRide in progress -> Trip no %d \n",trip_no);
}

void board(int x){
  printf("\nPassenger %d has boarded car\n",x);
}

void unboard(int x){
  printf("\nPassenger %d has unboarded car\n",x);
}

void * car_func ( void * arg)
{ 
  while(1){
    load();
    for(int i=0; i<C; i++)
      sem_post(&board_queue);
    sem_wait(&all_aboard);      
    run();
    unload();
    for(int i=0; i<C; i++)
      sem_post(&leave_queue);
    sem_wait(&all_unboard);
  }
}

void * passenger_func (int x)
{ 
  //Entering Car
  sem_wait(&board_queue);
  board(x);
  sem_wait(&mutex);
  if(++boarded_passengers==C){
    sem_post(&all_aboard);
    boarded_passengers=0;
  }
  sem_post(&mutex);
  //Leaving car
  sem_wait(&leave_queue);
  unboard(x);
  sem_wait(&mutex);
  if(++unboarded_passengers==C){
    sem_post(&all_unboard);
    unboarded_passengers=0;
  }
  sem_post(&mutex);
}

void initialize(){
  sem_init (&all_aboard, 0, 0);
  sem_init (&all_unboard, 0, 0);
  sem_init (&board_queue, 0, 0);
  sem_init (&leave_queue, 0, 0);
  sem_init (&mutex, 0, 1);
}

int main ()
{

  printf ("\nProgram has begun\n\n");

  pthread_t passengers[N], car;
  initialize();
  pthread_create(&car,NULL,car_func,NULL);
 
  for (int i = 0; i < N; i++)
    pthread_create (&passengers[i], NULL, passenger_func, i+1);   
  
  for (int i = 0; i < N; i++)
    pthread_join (passengers[i], NULL);

  printf ("\n\nProgram has ended\n");
  return 0;
}