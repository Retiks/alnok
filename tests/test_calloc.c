// test_calloc.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libft.h"

int main(void)
{
    void *p1 = ft_calloc(0, 10);
    void *p2 = ft_calloc(0, 20);
    if (!p1 || !p2) { fprintf(stderr,"FAIL: calloc returned NULL for zero\n"); return 1; }
    if (p1 == p2) { fprintf(stderr,"FAIL: calloc returned same pointer for zero sizes\n"); free(p1); free(p2); return 2; }
    free(p1); free(p2);
    unsigned char *p3 = ft_calloc(8,1);
    if (!p3) { fprintf(stderr,"FAIL: calloc(8,1) NULL\n"); return 3; }
    for (int i=0;i<8;i++) if (p3[i] != 0) { fprintf(stderr,"FAIL: calloc not zeroed at %d\n",i); free(p3); return 4; }
    free(p3);
    printf("test_calloc: OK\n");
    return 0;
}
