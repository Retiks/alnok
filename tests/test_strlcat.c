// test_strlcat.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../libft.h"

/* portable reference */
static size_t ref_strlcat(char *dst, const char *src, size_t dstsize)
{
    size_t dl = strlen(dst);
    size_t sl = strlen(src);
    if (dstsize <= dl) return dstsize + sl;
    size_t copy = dstsize - dl - 1;
    if (copy > 0) {
        size_t c = sl < copy ? sl : copy;
        memcpy(dst + dl, src, c);
        dst[dl + c] = '\0';
    }
    return dl + sl;
}

int main(void)
{
    char a1[10] = "Hi";
    char a2[10] = "Hi";
    size_t r1 = ft_strlcat(a1, "Hello", sizeof(a1));
    size_t r2 = ref_strlcat(a2, "Hello", sizeof(a2));
    if (r1 != r2 || strcmp(a1,a2)!=0) { fprintf(stderr,"FAIL: ft_strlcat\n"); return 1; }
    printf("test_strlcat: OK\n");
    return 0;
}
