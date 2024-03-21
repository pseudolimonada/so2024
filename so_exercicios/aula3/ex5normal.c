#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define MAX_LENGTH 2048
#define MAX_LINES 1000

void stringReplace(char* string, const char* original, const char* replacement) {
    char* pos;
    size_t originalSize = strlen(original);
    size_t replacementSize = strlen(replacement);
    while ((pos = strstr(string, original)) != NULL) {
        memmove(pos + replacementSize, pos + originalSize, strlen(pos + originalSize) + 1);
        strncpy(pos, replacement, replacementSize);
    }
}

void line_decrypter(char* linegiven, int i, char *patternfile){
   char word1[MAX_LENGTH];
   char word2[MAX_LENGTH];
   
   FILE *file = fopen(patternfile,"r");
   if(file == NULL){
	fprintf(stderr,"Error opening file inside decrypter\n");
   }
   else{
     while(fscanf(file,"%s %s",word1,word2) != EOF){
	stringReplace(linegiven, word2, word1);
     }  
     fclose(file); 
     printf("line %d: %s\n",i,linegiven);
 }
}

int main(int argc,char *argv[]){
    if(argc != 3){
         fprintf(stderr, "Usage: %s file1 file2\nfile1: decrypt pairs in format\"decrypted_str encrypted_str\"\nfile2: file to decrypt\n",argv[0]);
         return 1; 
    }

    //opening file to decrypt
    FILE *file = fopen(argv[2],"r");
    if(file == NULL){
 	 fprintf(stderr, "Error opening file\n");
 	 return 2;
    }
 
    // Reading lines of file
    char line[MAX_LINES][MAX_LENGTH];
    int i = 0;

    while(i < MAX_LINES && fgets(line[i], sizeof(line[i]), file) != NULL){
	i++;
    }
   
    fclose(file);
    
    // Creating workers for each line of file 
    for(int j = 0; j < i; j++){
        pid_t pid = fork();
        if (pid == 0) {
           line_decrypter(line[j], j, argv[1]);
           exit(1);
        }
    }

    // Wait for all child processes to complete
    for (int j = 0; j < i; j++) {
        wait(NULL);
    }

    printf("%d lines translated\n", i);
    return 0;
}
