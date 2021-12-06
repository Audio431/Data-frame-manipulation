#include <stdio.h>
#include <stdlib.h>
#include "get_each_csv_value.h"
#include "count_row_col.h"

double max_column(FILE*fp,int column){
    size_t width = count_row(fp);
    double max = 0;
    for(size_t i = 0; i < width ; i++){  //get each value and store into string array
        char data[100];
        get_value_csv(fp,data,i+1,column);
        double member = strtod(data,NULL);
        if (member > max){
            max = member;
        }
        else{
            break;
        }
    }
    return max;
}
    

double min_column(FILE*fp,int column){
    size_t width = count_row(fp);
    double min = max_column(fp,column);
    for(size_t i = 0; i < width ; i++){  //get each value and store into string array
        char data[100];
        get_value_csv(fp,data,i+1,column);
        double member = strtod(data,NULL);
        if (min > member){
            min = member;
        }
    }
    return min;  
}
