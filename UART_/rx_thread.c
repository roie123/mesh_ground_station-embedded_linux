//
// Created by royivri on 1/1/26.
//

#include "rx_thread.h"

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "rx_queue.h"
#include "uart_globals.h"

void* rx_thread(void* arg) {
    unsigned char rx_buffer[256];
    ssize_t bytes_read;

    while (uart_process_running) {
        // Read data from UART
        bytes_read = read(uart_fd, rx_buffer, sizeof(rx_buffer));

        if (bytes_read > 0) {
            // Process received data
            for (ssize_t i = 0; i < bytes_read; i++) {
                if (!rx_queue_push(&rx_queue, rx_buffer[i])) {
                    fprintf(stderr, "RX queue full, data lost!\n");
                    break;
                }
            }
        } else if (bytes_read < 0) {
            if (errno != EAGAIN && errno != EWOULDBLOCK) {
                fprintf(stderr, "UART read error: %s\n", strerror(errno));
                break;
            }
            usleep(1000);
        }
    }

    return NULL;
}

