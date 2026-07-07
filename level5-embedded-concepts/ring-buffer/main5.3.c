#define BUFFER_SIZE 5
#include <stdio.h>

typedef struct
{
  int data[BUFFER_SIZE];
  int head;  // звідки читаємо (pop)
  int tail;  // куди пишемо (push)
  int count; // скільки елементів зараз реально в буфері
} RingBuffer;

void ringInit(RingBuffer *rb);
void ringPush(RingBuffer *rb, int value);
int ringPop(RingBuffer *rb, int *value);
int isEmpty(RingBuffer *rb);

int main()
{
  RingBuffer rb;
  ringInit(&rb);

  int value;

  printf("--- Заповнюємо буфер (BUFFER_SIZE=5) ---\n");
  for (int i = 1; i <= 5; i++)
  {
    ringPush(&rb, i * 10);
    printf("push(%d) -> head=%d tail=%d count=%d\n", i * 10, rb.head, rb.tail, rb.count);
  }

  printf("\n--- Спроба push у повний буфер ---\n");
  ringPush(&rb, 999);

  printf("\n--- Читаємо 2 елементи ---\n");
  for (int i = 0; i < 2; i++)
  {
    if (ringPop(&rb, &value))
    {
      printf("pop() -> value=%d | head=%d tail=%d count=%d\n", value, rb.head, rb.tail, rb.count);
    }
  }

  printf("\n--- Push ще 2 елементи (перевірка закільцювання tail) ---\n");
  ringPush(&rb, 60);
  printf("push(60) -> head=%d tail=%d count=%d\n", rb.head, rb.tail, rb.count);
  ringPush(&rb, 70);
  printf("push(70) -> head=%d tail=%d count=%d\n", rb.head, rb.tail, rb.count);

  printf("\n--- Читаємо все, що залишилось ---\n");
  while (!isEmpty(&rb))
  {
    ringPop(&rb, &value);
    printf("pop() -> value=%d | head=%d tail=%d count=%d\n", value, rb.head, rb.tail, rb.count);
  }

  printf("\n--- Спроба pop із порожнього буфера ---\n");
  ringPop(&rb, &value);

  return 0;
}

void ringInit(RingBuffer *rb)
{
  rb->head = 0;
  rb->tail = 0;
  rb->count = 0;
}

int isEmpty(RingBuffer *rb)
{
  return rb->count == 0;
}

int isFull(RingBuffer *rb)
{
  return rb->count == BUFFER_SIZE;
}

void ringPush(RingBuffer *rb, int value)
{
  if (isFull(rb))
  {
    printf("буфер переповнений");
    return;
  }

  rb->data[rb->tail] = value;

  rb->tail = (rb->tail + 1) % BUFFER_SIZE; // якщо tail дійде до кінця BUFFER_SIZE то tail перестрибне на перший елемент BUFFER_SIZE
  rb->count++;
}

int ringPop(RingBuffer *rb, int *value)
{
  if (isEmpty(rb))
  {
    printf("буфер пустий\n");
    return 0;
  }

  *value = rb->data[rb->head];
  rb->head = (rb->head + 1) % BUFFER_SIZE; // ми прочитали комірку далі записали як вільну і пішли далі ми в цьому проекті ідемо по колу
  rb->count--;
  return 1;
}