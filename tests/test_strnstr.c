// test_strnstr.c
#include <stdio.h>
#include <string.h>
#include "../libft.h"

/* portable ref for strnstr */
static char *ref_strnstr(const char *hay, const char *nee, size_t len)
{
    if (!*nee) return (char*)hay;
    size_t nlen = strlen(nee);
    for (size_t i=0;i+ nlen<=len && hay[i]; ++i) {
        if (i + nlen > len) break;
        if (strncmp(hay+i, nee, nlen)==0) return (char*)(hay+i);
    }
    return NULL;
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
    const char *h = "hello world";
    
    // Basic tests
    TEST("strnstr world", ft_strnstr(h,"world",11) == ref_strnstr(h,"world",11));
    TEST("strnstr empty", ft_strnstr(h,"",5) == (char*)h);
    
    // Edge cases from test_edge_cases.c
    TEST("strnstr needle at end", ft_strnstr("hello", "lo", 5) != NULL);
    TEST("strnstr len too short", ft_strnstr("hello", "lo", 4) == NULL);
    TEST("strnstr needle longer", ft_strnstr("hi", "hello", 10) == NULL);
    const char *test_str = "test";
    TEST("strnstr empty needle", ft_strnstr(test_str, "", 10) == test_str);
    TEST("strnstr len=0", ft_strnstr("test", "t", 0) == NULL);
    
    // Sneaky tests from test_sneaky_bugs.c
    TEST("strnstr needle at boundary", ft_strnstr("hello", "lo", 5) != NULL);
    TEST("strnstr needle just past boundary", ft_strnstr("hello", "lo", 4) == NULL);
    const char *haystack = "lorem ipsum dolor sit amet";
    TEST("strnstr found", ft_strnstr(haystack, "dolor", 20) != NULL);
    TEST("strnstr not found (len)", ft_strnstr(haystack, "dolor", 10) == NULL);
    
    if (fail_count == 0) {
        printf("test_strnstr: OK (%d tests passed)\n", test_count);
        return 0;
    } else {
        fprintf(stderr, "\n❌ %d/%d tests failed\n", fail_count, test_count);
        return 1;
    }
}
