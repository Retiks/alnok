// test_strncmp.c
#include <stdio.h>
#include <string.h>
#include "../libft.h"

int main(void)
{
    if (ft_strncmp("abc","abd",2) != strncmp("abc","abd",2)) { fprintf(stderr,"FAIL: strncmp 2\n"); return 1; }
    if (ft_strncmp("abc","abc",10) != strncmp("abc","abc",10)) { fprintf(stderr,"FAIL: strncmp long\n"); return 2; }
    if (ft_strncmp("","",0) != strncmp("","",0)) { fprintf(stderr,"FAIL: strncmp zero\n"); return 3; }
    printf("test_strncmp: OK\n");
    return 0;
}
