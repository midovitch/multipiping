#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {

    int pa;
    int apipe[2];
    pid_t pid;
    char *cmd[2][3];

    cmd[0][0] = "ps";   cmd[0][1] = "-axu";     cmd[0][2] = NULL;
    cmd[1][0] = "grep"; cmd[1][1] = "root"; cmd[1][2] = NULL;

    pipe (apipe);
    pa = fork();
    if ((pid= fork())==-1){
        perror("fork");
        exit(1);

    }
    if ((pid=fork())==0) {
        close (apipe[1]);
        dup2 (apipe[0], 0);
        close (apipe[0]);
        execvp (cmd[1][0],cmd[1]);
        perror ("Child exec failed!\n");
        exit (1);
    } else {
        close (apipe[0]);
        dup2 (apipe[1], 1);
        close (apipe[1]);

        execvp (cmd[0][0], cmd[0]);
        perror ("Parent exec failed!\n");
        exit (1);
    }

    return 0;
}
