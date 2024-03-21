// Compile as: gcc matrix.c -lpthread -D_REENTRANT -Wall -o matrix

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define M 3 //first matrix lines
#define K 2 //first matrix columns; second matrix lines
#define N 3 //second matrix columns

struct v {
  int row;
  int column;
};

typedef struct v coordenate;
void *worker(void* coord);
void *show_matrix();	// prints matrices on screen

pthread_t my_thread[(M*N)+1];
int A[M][K] = { {1,4}, {2,5}, {3,6} };
int B[K][N] = { {8,7,6}, {5,4,3} };
int C[M][N];

int thread_id[M*N+1];

// creates mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void print_matrix(){ 
// prints matrices on screen when having exclusive access
  for(int m = 0; m < M; m++){
     printf("[");
     for(int n = 0; n < N; n++){
	printf(" %d ",C[m][n]);
     }
     printf("]\n");
  } 
}

int main(void) {
  // creates threads and sends each the coordinates of the element to calculate
  for(int i = 0; i < M*N; i++){
	C[i/N][i%N] = 0;
  }

  thread_id[M*N] = M*N+1;
  pthread_create(&my_thread[M*N],NULL, show_matrix, &thread_id[M*N]);
  
  for(int i = 0; i < M*N; i++){		
	thread_id[i] = i;
	pthread_create(&my_thread[i],NULL, worker, &thread_id[i]);
 }

  // waits for threads to finish
  for(int i = 0; i < M*N; i++){
	pthread_join(my_thread[i],NULL);
  }  
  pthread_join(my_thread[M*N+1],NULL);

// prints final results of the calculation and leaves
  print_matrix();
}


void *worker(void* coord) {
  // calculates each matrix element in the coordinate received
  int coo = *((int *)coord);
  //usleep(rand()*9000000+1000000);
  
  pthread_mutex_lock(&mutex);
  
  for(int i = 0; i < K; i++){
	C[coo/N][coo%N] += A[coo/N][i] * B[i][coo%N];
  }
  pthread_mutex_unlock(&mutex);
  pthread_exit(NULL);
}

void *show_matrix() {
// prints the status of the matrix in each second, along a period of 10 seconds
  for(int i = 0; i<10; i++){
   usleep(1000000);
   pthread_mutex_lock(&mutex);
   print_matrix();
   pthread_mutex_unlock(&mutex);
  }
  pthread_exit(NULL);
}
