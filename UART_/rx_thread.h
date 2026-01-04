//
// Created by royivri on 1/1/26.
//

#ifndef RX_THREAD_H
#define RX_THREAD_H
#include "rx_queue.h"


extern RxQueue rx_queue;


void* rx_thread(void *args);
#endif //RX_THREAD_H
