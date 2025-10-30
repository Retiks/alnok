// test_memcmp.c
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
    // Basic test
    char a[] = "abcdef";
    char b[] = "abcdeg";
    int r1 = memcmp(a,b,6);
    int r2 = ft_memcmp(a,b,6);
    TEST("memcmp basic", (r1==0) == (r2==0) && (r1<0) == (r2<0) && (r1>0) == (r2>0));
    
    // Edge cases from test_edge_cases.c
    TEST("memcmp n=0", ft_memcmp("abc", "xyz", 0) == 0);
    TEST("memcmp after null", memcmp("a\0b", "a\0c", 3) == ft_memcmp("a\0b", "a\0c", 3));
    
    // Ultra-sneaky tests from test_ultra_sneaky.c
    unsigned char m1[] = {0xff, 0x00};
    unsigned char m2[] = {0x01, 0x00};
    TEST("memcmp unsigned", ft_memcmp(m1, m2, 1) > 0);
    TEST("memcmp ultra n=0", ft_memcmp("abc", "xyz", 0) == 0);
    TEST("memcmp ultra after null", ft_memcmp("a\0b", "a\0c", 3) < 0);
    
    if (fail_count == 0) {
        printf("test_memcmp: OK (%d tests passed)\n", test_count);
        return 0;
    } else {
        fprintf(stderr, "\n❌ %d/%d tests failed\n", fail_count, test_count);
        return 1;
    }
}
