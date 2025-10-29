// test_edge_cases.c - Tests traîtres et cas limites vicieux
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>
#include "../libft.h"

static int test_count = 0;
static int fail_count = 0;

#define TEST(name, cond) do { \
    test_count++; \
    if (!(cond)) { \
        fprintf(stderr, "❌ FAIL [%d]: %s\n", test_count, name); \
        fail_count++; \
    } \
} while(0)

int main(void)
{
    // ========== ft_atoi: cas traîtres ==========
    // Overflow INT_MAX
    TEST("atoi overflow", ft_atoi("2147483648") == atoi("2147483648"));
    TEST("atoi underflow", ft_atoi("-2147483649") == atoi("-2147483649"));
    TEST("atoi whitespace mix", ft_atoi("  \t\n\v\f\r 42") == 42);
    TEST("atoi multiple signs", ft_atoi("+-42") == atoi("+-42"));
    TEST("atoi only whitespace", ft_atoi("   \t\n") == 0);
    
    // ========== ft_substr: cas limites ==========
    char *s;
    s = ft_substr("", 0, 5);
    TEST("substr empty string", s && strcmp(s, "") == 0);
    free(s);
    
    s = ft_substr("test", 0, 0);
    TEST("substr len=0", s && strcmp(s, "") == 0);
    free(s);
    
    s = ft_substr("hello", 2, 100);
    TEST("substr len > remaining", s && strcmp(s, "llo") == 0);
    free(s);
    
    s = ft_substr("test", 10, 5);
    TEST("substr start >= strlen", s && strcmp(s, "") == 0);
    free(s);
    
    // ========== ft_split: cas vicieux ==========
    char **arr;
    
    arr = ft_split("", 'x');
    TEST("split empty string", arr && arr[0] == NULL);
    free(arr);
    
    arr = ft_split("xxx", 'x');
    TEST("split only delimiters", arr && arr[0] == NULL);
    free(arr);
    
    arr = ft_split("hello", '\0');
    TEST("split null delimiter", arr && arr[0] && strcmp(arr[0], "hello") == 0 && arr[1] == NULL);
    if (arr) { for(int i=0; arr[i]; i++) free(arr[i]); free(arr); }
    
    arr = ft_split("   a   b   ", ' ');
    TEST("split multiple spaces", arr && arr[0] && strcmp(arr[0], "a") == 0 && arr[1] && strcmp(arr[1], "b") == 0);
    if (arr) { for(int i=0; arr[i]; i++) free(arr[i]); free(arr); }
    
    // ========== ft_strjoin: cas limites ==========
    s = ft_strjoin("", "");
    TEST("strjoin both empty", s && strcmp(s, "") == 0);
    free(s);
    
    s = ft_strjoin("test", "");
    TEST("strjoin s2 empty", s && strcmp(s, "test") == 0);
    free(s);
    
    s = ft_strjoin("", "test");
    TEST("strjoin s1 empty", s && strcmp(s, "test") == 0);
    free(s);
    
    // ========== ft_strtrim: cas traîtres ==========
    s = ft_strtrim("", "abc");
    TEST("strtrim empty string", s && strcmp(s, "") == 0);
    free(s);
    
    s = ft_strtrim("abcabc", "abc");
    TEST("strtrim all trimmed", s && strcmp(s, "") == 0);
    free(s);
    
    s = ft_strtrim("xxxhelloxxx", "x");
    TEST("strtrim both sides", s && strcmp(s, "hello") == 0);
    free(s);
    
    s = ft_strtrim("hello", "");
    TEST("strtrim empty set", s && strcmp(s, "hello") == 0);
    free(s);
    
    s = ft_strtrim("   ", " ");
    TEST("strtrim only spaces", s && strcmp(s, "") == 0);
    free(s);
    
    // ========== ft_strnstr: cas vicieux ==========
    TEST("strnstr needle at end", ft_strnstr("hello", "lo", 5) != NULL);
    TEST("strnstr len too short", ft_strnstr("hello", "lo", 4) == NULL);
    TEST("strnstr needle longer", ft_strnstr("hi", "hello", 10) == NULL);
    const char *test_str = "test";
    TEST("strnstr empty needle", ft_strnstr(test_str, "", 10) == test_str);
    TEST("strnstr len=0", ft_strnstr("test", "t", 0) == NULL);
    
    // ========== ft_memchr: cas limites ==========
    char buf[] = "hello\0world";
    TEST("memchr finds null", ft_memchr(buf, '\0', 11) == memchr(buf, '\0', 11));
    TEST("memchr after null", ft_memchr(buf, 'w', 11) == memchr(buf, 'w', 11));
    TEST("memchr not found", ft_memchr("test", 'x', 4) == NULL);
    
    // ========== ft_calloc: overflow protection ==========
    void *p = ft_calloc(SIZE_MAX, SIZE_MAX);
    TEST("calloc overflow SIZE_MAX*SIZE_MAX", p == NULL);
    if (p) free(p);
    
    p = ft_calloc(SIZE_MAX / 2, 3);
    TEST("calloc overflow SIZE_MAX/2 * 3", p == NULL);
    if (p) free(p);
    
    p = ft_calloc(SIZE_MAX, 2);
    TEST("calloc overflow SIZE_MAX * 2", p == NULL);
    if (p) free(p);
    
    // Test normal calloc behavior
    p = ft_calloc(100, 1);
    TEST("calloc normal allocation", p != NULL);
    if (p) {
        unsigned char *bytes = (unsigned char*)p;
        int all_zero = 1;
        for (int i = 0; i < 100; i++) {
            if (bytes[i] != 0) all_zero = 0;
        }
        TEST("calloc zeroes memory", all_zero);
        free(p);
    }
    
    // ========== ft_itoa: cas limites ==========
    s = ft_itoa(0);
    TEST("itoa zero", s && strcmp(s, "0") == 0);
    free(s);
    
    s = ft_itoa(INT_MIN);
    TEST("itoa INT_MIN", s && strcmp(s, "-2147483648") == 0);
    free(s);
    
    s = ft_itoa(INT_MAX);
    TEST("itoa INT_MAX", s && strcmp(s, "2147483647") == 0);
    free(s);
    
    s = ft_itoa(-1);
    TEST("itoa -1", s && strcmp(s, "-1") == 0);
    free(s);
    
    // ========== ft_strlcat: cas traîtres ==========
    char dst1[10] = "Hello";
    size_t ret = ft_strlcat(dst1, "World", 10);
    TEST("strlcat truncation", ret == 10 && strcmp(dst1, "HelloWorl") == 0);
    
    char dst2[5] = "Hi";
    ret = ft_strlcat(dst2, "Test", 2);
    TEST("strlcat size <= dstlen", ret == 6 && strcmp(dst2, "Hi") == 0);
    
    char dst3[10] = "";
    ret = ft_strlcat(dst3, "test", 10);
    TEST("strlcat empty dst", ret == 4 && strcmp(dst3, "test") == 0);
    
    // ========== ft_strncmp: cas vicieux ==========
    TEST("strncmp n=0", ft_strncmp("abc", "xyz", 0) == 0);
    TEST("strncmp with null byte", ft_strncmp("test\0abc", "test\0xyz", 10) == 0);
    TEST("strncmp unsigned char", ft_strncmp("\xff", "\x01", 1) > 0);
    
    // ========== ft_memcmp: cas limites ==========
    TEST("memcmp n=0", ft_memcmp("abc", "xyz", 0) == 0);
    TEST("memcmp after null", memcmp("a\0b", "a\0c", 3) == ft_memcmp("a\0b", "a\0c", 3));
    
    // ========== Résultat final ==========
    if (fail_count == 0) {
        printf("test_edge_cases: OK (%d tests passed)\n", test_count);
        return 0;
    } else {
        fprintf(stderr, "\n❌ %d/%d tests failed\n", fail_count, test_count);
        return 1;
    }
}
