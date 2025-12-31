//
// Created by royivri on 12/31/25.
//

#include "packet_router.h"

#include <signal.h>
void  packet_router_handle_signal() {

}

void packet_router_process() {
signal(SIGINT, packet_router_handle_signal);


}
