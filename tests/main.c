/*
** EPITECH PROJECT, 2023
** socknet
** File description:
** test file
*/

#include "socknet.h"

int main(void)
{
    net_t net;

    nets_init(&net, 4242, "server.log");
    net_deinit(&net);
    return 0;
}
