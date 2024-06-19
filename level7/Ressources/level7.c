#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

char c[68];

void m()
{
    printf("%s - %d\n", c, time(0));
}

int main(int argc, char **argv)
{
    int *buf1 = malloc(8);
    *buf1 = 1;
    buf1[1] = malloc(8);
    int *buf2 = malloc(8);
    *buf2 = 2;
    buf2[1] = malloc(8);
    
    strcpy((char*)buf1[1], argv[1]);
    strcpy((char*)buf2[1], argv[2]);

    fgets(c, 68, fopen("/home/user/level8/.pass", "r"));
    puts("~~");
    return(0);
}