#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/sysmacros.h>

unsigned char flag2[] = {58, 46, 37, 45, 57, 17, 58, 91, 90, 71, 88, 53, 78, 30, 56, 94, 9, 15, 53, 3, 78, 53, 43, 53, 83, 5, 5, 14, 53, 30, 5, 5, 38, 53, 30, 37, 53, 46, 89, 40, 31, 83, 53, 29, 91, 62, 2, 53, 57, 51, 78, 62, 15, 39, 53, 41, 11, 38, 38, 78, 23};

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
  for (int i = 0; i < sizeof(flag2); i++)
  {
    flag2[i] ^= 0x6a;
  }
  fwrite(flag2, 1, sizeof(flag2), devnull);
  fclose(devnull);
  printf("I threw the second flag to /dev/null, you will never find it hahaha!\n");
  exit(0);
TRICK:
  printf("You can't trick me!\n");
  exit(0);
}