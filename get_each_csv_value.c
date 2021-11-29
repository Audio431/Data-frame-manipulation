#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    buffer[j] = 0;
}

char * get_value_csv(FILE*fp,char * value,int row, int column ){

    size_t i = 0;
    size_t index_count = 0; 
    char table[1024];
    for (int c ; (c = fgetc(fp)) != EOF ;){        //find array length of delim index 
        if (c == ',' || c ==  '\n'){
           index_count++;  
        } 
        table[i++] =  c ;
    }

    int index_delim[index_count]; 
    size_t j = 0;
    for ( i = 0 ; i < strlen(table) ; i++){             //get index of delim in .csv and store to array
        if (table[i] ==  ',' || table[i] == '\n'){  
            index_delim[j++] = i; 
        }
    }
    
    char buff[1024];
    int (*count_column)(char*) = count_column;
    if (row == 0 && column == 0) {                     //slice string for get each value in table
        slice_str(table,buff,0,index_delim[column] - 1);
    }
    else {
        slice_str(table,buff,index_delim[(row*(count_column("untitle.csv")+1)+column-1)] + 1,index_delim[(row*(count_column("untitle.csv")+1))+column] -1);
    }  
    strcpy(value,buff);
    return value;
}
