#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "get_each_csv_value.h"
#include "count_row_col.h"

void display_col_row(char *value){
    
    FILE*fp = fopen("untitled.csv","r");
    size_t width = count_row(fp);
    size_t length = count_column(fp);
    size_t i;
    int row = -1;
    int col = -1;
    for (i = 0; i < width+1; i++)
    {
        for (size_t j = 0; j < length+1; j++)
        {
            char buff[100];
            get_value_csv(fp,buff,i,j);
            if (strcmp(value,buff) == 0) {
                row = i;
                col = j;
                break;
            }
        } 
    }
    if (row == -1 || col == -1){
        printf("Value is not found.");
    }
    else {
        printf("%s [row = %d col = %d]",value,row,col);
    }
}

