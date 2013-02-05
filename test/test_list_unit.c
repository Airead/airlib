/**
 * @file test_list_unit.c
 * @brief
 * @author Airead Fan <fgh1987168@gmail.com>
 * @date 2013/02/04 15:16:12
 */

#include <lcut.h>
#include "list.h"

struct node_s {
    struct list_head list;
    int i;
    char *str;
    float f;
};

LIST_HEAD(head_for_entry);
struct node_s nodes[3] = {
    {
            LIST_HEAD_INIT(nodes[0].list),
            1, "first", 1.1,
    },
    {
        LIST_HEAD_INIT(nodes[1].list),
        2, "second", 2.2,
    },
    {
        LIST_HEAD_INIT(nodes[2].list),
        3, "third", 3.3,
    },
};
static const int nodes_len = sizeof(nodes) / sizeof(struct node_s);

static void new_list_for_test_xxx_entry(void)
{
    int i;

    INIT_LIST_HEAD(&head_for_entry);
    for (i = 0; i < nodes_len; i++) {
        list_add_tail(&nodes[i].list, &head_for_entry);
    }
}

static void tc_LIST_HEAD_INIT(lcut_tc_t *tc, void *data)
{
    struct list_head head = LIST_HEAD_INIT(head);

    LCUT_PTR_EQUAL(tc, &head, head.next);
    LCUT_PTR_EQUAL(tc, &head, head.prev);
}

static void tc_LIST_HEAD(lcut_tc_t *tc, void *data)
{
    LIST_HEAD(head);

    LCUT_PTR_EQUAL(tc, &head, head.next);
    LCUT_PTR_EQUAL(tc, &head, head.prev);
}

static void tc_INIT_LIST_HEAD(lcut_tc_t *tc, void *data)
{
    struct list_head head;

    INIT_LIST_HEAD(&head);
    LCUT_PTR_EQUAL(tc, &head, head.next);
    LCUT_PTR_EQUAL(tc, &head, head.prev);
}

static void tc___list_add(lcut_tc_t *tc, void *data)
{
    LIST_HEAD(head);
    struct list_head new1, new2;

    /* +------+      +------+
     * | head |<---->| new1 |<---+
     * +------+      +------+    |
     *     ^                     |
     *     +---------------------+ */
    __list_add(&new1, head.prev, head.next);
    LCUT_PTR_EQUAL(tc, head.prev, &new1);
    LCUT_PTR_EQUAL(tc, head.next, &new1);
    LCUT_PTR_EQUAL(tc, new1.prev, &head);
    LCUT_PTR_EQUAL(tc, new1.next, &head);

    /* +------+      +------+      +------+
     * | head |<---->| new2 |----->| new1 |<---+
     * +------+      +------+      +------+    |
     *     ^                                   |
     *     +-----------------------------------+ */
    __list_add(&new2, new1.prev, &new1);
    LCUT_PTR_EQUAL(tc, head.next, &new2);
    LCUT_PTR_EQUAL(tc, head.prev, &new1);
    LCUT_PTR_EQUAL(tc, new2.prev, &head);
    LCUT_PTR_EQUAL(tc, new2.next, &new1);
    LCUT_PTR_EQUAL(tc, new1.prev, &new2);
    LCUT_PTR_EQUAL(tc, new1.next, &head);
}

static void tc_list_add(lcut_tc_t *tc, void *data)
{
    LIST_HEAD(head);
    struct list_head new1, new2;

    /* +------+      +------+
     * | head |<---->| new1 |<---+
     * +------+      +------+    |
     *     ^                     |
     *     +---------------------+ */
    list_add(&new1, &head);
    LCUT_PTR_EQUAL(tc, head.prev, &new1);
    LCUT_PTR_EQUAL(tc, head.next, &new1);
    LCUT_PTR_EQUAL(tc, new1.prev, &head);
    LCUT_PTR_EQUAL(tc, new1.next, &head);

    /* +------+      +------+      +------+
     * | head |<---->| new2 |----->| new1 |<---+
     * +------+      +------+      +------+    |
     *     ^                                   |
     *     +-----------------------------------+ */
    list_add(&new2, &head);
    LCUT_PTR_EQUAL(tc, head.next, &new2);
    LCUT_PTR_EQUAL(tc, head.prev, &new1);
    LCUT_PTR_EQUAL(tc, new2.prev, &head);
    LCUT_PTR_EQUAL(tc, new2.next, &new1);
    LCUT_PTR_EQUAL(tc, new1.prev, &new2);
    LCUT_PTR_EQUAL(tc, new1.next, &head);
}

