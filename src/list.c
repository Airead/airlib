/**
 * @file list.c
 * @brief 
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2012/10/17 17:05:42
 *
 * come from kernel source code
 */

#include <stdlib.h>
#include <string.h>
#include "list.h"

int list_init(struct list_head *h, unsigned long size, unsigned long len)
{
    int i;
    struct list_head *list;

    for (i = 0; i < len; i++) {
        if ((list = malloc(size)) == NULL) {
            goto failed;
        }
        memset(list, 0, size);
        list_add(list, h);
    }

    return i;
failed:
    list_free(h);
    return -1;
}

void list_free(struct list_head *h)
{
    struct list_head *_p, *tmp;
    
    list_for_each_safe(_p, tmp, h) {
        free(_p);
    }
}

struct list_head *list_loop_get_next(struct list_head *list, struct list_head *h)
{
    struct list_head *_p;

    _p = list->next;
    if (_p == h) {
        _p = h->next;
    }

    return _p;
}
