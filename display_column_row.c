#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "get_each_csv_value.h"
#include "count_row_col.h"

void display_col_row(FILE*fp,char *value){
    size_t width = count_row(fp)+1;
    size_t length = count_column(fp)+1;
    int row = -1;
    int col = -1;
    for (size_t i = 0; i < width; i++){
        for (size_t j = 0; j < length; j++){
            char*buff = (char*)malloc(sizeof(char)*100);
            get_value_csv(fp,buff,i,j);
            if (strcmp(value,buff) == 0){
                row = i;
                col = j;
                printf("%s [row = %d col = %d]\n",value,row,col);
            }
        } 
    }
    if (row == -1 || col == -1){
        printf("Value is not found.");
    }
}
