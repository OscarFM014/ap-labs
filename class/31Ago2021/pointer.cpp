#include <stdio.h>


void swap(int *px, int *py)
{
    int temp;
    temp = *px;
    *px = *py;
    *py = temp;
}

char *month_name(int n) {

   static char *name[] = {
       "Illegal month",
       "January", "February", "March",
       "April", "May", "June",
       "July", "August", "September",
       "October", "November", "December"
   };

   return (n < 1 || n > 12) ? name[0] : name[n];
}


int main() {

    int x = 1, y = 2;

    printf("Before Swap: x = %i, y = %i\n", x, y);

    swap(&x,&y);

    printf("After Swap: x = %i, y = %i\n", x, y);

    // month_name

    printf(month_name(5));

    return 0;
}