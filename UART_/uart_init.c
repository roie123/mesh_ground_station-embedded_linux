//
// Created by royivri on 12/31/25.
//

#include "uart_init.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>      // open()
#include <termios.h>    // UART configuration
#include <errno.h>
#include <signal.h>
#include <string.h>
#include "uart_globals.h"


void handle_signal(int sig) {
    uart_process_running = 0;
}
/**
 * Initialize UART on BeagleBone Green
 * @param device: UART device, e.g., "/dev/ttyS1"
 * @param baudrate: 9600, 115200, etc.
 * @return file descriptor for UART, or -1 on error
 */
int uart_init(const char *device, int baudrate) {
    int fd = open(device, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1) {
        perror("Failed to open UART");
        return UART_FAIL;
    }

    // Clear O_NDELAY so read() will block until data arrives
    fcntl(fd, F_SETFL, 0);

    // Configure UART
    struct termios options;
    if (tcgetattr(fd, &options) != 0) {
        perror("tcgetattr failed");
        close(fd);
        return UART_FAIL;
    }

    // Set input and output baud rates
    speed_t speed;
    switch (baudrate) {
        case 9600: speed = B9600; break;
        case 19200: speed = B19200; break;
        case 38400: speed = B38400; break;
        case 57600: speed = B57600; break;
        case 115200: speed = B115200; break;
        default:
            fprintf(stderr, "Unsupported baudrate %d, defaulting to 9600\n", baudrate);
            speed = B9600;
    }

    cfsetispeed(&options, speed);
    cfsetospeed(&options, speed);

    // 8N1 mode: 8 data bits, no parity, 1 stop bit
    options.c_cflag &= ~PARENB;   // no parity
    options.c_cflag &= ~CSTOPB;   // 1 stop bit
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;       // 8 bits

    // Enable receiver, ignore modem control lines
    options.c_cflag |= (CLOCAL | CREAD);

    // Raw input/output
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // raw input
    options.c_iflag &= ~(IXON | IXOFF | IXANY);         // no flow control
    options.c_oflag &= ~OPOST;                          // raw output

    // Apply settings immediately
    if (tcsetattr(fd, TCSANOW, &options) != 0) {
        perror("tcsetattr failed");
        close(fd);
        return -1;
    }

    uart_fd = fd;
    uart_process_running = 1;

    return fd;
}