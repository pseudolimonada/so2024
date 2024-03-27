#include "logs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void write_log(char *str){
  
    //syncronize the log file with all programs that are using it
    


    FILE *file = fopen("log.txt","a");
    //create log string with timestamp
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    fprintf(file, "[%d-%02d-%02d %02d:%02d:%02d]", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    fprintf(file, "%s\n",str);
    fclose(file);

    //fechar a sincronização
    printf("%s\n",str);
}