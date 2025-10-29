// test_bzero.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../libft.h"

int main(void)
{
    char s1[16], s2[16];
    for (int i=0;i<16;i++){ s1[i]=s2[i]=1; }
    bzero(s1, 16);
    ft_bzero(s2, 16);
    if (memcmp(s1,s2,16)!=0){ fprintf(stderr,"FAIL: ft_bzero\n"); return 1; }
    printf("test_bzero: OK\n");
    return 0;
}
