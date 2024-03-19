#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define MBUF 1024

void write_log(char *str){
    //é preciso sincronizar com probably semaforo
    //fara sentido ter isto num log.c para importar em todas as funcoes que vão logar
    FILE *file = fopen("log.txt","a");
    fwrite(str, sizeof(char), strlen(str), file);
    fclose(file);
    //fechar a sincronização
    printf("%s\n",str);
}

void display_help(int options){
    // FILE *file = fopen("menu.txt",'r');
    // char message[MBUF];
    // while(fgets(message,MBUF,file) != -1){
    //     printf("%s",message);
    // }
    // fclose(file);
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

int create_manager();

int create_mobile();

int create_backoffice();

int main(int argc, char const *argv[])
{
    char input[MBUF];
    char *token;
    int count;
    int parser_cond;
    int args[6];
    int started = 0;

    while(1){
        scanf("%s",input);
        token = strtok(input, " ");
        count = 0;

        if(strcmp(token,"backoffice_user") == 0){
            count = 0;
            while(token != NULL) {
                token = strtok(NULL, " ");
                strcpy(args[count],token);
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
            while(token != NULL) {
                token = strtok(NULL, " ");
                strcpy(args[count],token);
                count++;
            }
            
            if(count != 1){
                write_log("Invalid number of args.");
                display_help();
            }
            else if (started){
                write_log("System manager is already running.");
            }
            else {
                create_manager(args[0]);
            }


        }else{
            write_log("Command doesn't exist.");
        }

        




    }
    return 0;
}
