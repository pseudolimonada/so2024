//compile with: gcc -Wall -pthread sharedvariable_posix.c -o svar
//using POSIX named semaphores

#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h> // include POSIX semaphores

/*insert here the other libraries needed*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int * shared_var;
int shmid;
sem_t *mutex;

void worker()
	{
	usleep(1000000 + rand()%11*100000); //uses microseconds sleep and waits 1 to 2 seconds in periods of 0.1 secs
	
	sem_wait(mutex);
	
	(*shared_var)++;
	
	sem_post(mutex);	
	}

int main(int argc, char *argv[])
	{
	int i, n_procs;

	if(argc!=2) {
		printf("Wrong number of parameters\n");
		exit(0);
		}

	n_procs=atoi(argv[1]);

	// Create shared memory
	shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0777);
	if(shmid < 0){
		perror("Error creating shared memory using shmget\n");
		exit(1);	
	}
	
	// Attach shared memory
	shared_var = (int *) shmat(shmid, NULL, 0);
	if(*shared_var == -1){
		perror("Error associating shared var to shmid\n");
		exit(1);
	}

	// Create semaphore
	sem_unlink("MUTEX");
	mutex = sem_open("MUTEX", O_CREAT | O_EXCL, 0700, 1);
	if(mutex == SEM_FAILED){
		perror("Error creating semaphore\n");
		exit(1);
	}
	
	// initialize variable in shared memory
	*shared_var = 1000;

	// Create worker processes
	for(i = 0; i < n_procs; i++){
		if(fork() == 0){
			printf("Worker %d created\n",getpid());
			worker();
			printf("Worker %d leaving\n",getpid());
			exit(0);
		}	
	}	
	// Wait for all worker processes
	for(i = 0; i<n_procs; i++){
		wait(NULL);
	}
	
	// print final result
	printf("Final result = %d\n",*shared_var);	
		
	// remove resources (shared memory and semaphore)
	sem_close(mutex);
	sem_unlink("MUTEX");
	shmdt(shared_var);
	shmctl(shmid, IPC_RMID,NULL);

	exit(0);
}
