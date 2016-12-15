#include <lcthw/list.h>
#include <lcthw/list_algos.h>
#include <lcthw/dbg.h>

inline void ListNode_swap(ListNode *a, ListNode *b)
{
    void *temp = a->value;
    a->value = b->balue;
    b->value = temp;
}

int List_bubble_sort(List * list, List_compare cmp)
{
    int sorted = 1;

    if (List_count(list) <= 1) {
        return 0;
    }

    do {
        sorted = 1;


