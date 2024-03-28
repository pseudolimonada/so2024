#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/fcntl.h>
#include <semaphore.h>
#include <sys/wait.h>

typedef struct {
	int max_mobile_users;
} info_struct;

typedef struct {
	pid_t client_id; //pid client process
    int plafond; 
} mobile_struct;

typedef struct {
    

} auth_struct;


