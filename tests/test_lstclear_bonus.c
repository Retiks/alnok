// test_lstclear_bonus.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libft.h"

int main(void)
{
    t_list *a = ft_lstnew(strdup("one"));
    ft_lstadd_back(&a, ft_lstnew(strdup("two")));
    ft_lstclear(&a, free);
    if (a != NULL) { fprintf(stderr,"FAIL: lstclear not NULL\n"); return 1; }
    printf("test_lstclear_bonus: OK\n");
    return 0;
}
