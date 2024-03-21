#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
 int n = 10;
 for(int i = 0; i < n; i++){
   int id = fork();
   if(id == 0){
     printf("%d: %d\n",getpid(),i);
     exit(0);
   }else{
    wait(NULL);
   }
 }
}
