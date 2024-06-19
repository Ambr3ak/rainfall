#define _GNU_SOURCE
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int ac, char **av){

    char *arg = av[1];
    (void)ac;

    if (atoi(arg) == 423){
       
        char *shell[] = {"/bin/sh", 0};
        char *sh = strdup("/bin/sh");
    
        gid_t gid;
        uid_t uid;
        gid = getegid();
        uid = geteuid();

        setresgid(gid, gid, gid);
        setresuid(uid, uid, uid);

        execve(sh, shell, 0);
    }
    else{

        char str[] = "No !";
        fwrite(str, 1, sizeof(str), stderr);
        exit (0);
    }
}