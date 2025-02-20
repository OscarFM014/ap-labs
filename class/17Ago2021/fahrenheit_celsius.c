#include <stdio.h>

/* #define LOWER 0  */  /* lower limit of table */
/* #define UPPER 300 */ /* upper limit */
/* #define STEP 20  */  /* step size */

/* print Fahrenheit-Celsius table */

int main(int argc, char **argv)
{
    int fahr;
    if (argc < 2)
    {
        printf("Hey bro! Send at least 1 number like this: \n");
        printf("Examples: \n");
        printf("./fc <start> <end> <increment> \n");
        return -1;
    }

    // simple conversion case
    if (argc == 2)
    {
        fahr = atoi(argv[1]);
        printf("Fahrenheit: %3d, Celcius: %6.1f\n", fahr, (5.0 / 9.0) * (fahr - 32));
    }

    //range conversion
    if (argc == 4)
    {
        int lower = atoi(argv[1]);
        int upper = atoi(argv[2]);
        int step = atoi(argv[3]);
        for (fahr = lower; fahr <= upper; fahr = fahr + step)
            printf("Fahrenheit: %3d, Celcius: %6.1f\n", fahr, (5.0 / 9.0) * (fahr - 32));
    }

    return 0;
}