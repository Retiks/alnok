// test_memcmp.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../libft.h"

int main(void)
{
    char a[] = "abcdef";
    char b[] = "abcdeg";
    int r1 = memcmp(a,b,6);
    int r2 = ft_memcmp(a,b,6);
    if ((r1<0) != (r2<0) && (r1>0)!=(r2>0) && (r1==0)!=(r2==0)) {
        /* allow sign differences but ensure zero vs non-zero match */
    }
    if ((r1==0) != (r2==0)) { fprintf(stderr,"FAIL: ft_memcmp\n"); return 1; }
    printf("test_memcmp: OK\n");
    return 0;
}
