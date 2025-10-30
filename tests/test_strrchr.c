// test_strrchr.c
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
    const char *s = "abca";
    TEST("strrchr find 'a'", ft_strrchr(s,'a') == strrchr(s,'a'));
    TEST("strrchr not found", ft_strrchr(s,'z') == strrchr(s,'z'));
    
    // Sneaky tests from test_sneaky_bugs.c
    const char *str = "hello";
    TEST("strrchr finds null terminator", ft_strrchr(str, '\0') == str + 5);
    
    // Ultra-sneaky tests from test_ultra_sneaky.c
    str = "abcabcabc";
    TEST("strrchr last occurrence", ft_strrchr(str, 'b') == str + 7);
    
    if (fail_count == 0) {
        printf("test_strrchr: OK (%d tests passed)\n", test_count);
        return 0;
    } else {
        fprintf(stderr, "\n❌ %d/%d tests failed\n", fail_count, test_count);
        return 1;
    }
}
