#include <stdlib.h>
#include <stdio.h>
#define STRING_UTILS_H

char* duplicateString(const char *src){
    int len=0;

    while(src[len]!='\0'){
        len++;
    }

    //allocate memory on the heap
    char *copy=(char *)malloc(len+1);
    if(copy==NULL){
        printf("failed to allocate memory");
        return NULL;
    }

    for(int i=0;i<len;i++){
        copy[i]=src[i];
    }
    copy[len]='\0';
    
    
    return copy;


}

