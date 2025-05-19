/* The Producer-Consumer problem                                     */
/* 8 producers, 12 consumers, and a buffer size of 5.                */
/* Each Producer and Consumer is a seperate thread                   */
/* The buffer will be a shared, globally declared queue implemented with a  */
/* circular array of length 6, and will have two functions to modify it:   */
/* enqueue() and dequeue() .                                     */
/* Elements in the queue will be of type int .                     */


#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define PRODUCERS 8
#define CONSUMERS 12
#define BUFFERSIZE 5

#define FALSE 0
#define TRUE  1 

/* Producer and Consumer */
void *producer(void * );
void *consumer(void * );

/* Struct that defines semphores and buffer parameters */
typedef struct {
    sem_t mutex;
    sem_t empty;
    sem_t full;
    int buffer[6];
    int head , tail , size ;
  } args ;


void enqueue (int , args *);
int dequeue(args *);

int main(int argc , char** argv)
{
  args *params;    
  int p,c;
 
  pthread_t prodtid[PRODUCERS];
  pthread_t constid[CONSUMERS];

  params  = (args *)malloc ( sizeof(args));

  sem_init(&(params->empty),TRUE,5);
  sem_init(&(params->full),TRUE,0);
  sem_init(&(params->mutex),TRUE,TRUE);
  
  params->head = 0 ;
  params->tail = 0 ;
  params->size = 0 ;

  /* producer */
  for (p=0 ; p<8 ; p++)
  { 
   pthread_create(&prodtid[p],NULL,producer,(void *)params );
  }
  
  /* consumer */
  for (  c = 0 ; c < 12 ; c++)
  {
   pthread_create(&constid[c],NULL,consumer,(void *)params );
  }
 
  /* join producers and consumers */
  for ( p = 0 ; p < 8 ; p++)
  { 
     pthread_join(prodtid[p],NULL);
  }

  for ( c = 0 ; c < 12 ; c++)
  {
    pthread_join(constid[c],NULL);
  }
  
  /* deallocate memory */
  free(params);
  return 0;
}


void *producer(params)
  void *params;
{
  int i;
  for (i = 0 ; i < 12 ; i++)
  {
    int value ;
    value  = rand ();
    printf("The random number generated is %d \n" , value) ;
    sem_wait(&((args *)params)->empty);
    enqueue( value , (args *)params);
    sem_post(&((args *)params)->full);
  }
  return NULL;
}

void enqueue( int value , args *params)
{
    sem_wait(&((args *)params)->mutex);
    if (((args *)params)->size  < 5)
    {
      ((args *)params)->size++;
      ((args *)params)->buffer[((args *)params)->tail] = value;
      ((args *)params)->tail++;
      if  (((args *)params)->tail == 5)
      {
        ((args *)params)->tail = 0;
      }
    }
    printf( "Added %d  to the buffer \n", value);
    sem_post(&((args *)params)->mutex);
}

void *consumer(params)
     void *params;
{ 
  int i, value;
  for ( i = 0 ; i < 8 ; i++)
  {
    sem_wait(&((args *)params)->full);
    value = dequeue((args*)params);
    sem_post(&((args *)params)->empty);
    printf("The random number removed is %d \n" , value) ;
  }
  return NULL;
}

int dequeue(args *params)
{
    int value ;
    sem_wait(&((args *)params)->mutex);
    if (((args *)params)->size  > 0 )
    {
     ((args *)params)->size--;
     value =((args *)params)->buffer[((args *)params)->head];
     ((args *)params)->head++;
     if (((args *)params)->head ==5)
     {
       ((args *)params)->head = 0 ;
     }
    }
    sem_post(&((args *)params)->mutex);
    return value ;
}


