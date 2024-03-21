#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h> // include POSIX semaphores

#include <fcntl.h>
#include <errno.h>


#define MAX_LENGTH 2048

int shmid;
int *shared_var;
sem_t *mutex;

void line_decrypter(char* line, int i, char *patternfile, char *textfile){
   char word1[MAX_LENGTH];
   char word2[MAX_LENGTH];
   char pattern[2*MAX_LENGTH+7+sizeof(int)];
   
   FILE *file = fopen(patternfile,"r");
   if(file == NULL){
	fprintf(stderr,"Error opening file inside decrypter\n");
   }else{

   char lineonly_pattern[10];
   sprintf(lineonly_pattern,"%dp",i);
   printf("linha %d: \n",i);

   while(fscanf(file,"%s %s",word1,word2) != EOF){
      sem_wait(mutex);
      int id = fork();
      if(id == 0){
	//sed deve estar a escrever as linhas que nao altera, tentar com semaforo
         sprintf(pattern,"%ds/%s/%s/g",i,word1,word2);
	 printf(" processo %d linha %d, matching %s with %s\n",(int)getpid(),i,word1,word2);
	 execlp("sed","sed","-i",pattern,textfile,NULL);
      }
      else{
         waitpid(id,NULL,0);
  	 sem_post(mutex); 
      }
   }
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
  
  //semaphore
  shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0700);
  if(shmid < 0){perror("Shmid error");exit(1);}

  shared_var = (int *) shmat(shmid, NULL, 0);
  if(*shared_var == -1){perror("Shmad error");exit(1);}

  sem_unlink("MUTEX");
  mutex = sem_open("MUTEX", O_CREAT | O_EXCL, 0700, 1);
  if(mutex == SEM_FAILED){perror("Sem_open error");exit(1);}
 
  //creating workers for each line of file
  char line[MAX_LENGTH];
  int i = 0;
  while(fgets(line,sizeof(line),file) != NULL){
  i++;
  if (line[0] != '\n') {
	// printf("%s",line);
	pid_t pid = fork();
	if(pid == 0){
          line_decrypter(line,i,argv[1],argv[2]);
          exit(0);
	}
	
    }
  }
  for(int j = 0; j<i; j++){
     wait(NULL);
  }
  printf("%d lines translated\n",i);
}

