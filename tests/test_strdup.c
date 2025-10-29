// test_strdup.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../libft.h"

int main(void)
{
    char *s = ft_strdup("hello");
    if (!s) { fprintf(stderr,"FAIL: strdup NULL\n"); return 1; }
    if (strcmp(s,"hello")!=0) { fprintf(stderr,"FAIL: strdup content\n"); free(s); return 2; }
    free(s);
    printf("test_strdup: OK\n");
    return 0;
}
