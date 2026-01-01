//
// Created by royivri on 12/31/25.
//

#ifndef UART_INIT_H
#define UART_INIT_H

#define UART_READY 1
#define UART_FAIL 0
#include <signal.h>

extern  volatile sig_atomic_t uart_process_running;
int uart_init();


#endif //UART_INIT_H
