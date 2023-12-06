#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


#define ABS(x) ((x) > 0 ? (x) : -(x))



int main(int argc, char ** argv) {

    int res1 = 1;
    unsigned long long times[] = {56977875};
    unsigned long long distances[] = {546192711311139};
    for(int i = 0; i < 1; i++)
    {
        long long d = distances[i];
        long long t = times[i];
        long double delta = sqrtl(t * t - 4 * d);
        long double root1 = (t - delta)/2;
        long double root2 = (t + delta)/2;
        long long lower = ceill(root1);
        long long higher = floorl(root2);
        long long ways = ABS(higher - lower) + 1; 
        //check ends
        printf("%Lfd\n", (root1 * root1 - t * root1) + d);
        printf("%Lfd\n", (root2 * root2 - t * root2) + d);

        printf("%lld\n", (lower * lower - t * lower) + d);
        if((lower * lower - t * lower) + d >= 0)
            ways--;
        printf("%lld\n", (higher * higher - t * higher) + d);
        if((higher * higher - t * higher) + d >= 0)
            ways--;
        printf("l: %llu, h: %llu, ways:%llu\n", lower, higher, ways);
        res1 *= ways;
    }
    printf("result part1: %d\n", res1);

    return 0;
}


