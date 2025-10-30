// test_strchr.c
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
    const char *s = "abc\0def";
    TEST("strchr find 'a'", ft_strchr(s,'a') == strchr(s,'a'));
    TEST("strchr find NUL", ft_strchr(s,'\0') == strchr(s,'\0'));
    TEST("strchr not found", ft_strchr(s,'z') == strchr(s,'z'));
    
    // Sneaky tests from test_sneaky_bugs.c
    const char *str = "hello";
    TEST("strchr finds null terminator", ft_strchr(str, '\0') == str + 5);
    TEST("strchr not found z", ft_strchr(str, 'z') == NULL);
    
    // Ultra-sneaky tests from test_ultra_sneaky.c
    str = "abcabcabc";
    TEST("strchr first occurrence", ft_strchr(str, 'b') == str + 1);
    TEST("strchr negative char", ft_strchr("test\xff", -1) != NULL);
    
    if (fail_count == 0) {
        printf("test_strchr: OK (%d tests passed)\n", test_count);
        return 0;
    } else {
        fprintf(stderr, "\n❌ %d/%d tests failed\n", fail_count, test_count);
        return 1;
    }
}
