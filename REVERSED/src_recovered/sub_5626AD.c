#include <stdlib.h>

/* Bridge the game's legacy _onexit wrapper to the process CRT. */
int sub_5626AD(void *callback)
{
    return _onexit((_onexit_t)callback) != NULL ? 0 : -1;
}
