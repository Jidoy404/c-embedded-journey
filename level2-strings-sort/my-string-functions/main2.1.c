#include <stdio.h>

int my_strlen(char *s);
void my_strcpy(char *dst, char *src);
void my_strcat(char *dst, char *src);
int my_strcmp(char *a, char *b);

int main()
{

  char s1[] = "hello";
  printf("strlen: %d\n", my_strlen(s1));
  char s2[] = "helloaaaaa";
  printf("strlen: %d\n", my_strlen(s2));

  char dst[20];
  my_strcpy(dst, "wag");
  printf("strcpy: %s\n", dst);
  my_strcpy(dst, "world");
  printf("после strcpy в main: %s\n", dst); // выведет мусор, не "world"
  printf("strcpy: %s\n", dst);

  char base[20] = "hello ";
  my_strcat(base, "world");
  my_strcat(base, "wmasmd");

  printf("strcmp: %d\n", my_strcmp("abc", "abc")); // 0
  printf("strcmp: %d\n", my_strcmp("abc", "abd")); // отрицательное
  printf("strcmp: %d\n", my_strcmp("abd", "abc")); // положительное
  printf("strcmp: %d\n", my_strcmp("adc", "abc")); // 0
  printf("strcmp: %d\n", my_strcmp("abc", "acd")); // отрицательное
  printf("strcmp: %d\n", my_strcmp("azd", "abc")); // положительное

  return 0;
}

int my_strlen(char *s)
{
  int i = 0;

  while (s[i] != '\0')
  {
    i++;
  }

  return i;
}

// void my_strcpy(char *dst, char *src)
// {

//   dst = src;

//   printf("strcpy: %s\n", dst);
// }

void my_strcpy(char *dst, char *src)
{
  while (*src != '\0')
  {
    *dst = *src;
    dst++;
    src++;
  }
  *dst = '\0';
}

void my_strcat(char *dst, char *src)
{

  int i = 0;
  int b = 0;

  while (dst[i] != '\0')
  {
    i++;
  }

  while (src[b] != '\0')
  {

    dst[i] = src[b];

    i++;
    b++;
  }
  dst[i] = '\0';

  printf("strcat: %s\n", dst);
}

void my_strcat(char *dst, char *src) // на будущее 
{
    while (*dst) dst++;       // найти конец dst
    while (*src) *dst++ = *src++;  // скопировать src
    *dst = '\0';
}

int my_strcmp(char *a, char *b)
{

  while (*a && *a == *b)
  {
    a++;
    b++;
  }
  return *a - *b;
}