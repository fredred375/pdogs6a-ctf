#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/sysmacros.h>

unsigned char flag2[] = {80, 68, 79, 71, 83, 123, 80, 49, 48, 45, 50, 95, 36, 116, 82, 52, 99, 101, 95, 105, 36, 95, 65, 95, 57, 111, 111, 100, 95, 116, 111, 111, 76, 95, 116, 79, 95, 68, 51, 66, 117, 57, 95, 119, 49, 84, 104, 95, 83, 89, 36, 84, 101, 77, 95, 67, 97, 76, 76, 36, 125};

void printFlag1()
{
  unsigned char flag[] = {58, 46, 37, 45, 57, 17, 58, 91, 90, 71, 91, 53, 82, 47, 53, 9, 94, 56, 89, 12, 63, 38, 53, 29, 35, 93, 34, 53, 78, 26, 89, 41, 91, 43, 38, 53, 9, 34, 42, 24, 43, 9, 62, 89, 24, 57, 23};
  for (int i = 0; i < sizeof(flag); i++)
    putchar(flag[i] ^ 0x6a);
  putchar('\r');
}

int main()
{
  FILE *devnull = fopen("/dev/null", "wr");
  if (devnull == NULL)
    goto TRICK;
  struct stat *st;
  st = malloc(sizeof(struct stat));
  if (fstat(fileno(devnull), st) == -1)
    goto TRICK;
  if (major(st->st_rdev) != 1 || minor(st->st_rdev) != 3)
    goto TRICK;
  printf("I already gave you a flag hahaha.\n");
  printFlag1();
  fwrite(flag2, 1, sizeof(flag2), devnull);
  fclose(devnull);
  printf("I threw the second flag to /dev/null, you will never find it hahaha!\n");
  exit(0);
TRICK:
  printf("You can't trick me!\n");
  exit(0);
}