// test_lstnew_bonus.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../libft.h"

int main(void)
{
    t_list *n = ft_lstnew(strdup("one"));
    if (!n) { fprintf(stderr,"FAIL: lstnew NULL\n"); return 1; }
    if (strcmp(n->content, "one")!=0) { fprintf(stderr,"FAIL: lstnew content\n"); free(n); return 2; }
    free(n->content); free(n);
    printf("test_lstnew_bonus: OK\n");
    return 0;
}
