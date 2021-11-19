#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(){

    FILE* fp = fopen("/Users/User/OneDrive/Desktop/WORK/untitled.csv", "r");
    if (fp == NULL){
        perror("Unable to open the file.");
        exit(1);
    }

    int row = 0; 
    int column = 0; 
    char buffer[2048];
    int i;
    while (fgets(buffer,2048, fp) != NULL){
        ++row;
        if (row == 1){
            for(i = 0 ; i < strlen(buffer); i++){
                if(buffer[i] == ','){
                    column++;
                }
            }
        }
    }
    printf("Row: %d Column: %d", row-1 , column); //not count index column and labels
    return 0;
}