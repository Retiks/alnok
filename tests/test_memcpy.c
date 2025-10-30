// test_memcpy.c
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
    char src[32] = "This is a test for memcpy";
    char d1[32], d2[32];
    memcpy(d1, src, strlen(src)+1);
    ft_memcpy(d2, src, strlen(src)+1);
    TEST("memcpy basic", strcmp(d1,d2) == 0);
    
    strcpy(d1,"X");
    strcpy(d2,"X");
    memcpy(d1, src, 0);
    ft_memcpy(d2, src, 0);
    TEST("memcpy size0", d1[0] == d2[0]);
    
    // Ultra-sneaky tests from test_ultra_sneaky.c
    char buf[20] = "test";
    ft_memcpy(buf, "xxxx", 0);
    TEST("memcpy n=0", strcmp(buf, "test") == 0);
    
    if (fail_count == 0) {
        printf("test_memcpy: OK (%d tests passed)\n", test_count);
        return 0;
    } else {
        fprintf(stderr, "\n❌ %d/%d tests failed\n", fail_count, test_count);
        return 1;
    }
}
