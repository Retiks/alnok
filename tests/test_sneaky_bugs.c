// test_sneaky_bugs.c - Sneaky tests that often break projects
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
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
    // ========== ft_strlcpy: Classic bug line 30 ==========
    // Your code does i++ after null terminator, which is wrong
    char dst1[10];
    size_t ret = ft_strlcpy(dst1, "test", 10);
    TEST("strlcpy returns src length", ret == 4);
    TEST("strlcpy copies correctly", strcmp(dst1, "test") == 0);
    
    // Test with dstsize = 0 (should not write anything)
    char dst2[10] = "XXXXXXXX";
    ret = ft_strlcpy(dst2, "test", 0);
    TEST("strlcpy dstsize=0 returns src len", ret == 4);
    TEST("strlcpy dstsize=0 doesn't write", dst2[0] == 'X');
    
    // Test with dstsize = 1 (should just put '\0')
    char dst3[10] = "XXXXXXXX";
    ret = ft_strlcpy(dst3, "test", 1);
    TEST("strlcpy dstsize=1 returns src len", ret == 4);
    TEST("strlcpy dstsize=1 writes only null", dst3[0] == '\0' && dst3[1] == 'X');
    
    // ========== ft_strlcat: Bug with dst not null-terminated ==========
    // If dst is not null-terminated and dstsize > real strlen, crash possible
    char dst4[20];
    memset(dst4, 'A', 20);  // No '\0' !
    dst4[5] = '\0';  // We put a '\0' at position 5
    ret = ft_strlcat(dst4, "test", 20);
    TEST("strlcat with dst", ret == 9);  // 5 + 4
    
    // Test strlcat with dstsize <= strlen(dst)
    char dst5[20] = "Hello";
    ret = ft_strlcat(dst5, "World", 3);
    TEST("strlcat dstsize < dst_len", ret == 8);  // 3 + 5
    TEST("strlcat doesn't modify when dstsize < dst_len", strcmp(dst5, "Hello") == 0);
    
    // ========== ft_split: Allocation failure in middle ==========
    // If malloc fails in middle, must free what was allocated
    char **arr = ft_split("a b c d e f g h", ' ');
    TEST("split normal case", arr != NULL);
    if (arr) {
        TEST("split count", arr[0] && arr[7] && !arr[8]);
        for (int i = 0; arr[i]; i++) free(arr[i]);
        free(arr);
    }
    
    // Split with single very long word
    char long_word[1000];
    memset(long_word, 'a', 999);
    long_word[999] = '\0';
    arr = ft_split(long_word, ' ');
    TEST("split single long word", arr && arr[0] && !arr[1]);
    if (arr) {
        TEST("split long word content", strlen(arr[0]) == 999);
        for (int i = 0; arr[i]; i++) free(arr[i]);
        free(arr);
    }
    
    // ========== ft_substr: Case where start + len > strlen ==========
    char *s = ft_substr("0123456789", 5, 100);
    TEST("substr start+len > strlen", s && strcmp(s, "56789") == 0);
    free(s);
    
    s = ft_substr("hello", 0, 2);
    TEST("substr partial", s && strcmp(s, "he") == 0);
    free(s);
    
    s = ft_substr("test", 4, 10);
    TEST("substr start at end", s && strcmp(s, "") == 0);
    free(s);
    
    // ========== ft_strjoin: With empty strings ==========
    s = ft_strjoin("", "");
    TEST("strjoin empty+empty", s && strcmp(s, "") == 0);
    free(s);
    
    // ========== ft_strjoin: NULL tests (defensive coding - optional) ==========
    // Note: Subject doesn't require NULL handling, but it's good practice.
    // These tests are OPTIONAL - passing NULL is undefined behavior.
    
    s = ft_strjoin(NULL, "test");
    TEST("strjoin NULL+string returns NULL (defensive)", s == NULL);
    if (s) free(s);
    
    s = ft_strjoin("test", NULL);
    TEST("strjoin string+NULL returns NULL (defensive)", s == NULL);
    if (s) free(s);
    
    s = ft_strjoin(NULL, NULL);
    TEST("strjoin NULL+NULL returns NULL (defensive)", s == NULL);
    if (s) free(s)
    
    // ========== ft_strtrim: Trim all and NULL ==========
    s = ft_strtrim("   ", " ");
    TEST("strtrim all spaces", s && strcmp(s, "") == 0);
    
    s = ft_strtrim("abcabc", "abc");
    TEST("strtrim everything", s && strcmp(s, "") == 0);
    
    s = ft_strtrim("xxxHELLOxxx", "x");
    TEST("strtrim both sides", s && strcmp(s, "HELLO") == 0);
    free(s);
    
    // ========== ft_strtrim: NULL tests (defensive coding - optional) ==========
    // Note: Subject doesn't require NULL handling, but it's good practice.
    // These tests are OPTIONAL - passing NULL is undefined behavior.
    
    s = ft_strtrim(NULL, "abc");
    TEST("strtrim NULL+set returns NULL (defensive)", s == NULL);
    if (s) free(s);
    
    s = ft_strtrim("test", NULL);
    TEST("strtrim string+NULL returns NULL (defensive)", s == NULL);
    if (s) free(s);
    
    // ========== ft_atoi: Whitespace and signs ==========
    TEST("atoi multiple spaces", ft_atoi("   \t\n\r\v\f  42") == 42);
    TEST("atoi plus sign", ft_atoi("+123") == 123);
    TEST("atoi multiple signs", ft_atoi("++123") == 0);
    TEST("atoi space after sign", ft_atoi("- 123") == 0);
    
    char buf[20] = "0123456789";
    ft_memmove(buf + 2, buf, 5);
    TEST("memmove overlap forward", strcmp(buf, "0101234789") == 0);
    
    strcpy(buf, "0123456789");
    ft_memmove(buf, buf + 2, 5);
    TEST("memmove overlap backward", strcmp(buf, "2345656789") == 0);
    
    // ========== ft_strncmp: Unsigned char comparison ==========
    TEST("strncmp unsigned", ft_strncmp("\xff", "\x01", 1) > 0);
    TEST("strncmp with null", ft_strncmp("test\0abc", "test\0xyz", 10) == 0);
    
    // ========== ft_strnstr: Edge cases ==========
    TEST("strnstr needle at boundary", ft_strnstr("hello", "lo", 5) != NULL);
    TEST("strnstr needle just past boundary", ft_strnstr("hello", "lo", 4) == NULL);
    
    const char *haystack = "lorem ipsum dolor sit amet";
    TEST("strnstr found", ft_strnstr(haystack, "dolor", 20) != NULL);
    TEST("strnstr not found (len)", ft_strnstr(haystack, "dolor", 10) == NULL);
    
    // ========== ft_strchr/strrchr: Chercher '\0' ==========
    const char *str = "hello";
    TEST("strchr finds null terminator", ft_strchr(str, '\0') == str + 5);
    TEST("strrchr finds null terminator", ft_strrchr(str, '\0') == str + 5);
    TEST("strchr not found", ft_strchr(str, 'z') == NULL);
    
    // ========== ft_memchr: Search in area with '\0' ==========
    char mem[] = "hello\0world";
    TEST("memchr finds after null", ft_memchr(mem, 'w', 11) == mem + 6);
    TEST("memchr finds null", ft_memchr(mem, '\0', 11) == mem + 5);
    
    // ========== ft_itoa: Limites ==========
    s = ft_itoa(INT_MIN);
    TEST("itoa INT_MIN", s && strcmp(s, "-2147483648") == 0);
    free(s);
    
    s = ft_itoa(INT_MAX);
    TEST("itoa INT_MAX", s && strcmp(s, "2147483647") == 0);
    free(s);
    
    s = ft_itoa(0);
    TEST("itoa zero", s && strcmp(s, "0") == 0);
    free(s);
    
    // ========== ft_strmapi/striteri: NULL tests (defensive coding - optional) ==========
    // Note: Subject doesn't require NULL handling, but it's good practice.
    // These tests are OPTIONAL - passing NULL is undefined behavior.
    
    char *mapped = ft_strmapi("test", NULL);
    TEST("strmapi with NULL function returns NULL (defensive)", mapped == NULL);
    if (mapped) free(mapped);
    
    ft_striteri(NULL, NULL);
    TEST("striteri with NULL doesn't crash (defensive)", 1)
    
    // ========== ft_calloc: Zero size ==========
    void *p = ft_calloc(0, 10);
    TEST("calloc(0, 10) returns non-NULL", p != NULL);
    free(p);
    
    p = ft_calloc(10, 0);
    TEST("calloc(10, 0) returns non-NULL", p != NULL);
    free(p);
    
    // ========== ft_strdup: Empty string ==========
    s = ft_strdup("");
    TEST("strdup empty string", s && strcmp(s, "") == 0);
    free(s);
    
    // ========== Résultat final ==========
    if (fail_count == 0) {
        printf("test_sneaky_bugs: OK (%d tests passed) 🎯\n", test_count);
        return 0;
    } else {
        fprintf(stderr, "\n❌ %d/%d tests failed\n", fail_count, test_count);
        return 1;
    }
}
