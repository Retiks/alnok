// test_strmapi.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../libft.h"

static char f(unsigned int i, char c) { (void)i; return c - 32; }

int main(void)
{
    char *s = ft_strmapi("abc", f);
    if (!s) { fprintf(stderr,"FAIL: strmapi NULL\n"); return 1; }
    if (strcmp(s,"ABC")!=0) { fprintf(stderr,"FAIL: strmapi wrong\n"); free(s); return 2; }
    free(s);
    printf("test_strmapi: OK\n");
    return 0;
}
