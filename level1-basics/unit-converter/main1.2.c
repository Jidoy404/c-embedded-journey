#include <stdio.h>
#include <stdlib.h>

int readInt(const char *prompt, int min, int max);
float readFloat(const char *prompt);


float celsiusToFahrenheit(float c);
float fahrenheitToCelsius(float f);
float kmToMiles(float km);
float milesToKm(float miles);
float kgToPounds(float kg);
float poundsToKg(float pounds);

int main()
{

  char goorstop;

  do
  {

    printf("=== Конвертер ===\n");
    printf("1. Температура\n");
    printf("2. Длина\n");
    printf("3. Вес\n");
    printf("0. Выход\n");

    int choice1;
    int choice2;
    float result;

    choice1 = readInt("Please select one of the options, the number corresponds to the option 0 - 3", 0, 3);

    switch (choice1)
    {
    case 0:
      return 0;
    case 1:
    {
      printf("1. Celsius -> Fahrenheit\n");
      printf("2. Fahrenheit -> Celsius\n");
      choice2 = readInt("Please select one of the options, the number corresponds to the option 1 - 2", 1, 2);
      float value = readFloat("Введите число для конвертации: ");
      result = (choice2 == 1) ? celsiusToFahrenheit(value) : fahrenheitToCelsius(value);
      break;
    }
    case 2:
    {
      printf("1. KM -> Mils\n");
      printf("2. Mils -> KM\n");
      choice2 = readInt("Please select one of the options, the number corresponds to the option 1 - 2", 1, 2);
      float value = readFloat("Введите число для конвертации: ");
      result = (choice2 == 1) ? kmToMiles(value) : milesToKm(value);
      break;
    }
    case 3:
    {
      printf("1. Kg -> Pounds\n");
      printf("2. Pounds -> Kg\n");
      choice2 = readInt("Please select one of the options, the number corresponds to the option 1 - 2", 1, 2);
      float value = readFloat("Введите число для конвертации: ");
      result = (choice2 == 1) ? kgToPounds(value) : poundsToKg(value);
      break;
    }
    }

    printf("Результат: %.4f\n", result);

    printf("продовжуємо с ======= зупиняємося s\n");
    scanf(" %c", &goorstop);

  } while (goorstop != 's');

  return 0;
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

float readFloat(const char *prompt)
{
  float value;
  int i = 0;
  printf("%s", prompt);
  while (scanf("%f", &value) != 1)
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
  }
  return value;
}

float celsiusToFahrenheit(float c)
{
  return (c * 1.8) + 32;
}

float fahrenheitToCelsius(float f)
{
  return (f - 32) / 1.8;
}

float kmToMiles(float km)
{
  return km / 1.60934;
}

float milesToKm(float miles)
{
  return miles * 1.60934;
}

float kgToPounds(float kg)
{
  return kg * 2.20462;
}

float poundsToKg(float pounds)
{
  return pounds / 2.20462;
}