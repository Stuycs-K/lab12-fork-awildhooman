#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int childInstruction() {
   int randomFile = open("/dev/urandom", O_RDONLY, 0);
   int r = 0;
   read(randomFile, &r, 1);
   r = r % 5 + 1;
   printf("%d %dsec\n", getpid(), r);
   close(randomFile);
   sleep(r);
   printf("%d finished after %dsec\n", getpid(), r);
   return r;
}

int main() {
  pid_t p, p2;
  int status;
  printf("%d about to create 2 child processes\n", getpid());

  p = fork();
  if (p < 0) {
    perror("fork failed");
    exit(1);
  } else if (p == 0) {
    return childInstruction();
  }

  p2 = fork();
  if (p2 < 0) {
    perror("fork failed");
    exit(1);
  } else if (p2 == 0) {
    return childInstruction();
  }

  pid_t child = wait(&status);
  if (child > 0) {
    if (WIFEXITED(status)) {
        printf("Main Process %d is done. Child %d slept for %d seconds\n", getpid(), child, WEXITSTATUS(status));
    }
  }
}
