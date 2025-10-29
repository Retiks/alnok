// test_substr.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../libft.h"

int main(void)
{
    char *s = ft_substr("Hello", 1, 3); /* "ell" */
    if (!s || strcmp(s,"ell")!=0) { fprintf(stderr,"FAIL: substr normal\n"); free(s); return 1; }
    free(s);
    s = ft_substr("Hi", 5, 10);
    if (!s || strcmp(s,"")!=0) { fprintf(stderr,"FAIL: substr start>len\n"); free(s); return 2; }
    free(s);
    printf("test_substr: OK\n");
    return 0;
}
