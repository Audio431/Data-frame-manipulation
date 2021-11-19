#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void read_csv(char filename[100]){

    size_t len = strlen(filename);
    if (len > 0 && filename[len - 1] == '\0'){
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

}