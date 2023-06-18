#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void printFlag()
{
  unsigned char flag[] = {156, 136, 131, 139, 159, 183, 156, 248, 225, 253, 147, 160, 133, 162, 185, 180, 147, 156, 169, 190, 129, 133, 159, 249, 253, 252, 130, 191, 147, 140, 190, 169, 147, 164, 141, 158, 168, 177};
  for (int i = 0; i < 38; i++)
    // printf("%d,", flag[i] ^ 0xcc);
    putchar(flag[i] ^ 0xcc);
}

void printFlag2()
{
  unsigned char flag[] = {225, 245, 254, 246, 226, 202, 225, 133, 156, 131, 238, 225, 222, 248, 223, 229, 244, 227, 226, 238, 241, 227, 130, 238, 255, 254, 197, 238, 129, 223, 221, 232, 238, 215, 254, 195, 238, 242, 204};
  for (int i = 0; i < sizeof(flag); i++)
    putchar(flag[i] ^ 0xb1);
}

int main(int argc, char *argv[])
{
  const char *filename = "pdogs6a";
  char *linkname;
  struct stat *st;
  struct stat *lst;
  st = malloc(sizeof(struct stat));
  if (stat(filename, st) == -1)
  {
    printf("Cannot find pdogs6a\n");
    exit(EXIT_FAILURE);
  }
  if (!S_ISDIR(st->st_mode))
  {
    printf("pdogs6a is not a directory!\n");
    exit(EXIT_SUCCESS);
  }

  if ((st->st_mode & S_IRWXU) == S_IRWXU && (st->st_mode & S_IRWXG) == 0 && (st->st_mode & S_IRWXO) == 0)
  {
    printFlag();
    printf("\nHowever, can you make pdogs6a actually go to /home/pdoge/p5 ?\n");
    linkname = realpath(filename, NULL);
    if (linkname)
    {
      if (strcmp(linkname, "/home/pdoge/p5") == 0)
        printFlag2();
      free(linkname);
    }
    exit(EXIT_SUCCESS);
  }
  else
  {
    printf("Wrong permissions!\n");
    exit(EXIT_SUCCESS);
  }

  exit(EXIT_SUCCESS);
}