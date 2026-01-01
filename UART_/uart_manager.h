//
// Created by royivri on 12/31/25.
//

#ifndef UART_MANAGER_H
#define UART_MANAGER_H
#include <bits/pthreadtypes.h>

pthread_t uart_rx_tid;
pthread_t uart_tx_tid;




void *uart_rx_thread(void *arg);
void *uart_tx_thread(void *arg);
void uart_manager();
#endif //UART_MANAGER_H