static void tc_list_add_tail(lcut_tc_t *tc, void *data)
{
    LIST_HEAD(head);
    struct list_head new1, new2;

    /* +------+      +------+
     * | head |<---->| new1 |<---+
     * +------+      +------+    |
     *     ^                     |
     *     +---------------------+ */
    list_add_tail(&new1, &head);
    LCUT_PTR_EQUAL(tc, head.prev, &new1);
    LCUT_PTR_EQUAL(tc, head.next, &new1);
    LCUT_PTR_EQUAL(tc, new1.prev, &head);
    LCUT_PTR_EQUAL(tc, new1.next, &head);

    /* +------+      +------+      +------+
     * | head |<---->| new1 |----->| new2 |<---+
     * +------+      +------+      +------+    |
     *     ^                                   |
     *     +-----------------------------------+ */
    list_add_tail(&new2, &head);
    LCUT_PTR_EQUAL(tc, head.next, &new1);
    LCUT_PTR_EQUAL(tc, head.prev, &new2);
    LCUT_PTR_EQUAL(tc, new1.prev, &head);
    LCUT_PTR_EQUAL(tc, new1.next, &new2);
    LCUT_PTR_EQUAL(tc, new2.prev, &new1);
    LCUT_PTR_EQUAL(tc, new2.next, &head);
}

static void tc___list_del(lcut_tc_t *tc, void *data)
{
    LIST_HEAD(head);
    struct list_head new1, new2, new3;

    list_add_tail(&new1, &head);
    list_add_tail(&new2, &head);
    list_add_tail(&new3, &head);
    /* +------+      +------+      +------+      +------+
     * | head |<---->| new1 |----->| new2 |----->| new3 |<---+
     * +------+      +------+      +------+      +------+    |
     *     ^                                                 |
     *     +-------------------------------------------------+ */

    __list_del(new2.prev, new2.next);
    /* +------+      +------+      +------+
     * | head |<---->| new1 |----->| new3 |<---+
     * +------+      +------+      +------+    |
     *     ^                                   |
     *     +-----------------------------------+ */
    LCUT_PTR_EQUAL(tc, new1.next, &new3);
    LCUT_PTR_EQUAL(tc, new3.prev, &new1);

    __list_del(new1.prev, new1.next);
    /* +------+      +------+
     * | head |<---->| new3 |<---+
     * +------+      +------+    |
     *     ^                     |
     *     +---------------------+ */
    LCUT_PTR_EQUAL(tc, head.next, &new3);
    LCUT_PTR_EQUAL(tc, new3.prev, &head);

    __list_del(new3.prev, new3.next);
    /* +------+
     * | head |<---+
     * +------+    |
     *     ^       |
     *     +-------+ */
    LCUT_PTR_EQUAL(tc, head.next, &head);
    LCUT_PTR_EQUAL(tc, head.prev, &head);
}

