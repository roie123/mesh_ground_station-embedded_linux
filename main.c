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
#include "UART_/uart_init.h"
#define BUF_SIZE 128

static volatile sig_atomic_t running = 1;

void handle_signal(int sig) {
    running = 0;
}

int main(void) {
    // uart_init();
    pid_t original_pid = getpid();

    if (getpid() == original_pid) {
        int pid1 = fork();
        if (pid1 == 0) {
            execlp("./packet_router", "mesh_network_manager", NULL);
            perror("execlp packet router failed ");
            _exit(1);
        }

        int pid2 = fork();
        if (pid2 == 0) {
            execlp("./uart_manager", "uart_manager", NULL);
            perror("execlp uart_manager failed");
            _exit(1);
        }
    }


    while (1) {
    }
}
