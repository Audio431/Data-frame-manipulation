#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


void read_csv(FILE*fp);
int count_row(FILE*fp);
int count_column(FILE*fp);
int count_row_fn(char * filename);
int count_column_fn(char * filename);
void slice_str(const char * str, char * buffer, size_t start, size_t end);
void get_value_csv(FILE*fp,char * buff,int row, int column );
double max_column(FILE*fp,int column);
double min_column(FILE*fp,int column);
double sum_column(FILE*fp,int column);
double mean_column(FILE*fp,int column);
void display_col_row(FILE*fp,char *value);

int main(){
    FILE*fp = fopen("untitled.csv","r");
    size_t column = count_column(fp);
    size_t row = count_row(fp); 
    read_csv(fp);

    printf("\n");

    printf("column = %d row = %d\n",column,row);

    char buff[10];
    get_value_csv(fp,buff,4,4);
    printf("value = %s\n",buff);

    double max = max_column(fp,4);
    printf("max = %.2f\n",max);

    double min = min_column(fp,4);
    printf("min = %.2f\n",min);

    double sum = sum_column(fp,4);
    printf("sum = %.2f\n",sum);

    double mean = mean_column(fp,4);
    printf("mean = %.2f\n",mean);

    display_col_row(fp,"400");
}



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
    char buff[2048];

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
    fseek(fp,0,SEEK_END);
    char*buff = malloc(ftell(fp));
    fseek(fp,0,SEEK_SET);
    int row = 0; 
    while (fgets(buff,1024, fp) != NULL){
        ++row;
    }

    return row-1; //not count labels
}


int count_column_fn(char * filename){
    FILE*fp = fopen(filename,"r");
    int r = 0;
    int column = 0; 
    char buff[2048];

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
    
    fseek(fp,0,SEEK_SET);
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
