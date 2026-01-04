// rx_queue.c
#include "rx_queue.h"
#include <string.h>

void rx_queue_init(RxQueue* queue) {
    queue->head = 0;
    queue->tail = 0;
    queue->count = 0;
    pthread_mutex_init(&queue->mutex, NULL);
    pthread_cond_init(&queue->data_available, NULL);
    pthread_cond_init(&queue->space_available, NULL);
}

void rx_queue_destroy(RxQueue* queue) {
    pthread_mutex_destroy(&queue->mutex);
    pthread_cond_destroy(&queue->data_available);
    pthread_cond_destroy(&queue->space_available);
}

bool rx_queue_push(RxQueue* queue, char data) {
    bool success = false;

    pthread_mutex_lock(&queue->mutex);

    if (queue->count < RX_QUEUE_SIZE) {
        queue->buffer[queue->tail] = data;
        queue->tail = (queue->tail + 1) % RX_QUEUE_SIZE;
        queue->count++;
        success = true;
        pthread_cond_signal(&queue->data_available);
    }

    pthread_mutex_unlock(&queue->mutex);
    return success;
}

bool rx_queue_pop(RxQueue* queue, char* data) {
    bool success = false;

    pthread_mutex_lock(&queue->mutex);

    while (queue->count == 0) {
        pthread_cond_wait(&queue->data_available, &queue->mutex);
    }

    if (queue->count > 0) {
        *data = queue->buffer[queue->head];
        queue->head = (queue->head + 1) % RX_QUEUE_SIZE;
        queue->count--;
        success = true;
        pthread_cond_signal(&queue->space_available);
    }

    pthread_mutex_unlock(&queue->mutex);
    return success;
}

bool rx_queue_read_until(RxQueue* queue, char* buffer, size_t max_len, char delimiter, size_t* bytes_read) {
    bool found_delimiter = false;
    *bytes_read = 0;

    pthread_mutex_lock(&queue->mutex);

    while (!found_delimiter && *bytes_read < max_len) {
        while (queue->count == 0) {
            pthread_cond_wait(&queue->data_available, &queue->mutex);
        }

        char data = queue->buffer[queue->head];
        buffer[*bytes_read] = data;
        (*bytes_read)++;

        queue->head = (queue->head + 1) % RX_QUEUE_SIZE;
        queue->count--;

        if (data == delimiter) {
            found_delimiter = true;
        }
    }

    pthread_cond_signal(&queue->space_available);
    pthread_mutex_unlock(&queue->mutex);

    return found_delimiter;
}

bool rx_queue_is_empty(RxQueue* queue) {
    pthread_mutex_lock(&queue->mutex);
    bool empty = (queue->count == 0);
    pthread_mutex_unlock(&queue->mutex);
    return empty;
}

bool rx_queue_is_full(RxQueue* queue) {
    pthread_mutex_lock(&queue->mutex);
    bool full = (queue->count == RX_QUEUE_SIZE);
    pthread_mutex_unlock(&queue->mutex);
    return full;
}

size_t rx_queue_available_data(RxQueue* queue) {
    pthread_mutex_lock(&queue->mutex);
    size_t count = queue->count;
    pthread_mutex_unlock(&queue->mutex);
    return count;
}