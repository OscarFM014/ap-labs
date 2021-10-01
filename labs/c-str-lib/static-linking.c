#include <stdio.h>

int mystrlen(char*);

char* mystradd(char*, char*);

int mystrfind(char*, char*);



int main(int argc, char **argv) {

    if(argc != 4){
        printf("Program just support the following arguments: \n");
        printf("./main.o -add \"Initial String\" \"This is the rest to be added\" \n");
        printf("./main.o -find \"Initial String\" \"Init\" \n");
        return -1;
    }

    char *oper = argv[1];

    if(strcmp("-add", oper) != 0 && strcmp("-find", oper)!= 0){
        printf("Program just support the following arguments: \n");
        printf("./main.o -add \"Initial String\" \"This is the rest to be added\" \n");
        printf("./main.o -find \"Initial String \" \"Init\" \n");
        return -1;
    }

    char *fstring = argv[2];
    char *sstring = argv[3];

     
    if(strcmp("-add", oper) == 0 ){
        printf("Initial Length  : %i \n", mystrlen(fstring));
       char *myNewString = mystradd(fstring, sstring); 
        printf("New String      : %s \n", myNewString);
        printf("New Length      : %i \n", mystrlen(myNewString));
        return 0;
    }

    int position = -1;
    if(strcmp("-find", oper) == 0){
        position = mystrfind(fstring, sstring);
        if(position != -1){
            printf("['%s'] string was found at [%i] position \n", sstring, position);
        }else{
            printf("['%s'] string was not found in %s \n", sstring, fstring);
        }
    }

    return 0;
}
