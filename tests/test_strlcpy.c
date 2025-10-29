// test_strlcpy.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../libft.h"

/* portable reference */
static size_t ref_strlcpy(char *dst, const char *src, size_t dstsize)
{
    size_t sl = strlen(src);
    if (dstsize) {
        size_t c = sl >= dstsize ? dstsize - 1 : sl;
        memcpy(dst, src, c);
        dst[c] = '\0';
    }
    return sl;
}

int main(void)
{
    char d1[5], d2[5];
    const char *s = "HelloWorld";
    size_t r1 = ft_strlcpy(d1, s, sizeof(d1));
    size_t r2 = ref_strlcpy(d2, s, sizeof(d2));
    if (r1 != r2 || strcmp(d1,d2)!=0) { fprintf(stderr,"FAIL: ft_strlcpy\n"); return 1; }
    char z1[1] = {'X'}, z2[1]={'X'};
    if (ft_strlcpy(z1,"ABC",0) != ref_strlcpy(z2,"ABC",0)) { fprintf(stderr,"FAIL: strlcpy zero\n"); return 2; }
    printf("test_strlcpy: OK\n");
    return 0;
}
