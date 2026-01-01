//
// Created by royivri on 1/1/26.
//

#include "main.h"

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include "termios.h"
#include "rx_thread.h"
#include "tx_thread.h"
#include "uart_init.h"
#include <pthread.h>


void handle_signal_uart(int sig) {
    uart_process_running = 0;
}
int main(int argc, char *argv[]) {
    signal(SIGINT, handle_signal_uart);
    signal(SIGTERM, handle_signal_uart);

    int fd = uart_init("/dev/ttyS1", B115200);  // or your uart_init function
    if (fd < 0) {
        perror("uart_init failed");
        return 1;
    }

    pthread_t rx_tid, tx_tid;

    pthread_create(&rx_tid, NULL, rx_thread, &fd);
    pthread_create(&tx_tid, NULL, tx_thread, &fd);

    // Wait for threads to finish (when running = 0)
    pthread_join(rx_tid, NULL);
    pthread_join(tx_tid, NULL);

    close(fd);
    printf("UART manager exiting\n");




    while (uart_process_running) {






        sleep(1);
    }
}