static void tc_list_del(lcut_tc_t *tc, void *data)
{
    LIST_HEAD(head);
    struct list_head new1, new2, new3;

    list_add_tail(&new1, &head);
    list_add_tail(&new2, &head);
    list_add_tail(&new3, &head);
    /* +------+      +------+      +------+      +------+
     * | head |<---->| new1 |----->| new2 |----->| new3 |<---+
     * +------+      +------+      +------+      +------+    |
     *     ^                                                 |
     *     +-------------------------------------------------+ */

    list_del(&new2);
    /* +------+      +------+      +------+
     * | head |<---->| new1 |----->| new3 |<---+
     * +------+      +------+      +------+    |
     *     ^                                   |
     *     +-----------------------------------+ */
    LCUT_PTR_EQUAL(tc, new2.prev, NULL);
    LCUT_PTR_EQUAL(tc, new2.next, NULL);
    LCUT_PTR_EQUAL(tc, new1.next, &new3);
    LCUT_PTR_EQUAL(tc, new3.prev, &new1);

    list_del(&new1);
    /* +------+      +------+
     * | head |<---->| new3 |<---+
     * +------+      +------+    |
     *     ^                     |
     *     +---------------------+ */
    LCUT_PTR_EQUAL(tc, new1.prev, NULL);
    LCUT_PTR_EQUAL(tc, new1.next, NULL);
    LCUT_PTR_EQUAL(tc, head.next, &new3);
    LCUT_PTR_EQUAL(tc, new3.prev, &head);

    list_del(&new3);
    /* +------+
     * | head |<---+
     * +------+    |
     *     ^       |
     *     +-------+ */
    LCUT_PTR_EQUAL(tc, new3.prev, NULL);
    LCUT_PTR_EQUAL(tc, new3.next, NULL);
    LCUT_PTR_EQUAL(tc, head.prev, &head);
    LCUT_PTR_EQUAL(tc, head.next, &head);
}

static void tc_list_replace(lcut_tc_t *tc, void *data)
{
    LIST_HEAD(head);
    struct list_head new1, new2, new3;

    list_add_tail(&new1, &head);
    list_add_tail(&new2, &head);
    /* +------+      +------+      +------+
     * | head |<---->| new1 |----->| new2 |<---+
     * +------+      +------+      +------+    |
     *     ^                                   |
     *     +-----------------------------------+ */

    list_replace(&new1, &new3);
    /* +------+      +------+      +------+
     * | head |<---->| new3 |----->| new2 |<---+
     * +------+      +------+      +------+    |
     *     ^                                   |
     *     +-----------------------------------+ */
    LCUT_PTR_EQUAL(tc, head.next, &new3);
    LCUT_PTR_EQUAL(tc, new3.prev, &head);
    LCUT_PTR_EQUAL(tc, new3.next, &new2);
    LCUT_PTR_EQUAL(tc, new2.prev, &new3);
}

static void tc_list_move(lcut_tc_t *tc, void *data)
{
    LIST_HEAD(head1);
    LIST_HEAD(head2);
    struct list_head new1, new2;

    list_add_tail(&new1, &head1);
    list_add_tail(&new2, &head1);
    /* +------+      +------+      +------+
     * | head1|<---->| new1 |----->| new2 |<---+
     * +------+      +------+      +------+    |
     *     ^                                   |
     *     +-----------------------------------+ */

    list_move(&new1, &head2);
    /* +-------+      +------+      +-------+      +------+      
     * | head1 |<---->| new2 |<---+ | head2 |<---->| new1 |<---+ 
     * +-------+      +------+    | +-------+      +------+    | 
     *     ^                      |     ^                      | 
     *     +----------------------+     +----------------------+ */
    LCUT_PTR_EQUAL(tc, head1.next, &new2);
    LCUT_PTR_EQUAL(tc, new2.prev, &head1);

    LCUT_PTR_EQUAL(tc, head2.next, &new1);
    LCUT_PTR_EQUAL(tc, new1.prev, &head2);
    LCUT_PTR_EQUAL(tc, new1.next, &head2);
    LCUT_PTR_EQUAL(tc, head2.prev, &new1);
}

static void tc_list_move_tail(lcut_tc_t *tc, void *data)
{
    LIST_HEAD(head);
    struct list_head new1, new2;

    list_add_tail(&new1, &head);
    list_add_tail(&new2, &head);
    /* +------+      +------+      +------+
     * | head |<---->| new1 |----->| new2 |<---+
     * +------+      +------+      +------+    |
     *     ^                                   |
     *     +-----------------------------------+ */

    list_move_tail(&new1, &head);
    /* +------+      +------+      +------+
     * | head |<---->| new2 |----->| new1 |<---+
     * +------+      +------+      +------+    |
     *     ^                                   |
     *     +-----------------------------------+ */
    LCUT_PTR_EQUAL(tc, head.prev, &new1);
    LCUT_PTR_EQUAL(tc, head.next, &new2);
    LCUT_PTR_EQUAL(tc, new2.prev, &head);
    LCUT_PTR_EQUAL(tc, new2.next, &new1);
    LCUT_PTR_EQUAL(tc, new1.prev, &new2);
    LCUT_PTR_EQUAL(tc, new1.next, &head);

}

