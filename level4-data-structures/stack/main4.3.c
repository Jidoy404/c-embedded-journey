#include <stdio.h>
#include <stdlib.h>

typedef struct QueueNode
{
  int value;
  struct QueueNode *next;
} QueueNode;

typedef struct
{
  QueueNode *front; // перший
  QueueNode *rear;  // останній
} Queue;

typedef struct StackNode
{
  int value;
  struct StackNode *next;
} StackNode;

void push(StackNode **top, int value);
int pop(StackNode **top);
int peek(StackNode *top);
int isEmpty(StackNode *top);

int isBalanced(char *s);

void enqueue(Queue *q, int value); // додати в кінець
int dequeue(Queue *q);             // забрати з початку
int isQueueEmpty(Queue *q);

int main()
{

  StackNode *stack = NULL;
  push(&stack, 1);
  push(&stack, 2);
  push(&stack, 3);

  printf("%d\n", pop(&stack));    // 3
  printf("%d\n", pop(&stack));    // 2
  printf("%d\n", isEmpty(stack)); // 0
  printf("%d\n", pop(&stack));    // 1
  printf("%d\n", isEmpty(stack)); // 1

  printf("%d\n", isBalanced("(()())")); // 1
  printf("%d\n", isBalanced("(()"));    // 0
  printf("%d\n", isBalanced(")("));     // 0
  printf("%d\n", isBalanced(""));       // 1

  Queue q = {NULL, NULL};

  enqueue(&q, 10);
  enqueue(&q, 20);
  enqueue(&q, 30);

  printf("%d\n", dequeue(&q));      // 10
  printf("%d\n", dequeue(&q));      // 20
  printf("%d\n", dequeue(&q));      // 30
  printf("%d\n", isQueueEmpty(&q)); // 1

  return 0;
}

void push(StackNode **top, int value)
{
  StackNode *newNode = malloc(sizeof(StackNode));
  newNode->value = value;
  newNode->next = *top;
  *top = newNode;
}

int pop(StackNode **top)
{
  if (*top == NULL)
  {
    printf("Елементів немає");
    return 0;
  }

  StackNode *temp = *top; // ствюрюємо указатель і записуємо туди данні які будемо стирати якщо не створювати temp то будет неможливо звільнити памʼять бо і top вже будуть записані інші данні
  int value = temp->value;
  *top = temp->next;
  free(temp);
  return value;
}

int peek(StackNode *top)
{
  if (top == NULL)
  {
    printf("Stack is empty\n");
    return -1;
  }

  return top->value;
}

int isEmpty(StackNode *top)
{
  return top == NULL;
}

int isBalanced(char *s)
{
  StackNode *stack = NULL;

  while (*s != '\0')
  {
    if (*s == '(')
    {
      push(&stack, 1); // значення не важливе, важливий факт що щось є в стеку
    }
    else if (*s == ')')
    {
      if (isEmpty(stack))
        return 0; // закриваюча дужка без пари
      pop(&stack);
    }
    s++;
  }

  return isEmpty(stack); // якщо стек порожній — все закрито правильно
}

void enqueue(Queue *q, int value) // додати в кінець
{

  QueueNode *newNode = malloc(sizeof(QueueNode));
  newNode->value = value;
  newNode->next = NULL; // тут нул потому что если после елемента ничего нету то и адрес следующего не существует

  if (q->front == NULL) // черга порожня
  {
    q->front = newNode;
    q->rear = newNode;
    // і front, і rear мають вказувати на новий вузол
  }
  else
  {
    q->rear->next = newNode; // ми даем силку для последнего елемента на наш
    q->rear = newNode;       // и делаем наш последним елементом

    // q->front->next — next первого узла
    // q->rear->next  — next последнего узла

    // старий rear повинен вказувати на новий вузол, потім rear оновити
  }
}

int dequeue(Queue *q) // забрати з початку
{
  if (q->front == NULL)
  {
    printf("Елементів немає");
    return 0;
  }

  QueueNode *temp = q->front;
  int value = q->front->value;
  q->front = temp->next;
  free(temp);

  if (q->front == NULL)
  {
    q->rear = NULL;
  }
  return value;
}

int isQueueEmpty(Queue *q)
{
  return q->front == NULL;
}
