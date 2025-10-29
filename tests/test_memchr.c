// test_memchr.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../libft.h"

int main(void)
{
    const char *s = "abcdefg";
    void *r1 = memchr(s, 'd', strlen(s));
    void *r2 = ft_memchr(s, 'd', strlen(s));
    if (r1 != r2) { fprintf(stderr,"FAIL: ft_memchr\n"); return 1; }
    if (ft_memchr(s,'z',strlen(s)) != NULL) { fprintf(stderr,"FAIL: ft_memchr absent\n"); return 2; }
    printf("test_memchr: OK\n");
    return 0;
}
