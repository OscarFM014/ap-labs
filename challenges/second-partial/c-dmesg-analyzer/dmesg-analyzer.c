#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define REPORT_FILE "report.txt"
#define mySize 4000

void analizeLog(char *logFile, char *report);

//Element
struct DataItem {
   char *data[4000]; 
   char *key;
} ;

//HashCode Generator from char
int hashCode(const char* key) {
    unsigned int hash = 0;
	int c;

	while (c = *key++)
	    hash += c;

	return hash % mySize;
}

//Array of dataitems
struct DataItem *hashArray[mySize];

//Inser Values on the hashArray
void insert(char* key, char* word) {
    //Create item to add in the hashArray
    struct DataItem *item = (struct DataItem*) malloc(sizeof(struct DataItem));
   
   //Generate hashIndex from key with hashCode function
   int hashIndex = hashCode(key);
   int i = 0;
    
    //Check for available position for the new element
    while(hashArray[hashIndex] != NULL) {
        //If the key is already on the hashArray
        if(strcmp(hashArray[hashIndex]->key, key) == 0){
            while(hashArray[hashIndex]->data[i] != NULL){
                i++;
            }
            //Add just the word on the correc array from the hashArray 
            hashArray[hashIndex]->data[i] = malloc (sizeof(char) * strlen(word));
            strncpy(hashArray[hashIndex]->data[i], word, strlen(word));
        
            return;
        }
        
      ++hashIndex;
      hashIndex %= mySize;
    }
    //Empty space to add a new key
    //Generate the space location and add to the item and then add item to the hashArray
    item->key = malloc (sizeof(char) * strlen(key));
    strncpy(item->key, key, strlen(key));
    item->data[0] =  malloc (sizeof(char) * strlen(word));
    strncpy(item->data[0], word, strlen(word));
    hashArray[hashIndex] = item;
   
}

//Write the REPORT_FILE function 
void write() {
    int i = 0;
    FILE *output;
    output = fopen(REPORT_FILE, "w+");

    for(i = 0; i<mySize; i++) {
        if(hashArray[i] != NULL){
            fprintf(output,"%s: \n",hashArray[i]->key );
            for(int j = 0; j < mySize; j ++ ){
                if(hashArray[i]->data[j] !=NULL ){
                    fprintf(output, "     %s",  hashArray[i]->data[j]);
                }
            } 
        }
    }
}

//Substring function for get the correct format on the hashArray
char* substring(char *destination, const char *source, int beg, int n)
{
    strncpy(destination, (source + beg), n);
    return destination;
}

void analizeLog(char *logFile, char *report) {
    printf("Generating Report from: [%s] log file\n", logFile);

    // Implement your solution here.

    //Init the hashArray
    hashArray[mySize] = (struct DataItem*) malloc(sizeof(struct DataItem));
    
    FILE *fptr;
	char * line = NULL;
    size_t len = 0;
    ssize_t read;
	int sizeFile = 0;
    fptr = fopen(logFile,"r");

    //Check Null logFile
    if (fptr  == NULL){
		printf("Program should have the correct arguments and make sure the document is on the same directory \n");
		printf ("$ ./dmesg-analizer dmesg.txt \n");
		return -1;
	}

    //Read the logFile
    while ((read = getline(&line, &len, fptr)) != -1) {
		if(strcmp("\n", line) != 0){
            int hour = 0;
            int i = 0;
            int start = 0;
            int len = 0;
            
            //Get the size of the hour string and traverse the line 
            if('[' == line[i]){
                while(']' != line[i]){
                    i++;
                    hour++;
                }
                //First Letter
                i += 2;
                //i finish in ] so plus one in to capture it
                hour++;
                //Start the first letter
                start = i;
                
                //Get the size of the logtype sting and traverse the line 
                while(':' != line[i] && i < strlen(line)){
                    i++;
                    len++;
                }

                char logType[len];
                char hourChar[hour];
                
                //Check if the log string was found or not
                if(i != strlen(line)){
                   
                    //Substring of the logtype
                    substring(logType,line, start, len);
                    logType[len] = '\0';
                    
                    //Substring of the hour
                    substring(hourChar, line, 0, hour);
                    hourChar[hour] = '\0';

                    //Substring of the message
                    char restLine[strlen(line) - len - hour];
                    substring(restLine, line, i+1, strlen(line) - len - hour);
                    restLine[strlen(line) - len - hour] = '\0';

                    //Concanate the hour and the message
                    char finalLine[strlen(line) - len + 1];
                    strcpy(finalLine, hourChar);
                    strcat(finalLine, restLine);
                    finalLine[strlen(line) - len + 1] = '\0';

                    //Insert the final value on the hashArray
                    insert(logType, finalLine);
      
                }else /* log type not found */{
                    //Substring of the hour
                    substring(hourChar, line, 0, hour);
                    hourChar[hour] = '\0';

                    //Substring of the message
                    char restLine[strlen(line) - hour];
                    substring(restLine, line, hour,strlen(line) - hour);
                    restLine[strlen(line) - hour] = '\0';

                    //Concanate the hour and the message
                    char finalLine[strlen(line)];
                    strcpy(finalLine, hourChar);
                    strcat(finalLine, restLine);
                    finalLine[strlen(line)] = '\0';   

                    //Insert the final value on the hashArray
                    insert("General", finalLine);
	
                }               
            }
		}
    }

    //Write the document
    write();
    printf("Report is generated at: [%s]\n", report);
}


int main(int argc, char **argv) {

    if (argc < 2) {
        printf("ERROR: Usage:./dmesg-analizer logfile.txt\n");
        return -1;
    }
    analizeLog(argv[1], REPORT_FILE);
    return 0;
}
