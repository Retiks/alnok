// test_strlcpy.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../libft.h"

/* portable reference */
static size_t ref_strlcpy(char *dst, const char *src, size_t dstsize)
{
    size_t sl = strlen(src);
    if (dstsize) {
        size_t c = sl >= dstsize ? dstsize - 1 : sl;
        memcpy(dst, src, c);
        dst[c] = '\0';
    }
    return sl;
}

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
    char d1[5], d2[5];
    const char *s = "HelloWorld";
    size_t r1 = ft_strlcpy(d1, s, sizeof(d1));
    size_t r2 = ref_strlcpy(d2, s, sizeof(d2));
    TEST("strlcpy basic", r1 == r2 && strcmp(d1,d2) == 0);
    
    char z1[1] = {'X'}, z2[1]={'X'};
    TEST("strlcpy zero", ft_strlcpy(z1,"ABC",0) == ref_strlcpy(z2,"ABC",0));
    
    // Sneaky tests from test_sneaky_bugs.c
    char dst1[10];
    size_t ret = ft_strlcpy(dst1, "test", 10);
    TEST("strlcpy returns src length", ret == 4);
    TEST("strlcpy copies correctly", strcmp(dst1, "test") == 0);
    
    char dst2[10] = "XXXXXXXX";
    ret = ft_strlcpy(dst2, "test", 0);
    TEST("strlcpy dstsize=0 returns src len", ret == 4);
    TEST("strlcpy dstsize=0 doesn't write", dst2[0] == 'X');
    
    char dst3[10] = "XXXXXXXX";
    ret = ft_strlcpy(dst3, "test", 1);
    TEST("strlcpy dstsize=1 returns src len", ret == 4);
    TEST("strlcpy dstsize=1 writes only null", dst3[0] == '\0' && dst3[1] == 'X');
    
    // Ultra-sneaky tests from test_ultra_sneaky.c
    char dst_u[10] = "XXXXXXXXX";
    ret = ft_strlcpy(dst_u, "test", 0);
    TEST("strlcpy ultra dstsize=0 returns len", ret == 4);
    TEST("strlcpy ultra dstsize=0 no write", dst_u[0] == 'X');
    
    strcpy(dst_u, "XXXXXXXXX");
    ret = ft_strlcpy(dst_u, "test", 1);
    TEST("strlcpy ultra dstsize=1", ret == 4 && dst_u[0] == '\0' && dst_u[1] == 'X');
    
    ret = ft_strlcpy(dst_u, "", 10);
    TEST("strlcpy empty src", ret == 0 && dst_u[0] == '\0');
    
    if (fail_count == 0) {
        printf("test_strlcpy: OK (%d tests passed)\n", test_count);
        return 0;
    } else {
        fprintf(stderr, "\n❌ %d/%d tests failed\n", fail_count, test_count);
        return 1;
    }
}
