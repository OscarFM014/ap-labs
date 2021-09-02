#include <stdio.h>

/* month_day function's prototype*/
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    static char daytab[2][12] = {
        {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

    int days_left = yearday;
    int leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    for (int i = 0; i < 12; i++)
    {
        //check if still have days to advance to months
        if (days_left - daytab[leap][i] > 0)
        {
            days_left = days_left - daytab[leap][i];
            *pmonth = *pmonth + 1;
        }
        else
        {
            //I dont have more days to be converted to months
            *pday = days_left;
            return;
        }
    }
}

int main(int argc, char **argv)
{
    // Validate the correct number of items
    if (argc != 3)
    {
        printf("You need to write in correct order the input:\n");
        printf("./month_day <year> <yearday>\n");
        printf("./month_day 2019 33\n");
        return -1;
    }

    int year, day_year, leap;
    char *aux;

    //Validate two integers year and day year
    year = strtol(argv[1], &aux, 10);
    if (*aux != '\0')
    {
        printf("You need to write in correct order the input:\n");
        printf("./month_day <year> <yearday>\n");
        printf("./month_day 2019 33\n");
        return -1;
    }
    day_year = strtol(argv[2], &aux, 10);
    if (*aux != '\0')
    {
        printf("You need to write in correct order the input:\n");
        printf("./month_day <year> <yearday>\n");
        printf("./month_day 2019 33\n");
        return -1;
    }

    // 1 is leap year
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

    //Validate year
    if (year <= 0)
    {
        printf("You need to write in correct order the input and year > 0 (year 0 does not exits):\n");
        printf("./month_day <year> <yearday>\n");
        printf("./month_day 1 33\n");
        return -1;
    }

    //Validate correct day year
    if (day_year <= 0 || day_year >= 367)
    {
        printf("You need to write in correct order the input:\n");
        printf("year day is not a valid value\n");
        printf("./month_day <year> <yearday>\n");
        printf("./month_day 1 33\n");
        return -1;
    }

    //Validate correct day year related to the leap year
    if (leap != 1 && day_year > 365)
    {
        printf("You need to write in correct order the input:\n");
        printf("year day is not valid for a non leap year\n");
        printf("./month_day <year> <yearday>\n");
        printf("./month_day 1991 365\n");
        return -1;
    }
    int month = 0;
    int day = 0;

    // This are my months
    static char *name[] = {
        "Jan", "Feb", "Mar",
        "Apr", "May", "Jun",
        "Jul", "Aug", "Sep",
        "Oct", "Nov", "Dec"};
    month_day(year, day_year, &month, &day);

    printf("%s %02d, %i", name[month], day, year);

    return 0;
}
