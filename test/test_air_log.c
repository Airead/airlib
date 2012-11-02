/**
 * @file test_air_log.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/11/02 15:27:25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "air_log.h"

int main(int argc, char *argv[])
{
    if (air_log_init("test_air_log.log") < 0) {
        fprintf(stderr, "air_log_init failed\n");
        exit(1);
    }
    
    air_log(AIR_NOTICE, "==============start air_log test: level default============\n");
    air_log(AIR_STDERR, "test stderr\n");
    air_log(AIR_EMERG, "test emerg\n");
    air_log(AIR_ALERT, "test alert\n");
    air_log(AIR_CRIT, "test crit\n");
    air_log(AIR_ERR, "test err\n");
    air_log(AIR_WARN, "test warn\n");
    air_log(AIR_NOTICE, "test notice\n");
    air_log(AIR_INFO, "test info\n");
    air_log(AIR_DEBUG, "test debug\n");
    
    air_log_set_level(8);
    air_log(AIR_NOTICE, "\n==============start air_log test: level 0============\n");
    air_log(AIR_STDERR, "test stderr\n");
    air_log(AIR_EMERG, "test emerg\n");
    air_log(AIR_ALERT, "test alert\n");
    air_log(AIR_CRIT, "test crit\n");
    air_log(AIR_ERR, "test err\n");
    air_log(AIR_WARN, "test warn\n");
    air_log(AIR_NOTICE, "test notice\n");
    air_log(AIR_INFO, "test info\n");
    air_log(AIR_DEBUG, "test debug\n");
    air_log(AIR_NOTICE, "==============air_log test over============\n");

    air_log_close();
    return 0;
}


