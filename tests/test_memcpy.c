// test_memcpy.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../libft.h"

int main(void)
{
    char src[32] = "This is a test for memcpy";
    char d1[32], d2[32];
    memcpy(d1, src, strlen(src)+1);
    ft_memcpy(d2, src, strlen(src)+1);
    if (strcmp(d1,d2)!=0) { fprintf(stderr,"FAIL: ft_memcpy\n"); return 1; }
    /* size 0 */
    strcpy(d1,"X");
    strcpy(d2,"X");
    memcpy(d1, src, 0);
    ft_memcpy(d2, src, 0);
    if (d1[0]!=d2[0]){ fprintf(stderr,"FAIL: ft_memcpy size0\n"); return 2; }
    printf("test_memcpy: OK\n");
    return 0;
}
