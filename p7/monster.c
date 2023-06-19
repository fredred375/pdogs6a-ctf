#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void int_handler(int sig)
{
  printf("ctrl+c can't kill me, hahaha!\n");
}

void tstp_handler(int sig)
{
  printf("It's ctrl+z!? However it can only \"stop\" me but cannot \"terminate\" me. I will come back soon!\n");
  raise(SIGSTOP);
}

void term_handler(int sig)
{
  unsigned char flag[] = {226, 246, 253, 245, 225, 201, 226, 133, 159, 128, 237, 135, 222, 242, 235, 237, 198, 250, 247, 237, 193, 254, 215, 129, 194, 251, 252, 132, 237, 223, 130, 220, 150, 230, 215, 192, 207};
  for (int i = 0; i < sizeof(flag); i++)
    putchar(flag[i] ^ 0xb2);
  putchar('\n');
  exit(SIGTERM);
}

void quit_handler(int sig)
{
  printf("Ahhh I didn't expect you to use ctrl+\\.\n");
  unsigned char flag[] = {193, 213, 222, 214, 194, 234, 193, 166, 188, 160, 206, 242, 229, 227, 253, 186, 242, 206, 248, 194, 206, 209, 242, 197, 196, 208, 160, 221, 232, 206, 208, 206, 194, 248, 246, 255, 165, 253, 236,};
  for (int i = 0; i < sizeof(flag); i++)
    putchar(flag[i] ^ 0x91);
  putchar('\n');
  exit(SIGQUIT);
}

int main()
{
  signal(SIGINT, int_handler);
  signal(SIGTSTP, tstp_handler);
  signal(SIGTERM, term_handler);
  signal(SIGQUIT, quit_handler);
  while (1)
  {
    printf("No one can stop me! Hahaha!\n");
    sleep(1);
  }
  return 0;
}