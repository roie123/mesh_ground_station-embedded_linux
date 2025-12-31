//
// Created by royivri on 12/31/25.
//

#ifndef PACKET_ROUTER_H
#define PACKET_ROUTER_H

extern volatile static int running;

void packet_router_handle_signal(int signal);
void packet_router_process();



#endif //PACKET_ROUTER_H
