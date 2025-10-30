// test_memmove.c
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
    // Basic tests
    char a[32] = "0123456789abcdef";
    char b[32] = "0123456789abcdef";
    memmove(a+2, a, 8);
    ft_memmove(b+2, b, 8);
    TEST("memmove forward", memcmp(a,b,32) == 0);
    
    strcpy(a,"0123456789abcdef");
    strcpy(b,"0123456789abcdef");
    memmove(a, a+2, 8);
    ft_memmove(b, b+2, 8);
    TEST("memmove backward", memcmp(a,b,32) == 0);
    
    // Sneaky tests from test_sneaky_bugs.c
    char buf[20] = "0123456789";
    ft_memmove(buf + 2, buf, 5);
    TEST("memmove overlap forward", strcmp(buf, "0101234789") == 0);
    
    strcpy(buf, "0123456789");
    ft_memmove(buf, buf + 2, 5);
    TEST("memmove overlap backward", strcmp(buf, "2345656789") == 0);
    
    // Ultra-sneaky tests from test_ultra_sneaky.c
    strcpy(buf, "0123456789");
    ft_memmove(buf, buf, 10);
    TEST("memmove same pointer", strcmp(buf, "0123456789") == 0);
    
    if (fail_count == 0) {
        printf("test_memmove: OK (%d tests passed)\n", test_count);
        return 0;
    } else {
        fprintf(stderr, "\n❌ %d/%d tests failed\n", fail_count, test_count);
        return 1;
    }
}
