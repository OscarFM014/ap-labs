#include <stdio.h>
int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("You need to send at least 1 argument");
        return -1;
    }
    printf("Hello ");
    for (int i = 1; i < argc; i++)
    {
        printf("%s ", argv[i]);
    }

    return 0;
}