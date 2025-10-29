// test_strrchr.c
#include <stdio.h>
#include <string.h>
#include "../libft.h"

int main(void)
{
    const char *s = "abca";
    if (ft_strrchr(s,'a') != strrchr(s,'a')) { fprintf(stderr,"FAIL: strrchr a\n"); return 1; }
    if (ft_strrchr(s,'z') != strrchr(s,'z')) { fprintf(stderr,"FAIL: strrchr z\n"); return 2; }
    printf("test_strrchr: OK\n");
    return 0;
}
