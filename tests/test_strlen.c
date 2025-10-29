// test_strlen.c
#include <stdio.h>
#include <string.h>
#include "../libft.h"

int main(void)
{
    if (ft_strlen("") != 0) { fprintf(stderr,"FAIL: strlen empty\n"); return 1; }
    if (ft_strlen("Hello") != 5) { fprintf(stderr,"FAIL: strlen Hello\n"); return 2; }
    char big[1001];
    for (int i=0;i<1000;i++) big[i]='a';
    big[1000]=0;
    if (ft_strlen(big) != 1000) { fprintf(stderr,"FAIL: strlen big\n"); return 3; }
    printf("test_strlen: OK\n");
    return 0;
}
