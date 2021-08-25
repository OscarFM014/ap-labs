#include <stdio.h>
#include <string.h>

char *reverse(char *word)
{
    char *reversed_word = word;
    char aux;
    for (int i = 0; i < strlen(reversed_word) / 2; i++)
    {
        aux = reversed_word[strlen(reversed_word) - i - 1];
        reversed_word[strlen(reversed_word) - i - 1] = reversed_word[i];
        reversed_word[i] = aux;
    }
    return reversed_word;
}

int main(int argc, char **argv)
{
    char *word = argv[1];

    printf("Original Word: %s \n", word);

    printf("Reversed Word: %s \n", reverse(word));
    return 0;
}