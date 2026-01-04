// rx_queue.h
#ifndef RX_QUEUE_H
#define RX_QUEUE_H

#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>

#define RX_QUEUE_SIZE 1024  // Adjust size as needed

typedef struct {
    char buffer[RX_QUEUE_SIZE];
    size_t head;
    size_t tail;
    size_t count;
    pthread_mutex_t mutex;
    pthread_cond_t data_available;
    pthread_cond_t space_available;
} RxQueue;

// Queue management functions
void rx_queue_init(RxQueue* queue);
void rx_queue_destroy(RxQueue* queue);

// Data operations
bool rx_queue_push(RxQueue* queue, char data);
bool rx_queue_pop(RxQueue* queue, char* data);
bool rx_queue_read_until(RxQueue* queue, char* buffer, size_t max_len, char delimiter, size_t* bytes_read);

// Status functions
bool rx_queue_is_empty(RxQueue* queue);
bool rx_queue_is_full(RxQueue* queue);
size_t rx_queue_available_data(RxQueue* queue);

#endif // RX_QUEUE_H