/*
** EPITECH PROJECT, 2024
** socknet
** File description:
** logging utils
*/

#include "socknet.h"

bool net_set_log_level(net_t *net, log_level_t lvl)
{
    if (net)
        return logger_set_level(&net->logger, lvl);
    return false;
}
