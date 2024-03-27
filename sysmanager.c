#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#define MBUF 1024
#define NUM_CONFIG_VARS 6

int MOBILE_USERS, QUEUE_POS, AUTH_SERVERS, AUTH_PROC_TIME, MAX_VIDEO_WAIT, MAX_OTHERS_WAIT;


void write_log(char *str){
    char timestamp[MBUF];
    
    //create log string with timestamp
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    
    sprintf(timestamp, "[%d-%02d-%02d %02d:%02d:%02d]", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    
    FILE *file = fopen("log.txt","a");
    fprintf(file, "%s %s\n",timestamp,str);
    fclose(file);

    //fechar a sincronização
    printf("%s %s\n",timestamp,str);
}

void monitor_engine(){

}

void authorization_manager(){

}

void message_queue(){

}

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


int main(int argc, char const *argv[])
{
    if(argc != 2){
        write_log("Invalid number of arguments");
        exit(1);
    }

    //reads config file
    read_config(argv[1]);

    //creates shared memory (needs struct and pointer arithmetics)
    
    //creates authorization manager
    //creates monitor enginee
    //creates message queue

    // waits to capture end signal
    // sends end signal to other processes (to end them)


    // cleans message queue
    // cleans semaphores
    // cleans shared memory
    // sends final log message

    return 0;
}
