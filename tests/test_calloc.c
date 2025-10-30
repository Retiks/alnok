// test_calloc.c
#include <stdio.h>
#include <stdlib.h>
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
    void *p1 = ft_calloc(0, 10);
    void *p2 = ft_calloc(0, 20);
    TEST("calloc zero returns non-NULL", p1 && p2);
    TEST("calloc zero unique pointers", p1 != p2);
    free(p1); free(p2);
    
    unsigned char *p3 = ft_calloc(8,1);
    TEST("calloc(8,1) non-NULL", p3 != NULL);
    if (p3) {
        int all_zero = 1;
        for (int i=0;i<8;i++) if (p3[i] != 0) all_zero = 0;
        TEST("calloc zeroes memory", all_zero);
        free(p3);
    }
    
    // Ultra-sneaky tests from test_ultra_sneaky.c
    void *p = ft_calloc(0, 0);
    TEST("calloc(0, 0)", p != NULL);
    free(p);
    
    if (fail_count == 0) {
        printf("test_calloc: OK (%d tests passed)\n", test_count);
        return 0;
    } else {
        fprintf(stderr, "\n❌ %d/%d tests failed\n", fail_count, test_count);
        return 1;
    }
}
