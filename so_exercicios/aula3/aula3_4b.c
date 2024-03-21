#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
 int n = 5;
 int id = 0;
 int dad = getpid();
 for(int i = 0; i<n; i++){
  if(id==0){
   id = fork();
   if(id != 0)wait(NULL);
  }
}
 if((int) getpid() != dad){
   printf("I am %d, dad is %d\n",(int)getpid(),(int)getppid());
   exit(0);
 }
 printf("I AM DAD %d\n",dad);
 

 exit(0);
}
