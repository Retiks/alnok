// test_lstadd_back_bonus.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libft.h"

int main(void)
{
    t_list *a = ft_lstnew(strdup("one"));
    t_list *b = ft_lstnew(strdup("two"));
    ft_lstadd_back(&a, b);
    t_list *last = ft_lstlast(a);
    if (!last || strcmp(last->content,"two")!=0) { fprintf(stderr,"FAIL: lstadd_back\n"); ft_lstclear(&a, free); return 1; }
    ft_lstclear(&a, free);
    printf("test_lstadd_back_bonus: OK\n");
    return 0;
}
