/*
** EPITECH PROJECT, 2023
** socknet
** File description:
** test server
*/

#include <stdlib.h>
#include <stdio.h>
#include "socknet.h"

typedef struct {
    char first_name[32];
    char last_name[32];
    unsigned short age;
} user_t;

void handle_user(net_t *net, user_t *user)
{
    if (!net || !user)
        return;
    printf(
        "User %s %s, aged %d has been received\n",
        user->first_name, user->last_name, user->age
    );
}

int main(void)
{
    net_t net;
    net_transfer_t transfer = {0};
    net_status_t status = NET_OK;

    // Initialization & hosting
    if (!nets_init(&net, 4242, "server.log"))
        return 84;
    net_set_log_level(&net, DEBUG);

    // Main loop
    while ((status = net_update(&net)) == NET_OK) {
        if (nets_recv(&net, &transfer)) {
            handle_user(&net, transfer.packet.data);
            free(transfer.packet.data);
        }
    }

    // Deinitialization
    net_deinit(&net);
    return 0;
}