static void tc_list_is_last(lcut_tc_t *tc, void *data)
{
    LIST_HEAD(head);
    struct list_head new1, new2;

    list_add_tail(&new1, &head);
    list_add_tail(&new2, &head);
    /* +------+      +------+      +------+
     * | head |<---->| new1 |----->| new2 |<---+
     * +------+      +------+      +------+    |
     *     ^                                   |
     *     +-----------------------------------+ */
    LCUT_TRUE(tc, list_is_last(&new2, &head));
    LCUT_FALSE(tc, list_is_last(&new1, &head));
    LCUT_FALSE(tc, list_is_last(&head, &head));

    list_move_tail(&new1, &head);
    /* +------+      +------+      +------+
     * | head |<---->| new2 |----->| new1 |<---+
     * +------+      +------+      +------+    |
     *     ^                                   |
     *     +-----------------------------------+ */
    LCUT_TRUE(tc, list_is_last(&new1, &head));
    LCUT_FALSE(tc, list_is_last(&new2, &head));
    LCUT_FALSE(tc, list_is_last(&head, &head));
}

static void tc_list_empty(lcut_tc_t *tc, void *data)
{
    LIST_HEAD(head);
    struct list_head new1;

    LCUT_TRUE(tc, list_empty(&head));

    list_add(&new1, &head);
    LCUT_FALSE(tc, list_empty(&head));
}

static void tc_list_entry(lcut_tc_t *tc, void *data)
{
    /* has call new_list_for_test_xxx_entry()
     * head_for_entry has been ready */
    struct list_head *_p;
    struct node_s *node;
    float f;
    
    _p = head_for_entry.next->next;
    node = list_entry(_p, struct node_s, list);
    LCUT_INT_EQUAL(tc, 2, node->i);
    LCUT_STR_EQUAL(tc, "second", node->str);
    f = 2.2;
    LCUT_TRUE(tc, (f == node->f));
}

static void tc_list_first_entry(lcut_tc_t *tc, void *data)
{
    /* has call new_list_for_test_xxx_entry()
     * head_for_entry has been ready */
    struct node_s *node;
    float f;
    
    node = list_first_entry(&head_for_entry, struct node_s, list);
    LCUT_INT_EQUAL(tc, 1, node->i);
    LCUT_STR_EQUAL(tc, "first", node->str);
    f = 1.1;
    LCUT_TRUE(tc, (f == node->f));
}

static void tc___list_for_each(lcut_tc_t *tc, void *data)
{
    /* has call new_list_for_test_xxx_entry()
     * head_for_entry has been ready */
    struct list_head *_p;
    int i;
    
    i = 0;
    __list_for_each(_p, &head_for_entry) {
        LCUT_PTR_EQUAL(tc, &nodes[i].list, _p);
        i++;
    }
}

static void tc_list_for_each_safe(lcut_tc_t *tc, void *data)
{
    /* has call new_list_for_test_xxx_entry()
     * head_for_entry has been ready */
    struct list_head *_p, *tmp;
    int i;

    i = 0;
    list_for_each_safe(_p, tmp, &head_for_entry) {
        LCUT_PTR_EQUAL(tc, &nodes[i].list, _p);
        if (list_is_last(_p, &head_for_entry)) {
            LCUT_PTR_EQUAL(tc, tmp, &head_for_entry);
        } else {
            LCUT_PTR_EQUAL(tc, tmp, &nodes[i+1].list);
        }
        i++;
    }
}

static void tc___list_for_each_reverse(lcut_tc_t *tc, void *data)
{
    /* has call new_list_for_test_xxx_entry()
     * head_for_entry has been ready */
    struct list_head *_p;
    int i;
    
    i = nodes_len - 1;
    __list_for_each_reverse(_p, &head_for_entry) {
        LCUT_PTR_EQUAL(tc, &nodes[i].list, _p);
        i--;
    }
}

