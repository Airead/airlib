/**
 * @file air_timer.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/01/23 11:02:44
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/time.h>
#include "air_timer.h"
#include <limits.h>

#include "debug.h"

#if 0
struct timer_list mytimer;
init_timer (&mytimer);
mytimer.expires = jiffies + HZ/1000;
mytimer.data = 0/*or the pointer that pointing to your argument*/;
mytimer.function = /*your expireing function*/
add_timer (&mytimer);
#endif

static int is_run_val;

unsigned long air_timer_curtime(unsigned long t)
{
    struct timeval tv;
    unsigned long time;

    gettimeofday(&tv, NULL);
    time = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;

    return time + t;
}

struct air_timer_s *air_timer_new(unsigned long expires, struct air_timer_operation *ops, 
                                  void *data, unsigned long len)
{
    struct air_timer_s *at;

    at = malloc(sizeof(*at));
    if (at == NULL) {
        fprintf(stderr, "malloc failed: %s\n", strerror(errno));
        return NULL;
    }
    memset(at, 0, sizeof(*at));

    at->regtime = air_timer_curtime(0);
    at->expires = expires;
    at->ops = ops;
    at->data = at->ops->init(data, len);
    if (at->data == NULL) {
        fprintf(stderr, "air_timer_new init data failed\n");
        goto init_data_error;
    }
    at->datalen = len;

    return at;
init_data_error:
    free(at);
    return NULL;
}

static void set_run(int sig)
{
    DEBUG(stdout, "set run\n");
    is_run_val = 1;
}

static int set_signal(void)
{
    struct sigaction act, oact;

    memset(&act, 0, sizeof(act));

    act.sa_handler = set_run;
    //int sigemptyset(sigset_t *set);
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    //int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
    if (sigaction(SIGALRM, &act, &oact) < 0) {
        fprintf(stderr, "Install new signal handler for SIGINT failed: %s\n", strerror(errno));
    }

    return 0;
}

void air_timer_init(void)
{
    set_signal();
}

static int is_run(void)
{
    if (is_run_val) {
        return 1;
    } else {
        return 0;
    }
}

void air_timer_init_timer(struct air_timer_s *at)
{
    at->regtime = air_timer_curtime(0);
    at->expires = 0;
    at->ops = NULL;
    at->data = NULL;
}

int air_timer_setitimer(struct list_head *h)
{
    struct itimerval tick;
    struct list_head *_p;
    struct air_timer_s *at;
    long min_ms, tmp;

    min_ms = LONG_MAX;
    __list_for_each(_p, h) {
        at = list_entry(_p, struct air_timer_s, list);
        tmp = at->regtime + at->expires;
        if (min_ms > tmp) {
            min_ms = tmp;
        }
    }
    min_ms -= air_timer_curtime(0);
    if (min_ms <= 0) {
        DEBUG("raise(SIGALRM)\n");
        raise(SIGALRM);
    }

    if (min_ms > 0 && min_ms < LONG_MAX) {
        getitimer(ITIMER_REAL, &tick);
        DEBUG("min_ms %lu, sec %lu, usec %lu\n", 
                min_ms, tick.it_value.tv_sec, tick.it_value.tv_usec);
        if ((tick.it_value.tv_sec == 0 && tick.it_value.tv_usec == 0)
            || min_ms < tick.it_value.tv_sec * 1000 + tick.it_value.tv_usec / 1000) {
            DEBUG("setitimer\n");
            memset(&tick, 0, sizeof(tick));
            tick.it_value.tv_sec = min_ms / 1000;
            tick.it_value.tv_usec = (min_ms % 1000) * 1000;
            tick.it_interval.tv_sec = 0;
            tick.it_interval.tv_usec = 0;
            DEBUG("wait sec %lu, usec %lu\n", tick.it_value.tv_sec, tick.it_value.tv_usec);
            if (setitimer(ITIMER_REAL, &tick, NULL) < 0) {
                fprintf(stderr, "setitimer failed: %s\n", strerror(errno));
                return -1;
            }
        }
    }

    return 0;
}

int air_timer_add(struct air_timer_s *at, struct list_head *h)
{ 
    list_add(&at->list, h);

    air_timer_setitimer(h);

    return 0;
}

int air_timer_free(struct air_timer_s *at)
{
    at->ops->destroy(at->data);
    free(at);
    return 0;
}

int air_timer_run(struct list_head *h, unsigned long time)
{
    struct list_head *_p, *tmp;
    struct air_timer_s *at;
    int ret;
    int count;

    if (!is_run()) {
        return 0;
    }
    is_run_val = 0;
//    fprintf(stdout, "start to run\n");
    if (time == 0) {
        time = air_timer_curtime(0);
    }
    
    count = 0;
    list_for_each_safe(_p, tmp, h) {
        at = list_entry(_p, struct air_timer_s, list);
//        fprintf(stdout, "regtime + expires %lu, now: %lu\n", at->regtime + at->expires, time);
        if (at->regtime + at->expires <= time) { /* expired */
            count++;
            ret = at->ops->run(at->data, at->datalen);
            switch (ret) {
            case TIMER_RUNERR:
                fprintf(stderr, "run timer failed\n");
                list_del(&at->list);
                air_timer_free(at);
                break;
            case TIMER_FREE:
                list_del(&at->list);
                air_timer_free(at);
                break;
            case TIMER_CONTINUE:
                list_del(&at->list);
                at->regtime = time;
                air_timer_add(at, h);
                break;
            default:
                fprintf(stderr, "timer return val invaild\n");
                break;
            }
        }
    }

    if (ret != TIMER_CONTINUE) {
        air_timer_setitimer(h);
    }
 
    return count;
}
