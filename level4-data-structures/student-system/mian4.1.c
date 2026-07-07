#include <stddef.h>
#include <stdio.h>

typedef struct
{
  char name[30];
  int grades[5];
  float average;
} Student;

float calculateAverage(Student *s);
Student findBest(Student *students, int count);
void printStudents(Student *students, int count);

int main()
{

  Student students[5] = {
      {"Anna", {90, 85, 92, 88, 95}},
      {"Bob", {70, 65, 80, 75, 60}},
      {"Carl", {100, 95, 98, 92, 97}},
      {"Diana", {55, 60, 58, 62, 50}},
      {"Eva", {80, 85, 78, 90, 88}}};

  for (int i = 0; i < 5; i++)
    calculateAverage(&students[i]);

  printStudents(students, 5);

  return 0;
}

float calculateAverage(Student *s)
{
  size_t gradesCount = sizeof(s->grades) / sizeof(s->grades[0]);

  float sum = 0;

  for (size_t i = 0; i < gradesCount; i++)
  {
    sum += s->grades[i];
  }

  s->average = sum / gradesCount;
  return s->average;
}

Student findBest(Student *s, int count)
{

  size_t bestIndex = 0;

  for (int i = 1; i < count; i++)
  {
    if (s[i].average > s[bestIndex].average)
    {
      bestIndex = i;
    }
  }

  return s[bestIndex];
}

void printStudents(Student *s, int count)
{
  size_t gradesCount = sizeof(s->grades) / sizeof(s->grades[0]);

  printf("Список студентів\n");
  for (size_t i = 0; i < count; i++)
  {
    printf("%s", s[i].name);
    printf("  ");
    for (size_t j = 0; j < gradesCount; j++)
    {
      printf("%d ", s[i].grades[j]);
    }
    printf("  ");
    printf("%.2f", s[i].average); 
    printf("\n");
  }

  Student best = findBest(s, 5);
  printf("Best student: %s\n", best.name);
  printf("Grades: ");

  for (int i = 0; i < 5; i++)
  {
    printf("%d ", best.grades[i]);
  }

  printf("\n");
  printf("Average: %.2f\n", best.average);
}