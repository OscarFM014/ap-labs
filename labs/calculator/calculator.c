#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// adds/subtracts/multiplies all values that are in the *values array.
// nValues is the number of values you're reading from the array
// operator will indicate if it's an addition (1), subtraction (2) or
// multiplication (3)
long calc(int operator, int nValues, int *values) {
    return 0;
}

int main(int argc, char **argv) {
    printf("Pass minimum variables");
    if(argc < 2){
        printf("You need to write in correct order the input:\n");
        printf("./calculator.c add 1 2 3 4 5\n");
        return -1;
    }


    if(!strcmp(argv[1], 'add') || !strcmp(argv[1], 'sub') || !strcmp(argv[1], 'mult')){
        printf("You need to write in correct order the input and just this operations:\n");
        printf("  ./calculator.c add 1 2 3 4 5\n");
        printf("  ./calculator.c sub 1 2 3 4 5\n");
        printf("  ./calculator.c mult 1 2 3 4 5\n");
        return -1;
    }


    // Validate that the next are just numbers are int
    int *arr;
    arr = malloc(sizeof(int)* argc);

    for(int i = 2; i < argc; i ++){
        if(isdigit(atoi(argv[i]))){
            printf("%i", argv[i]);
        }
    }
    
    return -1;
}
