#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>

unsigned int randgen() {
  unsigned int randNumber;
  int rand = open("/dev/random", 0_RDONLY);
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
