#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <limits.h>

void stringParseHelper (char *array, char *tokens[], int *sz);

int main()
{
    char *exit[128];
    char buf[128];
    int sz;
    printf("Hello World!\n");
    while (stdin != NULL){
        if (fgets(buf, CHAR_MAX, stdin) != NULL){
            //printf("%s\n", buf);
            stringParseHelper(buf, exit, &sz);
            printf("%d", sz);
            for (int k = 0; k < sz; k++){
                printf("%s\n", exit[k]);
            }
        } else{
            printf("Error.");
            break;
        }
    }
    return 0;
}


void stringParseHelper (char *array, char *tokens[], int *sz){
    int size = 0;
    int word_len = 0;
    char tokenArray[128];

    for (unsigned i = 0; i < strlen(array); i++){

        if (array[i] == ' ' || array[i] == '\0' || array[i] == '\n'){
            tokenArray[word_len] = '\0';

            tokens[size] = tokenArray;
            //printf("ta %s", tokenArray);
            //printf("to %s", tokens[size]);
            size++;
            word_len = 0;
        }
        else{
            tokenArray[word_len] = array[i];
            //printf("te %c", tokenArray[word_len]);
            word_len++;
        }
    }
    *sz = size;
    //printf("%d", size);
}
