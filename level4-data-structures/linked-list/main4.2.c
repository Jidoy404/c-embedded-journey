#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
  int value;
  struct Node *next;
} Node;

void pushFront(Node **head, int value);
void pushBack(Node **head, int value);
void printList(Node *head);
int contains(Node *head, int value);
void freeList(Node **head);
void removeValue(Node **head, int value);

int main()
{
  Node *head = NULL; // тут завжди лежить адресс першого елемента цієї змійки 
  pushFront(&head, 1);
  pushFront(&head, 2);
  pushFront(&head, 3);
  printList(head); // очікую: 3 2 1

  pushBack(&head, 10);
  pushBack(&head, 20);
  printList(head);

  printf("%d\n", contains(head, 2)); // очікую 1
  printf("%d\n", contains(head, 99));

  removeValue(&head, 2);
  printList(head); // очікую: 3 1 10 20

  freeList(&head);
  printList(head); // очікую: порожній рядок (список пустий)
  return 0;
}

void pushFront(Node **head, int value)
{
  Node *newNode = malloc(sizeof(Node));
  newNode->value = value;
  newNode->next = *head; // новий вузол вказує на стару голову
  *head = newNode;
}

void pushBack(Node **head, int value)
{
  if (*head == NULL)
  {
    Node *newNode = malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL; // тут нул потому что если после елемента ничего нету то и адрес следующего не существует 
    *head = newNode;
    return;
  }

  Node *current = *head;
  while (current->next != NULL)
  {
    current = current->next;
  }
  // тепер current — це останній вузол
  Node *newNode = malloc(sizeof(Node));
  newNode->value = value;
  newNode->next = NULL;
  current->next = newNode; // ось тут приєднуєш
}

void printList(Node *head)
{
  Node *current = head;
  while (current != NULL)
  {
    printf("%d ", current->value);
    current = current->next;
  }
  printf("\n");
}

int contains(Node *head, int value)
{
  Node *current = head;
  while (current != NULL)
  {
    if (current->value == value)
      return 1;
    current = current->next;
  }
  return 0;
}

void freeList(Node **head)
{
  Node *current = *head;
  while (current != NULL)
  {
    Node *next = current->next; // зберегти ДО free
    free(current);
    current = next;
  }
  *head = NULL;
}

void removeValue(Node **head, int value)
{
  if (*head == NULL)
    return; // список порожній — нічого видаляти

  // Випадок 1 — видаляємо голову
  if ((*head)->value == value)
  {
    Node *toDelete = *head;
    *head = (*head)->next; // голова тепер другий елемент
    free(toDelete);
    return;
  }

  // Випадок 2 — шукаємо далі по списку
  Node *prev = *head;
  Node *current = (*head)->next; // тут підказка: треба (*head)->next, дужки важливі!

  while (current != NULL)
  {
    if (current->value == value)
    {
      prev->next = current->next;
      free(current);
      return;
    }
    prev = current;
    current = current->next;
  }
  // якщо дійшли сюди — значення не знайдено, нічого не робимо
}

// *head          -> настоящий head из main
// (*head)->value -> значение первого узла
// (*head)->next  -> следующий после первого узла

// current        -> текущий узел
// current->value -> значение текущего узла
// current->next  -> следующий узел

// prev           -> предыдущий узел
// prev->next     -> ссылка из предыдущего на следующий