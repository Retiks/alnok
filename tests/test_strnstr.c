// test_strnstr.c
#include <stdio.h>
#include <string.h>
#include "../libft.h"

/* portable ref for strnstr */
static char *ref_strnstr(const char *hay, const char *nee, size_t len)
{
    if (!*nee) return (char*)hay;
    size_t nlen = strlen(nee);
    for (size_t i=0;i+ nlen<=len && hay[i]; ++i) {
        if (i + nlen > len) break;
        if (strncmp(hay+i, nee, nlen)==0) return (char*)(hay+i);
    }
    return NULL;
}

int main(void)
{
    const char *h = "hello world";
    if (ft_strnstr(h,"world",11) != ref_strnstr(h,"world",11)) { fprintf(stderr,"FAIL: strnstr world\n"); return 1; }
    if (ft_strnstr(h,"",5) != (char*)h) { fprintf(stderr,"FAIL: strnstr empty\n"); return 2; }
    printf("test_strnstr: OK\n");
    return 0;
}
