// test_lstdelone_bonus.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libft.h"

static void del(void *p){ free(p); }

int main(void)
{
    t_list *n = ft_lstnew(strdup("one"));
    ft_lstdelone(n, del);
    /* cannot reliably check freed memory; just ensure no crash */
    printf("test_lstdelone_bonus: OK\n");
    return 0;
}
