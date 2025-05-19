#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#define THREADS 4

unsigned long long factorial(int n) {
	if (n <= 1) return 1;
	return n * factorial(n - 1);
}

void *printme(void *arg)
{
	int num = *(int *)arg;
	unsigned long long result = factorial(num);
	printf("Gija %lu: %d! = %llu\n", (unsigned long)pthread_self(), num, result);
	return NULL;
}

int main()
{
	int i;
	pthread_t *tid_array;
	void *retval;
	int err;

	tid_array = (pthread_t *)malloc(THREADS*sizeof(pthread_t));
	if(tid_array == NULL)
	{
		exit(1);
	}

	for (i = 0; i < THREADS; i++) 
	{
		int *val = malloc(sizeof(int));
		if(val == NULL)
		{
			exit(1);
		}

		*val = i + 1;

		err = pthread_create(&(tid_array[i]),
				     NULL,
				     printme,
				     val);

		if(err != 0)
		{
			fprintf(stderr,"thread %d ",i);
			perror("on create");
			exit(1);
		}
    	}

	for (i = 0; i < THREADS; i++) 
	{
    		pthread_join(tid_array[i], &retval);
  	}

	free(tid_array);

	return(0);
}


