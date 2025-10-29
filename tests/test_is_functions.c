// test_is_functions.c
#include <stdio.h>
#include <ctype.h>
#include "../libft.h"

int main(void)
{
    for (int i = -1; i <= 256; ++i) {
        int a = isalpha(i) ? 1 : 0;
        int b = ft_isalpha(i) ? 1 : 0;
        if (a != b) { fprintf(stderr,"FAIL: isalpha(%d)\n", i); return 1; }
        a = isdigit(i) ? 1 : 0; b = ft_isdigit(i) ? 1 : 0;
        if (a != b) { fprintf(stderr,"FAIL: isdigit(%d)\n", i); return 2; }
        a = isalnum(i) ? 1 : 0; b = ft_isalnum(i) ? 1 : 0;
        if (a != b) { fprintf(stderr,"FAIL: isalnum(%d)\n", i); return 3; }
        a = isascii(i) ? 1 : 0; b = ft_isascii(i) ? 1 : 0;
        if (a != b) { fprintf(stderr,"FAIL: isascii(%d)\n", i); return 4; }
        a = isprint(i) ? 1 : 0; b = ft_isprint(i) ? 1 : 0;
        if (a != b) { fprintf(stderr,"FAIL: isprint(%d)\n", i); return 5; }
    }
    printf("test_is_functions: OK\n");
    return 0;
}
