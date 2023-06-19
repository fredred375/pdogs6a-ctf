#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printFlag1()
{
  unsigned char flag[] = {99, 119, 124, 116, 96, 72, 99, 10, 30, 2, 108, 97, 86, 119, 90, 97, 118, 112, 103, 122, 124, 125, 108, 122, 23, 108, 69, 86, 97, 106, 108, 2, 126, 67, 3, 65, 4, 82, 93, 4, 78};
  for (int i = 0; i < sizeof(flag); i++)
    putchar(flag[i] ^ 0x33);
  putchar('\n');
}

void printFlag2()
{
  unsigned char flag[] = {202, 222, 213, 221, 201, 225, 202, 163, 183, 168, 197, 210, 218, 236, 223, 197, 227, 213, 207, 197, 210, 255, 251, 200, 254, 197, 170, 252, 197, 233, 173, 222, 171, 244, 197, 175, 206, 254, 170, 239, 206, 197, 190, 238, 222, 255, 232, 232, 197, 174, 244, 222, 197, 220, 243, 171, 223, 197, 254, 223, 233, 249, 200, 171, 234, 238, 213, 232, 165, 231};
  for (int i = 0; i < sizeof(flag); i++)
    // printf("%d, ", flag[i] ^ 0x9a);
    putchar(flag[i] ^ 0x9a);
  putchar('\n');
}

static char *rand_string(char *str, size_t size)
{
  const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  if (size)
  {
    --size;
    for (size_t n = 0; n < size; n++)
    {
      int key = rand() % (int)(sizeof charset - 1);
      str[n] = charset[key];
    }
    str[size] = '\0';
  }
  return str;
}

int main()
{
  char input[1024 * 50];
  char out[1024 * 50];
  char err[1024 * 50];
  int i = 0;
  int j = 0;
  rand_string(out, sizeof(out));
  rand_string(err, sizeof(err));
  scanf("%51199s", input);
  if (strncmp(input, out, sizeof(out)) == 0)
  {
    printf("I heard what my believer said! here you go:\n");
    printFlag1();
  }
  else if (strncmp(input, err, sizeof(err)) == 0)
  {
    printf("It seems that he mad many faults recently. No wonder he comes to talk to me.\n");
    printFlag2();
  }
  exit(0);
}