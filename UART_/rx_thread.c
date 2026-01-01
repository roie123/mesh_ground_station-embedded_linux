//
// Created by royivri on 1/1/26.
//

#include "rx_thread.h"

#include <signal.h>
#include <stdio.h>
#include <unistd.h>


extern  volatile sig_atomic_t uart_process_running;
void* rx_thread(void* arg) {
    int fd = *(int*)arg;
    char buf[128];

    while (uart_process_running) {
        int n = read(fd, buf, sizeof(buf) - 1);
        if (n > 0) {
            buf[n] = '\0';
            printf("[RX] %s\n", buf);  // or process the data
        }
        usleep(1000);  // small delay to avoid 100% CPU
    }

    return NULL;
}
