#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count_row(FILE*fp){
    fseek(fp,0,SEEK_SET);
    int row = 0; 
    char buffer[1024];
    while (fgets(buffer,1024, fp) != NULL){
        ++row;
    }

    return row-1; //not count labels
}

int count_column(FILE*fp){
    fseek(fp,0,SEEK_SET);
    int r = 0;
    int column = 0; 
    char buff[1024];

    while (fgets(buff,1024, fp) != NULL){
        ++r;
        if (r == 1){
            for(size_t i = 0 ; i < strlen(buff); i++){
                if(buff[i] == ','){
                    column++;
                }
            }
        }
    }
    return column; //not count index column 
}

int count_row_fn(char * filename){
    FILE*fp = fopen(filename,"r");
    int row = 0; 
    char buffer[1024];
    while (fgets(buffer,1024, fp) != NULL){
        ++row;
    }

    return row-1; //not count labels
}


int count_column_fn(char * filename){
    FILE*fp = fopen(filename,"r");
    int r = 0;
    int column = 0; 
    char buff[1024];

    while (fgets(buff,1024, fp) != NULL){
        ++r;
        if (r == 1){
            for(size_t i = 0 ; i < strlen(buff); i++){
                if(buff[i] == ','){
                    column++;
                }
            }
        }
    }
    return column; //not count index column 
}
