#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>


#define CANDIDATE_SIZE 10   
#define WINNERS_SIZE 25
#define TOTAL_CARDS 197
#define ABS(x) ((x) > 0 ? (x) : -(x))

int natoi(const char * str, int size);
int is_winner(int cand, int winners[]);


int main(int argc, char ** argv) {
    FILE *fp;
    if(argc < 2)
    {
        printf("supply input file name\n");
        exit(1);
    }

    fp = fopen(argv[1], "r");

    if (fp == NULL) {
        exit(1);
    }

    size_t line_len;
    int read_n = 0;
    char *line = NULL;
    const size_t card_len = strlen("Card ");
    int candidates[CANDIDATE_SIZE] = {0};
    int winners[WINNERS_SIZE] = {0};
    int res1 = 0;
    int copies[TOTAL_CARDS + 1];
    for(int i = 0 ; i < TOTAL_CARDS + 1; i++)
        copies[i] = 1;
    while(getline(&line, &line_len, fp) != -1){
        char *token = strtok(line, ":");
        int card_id = atoi(token + card_len);

        size_t candidate_i = 0;
        size_t winner_i = 0;
        while(token)
        {
            int number = atoi(token);

            if( number > 0 && candidate_i < CANDIDATE_SIZE)
            {
                candidates[candidate_i] = number;
                candidate_i++;
            }
            else if( number > 0 )
            {
                winners[winner_i] = number;
                winner_i++;
            }

            token = strtok(NULL, " ");
        }
        int reward = 0;
        for(int i = 0; i < CANDIDATE_SIZE; i++)
        {
            int cand = candidates[i];
            if(is_winner(cand, winners))
                reward++;

        }
        if(reward > 0){
            res1 += (1 <<(reward - 1));
            int factor = copies[card_id]; 
            for(int i = card_id + 1; i <= card_id + reward; i++)
                copies[i] += (factor);
        }
    }

    int res2 = 0;
    for(int i = 1; i < TOTAL_CARDS + 1; i++)
    {
        printf("%d\n", copies[i]);
        res2 += copies[i];
    }

    printf("result part1: %d\n", res1);
    printf("result part2: %d\n", res2);

    return 0;
}
int is_winner(int cand, int winners[])
{
    for(int i = 0; i < WINNERS_SIZE; i++)
    {
        if(winners[i] == cand)
            return 1;
    }
    return 0;
}


