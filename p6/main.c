#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

struct string
{
  char *ptr;
  size_t len;
};

void init_string(struct string *s)
{
  s->len = 0;
  s->ptr = malloc(s->len + 1);
  if (s->ptr == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s)
{
  size_t new_len = s->len + size * nmemb;
  s->ptr = realloc(s->ptr, new_len + 1);
  if (s->ptr == NULL) {
    fprintf(stderr, "realloc() failed\n");
    exit(EXIT_FAILURE);
  }
  memcpy(s->ptr + s->len, ptr, size * nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;

  return size * nmemb;
}

void printFlag()
{
  unsigned char flag[] = {13, 25, 18, 26, 14, 38, 13, 107, 2, 20, 2, 21, 50, 13, 56, 2, 36, 109, 40, 2, 40, 121, 110, 57, 2, 51, 100, 108, 19, 5, 32, 93};
  for (int i = 0; i < sizeof(flag); i++)
    putchar(flag[i] ^ 0x5d);
  putchar('\n');
}

int main(void)
{
  CURL *curl;
  CURLcode res;
  const char target[] = "Hello world from PDOGE!";
  curl = curl_easy_init();
  if (curl) {
    struct string s;
    init_string(&s);

    curl_easy_setopt(curl, CURLOPT_URL, "localhost");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
    res = curl_easy_perform(curl);

    if(res != CURLE_OK) {
      printf("I can't see anything!\n");
      goto CLEANUP;
    }
    /* always cleanup */

    if (strncmp(s.ptr, target, sizeof(target) - 1) == 0)
      printFlag();
    else
      printf("You gave me \n%s\ninstead of \n%s\n", s.ptr, target);

CLEANUP:
    curl_easy_cleanup(curl);
    free(s.ptr);
  }
  else
  {
    printf("Error: curl_easy_init() failed, contact manager.\n");
  }
  return 0;
}