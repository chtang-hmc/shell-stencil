#include "memset.h"

void *memset(void *s, int c, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        s[i] = c;
    }

    return s;
}
