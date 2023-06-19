#include <sys/stat.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

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
  for (int i = 0; i < 10; i++)
  {
    mkdir(std::to_string(i).c_str(), 0775);
    chdir(std::to_string(i).c_str());
    for (int j = 0; j < 10; j++)
    {
      mkdir(std::to_string(j).c_str(), 0775);
      chdir(std::to_string(j).c_str());
      for (int k = 0; k < 10; k++)
      {
        mkdir(std::to_string(k).c_str(), 0775);
        chdir(std::to_string(k).c_str());
        int file_count = rand() % 10 + 1;
        for (int l = 0; l < file_count; l++)
        {
          std::string buf;
          get_rand_name(buf, 5);
          FILE *fp = fopen(buf.c_str(), "w");
          if (i == 5 && j == 2 && k == 9 && l == 1)
          {
            int size_in_bytes = 114857600;
            for (int m = 0; m < size_in_bytes; m++)
            {
              fputc(fgetc(urandom), fp);
            }
          }
          else if (i == 8 && j == 3 && k == 6 && l == 0)
          {
            int size_in_bytes = 142723450;
            for (int m = 0; m < size_in_bytes; m++)
            {
              fputc(fgetc(urandom), fp);
            }
          }
          else
          {
            int size_in_bytes = (rand() % (5 * 1024));
            for (int m = 0; m < size_in_bytes; m++)
            {
              fputc(fgetc(urandom), fp);
            }
          }
          fclose(fp);
        }

        chdir("..");
      }
      chdir("..");
    }
    chdir("..");
  }
  return 0;
}