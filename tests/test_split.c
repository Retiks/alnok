// test_split.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libft.h"

static int count(char **arr){ int i=0; if(!arr) return -1; while(arr[i]) ++i; return i; }

int main(void)
{
    char **r = ft_split(",a,,b,", ',');
    if (!r) { fprintf(stderr,"FAIL: split NULL\n"); return 1; }
    int c = count(r);
    if (c != 2) { fprintf(stderr,"FAIL: split count %d expected 2\n", c); for(int i=0;r[i];++i) free(r[i]); free(r); return 2; }
    if (strcmp(r[0],"a")||strcmp(r[1],"b")) { fprintf(stderr,"FAIL: split tokens\n"); for(int i=0;r[i];++i) free(r[i]); free(r); return 3; }
    for (int i=0; r[i]; ++i) free(r[i]);
    free(r);
    printf("test_split: OK\n");
    return 0;
}
