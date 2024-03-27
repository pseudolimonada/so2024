#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "logs.h"

#define MBUF 1024


void display_help(int options){
    printf("Usage: ");
    switch(options){
        case 0:
            printf(" $ mobile_user / {plafond inicial} / {número de pedidos de autorização} / {intervalo VIDEO} {intervalo MUSIC} {intervalo SOCIAL} / {dados a reservar}\n");
            break;
        case 1:
            printf(" $ backoffice_user\n");
            break;
        case 2:
            printf(" $ 5g_auth_platform {config-file}");
            break;  
    }
}

int create_manager(char *config_file){
    char message[MBUF];
    sprintf(message,"System manager created with config file %s",config_file);
    write_log(message);
    return 0;
}


int create_backoffice(){
    write_log("Backoffice user created.");
    return 0;

}

int create_mobile(int start_plafond, int num_auth, int interval_video, int interval_music, int interval_social, int data){
    char message[MBUF];
    sprintf(message,"Mobile user created with plafond %d, %d auth requests, %d video, %d music, %d social and %d data",start_plafond,num_auth,interval_video,interval_music,interval_social,data);
    write_log(message);
    return 0;
}


int main()
{
    char input[MBUF];
    char *token;
    int count;
    int args[6];
    int started = 0;

    while(1){
        scanf("%s",input);
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
        token = strtok(input, " ");
        count = 0;

        //parse the input
        if(strcmp(token,"backoffice_user") == 0){
            count = 0;
            token = strtok(NULL, " ");
            while(token != NULL) {
                token = strtok(NULL, " ");
                count++;
            }

            if(count != 0){
                write_log("Invalid number of args.");
                display_help(1);
            }
            else{
                create_backoffice();
            }
        }

        else if(strcmp(token,"mobile_user") == 0){
            count = 0;
            token = strtok(NULL, " ");
            while(token != NULL) {
                token = strtok(NULL, " ");
                args[count] = atoi(token); //ter cuidado que o atoi devolve 0 em caso de erro
                if(args[count] <= 0){
                    write_log("Argument is invalid. Must be a positive integer");
                }
                count++;
            }

            if(count != 6){
                write_log("Invalid number of args.");
                display_help(0);
            }
            else{
                create_mobile(args[0],args[1],args[2],args[3],args[4],args[5]);
            }
        }
        
        else if(strcmp(token,"5g_auth_platform") == 0){
            count = 0;
            token = strtok(NULL, " ");
            while(token != NULL) {
                token = strtok(NULL, " ");
                strcpy(input,token);
                count++;
            }
            if(count != 1){
                write_log("Invalid number of args.");
                display_help(2);
            }
            else if (started){
                write_log("System manager is already running.");
            }
            else {
                create_manager(input);
            }


        }else{
            write_log("Command doesn't exist.");
        }

    }
    return 0;
}
