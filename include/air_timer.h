
#ifndef _AIR_TIMER_H_
#define _AIR_TIMER_H_

#include "list.h"

enum timer_retval {
    TIMER_FREE,
    TIMER_CONTINUE,
    TIMER_RUNERR,
};

typedef void *(*air_timer_callback_init)(void *data, unsigned long len);
typedef int (*air_timer_callback_run)(void *data, unsigned long len);
typedef int (*air_timer_callback_destroy)(void *data);

struct air_timer_operation {
    air_timer_callback_init init;
    air_timer_callback_run run;
    air_timer_callback_destroy destroy;
};

struct air_timer_s {
    struct list_head list;
    unsigned long regtime;
    unsigned long expires;
    struct air_timer_operation *ops;
    unsigned long datalen;
    void *data;
};

unsigned long air_timer_curtime(unsigned long t);
struct air_timer_s *air_timer_new(unsigned long expires, struct air_timer_operation *ops, 
                                  void *data, unsigned long len);
void air_timer_init_timer(struct air_timer_s *at);
void air_timer_init(void);
int air_timer_add(struct air_timer_s *at, struct list_head *h);
int air_timer_free(struct air_timer_s *at);
int air_timer_run(struct list_head *h, unsigned long time);

#endif /* _AIR_TIMER_H_ */
