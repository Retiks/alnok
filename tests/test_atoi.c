// test_atoi.c
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "../libft.h"

int main(void)
{
    const char *cases[] = {"0","  -42","+123","2147483647","-2147483648","  0012a","", "  +0"};
    for (size_t i=0;i<sizeof(cases)/sizeof(cases[0]);++i) {
        int r1 = atoi(cases[i]);
        int r2 = ft_atoi(cases[i]);
        if (r1 != r2) { fprintf(stderr,"FAIL: atoi '%s' -> atoi=%d ft_atoi=%d\n",cases[i],r1,r2); return 1; }
    }
    printf("test_atoi: OK\n");
    return 0;
}
