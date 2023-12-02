#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <regex.h>
#include <string.h>


int natoi(const char * str, int size);
int maxof(const char *s, char * color, regoff_t len);

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

    regex_t regex_game;
    regoff_t off, len;

    char * game = "Game [0-9]+";
    if(regcomp(&regex_game, game, REG_EXTENDED))
        exit(1);

    int res = 0;
    size_t line_len;
    while(getline(&line, &line_len, fp) != -1){

        regmatch_t match[1];
        if(regexec(&regex_game, line, sizeof(match)/sizeof(match[0]), match, 0))
            break;
        len = match[0].rm_eo - match[0].rm_so;
        int game_id = atoi(line + match[0].rm_so + strlen("Game "));

        const char *s = line;
        int maxR = maxof(s, "red", len);
        int maxB = maxof(s, "blue", len);
        int maxG = maxof(s, "green", len);
        //printf("r: %d, g: %d, b: %d\n", maxR, maxG, maxB);

        if(maxR <= 12 && maxB <= 14 && maxG <= 13)
            res += game_id;
    }
    printf("res: %d\n", res);

    return 0;
}
int maxof(const char *s, char * color, regoff_t len){
    regmatch_t match[1];
    regex_t regex;
    int max = -1;
    char re[15] = "[0-9]+ ";
    strncat(re, color, strlen(color));

    if(regcomp(&regex, re, REG_EXTENDED))
        exit(1);

    for(int i = 0; ; i++)
    {
        if(regexec(&regex, s, sizeof(match)/sizeof(match[0]), match, 0))
            break;
        len = match[0].rm_eo - match[0].rm_so;
        int current = natoi(s + match[0].rm_so, len - (strlen(color) + 1));
        if(current > max)
            max = current;
        s += match[0].rm_eo;
    }
    return max;
}

int natoi(const char * str, int size){
    int result = 0;
    for(int i = 0 ; i < size; i++){
        result = result * 10 + ((int) (str[i] - '0'));
    }
    return result;
}

