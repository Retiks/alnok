// test_atoi.c
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <string.h>
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
    // Basic tests
    const char *cases[] = {"0","  -42","+123","2147483647","-2147483648","  0012a","", "  +0"};
    for (size_t i=0;i<sizeof(cases)/sizeof(cases[0]);++i) {
        int r1 = atoi(cases[i]);
        int r2 = ft_atoi(cases[i]);
        char test_name[100];
        snprintf(test_name, sizeof(test_name), "atoi '%s'", cases[i]);
        TEST(test_name, r1 == r2);
    }
    
    // Edge cases from test_edge_cases.c
    TEST("atoi overflow", ft_atoi("2147483648") == atoi("2147483648"));
    TEST("atoi underflow", ft_atoi("-2147483649") == atoi("-2147483649"));
    TEST("atoi whitespace mix", ft_atoi("  \t\n\v\f\r 42") == 42);
    TEST("atoi multiple signs", ft_atoi("+-42") == atoi("+-42"));
    TEST("atoi only whitespace", ft_atoi("   \t\n") == 0);
    
    // Sneaky tests from test_sneaky_bugs.c
    TEST("atoi multiple spaces", ft_atoi("   \t\n\r\v\f  42") == 42);
    TEST("atoi plus sign", ft_atoi("+123") == 123);
    TEST("atoi multiple signs ++", ft_atoi("++123") == 0);
    TEST("atoi space after sign", ft_atoi("- 123") == 0);
    
    // Ultra-sneaky tests from test_ultra_sneaky.c
    TEST("atoi all whitespace types", ft_atoi(" \t\n\v\f\r42") == 42);
    TEST("atoi overflow behavior", ft_atoi("9999999999999999999") == atoi("9999999999999999999"));
    TEST("atoi underflow behavior", ft_atoi("-9999999999999999999") == atoi("-9999999999999999999"));
    TEST("atoi double plus", ft_atoi("++5") == atoi("++5"));
    TEST("atoi plus minus", ft_atoi("+-5") == atoi("+-5"));
    TEST("atoi minus plus", ft_atoi("-+5") == atoi("-+5"));
    TEST("atoi trailing letters", ft_atoi("42abc") == 42);
    TEST("atoi trailing spaces", ft_atoi("42   ") == 42);
    TEST("atoi only plus", ft_atoi("+") == 0);
    TEST("atoi only minus", ft_atoi("-") == 0);
    
    if (fail_count == 0) {
        printf("test_atoi: OK (%d tests passed)\n", test_count);
        return 0;
    } else {
        fprintf(stderr, "\n❌ %d/%d tests failed\n", fail_count, test_count);
        return 1;
    }
}
