#include <string.h>
#include <stdio.h>

void read_csv(FILE*fp){
    fseek(fp,0,SEEK_SET);
    char line[200];

    while(fgets(line, sizeof(line), fp)){
        char * token;
        
        token = strtok(line, ",");

        while(token != NULL){
            printf("%-10s",token);
            token = strtok(NULL, ",");
        }

        printf("\n");       
    }
}