// test_strdup.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../libft.h"

static int test_count = 0;
static int fail_count = 0;

#define TEST(name, cond) do { \
    test_count++; \
    fprintf(stderr, "[TEST %d] %s\n", test_count, name); \
    fflush(stderr); \
    if (!(cond)) { \
        fprintf(stderr, "❌ FAIL [%d]: %s\n", test_count, name); \
        fail_count++; \
    } \
} while(0)

int main(void)
{
    char *s = ft_strdup("hello");
    TEST("strdup basic", s && strcmp(s,"hello") == 0);
    free(s);
    
    // Sneaky tests from test_sneaky_bugs.c
    s = ft_strdup("");
    TEST("strdup empty string", s && strcmp(s, "") == 0);
    free(s);
    
    // Ultra-sneaky tests from test_ultra_sneaky.c
    char very_long[1000];
    memset(very_long, 'X', 999);
    very_long[999] = '\0';
    s = ft_strdup(very_long);
    TEST("strdup long string", s && strlen(s) == 999 && s[0] == 'X' && s[998] == 'X');
    free(s);
    
    if (fail_count == 0) {
        printf("test_strdup: OK (%d tests passed)\n", test_count);
        return 0;
    } else {
        fprintf(stderr, "\n❌ %d/%d tests failed\n", fail_count, test_count);
        return 1;
    }
}
