cmake_minimum_required(VERSION 3.16)
project(ground_station C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# -----------------------------
# Ground station process
# -----------------------------
add_executable(ground_station
        main.c
)

# -----------------------------
# Packet router
# -----------------------------
add_executable(packet_router Packet_Router/main.c)

# -----------------------------
# UART manager process
# -----------------------------
add_executable(uart_manager
        UART_/main.c
        UART_/uart_init.c
        UART_/rx_thread.c
        UART_/tx_thread.c
)

target_include_directories(uart_manager PRIVATE UART_)
target_link_libraries(uart_manager pthread)
