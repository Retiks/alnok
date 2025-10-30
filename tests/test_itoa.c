// test_itoa.c
#include <stdio.h>
#include <limits.h>
#include <stdint.h>
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
    char *s;
    
    // Basic tests
    s = ft_itoa(0);
    TEST("itoa zero", s && strcmp(s, "0") == 0);
    free(s);
    
    s = ft_itoa(INT_MIN);
    TEST("itoa INT_MIN", s && strcmp(s, "-2147483648") == 0);
    free(s);
    
    s = ft_itoa(INT_MAX);
    TEST("itoa INT_MAX", s && strcmp(s, "2147483647") == 0);
    free(s);
    
    // Edge cases from test_edge_cases.c
    s = ft_itoa(-1);
    TEST("itoa -1", s && strcmp(s, "-1") == 0);
    free(s);
    
    // Ultra-sneaky tests from test_ultra_sneaky.c
    s = ft_itoa(123456789);
    TEST("itoa many digits", s && strcmp(s, "123456789") == 0);
    free(s);
    
    if (fail_count == 0) {
        printf("test_itoa: OK (%d tests passed)\n", test_count);
        return 0;
    } else {
        fprintf(stderr, "\n❌ %d/%d tests failed\n", fail_count, test_count);
        return 1;
    }
}
