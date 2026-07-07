#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int readInt(const char *prompt, int min, int max);
int *createArray(int size);
void fillArray(int *arr, int size);
void printArray(int *arr, int size);
float sumArray(int *arr, int size);
float averageArray(int *arr, int size);
void freeArray(int *arr);

int main()
{
  srand(time(NULL));

  int n = readInt("Введіть розмір масиву: ", 1, 100);
  int *arr = createArray(n);
  if (arr == NULL) return 1;
  fillArray(arr, n);
  printArray(arr, n);
  printf("Сума: %.2f\n", sumArray(arr, n));
  printf("Середнє: %.2f\n", averageArray(arr, n));
  freeArray(arr);
}

int readInt(const char *prompt, int min, int max)
{
  int value;
  int status;
  int i = 0;
  printf("%s", prompt);
  status = scanf("%d", &value);
  while (status != 1 || !(value >= min && value <= max))
  {
    printf("You are not in the right number\n");
    while (getchar() != '\n')
      ;
    printf("%s", prompt);
    i++;
    if (i == 3)
    {
      printf("занадто багато спроб спробуйте пізніше\n");
      exit(1);
    }
    status = scanf("%d", &value);
  }
  return value;
}

int *createArray(int size)
{

  int *arr = malloc(size * sizeof(int));

  if (arr == NULL)
  {
    printf("Не хватило памяти!\n");
    return NULL;
  }
  return arr;
}

void fillArray(int *arr, int size)
{
  for (int i = 0; i < size; i++)
  {
    arr[i] = rand() % 100;
  }
}

void printArray(int *arr, int size)
{

  for (int i = 0; i < size; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

float sumArray(int *arr, int size)
{
  float sum = 0;

  for (int i = 0; i < size; i++)
  {
    sum += arr[i];
  }

  return sum;
}

float averageArray(int *arr, int size)
{

  float average = (sumArray(arr, size)) / size;
  return average;
}

void freeArray(int *arr)
{

  free(arr);
  printf("Памʼять масиву звільнено");
}
