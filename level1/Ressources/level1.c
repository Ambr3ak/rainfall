#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>

int run(){
    fwrite("Good ... Wait what?", 1, 19, stdout);
    return(system("/bin/bash"));
}

int main(){

    char buff[64];
    gets(buff);
    return 0;
}