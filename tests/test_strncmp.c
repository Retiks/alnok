// test_strncmp.c
#include <stdio.h>
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
    TEST("strncmp 2", ft_strncmp("abc","abd",2) == strncmp("abc","abd",2));
    TEST("strncmp long", ft_strncmp("abc","abc",10) == strncmp("abc","abc",10));
    TEST("strncmp zero", ft_strncmp("","",0) == strncmp("","",0));
    
    // Edge cases from test_edge_cases.c
    TEST("strncmp n=0", ft_strncmp("abc", "xyz", 0) == 0);
    TEST("strncmp with null byte", ft_strncmp("test\0abc", "test\0xyz", 10) == 0);
    TEST("strncmp unsigned char", ft_strncmp("\xff", "\x01", 1) > 0);
    
    // Ultra-sneaky tests from test_ultra_sneaky.c
    TEST("strncmp unsigned comparison", ft_strncmp("\xff", "\x01", 1) > 0);
    TEST("strncmp unsigned equal", ft_strncmp("\xff", "\xff", 1) == 0);
    TEST("strncmp ultra n=0", ft_strncmp("abc", "xyz", 0) == 0);
    TEST("strncmp with embedded null", ft_strncmp("test\0abc", "test\0xyz", 10) == 0);
    
    if (fail_count == 0) {
        printf("test_strncmp: OK (%d tests passed)\n", test_count);
        return 0;
    } else {
        fprintf(stderr, "\n❌ %d/%d tests failed\n", fail_count, test_count);
        return 1;
    }
}
