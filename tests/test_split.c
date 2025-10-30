// test_split.c
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
    char **arr;
    
    // Basic test
    arr = ft_split(",a,,b,", ',');
    TEST("split basic", arr && arr[0] && strcmp(arr[0], "a") == 0 && arr[1] && strcmp(arr[1], "b") == 0 && arr[2] == NULL);
    if (arr) { for(int i=0; arr[i]; i++) free(arr[i]); free(arr); }
    
    // Edge cases from test_edge_cases.c
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
    
    // Sneaky tests from test_sneaky_bugs.c
    arr = ft_split("a b c d e f g h", ' ');
    TEST("split normal case", arr != NULL);
    if (arr) {
        TEST("split count", arr[0] && arr[7] && !arr[8]);
        for (int i = 0; arr[i]; i++) free(arr[i]);
        free(arr);
    }
    
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
    
    // Ultra-sneaky tests from test_ultra_sneaky.c
    char many_delims[300];
    memset(many_delims, ',', 100);
    strcpy(many_delims + 100, "word");
    memset(many_delims + 104, ',', 100);
    many_delims[204] = '\0';
    arr = ft_split(many_delims, ',');
    TEST("split 100 delimiters", arr && arr[0] && strcmp(arr[0], "word") == 0 && !arr[1]);
    if (arr) { for(int i=0; arr[i]; i++) free(arr[i]); free(arr); }
    
    arr = ft_split("x", ',');
    TEST("split single char", arr && arr[0] && strcmp(arr[0], "x") == 0 && !arr[1]);
    if (arr) { for(int i=0; arr[i]; i++) free(arr[i]); free(arr); }
    
    if (fail_count == 0) {
        printf("test_split: OK (%d tests passed)\n", test_count);
        return 0;
    } else {
        fprintf(stderr, "\n❌ %d/%d tests failed\n", fail_count, test_count);
        return 1;
    }
}
