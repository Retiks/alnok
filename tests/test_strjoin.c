// test_strjoin.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../libft.h"

int main(void)
{
    char *s = ft_strjoin("Hello","World");
    if (!s || strcmp(s,"HelloWorld")!=0) { fprintf(stderr,"FAIL: strjoin\n"); free(s); return 1; }
    free(s);
    printf("test_strjoin: OK\n");
    return 0;
}
