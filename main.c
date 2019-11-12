#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>

unsigned int randgen() {
  unsigned int randNumber;
  int rand = open("/dev/urandom", O_RDONLY);
  // opening file error
  if (errno) {
    printf("error #: %d error: %s\n", errno, strerror(errno));
    return 0;
  }
  read(rand, &randNumber, sizeof(int));
  // reading error
  if (errno) {
    printf("error #: %d error: %s\n", errno, strerror(errno));
    return 0;
  }
  close(rand);
  return randNumber;
}

int main() {
  // populating the array of ints
  unsigned int randarrayinit[10];
  unsigned int randarraycopy[10];
  int write_to = open("randfile.in", O_WRONLY | O_CREAT, 0666);
  if (errno) {
    printf("error #: %d error: %s\n", errno, strerror(errno));
    return 0;
  }
  printf("Generating Random Numbers: \n" );
  for (int i = 0; i < 10; i++) {
    randarrayinit[i] = randgen();
    printf("random %d: %u\n", i, randarrayinit[i]);
  }

  printf("\nWriting numbers to file...\n");
  write(write_to, &randarrayinit, sizeof(int) * 10);
  if (errno) {
    printf("error #: %d error: %s\n", errno, strerror(errno));
    return 0;
  }
  close(write_to);

  int read_from = open("randfile.in", O_RDONLY);
  if (errno) {
    printf("error #: %d error: %s\n", errno, strerror(errno));
    return 0;
  }

  printf("\nReading numbers from file...\n\n");
  read(read_from, &randarraycopy, sizeof(int) * 10);
  if (errno) {
    printf("error #: %d error: %s\n", errno, strerror(errno));
    return 0;
  }
  close(read_from);

  printf("Verification that written values were the same:\n");
  for (int i = 0; i < 10; i++) {
    printf("\trandom %d: %u\n", i, randarraycopy[i]);
  }
  return 0;
}
