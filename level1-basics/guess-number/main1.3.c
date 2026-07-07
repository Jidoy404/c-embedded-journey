#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int readInt(const char *prompt, int min, int max);

int main()
{

  srand(time(NULL));

  printf("Привіт, це гра вгадай число від 1 до 100, в тебе буде 10 шансів вгадати число \n");

  int secret = rand() % 100 + 1;
  char text[100];

  for (int i = 1; i < 11; i++)
  {
    snprintf(text,
             sizeof(text),
             "Спроба № %d",
             i);

    int guess = readInt(text, 1, 100);

    if (guess == secret)
    {
      printf("Вітаю! Ви вгадали число за %d спроб(и)!\n", i);
      return 0;
    }
    else if (guess < secret)
    {
      printf("Загадане число є більшим");
    }
    else
    {
      printf("Загадане число є меншим");
    }
  }

  printf("Вірне число %d", secret);

  return 0;
}

int readInt(const char *prompt, int min, int max)
{
  int value;
  int i = 0;
  printf("%s", prompt);
  while (scanf("%d", &value) != 1 || value < min || value > max)
  {
    printf("Введіть число від %d до %d\n", min, max);
    while (getchar() != '\n')
      ;
    printf("%s", prompt);
    i++;
    if (i == 3)
    {
      printf("занадто багато спроб спробуйте пізніше\n");
      exit(1);
    }
  }
  return value;
}