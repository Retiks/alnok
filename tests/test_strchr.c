// test_strchr.c
#include <stdio.h>
#include <string.h>
#include "../libft.h"

int main(void)
{
    const char *s = "abc\0def";
    if (ft_strchr(s,'a') != strchr(s,'a')) { fprintf(stderr,"FAIL: strchr a\n"); return 1; }
    if (ft_strchr(s,'\0') != strchr(s,'\0')) { fprintf(stderr,"FAIL: strchr NUL\n"); return 2; }
    if (ft_strchr(s,'z') != strchr(s,'z')) { fprintf(stderr,"FAIL: strchr z\n"); return 3; }
    printf("test_strchr: OK\n");
    return 0;
}
