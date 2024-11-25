#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void childInstruction() {
  // int randomFile = open("/dev/urandom", O_RDONLY, 0);
  // int r;
  // read(randomFile, &r, 1);
  // r = r%5;
  // printf("%d %d\n", getpid(), r);
  // close(randomFile);
}

int main() {
  pid_t p, p2;
  p = fork();
  if (p < 0) {
    perror("fork failed");
    exit(1);
  } else if (p == 0) {
    childInstruction();
  } else {
    p2 = fork();
  }
  if (p2 < 0) {
    perror("fork failed");
    exit(1);
  } else if (p == 0) {
    childInstruction();
  }
}
