// test_lstiter_bonus.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libft.h"

static void f(void *p){ char *s = (char*)p; s[0] = 'X'; }

int main(void)
{
    t_list *a = ft_lstnew(strdup("one"));
    ft_lstadd_back(&a, ft_lstnew(strdup("two")));
    ft_lstiter(a, f);
    if (a && a->content && ((char*)a->content)[0] != 'X') { fprintf(stderr,"FAIL: lstiter\n"); ft_lstclear(&a, free); return 1; }
    ft_lstclear(&a, free);
    printf("test_lstiter_bonus: OK\n");
    return 0;
}
