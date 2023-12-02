#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>

char *numbers[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
int is_in(char * left, int size){
    int i;
    for(i = 0; i < 9; i++)
    { 
        if(strncmp(left, numbers[i], size > strlen(numbers[i]) ? size : strlen(numbers[i])) == 0)
        {
            //printf("num[%d]: %s, %d\n", i, numbers[i], size);
            return i + 1;
        }
    }
    return -1;
}
int check(int left , int right, char *str)
{
    return is_in(str + left, right - left + 1);
}



int main(int argc, char ** argv) {
    FILE *fp;
    char *line = NULL;
    if(argc < 2)
    {
        printf("supply input file name\n");
        exit(1);
    }

    fp = fopen(argv[1], "r");

    if (fp == NULL) {
        exit(1);
    }

    uint64_t res = 0;
    size_t len = 0;
    while(getline(&line, &len, fp) != -1){
        int first = -1;
        int last = -1;
        size_t line_size = strlen(line);
        int i;
        int j = 0;

        for(i = 0; i < line_size; i++) {
            char flag = 0;
            for (j = 0;  j < 5; j++)
            {
                if(j == 0 && isdigit(line[i + j]) && first == -1) {
                   first = (int)(line[i +j] - '0');
                   break;
                }
                else if (j == 0 && isdigit(line[i + j])) {
                    last = (int)(line[i +j] - '0');
                    break;
                }
                else if(j >= 2){
                    int num;
                    if( (num = check(i, i + j, line)) > 0 )
                    {
                        flag = 1;
                        if(first > 0){
                            last = num;
                        }
                        else {
                            first = num;
                        }
                    }
                    break;
                }
            }

        }
        if(first >=0 && last >= 0)
        {
            //printf("%d, %d, %s", first, last, line);
            res += last;
            res += first* 10;
        }
        else if (first >=0){
            //printf("%d, %d, %s", first, first, line);
            res+= first;
            res += 10 * first;
        }
        else
        {
            printf("ANAN\n");
        }


    }
    printf("res: %lu\n", res);

    return 0;
}
