#include <stdio.h>
#include <stdlib.h>
#include <grp.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

void printFlag()
{
  unsigned char flag[] = {156, 136, 131, 139, 159, 183, 156, 254, 147, 149, 252, 185, 147, 173, 158, 137, 147, 140, 147, 249, 185, 156, 255, 190, 147, 153, 159, 169, 158, 237, 237, 237, 177};
  for (int i = 0; i < 33; i++)
    putchar(flag[i] ^ 0xcc);
}

int main(int argc, char *argv[])
{
  uid_t uid = getuid(); // get current user id
  struct passwd *pw = getpwuid(uid);
  struct passwd *pw_pdoge = getpwnam("pdoge");
  int ngroups = 0;
  gid_t *groups;

  if (pw == NULL)
  {
    printf("Error: getpwuid() failed, contact manager\n");
    exit(EXIT_FAILURE);
  }

  // check if the user is root
  if (uid == 0)
  {
    printf("You can't trick me with root!\n");
    exit(EXIT_SUCCESS);
  }

  // check if user pdoge is tampered
  if (pw_pdoge == NULL || pw_pdoge->pw_uid != 1000 || pw_pdoge->pw_gid != 1000)
  {
    printf("Don't mess with pdoge!\n");
    exit(EXIT_SUCCESS);
  }

  // check if the user is pdoge
  if (uid == 1000)
  {
    printf("Come to me with a different user\n");
    exit(EXIT_SUCCESS);
  }

  // this call is just to get the correct ngroups
  getgrouplist(pw->pw_name, pw->pw_gid, NULL, &ngroups);
  groups = malloc(ngroups * sizeof(gid_t));

  // here we actually get the groups
  getgrouplist(pw->pw_name, pw->pw_gid, groups, &ngroups);

  // check for the sudo group
  for (int i = 0; i < ngroups; i++)
  {
    struct group *gr = getgrgid(groups[i]);
    if (gr == NULL)
      continue;
    if (strcmp(gr->gr_name, "sudo") == 0)
    {
      printFlag();
      goto END;
    }
  }
  printf("You are not a sudoer!\n");
END:
  free(groups);

  exit(EXIT_SUCCESS);
}