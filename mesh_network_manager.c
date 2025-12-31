//
// Created by royivri on 12/31/25.
//

#include "mesh_network_manager.h"

#include <signal.h>
#include <stdio.h>

void mesh_network_handle_signal(int signal){


}

int main(int argc, char *argv[]) {
signal(SIGINT, mesh_network_handle_signal);


printf("network manager started\n");
return 1;
}
