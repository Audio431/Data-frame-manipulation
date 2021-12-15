#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "count_row_col.h"

void slice_str(const char * str, char * buffer, size_t start, size_t end) //function to slice string
{
    if (start > end){
        printf("Unable to slice between this index.");
    }
    size_t j = 0;
    for ( size_t i = start; i <= end; ++i ) {
        buffer[j++] = str[i];
    }
    buffer[j] = '\0';
}

void get_value_csv(FILE*fp,char * buff,int row, int column ){
    
    fseek(fp,0,SEEK_END);
    char *table = malloc(ftell(fp));
    fseek(fp,0,SEEK_SET); //set pointer file to the beginning
    size_t i = 0;
    size_t index_count = 0; 
    for (int c ; (c = fgetc(fp)) != EOF ;){        //find array length of delim index 
        if (c == ',' || c ==  '\n'){
           index_count++;  
        } 
        table[i++] =  c;
    }
    table[i] = '\0';

    int index_delim[index_count];
    size_t j = 0;
    for ( i = 0 ; i < strlen(table) ; i++){             //get index of delim in .csv and store to array
        if (table[i] ==  ',' || table[i] == '\n' || table[i] == '\0'){  
            index_delim[j++] = i; 
        }
    }

    const int length = count_column(fp) + 1;
    const int width = count_row(fp) + 1;
    if (row == 0 && column == 0) {                     //slice string for get each value in table
        slice_str(table,buff,0,index_delim[column] - 1);
    }
    else if  (column == 0){
        slice_str(table,buff,index_delim[((row-1)*length) + length-1]+1,index_delim[row*length + column] -1);
    }
    else if (column == length-1 && row == width-1 ){
        slice_str(table,buff,index_delim[row*length + (column-1)] + 1,strlen(table));
    }
    else {
        slice_str(table,buff,index_delim[row*length + (column-1)] + 1,index_delim[row*length + column] -1);
    }
    free(table);
}
