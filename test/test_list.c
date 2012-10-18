/**
 * @file list_test.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/10/17 17:10:29
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "list.h"

struct example_head {
    int i;
    double d;
    char str[64];
    struct list_head list;
};

static struct example_head *example_create(int i, double d, char *str)
{
    struct example_head *e;

    e = malloc(sizeof(struct example_head));
    if (e == NULL) {
        fprintf(stderr, "malloc failed: %s\n", strerror(errno));
        return NULL;
    }

    e->i = i;
    e->d = d;
    strncpy(e->str, str, 64 - 1);

    return e;
}

int main(int argc, char *argv[])
{
    struct example_head *e;
    struct list_head *_p;

    fprintf(stdout, "list initialize....\n");
    LIST_HEAD(eh);

    if (list_empty(&eh)) {
        fprintf(stdout, "list is empty\n");
    }

    e = example_create(1, 1.1, "str 1.1");
    fprintf(stdout, "list_add(1)\n");
    list_add(&e->list, &eh);
    e = example_create(2, 2.2, "str 2.2");
    fprintf(stdout, "list_add(2)\n");
    list_add(&e->list, &eh);
    e = example_create(3, 3.3, "str 3.3");
    fprintf(stdout, "list_add(3)\n");
    list_add(&e->list, &eh);
    e = example_create(4, 4.4, "str 4.4");
    fprintf(stdout, "list_add(4)\n");
    list_add(&e->list, &eh);

    fprintf(stdout, "=================================\n");
    __list_for_each(_p, &eh) {
        e = list_entry(_p, struct example_head, list);
        fprintf(stdout, "%d, %.2f, %s\n", e->i, e->d, e->str);
    }

    /* delete 3 */
    fprintf(stdout, "delete 3\n");
    __list_for_each(_p, &eh) {
        e = list_entry(_p, struct example_head, list);
        if (e->i == 3) {
            list_del(_p);
            free(e);
            break;
        }
    }

    fprintf(stdout, "=================================\n");
    __list_for_each(_p, &eh) {
        e = list_entry(_p, struct example_head, list);
        fprintf(stdout, "%d, %.2f, %s\n", e->i, e->d, e->str);
    }

    e = example_create(6, 6.6, "str 6.6");
    fprintf(stdout, "list_add_tail(6)\n");
    list_add_tail(&e->list, &eh);

    fprintf(stdout, "=================================\n");
    __list_for_each(_p, &eh) {
        e = list_entry(_p, struct example_head, list);
        fprintf(stdout, "%d, %.2f, %s\n", e->i, e->d, e->str);
    }

    /* print reverse */
    fprintf(stdout, "=================================\n");
    fprintf(stdout, "print by reverse\n");
    __list_for_each_reverse(_p, &eh) {
        e = list_entry(_p, struct example_head, list);
        fprintf(stdout, "%d, %.2f, %s\n", e->i, e->d, e->str);
    }
    return 0;
}
