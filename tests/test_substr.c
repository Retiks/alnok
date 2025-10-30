// test_substr.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
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
    s = ft_substr("Hello", 1, 3);
    TEST("substr normal", s && strcmp(s, "ell") == 0);
    free(s);
    
    s = ft_substr("Hi", 5, 10);
    TEST("substr start>len", s && strcmp(s, "") == 0);
    free(s);
    
    // Edge cases from test_edge_cases.c
    s = ft_substr("", 0, 5);
    TEST("substr empty string", s && strcmp(s, "") == 0);
    free(s);
    
    s = ft_substr("test", 0, 0);
    TEST("substr len=0", s && strcmp(s, "") == 0);
    free(s);
    
    s = ft_substr("hello", 2, 100);
    TEST("substr len > remaining", s && strcmp(s, "llo") == 0);
    free(s);
    
    s = ft_substr("test", 10, 5);
    TEST("substr start >= strlen", s && strcmp(s, "") == 0);
    free(s);
    
    // Sneaky tests from test_sneaky_bugs.c
    s = ft_substr("0123456789", 5, 100);
    TEST("substr start+len > strlen", s && strcmp(s, "56789") == 0);
    free(s);
    
    s = ft_substr("hello", 0, 2);
    TEST("substr partial", s && strcmp(s, "he") == 0);
    free(s);
    
    s = ft_substr("test", 4, 10);
    TEST("substr start at end", s && strcmp(s, "") == 0);
    free(s);
    
    // Ultra-sneaky tests from test_ultra_sneaky.c
    s = ft_substr("test", UINT_MAX, 10);
    TEST("substr start=UINT_MAX", s && strcmp(s, "") == 0);
    free(s);
    
    s = ft_substr("hello", 2, 1000);
    TEST("substr len very large", s && strcmp(s, "llo") == 0);
    free(s);
    
    s = ft_substr("test", 1000000, 10);
    TEST("substr start very large", s && strcmp(s, "") == 0);
    free(s);
    
    if (fail_count == 0) {
        printf("test_substr: OK (%d tests passed)\n", test_count);
        return 0;
    } else {
        fprintf(stderr, "\n❌ %d/%d tests failed\n", fail_count, test_count);
        return 1;
    }
}
