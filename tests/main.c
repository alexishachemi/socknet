/*
** EPITECH PROJECT, 2023
** socknet
** File description:
** test file
*/

#include "socknet.h"

int main(void)
{
    logger_t logger;

    init_enabled_logger(&logger, "test.log");
    LOG(&logger, INFO, "Hello, world!");
    deinit_logger(&logger);
    return 0;
}
