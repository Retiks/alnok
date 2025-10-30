// test_strlcat.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../libft.h"

/* portable reference */
static size_t ref_strlcat(char *dst, const char *src, size_t dstsize)
{
    size_t dl = strlen(dst);
    size_t sl = strlen(src);
    if (dstsize <= dl) return dstsize + sl;
    size_t copy = dstsize - dl - 1;
    if (copy > 0) {
        size_t c = sl < copy ? sl : copy;
        memcpy(dst + dl, src, c);
        dst[dl + c] = '\0';
    }
    return dl + sl;
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
    // Basic test
    char a1[10] = "Hi";
    char a2[10] = "Hi";
    size_t r1 = ft_strlcat(a1, "Hello", sizeof(a1));
    size_t r2 = ref_strlcat(a2, "Hello", sizeof(a2));
    TEST("strlcat basic", r1 == r2 && strcmp(a1,a2) == 0);
    
    // Edge cases from test_edge_cases.c
    char dst1[10] = "Hello";
    size_t ret = ft_strlcat(dst1, "World", 10);
    TEST("strlcat truncation", ret == 10 && strcmp(dst1, "HelloWorl") == 0);
    
    char dst2[5] = "Hi";
    ret = ft_strlcat(dst2, "Test", 2);
    TEST("strlcat size <= dstlen", ret == 6 && strcmp(dst2, "Hi") == 0);
    
    char dst3[10] = "";
    ret = ft_strlcat(dst3, "test", 10);
    TEST("strlcat empty dst", ret == 4 && strcmp(dst3, "test") == 0);
    
    // Sneaky tests from test_sneaky_bugs.c
    char dst4[20];
    memset(dst4, 'A', 20);
    dst4[5] = '\0';
    ret = ft_strlcat(dst4, "test", 20);
    TEST("strlcat with dst", ret == 9);
    
    char dst5[20] = "Hello";
    ret = ft_strlcat(dst5, "World", 3);
    TEST("strlcat dstsize < dst_len", ret == 8);
    TEST("strlcat doesn't modify when dstsize < dst_len", strcmp(dst5, "Hello") == 0);
    
    // Ultra-sneaky tests from test_ultra_sneaky.c
    char dst_u[10];
    memset(dst_u, 'X', 10);
    dst_u[5] = '\0';
    ret = ft_strlcat(dst_u, "test", 10);
    TEST("strlcat ultra dst with null", ret == 9);
    TEST("strlcat ultra result", strcmp(dst_u, "XXXXXtest") == 0);
    
    strcpy(dst_u, "Hello");
    ret = ft_strlcat(dst_u, "World", 3);
    TEST("strlcat ultra dstsize < dst_len", ret == 8);
    TEST("strlcat ultra no modification", strcmp(dst_u, "Hello") == 0);
    
    if (fail_count == 0) {
        printf("test_strlcat: OK (%d tests passed)\n", test_count);
        return 0;
    } else {
        fprintf(stderr, "\n❌ %d/%d tests failed\n", fail_count, test_count);
        return 1;
    }
}
