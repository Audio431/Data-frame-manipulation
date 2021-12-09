#include <stdio.h>
#include <stdlib.h>
#include "get_each_csv_value.h"
#include "count_row_col.h"

double sum_column(FILE*fp,int column){
    size_t width = count_row(fp);
    double sum;
    for(size_t i = 0; i < width ; i++){  //get each value and store into string array
        char data[100];
        get_value_csv(fp,data,i+1,column);
        double member = strtod(data,NULL);
        sum += member;
    }
    return sum;
}
    

double mean_column(FILE*fp,int column){
    size_t width = count_row(fp);
    return sum_column(fp,column) / width;
}

