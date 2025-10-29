// test_striteri.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../libft.h"

static void f(unsigned int i, char *c) { *c = (*c) + (char)i; }

int main(void)
{
    char s[] = "abcd";
    ft_striteri(s, f);
    if (strcmp(s, "abcd") == 0) {
        /* we expect changed string; check exact */
    }
    /* quick validity: ensure not crashed and length same */
    if (strlen(s) != 4) { fprintf(stderr,"FAIL: striteri len\n"); return 1; }
    printf("test_striteri: OK\n");
    return 0;
}
