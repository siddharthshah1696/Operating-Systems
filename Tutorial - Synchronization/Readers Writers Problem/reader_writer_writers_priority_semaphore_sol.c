
// Semaphore solution for Readers-Writer Problem - Writers have priority

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#define N 1000

sem_t mutex1,mutex2,mutex3,r,w;
int rcount=0,wcount=0;

int data=0;
int readers_finished = 0, writers_finished = 0;

void * writer (int writer_no)
{
  sem_wait (&mutex2);
  wcount++;
  if(wcount==1)
    sem_wait(&r);
  sem_post(&mutex2);

  sem_wait(&w);
  data++;
  printf ("\nWrite operation by writer : %d , Data = %d ", writer_no, data);
  sem_post(&w);

  sem_wait (&mutex2);
  wcount--;
  if(wcount==0)
    sem_post(&r);
  sem_post(&mutex2);

}

void * reader (int reader_no)
{
  sem_wait (&mutex3);

  sem_wait(&r);
  sem_wait(&mutex1);
  rcount++;
  if (rcount == 1)
    sem_wait (&w);		
  sem_post (&mutex1);
  sem_post(&r);

  sem_post(&mutex3);

  // Read operation on data
  printf ("\nRead operation by reader :  %d , Data = %d ", reader_no, data);

  // Readers exits 
 sem_wait(&mutex1);
  rcount--;
  if (rcount == 0)
    sem_post (&w);    
  sem_post (&mutex1);

}

int main ()
{
  printf ("\nProgram has begun \n");
  pthread_t readers[N], writers[N];
  
  sem_init (&mutex1, 0, 1);
  sem_init (&mutex2, 0, 1);
  sem_init (&mutex3, 0, 1);
  sem_init (&r, 0, 1);
  sem_init (&w, 0, 1);

  for (int i = 0; i < N; i++)
    {
      pthread_create (&writers[i], NULL, writer, i + 1);
      pthread_create (&readers[i], NULL, reader, i + 1);
    }

  for (int i = 0; i < N; i++)
    {
      pthread_join (writers[i], NULL);
      pthread_join (readers[i], NULL);
    }

  printf ("\n\nProgram has ended \n");
  return 0;
}
