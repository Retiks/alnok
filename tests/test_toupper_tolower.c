// test_toupper_tolower.c
#include <stdio.h>
#include <ctype.h>
#include "../libft.h"

int main(void)
{
    for (int i = -1; i <= 256; ++i) {
        int a = toupper(i);
        int b = ft_toupper(i);
        if (a != b) { fprintf(stderr,"FAIL: toupper(%d) -> %d vs %d\n", i, a, b); return 1; }
        a = tolower(i);
        b = ft_tolower(i);
        if (a != b) { fprintf(stderr,"FAIL: tolower(%d)\n", i); return 2; }
    }
    printf("test_toupper_tolower: OK\n");
    return 0;
}
