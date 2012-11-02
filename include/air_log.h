/**
 * @file air_log.h
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/08/21 13:46:58
 */

#ifndef _AIR_LOG_H_
#define _AIR_LOG_H_

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <stdarg.h>

#define AIR_STDERR            0
#define AIR_EMERG             1
#define AIR_ALERT             2
#define AIR_CRIT              3
#define AIR_ERR               4
#define AIR_WARN              5
#define AIR_NOTICE            6
#define AIR_INFO              7
#define AIR_DEBUG             8

struct air_log_t {
    int level;
    FILE *out;
};

int air_log_init(char *file);
int air_log_close(void);
void air_log_set_level(int level);
void air_log(int level, char *fmt, ...);

#endif /* _AIR_LOG_H_ */
