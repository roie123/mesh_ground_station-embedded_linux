//
// Created by royivri on 1/1/26.
//

#include "tx_thread.h"

#include <signal.h>
#include <string.h>
#include <unistd.h>
extern  volatile sig_atomic_t uart_process_running;
void* tx_thread(void* arg) {
    int fd = *(int*)arg;
    const char* msg = "Hello from TX\n";

    while (uart_process_running) {
        write(fd, msg, strlen(msg));
        sleep(1);  // send every second
    }

    return NULL;
}
