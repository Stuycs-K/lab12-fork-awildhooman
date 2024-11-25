#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  pid_t p = fork();
  pid_t p2;
  if (p < 0) {
    perror("fork failed");
    exit(1);
  } else if (p == 0) {
    printf("Child 1\n");
  } else {
    p2 = fork();
  }
  if (p2 < 0) {
    perror("fork failed");
  } else if (p == 0) {
    printf("Child 2\n");
  }
}
