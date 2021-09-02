#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// adds/subtracts/multiplies all values that are in the *values array.
// nValues is the number of values you're reading from the array
// operator will indicate if it's an addition (1), subtraction (2) or
// multiplication (3)
long calc(int operator, int nValues, int *values)
{
    long result = values[0];
    printf("%i ", result);
    for (int i = 1; i < nValues; i++)
    {
        if (operator== 1)
        {
            result += values[i];
            printf(" + %i", values[i]);
        }
        else if (operator== 2)
        {
            result -= values[i];
            printf(" - %i", values[i]);
        }
        else
        {
            result *= values[i];
            printf(" * %i", values[i]);
        }
    }
    printf(" = %i \n", result);
    return result;
}

int main(int argc, char **argv)
{
    // Validate correct size inputs
    if (argc < 3)
    {
        printf("You need to write in correct order the input:\n");
        printf("./calculator.c add 1 2 3 4 5\n");
        return -1;
    }

    char *word_oper = argv[1];

    //Validate just correct operators
    if (!strcmp(word_oper, "add") == 0 && !strcmp(word_oper, "sub") == 0 && !strcmp(word_oper, "mult") == 0)
    {
        printf("You need to write in correct order the input and just this operations:\n");
        printf("  ./calculator.c add 1 2 3 4 5\n");
        printf("  ./calculator.c sub 1 2 3 4 5\n");
        printf("  ./calculator.c mult 1 2 3 4 5\n");
        return -1;
    }

    // Validate that the next are just numbers are int
    int arr[argc - 2];
    int size_array = sizeof(arr) / sizeof(arr[0]);
    int number;
    char *aux;

    for (int i = 2; i < argc; i++)
    {
        number = strtol(argv[i], &aux, 10);
        if (*aux == '\0')
        {
            arr[i - 2] = number;
        }
        else
        {
            printf("You need to write in correct order the input (just integers):\n");
            printf("./calculator.c add 1 2 3 4 5\n");
            return -1;
        }
    }

    int operator;
    if (strcmp(word_oper, "add") == 0)
    {

        operator= 1;
    }
    else if (strcmp(word_oper, "sub") == 0)
    {
        operator= 2;
    }
    else
    {
        operator= 3;
    }

    calc(operator, size_array, arr);
    return -1;
}
