#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#define ABS(x) ((x) > 0 ? (x) : -(x))
#define HAND_COUNT 1000
const char strengths[13] = {'J', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'Q', 'K', 'A'};

void swap_chararr(char **left, char **right);
int get_str(char c);
int get_type(char * hand);
void swap_int(int * left, int * right);

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
    char *line = NULL;

    int res1 = 0;

    char *hands[HAND_COUNT];
    int bids[HAND_COUNT] = {0};
    size_t bids_idx = 0;
    size_t hands_idx = 0;

    while(getline(&line, &line_len, fp) != -1)
    {
        char * tok = strtok(line, " ");
        int bid = atoi(strtok(NULL, " "));

        hands[hands_idx] = malloc(sizeof(char) * 6);
        memcpy(hands[hands_idx], tok, 6); 
        hands_idx++;
        bids[bids_idx++] = bid;
    }
    for(int i = 0; i < HAND_COUNT - 1; i++)
    {
        for(int j = 0; j < HAND_COUNT - i - 1; j++)
        {
            int typei = get_type(hands[j]);
            int typej = get_type(hands[j + 1]);
            if(typei > typej)
            {
                swap_chararr(&hands[j], &hands[j + 1]);
                swap_int(bids + j + 1, bids + j);
            }
            else if(typei == typej)
            {
                //printf("%s %s\n", hands[j], hands[j+1]);
                for(int k = 0; k < 5; k++)
                {
                    if(get_str(hands[j][k]) > get_str(hands[j + 1][k]))
                    {
                        swap_chararr(&hands[j], &hands[j + 1]);
                        swap_int(bids + j + 1, bids + j);
                        break;
                    }
                    else if(get_str(hands[j][k]) < get_str(hands[j + 1][k]))
                        break;
                }
            }
        }
    }
    for(int i = 0; i < HAND_COUNT; i++)
    {
        printf("%s %d\n", hands[i], get_type(hands[i]));
        res1 += (i + 1) * bids[i];
    }

    printf("result part1: %d\n", res1);

    return 0;
}

int get_type(char * hand)
{
    int hash[37];
    int hasj = 0;
    for(int i = 0; i < 37; i++)
        hash[i] = -1;
    for(int i = 0; i < 5; i++)
    {
        if(hand[i] == 'J')
            hasj = 1;
        int hash_num = hand[i] % 37;
        hash[hash_num]++;
    }
    if (hasj)
    {
        int most_freq = -1;
        char letter;
        for(int i = 1; i < 13; i++)
        {
            if(hash[strengths[i] % 37] > most_freq)
            {
                most_freq = hash[strengths[i] % 37];
                letter = strengths[i];
            }
        }
        if( most_freq != -1 )
        {
            //printf("=hand %s = \tmf: %d, letter: %c, j_count: %d\n", hand,
            //        most_freq, letter, hash['J' % 37]);
            hash[letter % 37] += (hash['J' % 37] + 1);
            hash['J' % 37] = -1;
        }

    }


    int pairs = 0;
    int tris = 0;
    int fours = 0; 
    for(int i = 0; i < 37; i++)
    {
        if (hash[i] == 4)
            return 6;
        else if (hash[i] == 3)
            return 5;
        else if (hash[i] == 2)
            tris = 1;
        else if (hash[i] == 1)
            pairs++;
    }
    if(tris && pairs)
        return 4;
    if(tris)
        return 3;
    return pairs;
    
}

void swap_int(int * left, int * right)
{
    int temp = *left;
    *left = *right;
    *right = temp;
}
void swap_chararr(char **left, char **right)
{
    char * temp = *right;
    *right = *left;
    *left = temp;
}

int get_str(char c)
{
    for(size_t i = 0; i < 13; i++)
        if(strengths[i] == c)
            return i;
    return -1;
}

    



