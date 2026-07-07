#include <stdio.h>
#include <stdlib.h>

typedef struct // ми зробили ссвій тип данних по типу int, float і назвали його DynamicArray
{
  int *data;    // вказівник на дані
  int count;    // скільки елементів зараз
  int capacity; // скільки місця виділено
} DynamicArray;

DynamicArray *createDynArray(int initialCapacity);
void addElement(DynamicArray *da, int value);
void printDynArray(DynamicArray *da);
void freeDynArray(DynamicArray *da);

// da.count      // якщо звичайна змінна
// da->count     // якщо вказівник

int main()
{

  DynamicArray *da = createDynArray(2);

  for (int i = 1; i <= 10; i++)
  {
    addElement(da, i * 10);
    printf("count=%d capacity=%d | ", da->count, da->capacity);
    printDynArray(da);
  }

  freeDynArray(da);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

DynamicArray *createDynArray(int initialCapacity)
{
  DynamicArray *da = malloc(sizeof(DynamicArray));
  if (da == NULL)
  {
    printf("malloc failed\n");
    exit(1);
  }
  da->data = malloc(initialCapacity * sizeof(int));
  da->count = 0;
  da->capacity = initialCapacity;
  return da;
}

void addElement(DynamicArray *da, int value)
{

  if (da->count == da->capacity)
  {
    // подвоюємо capacity
    // realloc — як malloc але переміщує існуючі дані
    int newCapacity = da->capacity * 2;                          // увеличиваем размер не самого массива а в типе вот тут typedef struct но не вносим изменения
    int *newData = realloc(da->data, newCapacity * sizeof(int)); // а тут уже увеличиваем размер самого массива но не вносим изменения
    if (newData == NULL)
    {
      printf("realloc failed\n");
      exit(1);
    }
    da->data = newData;                            // а тут уже вносим изменения в массив typedef struct
    da->capacity = newCapacity;                    // а тут вносим изменения уже в тип typedef struct
    printf(">>> розширення до %d\n", newCapacity); // щоб бачити коли росте
  }
  da->data[da->count] = value; // ми добавляем данние в свободний слот с помощю da->count и чтоби в следующий раз добавить данние с вободний слот ми увеличивем каунт на 1 da->count++;
  da->count++;
}

void printDynArray(DynamicArray *da)
{

  for (int i = 0; i < da->count; i++)
  {
    printf("%d ", da->data[i]);
  }
}

void freeDynArray(DynamicArray *da)
{

  free(da->data);
  free(da);
  printf("Памʼять масиву звільнено");
}
