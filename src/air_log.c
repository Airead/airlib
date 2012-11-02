/**
 * @file air_log.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/08/21 13:45:17
 */

#include "air_log.h"

static struct air_log_t airlog;
static int log_level = AIR_WARN;       /* default: AIR_INFO */

int air_log_init(char *file)
{
    if (airlog.level == 0) {
        airlog.level = log_level;   
    }

    airlog.out = fopen(file, "a");
    if (airlog.out == NULL) {
        fprintf(stderr, "air_log_init %s failed: %s\n", file, strerror(errno));
        return -1;
    }

    return 0;
}

int air_log_close(void)
{
    if (airlog.out != NULL) {
        fclose(airlog.out);
    }

    return 0;
}

void air_log_set_level(int level)
{
    airlog.level = level;

}

void air_log(int level, char *fmt, ...) 
{
    va_list  args;
    FILE *out;
    char timestr[32];
    time_t t;
    struct tm *tmp;

    if (airlog.out == NULL) {
        fprintf(stderr, "waring: log not initialize\n");
        out = stdout;
    } else {
        out = airlog.out;
    }

    if (level > airlog.level) {
        goto out;
    }

    t = time(NULL);
    tmp = localtime(&t);
    if (tmp == NULL) {
        fprintf(stderr, "localtime failed\n");
        snprintf(timestr, sizeof(timestr), "get bad time ");
    }
    if (strftime(timestr, sizeof(timestr), "%Y/%m/%d %H:%M:%S", tmp) == 0) {
        fprintf(stderr, "strftime returned 0");
        snprintf(timestr, sizeof(timestr), "get bad time ");
    }

    fprintf(out, "%s ", timestr);
   
    va_start(args, fmt);
    switch (level) {
    case AIR_STDERR:
        vfprintf(stderr, fmt, args);
        break;
    case AIR_EMERG:
        fprintf(out, "[emerg] ");
        break;
    case AIR_ALERT:
        fprintf(out, "[alert] ");
        break;
    case AIR_CRIT:
        fprintf(out, "[crit] ");
        break;
    case AIR_ERR:
        fprintf(out, "[err] ");
        break;
    case AIR_WARN:
        fprintf(out, "[warn] ");
        break;
    case AIR_NOTICE:            
        fprintf(out, "[notice] ");
        break;
    case AIR_INFO:
        fprintf(out, "[info] ");
        break;
    case AIR_DEBUG:
        fprintf(out, "[debug] ");
        break;
    default:
        fprintf(stderr, "can not reach here\n");
    }
    vfprintf(out, fmt, args);
    va_end(args);
    
    fflush(out);

out:
    return ;
}
