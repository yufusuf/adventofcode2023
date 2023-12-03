#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>


#define N 140
struct loc{
    int row;
    int start;
    int end;
    int val;
};
#define LOCS_MAX 1200
int natoi(const char * str, int size);
int check_position(char map[N][N + 1], int row, int i);
int check(char map[N][N+1], int row, int start, int end);
int check_around_gear(char map[N][N+1], int star_i, int star_j, struct loc locs[], int count);
int part1(char map[N][N+1], struct loc locs[LOCS_MAX]);
void part2(char map[N][N+1], struct loc locs[LOCS_MAX], int count);

#define ABS(x) ((x) > 0 ? (x) : -(x))

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

    size_t line_len;
    char map[N][N + 1];
    int n = 0;
    while(getline(&line, &line_len, fp) != -1){
        for(int i = 0; i < N; i++)
        {
            map[n][i] = line[i];
        }
        map[n][N] = '|';
        n++;
    }
    int count;
    struct loc locs [LOCS_MAX];
    count = part1(map, locs);
    part2(map, locs, count);

    return 0;
}

int part1(char map[N][N+1], struct loc locs[LOCS_MAX])
{
    int res = 0;
    int num_start_i;
    int count = 0;
    for(int i = 0; i < N; i++)
    {
        num_start_i = -1;
        for (int j = 0; j < N + 1; j++)
        {
            if( isdigit(map[i][j])  && num_start_i == -1) 
            {
                num_start_i = j;
            }
            else if ( !isdigit(map[i][j])  && num_start_i != -1)
            {
                if( check(map, i, num_start_i, j) )
                {
                    int number_val = natoi(map[i] + num_start_i, j - num_start_i);
                    //printf("found: %d on (%d,%d)\n", number_val, i, num_start_i);
                    //for part 2
                    struct loc location;
                    location.row = i;
                    location.start = num_start_i;
                    location.end = j - 1;
                    location.val = number_val;
                    memcpy(&locs[count], &location, sizeof(location));
                    count++;
                    if(count >= LOCS_MAX){
                        printf("count > LOCS_MAX\n");
                        exit(1);
                    }

                    res += number_val;
                }
                num_start_i = -1;
            }
        }
    }
    printf("part1 res: %d\n", res);
    return count;
}

void part2(char map[N][N+1], struct loc locs[LOCS_MAX], int count)
{
    int res = 0;
    for(int i = 0; i < N; i++)
    {
        for (int j = 0; j < N+1; j++)
        {
            if(map[i][j] == '*')
            {
                int result = check_around_gear(map, i, j, locs, count);
                if ( result > 0 )
                    res += result;
            }
        }
    }
    printf("part2 res: %d\n", res);


}

int check_around_gear(char map[N][N+1], int star_i, int star_j, struct loc locs[], int count)
{
    int numbers_around = 0;
    int res = 1;
    for(int lx = 0; lx < count; lx++)
    {
        if(star_i >= locs[lx].row - 1 && star_i <= locs[lx].row + 1
                && (ABS(locs[lx].end - star_j) <= 1 || ABS(locs[lx].start - star_j) <= 1))
        {
            res *= locs[lx].val;
            numbers_around++;
        }
    }
    if(numbers_around == 2)
        return res;
    else 
        return -1;
}

int check(char map[N][N+1], int row, int start, int end)
{
    //end is not inclusive
    //if(start < end)
    //{
    //    printf("check(): start (%d) < end(%d)\n", start, end);
    //    exit(1);
    //}
    for(int i = start; i < end; i++)
    {
        if(check_position(map, row, i))
            return 1;
    }
    return 0;
}

int check_position(char map[N][N + 1], int row, int i)
{
    for(int x = row - 1; x < row + 2; x++)
    {
        for(int y = i - 1; y < i + 2; y++)
        {
            if(x >= 0 && x < N && y >= 0 && y < N)
            {
                if(map[x][y] != '.' && !isdigit(map[x][y]))
                    return 1;
            }
        }
    }
    return 0;
}

int natoi(const char * str, int size){
    int result = 0;
    for(int i = 0 ; i < size; i++){
        result = result * 10 + ((int) (str[i] - '0'));
    }
    return result;
}

