#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>

int main(void) {
  pid_t mypid;
  pid_t childpid;

  mypid = getpid();
  childpid = fork();

  if (childpid == 0) {
    printf("child mypid :%ld\n", (long)mypid);
    printf("child getpid() :%ld\n", (long)getpid());
    printf("child getppid() :%ld\n", (long)getppid());
  } else {
    sleep(5);
    printf("mypid :%ld\n", (long)mypid);
    printf("getpid() :%ld\n", (long)getpid());
    printf("getppid() :%ld\n", (long)getppid());
    wait(NULL);
  }
  return 0;
}

