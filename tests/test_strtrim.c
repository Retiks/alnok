// test_strtrim.c
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
    char *s;
    
    // Basic tests
    s = ft_strtrim("  abc  "," ");
    TEST("strtrim basic", s && strcmp(s, "abc") == 0);
    free(s);
    
    s = ft_strtrim("abc","xyz");
    TEST("strtrim no trim", s && strcmp(s, "abc") == 0);
    free(s);
    
    // Edge cases from test_edge_cases.c
    s = ft_strtrim("", "abc");
    TEST("strtrim empty string", s && strcmp(s, "") == 0);
    free(s);
    
    s = ft_strtrim("abcabc", "abc");
    TEST("strtrim all trimmed", s && strcmp(s, "") == 0);
    free(s);
    
    s = ft_strtrim("xxxhelloxxx", "x");
    TEST("strtrim both sides", s && strcmp(s, "hello") == 0);
    free(s);
    
    s = ft_strtrim("hello", "");
    TEST("strtrim empty set", s && strcmp(s, "hello") == 0);
    free(s);
    
    s = ft_strtrim("   ", " ");
    TEST("strtrim only spaces", s && strcmp(s, "") == 0);
    free(s);
    
    // Ultra-sneaky tests from test_ultra_sneaky.c
    s = ft_strtrim("abc", "abc");
    TEST("strtrim set contains all", s && strcmp(s, "") == 0);
    free(s);
    
    s = ft_strtrim("xyzHELLOxyz", "abcdefghijklmnopqrstuvwxyz");
    TEST("strtrim long set", s && strcmp(s, "HELLO") == 0);
    free(s);
    
    s = ft_strtrim("\n\t\r  hello  \n\t\r", " \t\n\r");
    TEST("strtrim special chars", s && strcmp(s, "hello") == 0);
    free(s);
    
    if (fail_count == 0) {
        printf("test_strtrim: OK (%d tests passed)\n", test_count);
        return 0;
    } else {
        fprintf(stderr, "\n❌ %d/%d tests failed\n", fail_count, test_count);
        return 1;
    }
}
