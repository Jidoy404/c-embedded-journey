#include <stdio.h>

void swap(char *a, char *b);
void reverseString(char *s);
int isPalindrome(char *s);
void my_strcpy(char *dst, char *src);
int my_strcmp(char *a, char *b);
int isPalindrome2(char *s);

int main()
{

  char s1[] = "hello";
  reverseString(s1);
  printf("%s\n", s1); // "olleh"

  char s2[] = "abcde";
  reverseString(s2);
  printf("%s\n", s2); // "edcba"

  // printf("%d\n", isPalindrome("racecar")); // 1
  // printf("%d\n", isPalindrome("madam"));   // 1
  // printf("%d\n", isPalindrome("hello"));   // 0
  // printf("%d\n", isPalindrome("abba"));    // 1
  // printf("%d\n", isPalindrome("a"));       // 1
  // printf("%d\n", isPalindrome(""));        // 1

  printf("%d\n", isPalindrome2("racecar")); // 1
  printf("%d\n", isPalindrome2("madam"));   // 1
  printf("%d\n", isPalindrome2("hello"));   // 0
  printf("%d\n", isPalindrome2("abba"));    // 1
  printf("%d\n", isPalindrome2("a"));       // 1
  printf("%d\n", isPalindrome2(""));        // 1

  return 0;
}

void swap(char *a, char *b)
{
  char temp = *a;
  *a = *b;
  *b = temp;
}

int my_strlen(char *s)
{
  int temp = 0;

  while (s[temp] != '\0')
  {
    temp++;
  }

  return temp;
}

void reverseString(char *s)
{

  int size = my_strlen(s);

  char *left = s;
  char *right = s + size - 1;
  while (left < right)
  {
    swap(left, right);
    left++;
    right--;
  }
}

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

int my_strcmp(char *a, char *b)
{

  while (*a && *a == *b)
  {
    a++;
    b++;
  }
  return *a - *b;
}

// Варіант 1/////////////////////////////////////////////////////////

int isPalindrome(char *s)
{

  int size = my_strlen(s);

  char copy[size]; // краще не використовувати

  // варіант 1 — фіксований буфер
  // char copy[256];

  // // варіант 2 — динамічна пам'ять
  // char *copy = malloc(size + 1);
  // if (copy == NULL) return 0;
  // my_strcpy(copy, s);
  // reverseString(copy);
  // int result = my_strcmp(s, copy);
  // free(copy);
  // return result == 0;

  my_strcpy(copy, s);

  reverseString(copy);

  int result = my_strcmp(s, copy);

  if (result == 0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

////////////////////////////////////////

//   printf("%d\n", isPalindrome2("racecar")); // 1  0  1
//   printf("%d\n", isPalindrome2("madam"));   // 1  0  1
//   printf("%d\n", isPalindrome2("hello"));   // 0  0  0
//   printf("%d\n", isPalindrome2("abba"));    // 1  0  1
//   printf("%d\n", isPalindrome2("a"));       // 1  1  1
//   printf("%d\n", isPalindrome2(""));        // 1  1  1

int isPalindrome2(char *s)
{

  int size = my_strlen(s);

  char *left = s;
  char *right = s + size - 1;
  while (left < right)
  {
    if (*left != *right)
    {
      return 0;
    }
    left++;
    right--;
  }
  return 1;
}