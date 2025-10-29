// test_lstmap_bonus.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libft.h"

/* f duplicates content; returns NULL for second element to test cleanup */
static int counter = 0;
static void *f(void *c)
{
    ++counter;
    if (counter == 2) return NULL;
    char *s = strdup((char*)c);
    return s;
}
static void del(void *p){ free(p); }

int main(void)
{
    t_list *a = ft_lstnew(strdup("one"));
    ft_lstadd_back(&a, ft_lstnew(strdup("two")));
    ft_lstadd_back(&a, ft_lstnew(strdup("three")));
    t_list *res = ft_lstmap(a, f, del);
    if (res != NULL) {
        fprintf(stderr,"FAIL: lstmap should return NULL on f failure\n");
        ft_lstclear(&res, del);
        ft_lstclear(&a, free);
        return 1;
    }
    ft_lstclear(&a, free);
    printf("test_lstmap_bonus: OK\n");
    return 0;
}
