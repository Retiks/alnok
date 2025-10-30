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
        fprintf(stderr, "FAIL [%d]: %s\n", test_count, name); \
        fail_count++; \
    } \
} while(0)

int main(void)
{
    char *s;
    
    // Basic test
    s = ft_strjoin("Hello", " World");
    TEST("strjoin basic", s && strcmp(s, "Hello World") == 0);
    free(s);
    
    // Edge cases from test_edge_cases.c
    s = ft_strjoin("", "");
    TEST("strjoin both empty", s && strcmp(s, "") == 0);
    free(s);
    
    s = ft_strjoin("test", "");
    TEST("strjoin s2 empty", s && strcmp(s, "test") == 0);
    free(s);
    
    s = ft_strjoin("", "test");
    TEST("strjoin s1 empty", s && strcmp(s, "test") == 0);
    free(s);
    
    // Ultra-sneaky tests from test_ultra_sneaky.c
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
    
    if (fail_count == 0) {
        printf("test_strjoin: OK (%d tests passed)\n", test_count);
        return 0;
    } else {
        fprintf(stderr, "\nFAIL %d/%d tests failed\n", fail_count, test_count);
        return 1;
    }
}
