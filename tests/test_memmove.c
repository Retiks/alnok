// test_memmove.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../libft.h"

int main(void)
{
    char a[32] = "0123456789abcdef";
    char b[32] = "0123456789abcdef";
    memmove(a+2, a, 8);
    ft_memmove(b+2, b, 8);
    if (memcmp(a,b,32)!=0){ fprintf(stderr,"FAIL: ft_memmove forward\n"); return 1; }
    strcpy(a,"0123456789abcdef");
    strcpy(b,"0123456789abcdef");
    memmove(a, a+2, 8);
    ft_memmove(b, b+2, 8);
    if (memcmp(a,b,32)!=0){ fprintf(stderr,"FAIL: ft_memmove backward\n"); return 2; }
    printf("test_memmove: OK\n");
    return 0;
}
