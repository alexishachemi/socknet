/*
** EPITECH PROJECT, 2023
** socknet
** File description:
** test client
*/

#include <stdlib.h>
#include <string.h>
#include "socknet_dev.h"

typedef struct {
    char first_name[32];
    char last_name[32];
    unsigned short age;
} user_t;

bool prompt_user(user_t *user_buf)
{
    char buf[32] = {0};
    int bytes_read = 0;

    if (!user_buf)
        return false;
    memset(user_buf, 0, sizeof(user_t));
    printf("Enter your first name: ");
    fflush(stdout);
    bytes_read = read(0, buf, 32);
    if (bytes_read < 0)
        return false;
    buf[bytes_read - 1] = 0;
    memcpy(&user_buf->first_name, buf, bytes_read);
    printf("Enter your last name: ");
    fflush(stdout);
    bytes_read = read(0, buf, 32);
    if (bytes_read < 0)
        return false;
    buf[bytes_read - 1] = 0;
    memcpy(&user_buf->last_name, buf, bytes_read);
    printf("Enter your age: ");
    fflush(stdout);
    bytes_read = read(0, buf, 32);
    if (bytes_read < 0)
        return false;
    buf[bytes_read - 1] = 0;
    user_buf->age = atoi(buf);
    printf("\n");
    return true;
}

int main(void)
{
    net_t net;
    net_transfer_t transfer = {0};
    net_status_t status = NET_OK;
    user_t user = {0};

    // Initialization & connection
    if (!netc_init(&net, 4041, "client.log"))
        return 84;
    net_set_log_level(&net, DEBUG);
    if (!netc_connect(&net, "127.0.0.1", 4242))
        return 84;

    // Main loop
    while ((status = net_update(&net)) == NET_OK) {
        
        // sending
        prompt_user(&user);
        netc_send(&net, &user, sizeof(user_t));

        // receiving
        if (netc_recv(&net, &transfer)) {
            write(1, transfer.packet.data, transfer.packet.header.data_size);
            free(transfer.packet.data);
        }

    }

    // Deinitialization
    net_deinit(&net);
    return 0;
}
