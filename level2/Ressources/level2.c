#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void p(){

    char buffer[76];
    unsigned int ret;
    fflush(stdout);
  
    gets(buffer);
  
    if((ret & 0xb0000000) == 0xb0000000) {
        printf("(%p)\n", ret);
        exit(1);
    }

    puts(buffer);
    strdup(buffer);
}
int main(void){
    p();

    return 0;
}