static void tc_list_init(lcut_tc_t *tc, void *data)
{
    LIST_HEAD(head);
    struct list_head *_p;
    int size, num, i;

    size = 64;
    num = 100;
    LCUT_INT_EQUAL(tc, num, list_init(&head, size, num));
    
    i = 0;
    __list_for_each(_p, &head) {
        i++;
    }
    LCUT_INT_EQUAL(tc, num, i);

    list_free(&head);
}

static void tc_list_loop_get_next(lcut_tc_t *tc, void *data)
{
    /* has call new_list_for_test_xxx_entry()
     * head_for_entry has been ready */
    struct list_head *_p;

    _p = &nodes[0].list;

    _p = list_loop_get_next(_p, &head_for_entry);
    LCUT_PTR_EQUAL(tc, &nodes[1].list, _p);

    _p = list_loop_get_next(_p, &head_for_entry);
    LCUT_PTR_EQUAL(tc, &nodes[2].list, _p);

    _p = list_loop_get_next(_p, &head_for_entry);
    LCUT_PTR_EQUAL(tc, &nodes[0], _p);

    _p = list_loop_get_next(_p, &head_for_entry);
    LCUT_PTR_EQUAL(tc, &nodes[1].list, _p);
}

int main() {
    lcut_ts_t   *suite = NULL;
    LCUT_TEST_BEGIN("air_list test", NULL, NULL);

    LCUT_TS_INIT(suite, "air_list unit test suite", NULL, NULL);
    /* test init */
    LCUT_TC_ADD(suite, "LIST_HEAD_INIT test case", tc_LIST_HEAD_INIT, NULL, NULL, NULL);
    LCUT_TC_ADD(suite, "LIST_HEAD test case", tc_LIST_HEAD, NULL, NULL, NULL);
    LCUT_TC_ADD(suite, "INIT_LIST_HEAD test case", tc_INIT_LIST_HEAD, NULL, NULL, NULL);

    /* test operations */
    LCUT_TC_ADD(suite, "__list_add test case", tc___list_add, NULL, NULL, NULL);
    LCUT_TC_ADD(suite, "list_add test case", tc_list_add, NULL, NULL, NULL);
    LCUT_TC_ADD(suite, "list_add_tail test case", tc_list_add_tail, NULL, NULL, NULL);
    LCUT_TC_ADD(suite, "__list_del test case", tc___list_del, NULL, NULL, NULL);
    LCUT_TC_ADD(suite, "list_del test case", tc_list_del, NULL, NULL, NULL);
    LCUT_TC_ADD(suite, "list_replace test case", tc_list_replace, NULL, NULL, NULL);
    LCUT_TC_ADD(suite, "list_move test case", tc_list_move, NULL, NULL, NULL);
    LCUT_TC_ADD(suite, "list_move_tail test case", tc_list_move_tail, NULL, NULL, NULL);
    LCUT_TC_ADD(suite, "list_is_last test case", tc_list_is_last, NULL, NULL, NULL);
    LCUT_TC_ADD(suite, "list_empty test case", tc_list_empty, NULL, NULL, NULL);
    LCUT_TC_ADD(suite, "list_entry test case", tc_list_entry, NULL, new_list_for_test_xxx_entry, NULL);
    LCUT_TC_ADD(suite, "list_first_entry test case", tc_list_first_entry, NULL, new_list_for_test_xxx_entry, NULL);
    LCUT_TC_ADD(suite, "__list_for_each test case", tc___list_for_each, NULL, new_list_for_test_xxx_entry, NULL);
    LCUT_TC_ADD(suite, "list_for_each_safe test case", tc_list_for_each_safe, NULL, new_list_for_test_xxx_entry, NULL);
    LCUT_TC_ADD(suite, "__list_for_each_reverse test case", tc___list_for_each_reverse, NULL, new_list_for_test_xxx_entry, NULL);
    LCUT_TC_ADD(suite, "list_init test case", tc_list_init, NULL, NULL, NULL);
    LCUT_TC_ADD(suite, "list_loop_get_next test case", tc_list_loop_get_next, NULL, new_list_for_test_xxx_entry, NULL);
    LCUT_TS_ADD(suite);

    LCUT_TEST_RUN();
    LCUT_TEST_REPORT();
    LCUT_TEST_END();

    LCUT_TEST_RESULT();
}

