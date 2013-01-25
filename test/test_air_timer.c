/**
 * @file test_air_timer.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/01/23 11:22:58
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include "air_timer.h"

LIST_HEAD(timer_head);

void *test_timer_init(void *data, unsigned long len)
{
    void *tmp;

    tmp = malloc(len);
    if (tmp == NULL) {
        return NULL;
    }

    memcpy(tmp, data, len);

    return tmp;
}

int test_timer_run(void *data, unsigned long len)
{
    int *num = data;

    fprintf(stdout, "num %d\n", *num);

    return TIMER_CONTINUE;
}

int test_timer_run_once(void *data, unsigned long len)
{
    int *num = data;

    fprintf(stdout, "num %d\n", *num);

    return TIMER_FREE;
}

int test_timer_destroy(void *data)
{
    free(data);

    return 0;
}

struct air_timer_operation test_timer_ops_continue= {
    .init = test_timer_init,
    .run = test_timer_run,
    .destroy = test_timer_destroy
};

struct air_timer_operation test_timer_ops_once= {
    .init = test_timer_init,
    .run = test_timer_run_once,
    .destroy = test_timer_destroy
};


int main(int argc, char *argv[])
{
    struct air_timer_s *at;
    int num;
    char buf[4096];

    air_timer_init();

    num = 1;
    at = air_timer_new(1000, &test_timer_ops_continue, &num, sizeof(num));
    air_timer_add(at, &timer_head);

    num = 2;
    at = air_timer_new(3000, &test_timer_ops_once, &num, sizeof(num));
    air_timer_add(at, &timer_head);

    num = 3;
    at = air_timer_new(2500, &test_timer_ops_continue, &num, sizeof(num));
    air_timer_add(at, &timer_head);

    while (1) {
        if (read(STDIN_FILENO, buf, 1) < 0) {
            fprintf(stderr, "read failed: %s\n", strerror(errno));
        }
        fprintf(stdout, "=================================\n");
        air_timer_run(&timer_head, 0);
    }
    
    return 0;
}
