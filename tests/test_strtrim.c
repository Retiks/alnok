// test_strtrim.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../libft.h"

int main(void)
{
    char *s = ft_strtrim("  abc  "," ");
    if (!s || strcmp(s,"abc")!=0) { fprintf(stderr,"FAIL: strtrim\n"); free(s); return 1; }
    free(s);
    s = ft_strtrim("abc","xyz");
    if (!s || strcmp(s,"abc")!=0) { fprintf(stderr,"FAIL: strtrim no trim\n"); free(s); return 2; }
    free(s);
    printf("test_strtrim: OK\n");
    return 0;
}
