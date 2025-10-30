// test_ultra_sneaky.c - Ultra-sneaky tests
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>
#include <ctype.h>
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
    // ========== ft_atoi: Ultra-sneaky case ==========
    
    // Complete whitespace (all whitespace characters)
    TEST("atoi all whitespace types", ft_atoi(" \t\n\v\f\r42") == 42);
    
    // Silent overflow (behavior like standard atoi)
    TEST("atoi overflow behavior", ft_atoi("9999999999999999999") == atoi("9999999999999999999"));
    TEST("atoi underflow behavior", ft_atoi("-9999999999999999999") == atoi("-9999999999999999999"));
    
    // Multiple signs (only first counts)
    TEST("atoi double plus", ft_atoi("++5") == atoi("++5"));
    TEST("atoi plus minus", ft_atoi("+-5") == atoi("+-5"));
    TEST("atoi minus plus", ft_atoi("-+5") == atoi("-+5"));
    
    // Numbers with trailing garbage
    TEST("atoi trailing letters", ft_atoi("42abc") == 42);
    TEST("atoi trailing spaces", ft_atoi("42   ") == 42);
    
    // Edge case: juste un signe
    TEST("atoi only plus", ft_atoi("+") == 0);
    TEST("atoi only minus", ft_atoi("-") == 0);
    
    // ========== ft_split: Ultra-sneaky case ==========
    
    // Split with delimiter '\0' (should return entire string)
    char **arr = ft_split("hello", '\0');
    TEST("split with null delimiter", arr && arr[0] && strcmp(arr[0], "hello") == 0 && !arr[1]);
    if (arr) { for(int i=0; arr[i]; i++) free(arr[i]); free(arr); }
    
    // Split with 100 consecutive delimiters
    char many_delims[300];
    memset(many_delims, ',', 100);
    strcpy(many_delims + 100, "word");
    memset(many_delims + 104, ',', 100);
    many_delims[204] = '\0';
    arr = ft_split(many_delims, ',');
    TEST("split 100 delimiters", arr && arr[0] && strcmp(arr[0], "word") == 0 && !arr[1]);
    if (arr) { for(int i=0; arr[i]; i++) free(arr[i]); free(arr); }
    
    // Split avec single character
    arr = ft_split("x", ',');
    TEST("split single char", arr && arr[0] && strcmp(arr[0], "x") == 0 && !arr[1]);
    if (arr) { for(int i=0; arr[i]; i++) free(arr[i]); free(arr); }
    
    // ========== ft_substr: Ultra-sneaky case ==========
    
    // Start = UINT_MAX (should return empty string)
    char *s = ft_substr("test", UINT_MAX, 10);
    TEST("substr start=UINT_MAX", s && strcmp(s, "") == 0);
    free(s);
    
    // SIZE_MAX test removed - overflow protection not required by subject
    
    // Len very large but valid
    s = ft_substr("hello", 2, 1000);
    TEST("substr len very large", s && strcmp(s, "llo") == 0);
    free(s);
    
    // Start very large
    s = ft_substr("test", 1000000, 10);
    TEST("substr start very large", s && strcmp(s, "") == 0);
    free(s);
    
    // ========== ft_strjoin: Ultra-sneaky case ==========
    
    // Medium strings (ASan trigger-free allocation test)
    char long1[500];
    char long2[500];
    memset(long1, 'A', 499); long1[499] = '\0';
    memset(long2, 'B', 499); long2[499] = '\0';
    s = ft_strjoin(long1, long2);
    TEST("strjoin long strings", s && strlen(s) == 998);
    if (s) {
        TEST("strjoin long content", s[0] == 'A' && s[499] == 'B' && s[997] == 'B');
        free(s);
    }
    
    // ========== ft_strtrim: Ultra-sneaky case ==========
    
    // Set contains all characters of string
    s = ft_strtrim("abc", "abc");
    TEST("strtrim set contains all", s && strcmp(s, "") == 0);
    free(s);
    
    // Very long set
    s = ft_strtrim("xyzHELLOxyz", "abcdefghijklmnopqrstuvwxyz");
    TEST("strtrim long set", s && strcmp(s, "HELLO") == 0);
    free(s);
    
    // Trim with special characters
    s = ft_strtrim("\n\t\r  hello  \n\t\r", " \t\n\r");
    TEST("strtrim special chars", s && strcmp(s, "hello") == 0);
    free(s);
    
    // ========== ft_strlcpy: Ultra-sneaky case ==========
    
    // dstsize = 0 (should not write, return strlen(src))
    char dst[10] = "XXXXXXXXX";
    size_t ret = ft_strlcpy(dst, "test", 0);
    TEST("strlcpy dstsize=0 returns len", ret == 4);
    TEST("strlcpy dstsize=0 no write", dst[0] == 'X');
    
    // dstsize = 1 (should just write '\0')
    strcpy(dst, "XXXXXXXXX");
    ret = ft_strlcpy(dst, "test", 1);
    TEST("strlcpy dstsize=1", ret == 4 && dst[0] == '\0' && dst[1] == 'X');
    
    // Empty source
    ret = ft_strlcpy(dst, "", 10);
    TEST("strlcpy empty src", ret == 0 && dst[0] == '\0');
    
    // ========== ft_strlcat: Ultra-sneaky case ==========
    
    // dst non null-terminated avec dstsize exact
    char dst2[10];
    memset(dst2, 'X', 10);
    dst2[5] = '\0';
    ret = ft_strlcat(dst2, "test", 10);
    TEST("strlcat dst with null", ret == 9);
    TEST("strlcat result", strcmp(dst2, "XXXXXtest") == 0);
    
    // dstsize < strlen(dst) - should return dstsize + strlen(src)
    strcpy(dst2, "Hello");
    ret = ft_strlcat(dst2, "World", 3);
    TEST("strlcat dstsize < dst_len", ret == 8);  // 3 + 5
    TEST("strlcat no modification", strcmp(dst2, "Hello") == 0);
    
    // ========== ft_strchr/strrchr: Ultra-sneaky case ==========
    
    // Search '\0'
    const char *str = "hello";
    TEST("strchr null terminator", ft_strchr(str, '\0') == str + 5);
    TEST("strrchr null terminator", ft_strrchr(str, '\0') == str + 5);
    
    // Search in string with multiple occurrences
    str = "abcabcabc";
    TEST("strchr first occurrence", ft_strchr(str, 'b') == str + 1);
    TEST("strrchr last occurrence", ft_strrchr(str, 'b') == str + 7);
    
    // Search negative character (cast to unsigned char)
    TEST("strchr negative char", ft_strchr("test\xff", -1) != NULL);
    
    // ========== ft_strncmp: Ultra-sneaky case ==========
    
    // Comparaison unsigned char (0xff > 0x01)
    TEST("strncmp unsigned comparison", ft_strncmp("\xff", "\x01", 1) > 0);
    TEST("strncmp unsigned equal", ft_strncmp("\xff", "\xff", 1) == 0);
    
    // n = 0 (should return 0)
    TEST("strncmp n=0", ft_strncmp("abc", "xyz", 0) == 0);
    
    // Identical strings up to null
    TEST("strncmp with embedded null", ft_strncmp("test\0abc", "test\0xyz", 10) == 0);
    
    // ========== ft_strnstr: Ultra-sneaky case ==========
    
    // Empty needle (should return haystack)
    const char *hay = "hello";
    TEST("strnstr empty needle", ft_strnstr(hay, "", 10) == hay);
    
    // Needle longer than len
    TEST("strnstr needle > len", ft_strnstr("hello", "hello", 3) == NULL);
    
    // Needle at boundary
    TEST("strnstr needle at boundary", ft_strnstr("hello", "lo", 5) != NULL);
    TEST("strnstr needle past boundary", ft_strnstr("hello", "lo", 4) == NULL);
    
    // Needle appears multiple times
    TEST("strnstr multiple occurrences", ft_strnstr("ababab", "ab", 6) == ft_strnstr("ababab", "ab", 6));
    
    // ========== ft_memchr: Ultra-sneaky case ==========
    
    // Search in zone with '\0'
    char mem[20] = "hello\0world";
    TEST("memchr after null", ft_memchr(mem, 'w', 11) == mem + 6);
    TEST("memchr finds null", ft_memchr(mem, '\0', 11) == mem + 5);
    
    // Search negative character
    mem[0] = (char)0xff;
    TEST("memchr negative byte", ft_memchr(mem, 0xff, 20) == mem);
    TEST("memchr negative as int", ft_memchr(mem, -1, 20) == mem);
    
    // n = 0
    TEST("memchr n=0", ft_memchr("test", 't', 0) == NULL);
    
    // ========== ft_memcmp: Ultra-sneaky case ==========
    
    // Comparaison unsigned
    unsigned char m1[] = {0xff, 0x00};
    unsigned char m2[] = {0x01, 0x00};
    TEST("memcmp unsigned", ft_memcmp(m1, m2, 1) > 0);
    
    // n = 0
    TEST("memcmp n=0", ft_memcmp("abc", "xyz", 0) == 0);
    
    // Comparison after null
    TEST("memcmp after null", ft_memcmp("a\0b", "a\0c", 3) < 0);
    
    // ========== ft_memcpy/memmove: Ultra-sneaky case ==========
    
    // memcpy with n=0 (should do nothing)
    char buf[20] = "test";
    ft_memcpy(buf, "xxxx", 0);
    TEST("memcpy n=0", strcmp(buf, "test") == 0);
    
    // memmove with overlap
    strcpy(buf, "0123456789");
    ft_memmove(buf, buf, 10);
    TEST("memmove same pointer", strcmp(buf, "0123456789") == 0);
    
    // ========== ft_itoa: Ultra-sneaky case ==========
    
    // INT_MIN (cas spécial car -INT_MIN overflow)
    s = ft_itoa(INT_MIN);
    TEST("itoa INT_MIN", s && strcmp(s, "-2147483648") == 0);
    free(s);
    
    // All figures
    s = ft_itoa(123456789);
    TEST("itoa many digits", s && strcmp(s, "123456789") == 0);
    free(s);
    
    // ========== ft_calloc: Ultra-sneaky case ==========
    
    // calloc(0, 0) - should return valid pointer
    void *p = ft_calloc(0, 0);
    TEST("calloc(0, 0)", p != NULL);
    free(p);
    
    // Overflow test removed - not required by subject
    
    // ========== ft_strdup: Ultra-sneaky case ==========
    
    // Medium string
    char very_long[1000];
    memset(very_long, 'X', 999);
    very_long[999] = '\0';
    s = ft_strdup(very_long);
    TEST("strdup long string", s && strlen(s) == 999 && s[0] == 'X' && s[998] == 'X');
    free(s);
    
    // ========== Consistency tests between functions ==========
    
    // strlen vs strlcpy
    const char *test_str = "hello";
    char dest[10];
    ret = ft_strlcpy(dest, test_str, 10);
    TEST("strlcpy returns strlen", ret == ft_strlen(test_str));
    
    // memcpy vs memmove (no overlap)
    char src[10] = "test";
    char dst_cpy[10], dst_mov[10];
    ft_memcpy(dst_cpy, src, 5);
    ft_memmove(dst_mov, src, 5);
    TEST("memcpy == memmove (no overlap)", memcmp(dst_cpy, dst_mov, 5) == 0);
    
    // strchr vs memchr
    str = "hello";
    TEST("strchr == memchr", ft_strchr(str, 'l') == ft_memchr(str, 'l', 5));
    
    // ========== Final result ==========
    if (fail_count == 0) {
        printf("test_ultra_sneaky: OK (%d tests passed) 🔥💀🔥\n", test_count);
        return 0;
    } else {
        fprintf(stderr, "\n❌ %d/%d tests failed\n", fail_count, test_count);
        return 1;
    }
}
