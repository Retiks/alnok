// test_lstlast_bonus.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libft.h"

int main(void)
{
    t_list *a = ft_lstnew(strdup("one"));
    ft_lstadd_back(&a, ft_lstnew(strdup("two")));
    t_list *last = ft_lstlast(a);
    if (!last || strcmp(last->content,"two")!=0) { fprintf(stderr,"FAIL: lstlast\n"); ft_lstclear(&a, free); return 1; }
    ft_lstclear(&a, free);
    printf("test_lstlast_bonus: OK\n");
    return 0;
}
