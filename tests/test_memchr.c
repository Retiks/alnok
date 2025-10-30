// test_memchr.c
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
    const char *s = "abcdefg";
    
    // Basic tests
    TEST("memchr find 'd'", memchr(s, 'd', strlen(s)) == ft_memchr(s, 'd', strlen(s)));
    TEST("memchr absent", ft_memchr(s,'z',strlen(s)) == NULL);
    
    // Edge cases from test_edge_cases.c
    char buf[] = "hello\0world";
    TEST("memchr finds null", ft_memchr(buf, '\0', 11) == memchr(buf, '\0', 11));
    TEST("memchr after null", ft_memchr(buf, 'w', 11) == memchr(buf, 'w', 11));
    TEST("memchr not found", ft_memchr("test", 'x', 4) == NULL);
    
    // Ultra-sneaky tests from test_ultra_sneaky.c
    char mem[20] = "hello\0world";
    TEST("memchr ultra after null", ft_memchr(mem, 'w', 11) == mem + 6);
    TEST("memchr ultra finds null", ft_memchr(mem, '\0', 11) == mem + 5);
    mem[0] = (char)0xff;
    TEST("memchr negative byte", ft_memchr(mem, 0xff, 20) == mem);
    TEST("memchr negative as int", ft_memchr(mem, -1, 20) == mem);
    TEST("memchr n=0", ft_memchr("test", 't', 0) == NULL);
    
    if (fail_count == 0) {
        printf("test_memchr: OK (%d tests passed)\n", test_count);
        return 0;
    } else {
        fprintf(stderr, "\n❌ %d/%d tests failed\n", fail_count, test_count);
        return 1;
    }
}
