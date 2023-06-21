#include <sys/stat.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <mntent.h>
#include <cstring>

int flag1 = 0;
int flag2 = 0;
int mnt = 0;

void printFlag1()
{
  unsigned char flag[] = {144, 132, 143, 135, 147, 187, 144, 248, 237, 241, 159, 134, 169, 174, 132, 159, 240, 178, 159, 132, 149, 159, 161, 178, 165, 159, 149, 245, 165, 134, 149, 140, 159, 181, 148, 137, 241, 137, 247, 241, 243, 228, 189};
  for (int i = 0; i < sizeof(flag); i++)
    putchar(flag[i] ^ 0xc0);
  putchar('\n');
}

void printFlag2()
{
  unsigned char flag[] = {246, 226, 233, 225, 245, 221, 246, 158, 139, 148, 249, 226, 151, 194, 249, 255, 201, 211, 249, 145, 206, 207, 232, 205, 249, 242, 238, 227, 249, 224, 239, 151, 195, 130, 255, 147, 242, 227, 235, 249, 151, 147, 249, 245, 242, 212, 146, 232, 193, 149, 153, 219};
  for (int i = 0; i < sizeof(flag); i++)
    putchar(flag[i] ^ 0xa6);
  putchar('\n');
}

void get_rand_name(std::string &buf, int len)
{
  buf.resize(len);
  for (int i = 0; i < len; i++)
  {
    buf[i] = 'a' + rand() % 26;
  }
  return;
}

int main()
{
  FILE *urandom = fopen("/dev/urandom", "r");
  FILE *mounts;
  struct mntent *ent;
  mounts = setmntent("/proc/mounts", "r");
  while (NULL != (ent = getmntent(mounts)))
  {
    if (strcmp(ent->mnt_dir, "/home/pdoge/p8/8/3/6") == 0)
    {
      mnt = 1;
      break;
    }
  }
  endmntent(mounts);
  for (int i = 0; i < 10; i++)
  {
    if (chdir(std::to_string(i).c_str()) == -1)
    {
    FOLDER_EXIT:
      printf("My folders are missing!!!\n");
      exit(0);
    }
    for (int j = 0; j < 10; j++)
    {
      if (chdir(std::to_string(j).c_str()) == -1)
      {
        goto FOLDER_EXIT;
      }
      for (int k = 0; k < 10; k++)
      {
        if (chdir(std::to_string(k).c_str()) == -1)
        {
          goto FOLDER_EXIT;
        }
        int file_count = rand() % 10 + 1;
        for (int l = 0; l < file_count; l++)
        {
          std::string buf;
          get_rand_name(buf, 5);
          if (i == 5 && j == 2 && k == 9 && l == 1)
          {
            if (access(buf.c_str(), F_OK) != 0)
              flag1 = 1;
          }
          else if (i == 8 && j == 3 && k == 6 && l == 0)
          {
            if (mnt == 0 && access(buf.c_str(), F_OK) != 0)
              flag2 = 1;
          }
          else
          {
            rand();
            if (access(buf.c_str(), F_OK) != 0)
            {
              // std::cout << buf << ":" << i << "/" << j << "/" << k << "/" << std::endl;
              printf("You touched my precious files!!!\n");
              exit(0);
            }
          }
        }

        chdir("..");
      }
      chdir("..");
    }
    chdir("..");
  }
  if (flag1)
  {
    printf("You delete the first redundant file.\n");
    printFlag1();
  }
  if (flag2)
  {
    printf("I have never thought you can even delete the second redundant file!! Here is the flag:\n");
    printFlag2();
  }
  if (!flag1 && !flag2)
    printf("Please help me delete the redundant files!!!\n");
  exit(0);
}