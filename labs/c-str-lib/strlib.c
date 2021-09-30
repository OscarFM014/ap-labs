
int mystrlen(char *str){
    int count = 0;
    while(*str != '\0')
    {
        count++;
        *str++;
    }
    return count;
}

char *mystradd(char *origin, char *addition){
    char *result = malloc(mystrlen(origin) + mystrlen(origin) + 1);
    strcpy(result, origin);
    strcat(result, addition);
    return result;
}

int mystrfind(char *origin, char *substr){
    
    if(mystrlen(origin) < mystrlen(substr) || mystrlen(substr) == 0 || mystrlen(origin) == 0){
        return -1;
    }

    int size_origin = mystrlen(origin);
    int size_substring = mystrlen(substr);
    int size_find_substring = 0;
    int position_substring = size_origin+1;
    int iter_sub = 0;
    int iter_ori = 0;
    char o = "";
    char s = substr[0];
    for(int i = 0; i < size_origin; i++){
        o = origin[i];
        if(o == s){
            position_substring = i;
            iter_ori = i;
            iter_sub = 0;
            while(iter_ori < size_origin && iter_sub < size_substring && o == s){
                size_find_substring ++;
                iter_sub++;
                iter_ori++;
                s = substr[iter_sub];
                o = origin[iter_ori];
            }
            if(size_find_substring == size_substring){
                return position_substring;
            }
            position_substring = -1;
            size_find_substring = 0;
            i = iter_ori;
            s = substr[0];
        }
    }

    return -1; 
    
}