#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>
#include <syslog.h>

#define BUF_SIZE 128

static volatile sig_atomic_t running = 1;

void handle_signal(int sig) {
    running = 0;
}

int main(void) {

    int pid = fork();
    if (pid == 0) {
        execlp("./mesh_network_manager", "mesh_network_manager", NULL);
    }



    while (1) {

    }


}
