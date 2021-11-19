#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){

    char filename[100];
    printf("Enter your .csv file location.: ");
    fgets(filename, 15, stdin);
    size_t len = strlen(filename);
    if (len > 0 && filename[len - 1] == '\n'){
    filename[len - 1] = '\0';
    }

    FILE* file = fopen(filename,"r");
    if (file == NULL){
        perror("Unable to open the file.");
        exit(1);
    }

    char line[200];
    
    while(fgets(line, sizeof(line), file)){
        char * token;
        
        token = strtok(line, ",");

        while(token != NULL){
            printf("%-10s",token);
            token = strtok(NULL, ",");
        }

        printf("\n");       
    }

    fclose(file);
    return 0;
}