// test_memset.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "../libft.h"

int main(void)
{
    char a[20], b[20];
    memset(a, 'A', sizeof(a));
    ft_memset(b, 'A', sizeof(b));
    if (memcmp(a, b, sizeof(a)) != 0) {
        fprintf(stderr, "FAIL: ft_memset differs\n");
        return 1;
    }
    /* zero and partial */
    memset(a+5, 0, 5);
    ft_memset(b+5, 0, 5);
    if (memcmp(a, b, sizeof(a)) != 0) {
        fprintf(stderr, "FAIL: ft_memset partial differs\n");
        return 2;
    }
    printf("test_memset: OK\n");
    return 0;
}
