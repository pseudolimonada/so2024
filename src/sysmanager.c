#include "logs.h"
#include "sysmanager.h"
#include "authmanager.h"
#include <errno.h>

#define MBUF 1024
#define NUM_CONFIG_VARS 6

int MOBILE_USERS, QUEUE_POS, AUTH_SERVERS, AUTH_PROC_TIME, MAX_VIDEO_WAIT, MAX_OTHERS_WAIT;

sem_t *mutex_log, *mutex_memory;
info_struct *info;
mobile_struct *mobiles;

void *monitor_engine(){
    return(0);
}

void *authorization_manager(){
    return(0);
}

void *message_queue(){
    return(0);
}

//reads config file
void read_config(const char *config_file){
    char message[MBUF];
    FILE *file = fopen(config_file,"r");
    if (file == NULL) {
        write_log("Error opening config file");
        exit(1);
    }

    int config_values[NUM_CONFIG_VARS];

    char line[MBUF];
    int count = 0;
    while(fgets(line, sizeof(line), file) != NULL && count < 6){
        // Remove newline character from line
        line[strcspn(line, "\n")] = '\0';

        // Convert line to integer
        char *end;
        errno = 0;
        config_values[count] = strtol(line, &end, 10);
        if (errno != 0 || *end != '\0' || config_values[count] < 0) {
            write_log("Error reading config file: values must be non-negative integers");
            exit(1);
        }

        count++;
    }

    // Check if count < NUM_CONFIG_VARS (currently ignores extra lines)
    if(count != NUM_CONFIG_VARS){
        write_log("Error reading config file: incorrect number of lines");
        exit(1);
    }

    fclose(file);

    // Check if specific config variable conditions are met
    if(config_values[2] == 0 || config_values[3] == 0 || config_values[4] == 0 || config_values[5] == 0){
        write_log("Error reading config file: invalid values");
        exit(1);
    }

    MOBILE_USERS = config_values[0];
    QUEUE_POS = config_values[1];
    AUTH_SERVERS = config_values[2];
    AUTH_PROC_TIME = config_values[3];
    MAX_VIDEO_WAIT = config_values[4];
    MAX_OTHERS_WAIT = config_values[5];
    
    sprintf(message,"Config file read successfully. MOBILE_USERS: %d, QUEUE_POS: %d, AUTH_SERVERS: %d, AUTH_PROC_TIME: %d, MAX_VIDEO_WAIT: %d, MAX_OTHERS_WAIT: %d", MOBILE_USERS, QUEUE_POS, AUTH_SERVERS, AUTH_PROC_TIME, MAX_VIDEO_WAIT, MAX_OTHERS_WAIT);
    write_log(message);
}

void show_shm(){
  printf("Showing shm (integer by integer):\n");
  // The effect of p+n where p is a pointer and n is an integer is to compute the address equal to p plus n times the size of whatever p points to
  int *p = (int *) info;
//   for(int i=0;i<( (sizeof(info_struct)+sizeof(order_struct)*n_orders+sizeof(sell_struct)*n_orders)/sizeof(int));i++){
//     printf("%d  ",*(p+i));
//     if(i%2==1) printf("\n");
//   }
  printf("\n");
}

//cleans resources after SIGNINT
void finish() {
  show_shm();

  printf("Cleaning resources...\n");
  sem_close(mutex_log);
  sem_close(mutex_memory);
  sem_unlink("MUTEX_LOG");
  sem_unlink("MUTEX_MEMORY");
  shmdt(info);
  // shmctl(shmid, IPC_RMID, NULL);

  write_log("Closing program!");
  exit(0);
}

//called on SIGNINT signal
void sigint(int signum){
  finish();
}


int main(int argc, char const *argv[])
{
    if(argc != 2){
        write_log("Invalid number of arguments");
        exit(1);
    }

    //reads config file
    read_config(argv[1]);

    //cria shared mem (info + NMAX_USERS * client_struct + )
    
    

    // creates semaphores of log for all of these
    sem_unlink("MUTEX_LOG");
	mutex_log=sem_open("MUTEX_LOG",O_CREAT|O_EXCL,0700,1); // create semaphore
	if(mutex_log==SEM_FAILED){
		perror("Failure creating the semaphore MUTEX");
    finish();
    exit(1);
	}

	sem_unlink("MUTEX_MEMORY");
	mutex_memory=sem_open("MUTEX_MEMORY",O_CREAT|O_EXCL,0700,0); // create semaphore
	if(mutex_memory==SEM_FAILED){
		perror("Failure creating the semaphore GO_WORKERS");
    finish();
    exit(1);
	}

    // creates authorization manager  (já é dado o numero de authorization engines que vao ser criados ao inicio)
    //// creates authorization engines
    //// creates sender/receiver
    // creates monitor enginee
    // creates message queue

    // waits to capture end signal
    // sends end signal to other processes (to end them)


    // cleans message queue
    // cleans semaphores
    // cleans shared memory
    // sends final log message

    return 0;
}
