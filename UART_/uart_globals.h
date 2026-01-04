//
// Created by royivri on 1/4/26.
//

#ifndef UART_GLOBALS_H
#define UART_GLOBALS_H
#include <signal.h>
#include "rx_queue.h"

extern volatile sig_atomic_t uart_process_running;
extern int uart_fd;
extern RxQueue rx_queue;

#endif //UART_GLOBALS_H
