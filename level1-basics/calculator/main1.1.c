#include <stdio.h>
#include <stdbool.h>

float calculate(float a, float b, char operation);

int main()
{
    char goorstop;
    printf("Hello, this is calculator\n");

    do
    {
        float num1 = 0;
        float num2 = 0;
        char operation;
        
        int status1;

        printf("To start, please enter the first number: \n");
        status1 = scanf("%f", &num1);

        while (status1 != 1)
        {

            printf("You are not in the right number\n");

            printf("Please enter the first number: \n");

            while (getchar() != '\n')
                ;

            status1 = scanf("%f", &num1);
        }

        int status2;

        printf("Please enter the second number: \n");
        status2 = scanf("%f", &num2);

        while (status2 != 1)
        {
            printf("You are not in the right number\n");

            printf("Please enter the second number: \n");

            while (getchar() != '\n')
                ;

            status2 = scanf("%f", &num2);
        }

        operation = 'a';

        printf("Please enter the operation you want to perform (+, -, *, /): \n");
        scanf(" %c", &operation);

        while (operation != '+' && operation != '-' && operation != '*' && operation != '/')
        {

            printf("You are not in the right operation\n");

            printf("Please enter the operation you want to perform (+, -, *, /): \n");

            while (getchar() != '\n')
                ;

            scanf(" %c", &operation);
        }

        if (num2 == 0 && operation == '/')
        {
            printf("Ділити на нуль неможна\n");
            return 1;
        }

        printf("%.2f\n", calculate(num1, num2, operation));

        printf("please type c to continue and s to stop\n");
        scanf(" %c", &goorstop);
    }

    while (goorstop != 's');

    return 0;
}

float calculate(float num1, float num2, char operation)
{

    switch (operation)
    {
    case '+':
        return num1 + num2;
    case '-':
        return num1 - num2;
    case '*':
        return num1 * num2;
    case '/':
        return num1 / num2;
    }
    return 1;
}
