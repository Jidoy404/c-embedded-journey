#include <stdio.h>
#include <stdlib.h>

void printArray(int *arr, int size);
void swap(int *a, int *b);
void sortInPlace(int *arr, int size);
int *sortCopy(int *arr, int size);
void reverseInPlace(int *arr, int size);

int main()
{

  int arr[] = {5, 2, 8, 1, 9, 3};
  int size = 6;
  sortInPlace(arr, size);
  printArray(arr, size);

  int original[] = {5, 2, 8, 1, 9, 3};
  int *sorted = sortCopy(original, size);
  printArray(original, size);
  printArray(sorted, size);
  free(sorted); // обязательно!

  reverseInPlace(arr, size);
  printArray(arr, size);

  return 0;
}

///////////////////////////////////////////////////////////////////////////////

void printArray(int *arr, int size)
{
  for (int i = 0; i < size; i++)
    printf("%d ", arr[i]);
  printf("\n");
}

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

void sortInPlace(int *arr, int size)
{
  for (int i = 0; i < size - 1; i++)
  {
    for (int j = 0; j < size - 1 - i; j++)
    {
      if (arr[j] > arr[j + 1])
        swap(&arr[j], &arr[j + 1]);
    }
  }
}

int *sortCopy(int *arr, int size)
{

  int *arr2 = malloc(size * sizeof(int));
  if (arr2 == NULL)
  {
    printf("malloc failed\n");
    return NULL;
  }

  for (int i = 0; i < size; i++)
  {
    arr2[i] = arr[i];
  }

  sortInPlace(arr2, size);

  return arr2;
}

// malloc()  -> взяти пам’ять
// free()    -> повернути пам’ять назад
// arr       -> після free більше не можна використовувати

void reverseInPlace(int *arr, int size)
{
  int *left = arr;
  int *right = arr + size - 1;
  while (left < right)
  {
    swap(left, right);
    left++;
    right--;
  }
}