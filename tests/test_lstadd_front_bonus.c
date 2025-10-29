// test_lstadd_front_bonus.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libft.h"

int main(void)
{
    t_list *a = ft_lstnew(strdup("one"));
    t_list *b = ft_lstnew(strdup("two"));
    ft_lstadd_front(&b, a);
    if (b->content == NULL) { fprintf(stderr,"FAIL: lstadd_front\n"); return 1; }
    if (strcmp(b->content,"one")!=0) { fprintf(stderr,"FAIL: lstadd_front order\n"); return 2; }
    ft_lstclear(&b, free);
    printf("test_lstadd_front_bonus: OK\n");
    return 0;
}
