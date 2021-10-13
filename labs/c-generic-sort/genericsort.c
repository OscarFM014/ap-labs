#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include<stdlib.h>

void quicksort(void *lineptr[], int left, int right,
	   int (*comp)(void *, void *));

void mergesort(void *lineptr[], int left, int right,
	   int (*comp)(void *, void *));

int numcmp(const void *p1, const void *p2)
{
     double v1 = atof(p1),
        v2 = atof(p2);

    return (int) (v1 - v2);
}

int main(int argc, char **argv)
{
	if(argc>6 || argc < 3){
		printf("Program should have the correct arguments \n");
		printf ("$ ./genericsort -n numbers.txt -quicksort -o qs_sorted_numbers.txt \n");
		printf ("$ ./genericsort strings.txt -mergesort -o ms_sorted_strings.txt \n");
		return -1;
	}

	bool isNumberFile = true;
	char *fileName = 'fileName';
	char *sortType = 'mergesort';
	char *nameOutputFile = 'sorted.txt';
	
	if(strcmp("-n", argv[1]) != 0){
		isNumberFile = false;
		fileName = argv[1];
		sortType = argv[2];
		if(strcmp("-o", argv[3]) == 0){
			nameOutputFile = argv[4];
		}else{
			printf("Program should have the correct arguments (output file) \n");
			printf ("$ ./genericsort -n numbers.txt -quicksort -o qs_sorted_numbers.txt \n");
			printf ("$ ./genericsort strings.txt -mergesort -o ms_sorted_strings.txt \n");
			return -1;
		}
	}else{
		fileName = argv[2];
		sortType = argv[3];
		if(strcmp("-o", argv[4]) == 0){
			nameOutputFile = argv[5];
		}else{
			printf("Program should have the correct arguments (output file) \n");
			printf ("$ ./genericsort -n numbers.txt -quicksort -o qs_sorted_numbers.txt \n");
			printf ("$ ./genericsort strings.txt -mergesort -o ms_sorted_strings.txt \n");
			return -1;
		}
	}


	//Read document
	// Declaration pointer
	FILE *fptr;
	char * line = NULL;
    size_t len = 0;
    ssize_t read;
	int sizeFile = 0;
	ssize_t maxLineSize =0;

	fptr = fopen(fileName,"r");

	//Check if the file exist
	if (fptr  == NULL){
		printf("Program should have the correct arguments and make sure the document is on the same directory \n");
		printf ("$ ./genericsort -n numbers.txt -quicksort -o qs_sorted_numbers.txt \n");
		printf ("$ ./genericsort strings.txt -mergesort -o ms_sorted_strings.txt \n");
		return -1;
	}

	//Get the size of the file
	while ((read = getline(&line, &len, fptr)) != -1) {
		if(strcmp("\n", line) != 0 && strcmp(" ", line) != 0){
			  //printf("Retrieved line of length %zu:\n", read);
			  if(read > maxLineSize){
				  maxLineSize = read;
			  }
        	//printf("%s", line);
			sizeFile++;
			//printf("Document Size of: %i \n", sizeFile);
		}
    }

	//Create the array of void pointers
	fptr = fopen(fileName,"r");
	int left = 0;
	int right = sizeFile - 1;
	int numLines = 0;
	void *lineptr[sizeFile];
	len = 0;
	while ((read = getline(&line, &len, fptr) != -1)) {
			lineptr[numLines] = malloc(strlen(line));
			strcpy(lineptr[numLines++], line);
    }
	
	
	// Save the element depending of the -n command
	if(isNumberFile){
		if(strcmp("-quicksort", sortType) == 0){
			quicksort(lineptr, left, right, (int (*)(void *, void *))numcmp);
		}else if(strcmp("-mergesort", sortType) == 0){
			mergesort(lineptr, left, right, (int (*)(void *, void *))numcmp);
		}else {
			printf("Program should have the correct arguments and make sure the sorted array \n");
			printf ("$ ./genericsort -n numbers.txt -quicksort -o qs_sorted_numbers.txt \n");
			printf ("$ ./genericsort strings.txt -mergesort -o ms_sorted_strings.txt \n");
			return -1;
		}
	}else{
		if(strcmp("-quicksort", sortType) == 0){
			quicksort( lineptr, left, right, (int (*)(void *, void *))strcmp);
		
		}else if(strcmp("-mergesort", sortType) == 0){
			mergesort( lineptr, left, right, (int (*)(void *, void *))strcmp);
			
		}else {
			printf("Program should have the correct arguments and make sure the sorted array \n");
			printf ("$ ./genericsort -n numbers.txt -quicksort -o qs_sorted_numbers.txt \n");
			printf ("$ ./genericsort strings.txt -mergesort -o ms_sorted_strings.txt \n");
			return -1;
		}
	} 

	/* for (int i = 0; i < sizeFile; i++) {
		printf("%s", (char *)lineptr[i]);
	}  */

	FILE *output;
	output = fopen(nameOutputFile, "w+");
	for (int i = 0; i < sizeFile; i++) {
        fprintf(output, "%s", (char *)lineptr[i]);
    }

	fclose(fptr);
	fclose(output);
    return 0;
}
