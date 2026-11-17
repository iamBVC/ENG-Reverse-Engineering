/* Recovered static-list finalizer thunk at 0x0040E070. */
#include <stdint.h>

void sub_40E070(void)
{
    int *head = DAT_00582260;
    int *node = (int *)(uintptr_t)(unsigned int)head[0];
    int *sentinel = head + 1;

    while (node != sentinel) {
        int *previous = (int *)(uintptr_t)(unsigned int)node[0];
        int *next = (int *)(uintptr_t)(unsigned int)node[1];

        if (previous != 0 && next != 0) {
            previous[1] = (int)(uintptr_t)next;
            next[0] = (int)(uintptr_t)previous;
            node[0] = 0;
            node[1] = 0;
        }
        node = (int *)(uintptr_t)(unsigned int)head[0];
    }
}
