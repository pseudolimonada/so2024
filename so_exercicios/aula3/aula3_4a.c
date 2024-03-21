#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){
   int  n = 5;
   int id = 0;
   int dad = getpid();
   for(int i = 0; i<n; i++){
    if(id == 0){
       id = fork();
    }
    // not at else, otherwise the 2 last processes have no sleep
    if(id != 0){
      sleep(1); 
    }
   }
   if ((int) getpid() == dad) printf("I am the original %d\n",dad);
   else{
      printf("I am %d and my dad is %d\n",(int)getpid(),(int)getppid());
   }exit(0);
}
