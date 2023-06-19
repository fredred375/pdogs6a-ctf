#include <stdio.h>
#include <stdlib.h>

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
  char out[1024 * 50];
  char err[1024 * 50];
  int i = 0;
  int j = 0;
  rand_string(out, sizeof(out));
  rand_string(err, sizeof(err));
  while (i < sizeof(out) || j < sizeof(err))
  {
    if (i == sizeof(out))
    {
      fprintf(stderr, "%c", err[j++]);
    }
    else if (j == sizeof(err))
    {
      fprintf(stdout, "%c", out[i++]);
    }
    else
    {
      if (rand() % 2)
      {
        fprintf(stdout, "%c", out[i++]);
      }
      else
      {
        fprintf(stderr, "%c", err[j++]);
      }
    }
  }
  return 0;
}