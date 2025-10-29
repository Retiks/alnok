// test_lstsize_bonus.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libft.h"

int main(void)
{
    t_list *a = ft_lstnew(strdup("one"));
    ft_lstadd_back(&a, ft_lstnew(strdup("two")));
    ft_lstadd_back(&a, ft_lstnew(strdup("three")));
    if (ft_lstsize(a) != 3) { fprintf(stderr,"FAIL: lstsize %d\n", ft_lstsize(a)); ft_lstclear(&a, free); return 1; }
    ft_lstclear(&a, free);
    printf("test_lstsize_bonus: OK\n");
    return 0;
}
