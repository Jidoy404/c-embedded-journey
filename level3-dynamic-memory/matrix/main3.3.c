#include <stdlib.h>
#include <stdio.h>

int **createMatrix(int rows, int cols);
void fillMatrix(int **matrix, int rows, int cols);
void printMatrix(int **matrix, int rows, int cols);
int **transpose(int **matrix, int rows, int cols);
void freeMatrix(int **matrix, int rows);

// typedef struct // ми зробили ссвій тип данних по типу int, float і назвали його DynamicArray
// {
//   int **data;    // вказівник на вказіник надані
//   int rows;    // кількість рядків
//   int cols; // кількісь стовпців
// } DynamicArray;

int main()
{

  int rows = 3, cols = 4;
  int **m = createMatrix(rows, cols);
  fillMatrix(m, rows, cols);
  printMatrix(m, rows, cols);

  int **t = transpose(m, rows, cols);
  printMatrix(t, cols, rows); // увага: cols і rows міняються місцями!

  freeMatrix(m, rows);
  freeMatrix(t, cols); // увага: t має cols рядків, не rows!

  return 0;
}

// matrix[i][j]
// i -> номер рядка
// j -> номер стовпця

int **createMatrix(int rows, int cols)
{

  int **matrix = malloc(rows * sizeof(int *));

  if (matrix == NULL)
  {
    printf("malloc failed\n");
    exit(1);
  }

  for (int i = 0; i < rows; i++)
  {
    matrix[i] = malloc(cols * sizeof(int));

    if (matrix[i] == NULL) // при ошибке виделения памяти
    {
      for (int j = 0; j < i; j++) // очистка строк которие уже создались
      {
        free(matrix[j]);
      }

      free(matrix);

      printf("malloc failed\n");
      exit(1);
    }
  }

  return matrix;
}

void fillMatrix(int **matrix, int rows, int cols)
{

  int temp = 1;

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {

      matrix[i][j] = temp;

      temp++;
    }
  }
}

void printMatrix(int **matrix, int rows, int cols)
{
  for (int i = 0; i < rows; i++)
  {

    for (int j = 0; j < cols; j++)
    {

      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
}

int **transpose(int **matrix, int rows, int cols)
{

  int **res = createMatrix(cols, rows);

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {

      res[j][i] = matrix[i][j];
    }
  }
  return res;
}

void freeMatrix(int **matrix, int rows)
{
  if (matrix == NULL)
  {
    return;
  }

  for (int i = 0; i < rows; i++)
  {
    free(matrix[i]);
  }

  free(matrix);
}
