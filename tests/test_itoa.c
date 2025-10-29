// test_itoa.c
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include "../libft.h"

int main(void)
{
    char *s = ft_itoa(0);
    if (!s || strcmp(s,"0")!=0) { fprintf(stderr,"FAIL: itoa 0 -> '%s'\n", s? s:"NULL"); free(s); return 1; }
    free(s);
    s = ft_itoa(INT_MAX);
    char buf[64];
    sprintf(buf,"%d", INT_MAX);
    if (!s || strcmp(s,buf)!=0) { fprintf(stderr,"FAIL: itoa INT_MAX\n"); free(s); return 2; }
    free(s);
    s = ft_itoa(INT_MIN);
    sprintf(buf,"%d", INT_MIN);
    if (!s || strcmp(s,buf)!=0) { fprintf(stderr,"FAIL: itoa INT_MIN -> '%s' expected '%s'\n", s?s:"NULL", buf); free(s); return 3; }
    free(s);
    printf("test_itoa: OK\n");
    return 0;
}
