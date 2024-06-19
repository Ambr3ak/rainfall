#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int m;

void p(char *string)
{
  printf(string);
}

void n()
{
  char buffer[512];

  fgets(buffer, sizeof(buffer), stdin);

  p(buffer);
  
  if(m == 0x01025544)
    system("/bin/cat /home/user/level5/.pass");
}

int main(void)
{
  n();
}