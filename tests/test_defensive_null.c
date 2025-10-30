// test_defensive_null.c - Optional defensive coding tests for NULL parameters
// These tests are NOT required by the 42 subject (undefined behavior is allowed)
// They check if your functions handle NULL gracefully instead of segfaulting
// 
// ⚠️  WARNING: This test is designed to potentially segfault!
// Do NOT run with Valgrind or AddressSanitizer - they will crash
// Run directly: ./run_test_defensive_null

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <setjmp.h>
#include <ctype.h>
#include "../libft.h"

static int test_count = 0;
static int pass_count = 0;
static int fail_count = 0;
static jmp_buf segfault_jmp;

void segfault_handler(int sig) {
    (void)sig;
    longjmp(segfault_jmp, 1);
}

#define TEST_NULL(name, code) do { \
    test_count++; \
    signal(SIGSEGV, segfault_handler); \
    if (setjmp(segfault_jmp) == 0) { \
        code; \
        printf("✅ PASS [%d]: %s - handled NULL correctly\n", test_count, name); \
        pass_count++; \
    } else { \
        printf("⚠️  FAIL [%d]: %s - segfault (NULL not handled)\n", test_count, name); \
        fail_count++; \
    } \
    signal(SIGSEGV, SIG_DFL); \
} while(0)

int main(void)
{
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════════╗\n");
    printf("║  🛡️  DEFENSIVE CODING TESTS - NULL PARAMETER HANDLING         ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("⚠️  These tests are OPTIONAL - the 42 subject does NOT require\n");
    printf("   NULL handling. Passing NULL is undefined behavior.\n");
    printf("\n");
    printf("   However, implementing NULL checks is good practice and shows\n");
    printf("   defensive programming skills.\n");
    printf("\n");
    printf("───────────────────────────────────────────────────────────────\n");
    printf("\n");

    char *s;

    // ========== ft_strjoin NULL tests ==========
    printf("Testing ft_strjoin with NULL parameters:\n");
    
    TEST_NULL("ft_strjoin(NULL, \"test\")", {
        s = ft_strjoin(NULL, "test");
        if (s) free(s);
    });
    
    TEST_NULL("ft_strjoin(\"test\", NULL)", {
        s = ft_strjoin("test", NULL);
        if (s) free(s);
    });
    
    TEST_NULL("ft_strjoin(NULL, NULL)", {
        s = ft_strjoin(NULL, NULL);
        if (s) free(s);
    });
    
    printf("\n");

    // ========== ft_strtrim NULL tests ==========
    printf("Testing ft_strtrim with NULL parameters:\n");
    
    TEST_NULL("ft_strtrim(NULL, \"abc\")", {
        s = ft_strtrim(NULL, "abc");
        if (s) free(s);
    });
    
    TEST_NULL("ft_strtrim(\"test\", NULL)", {
        s = ft_strtrim("test", NULL);
        if (s) free(s);
    });
    
    TEST_NULL("ft_strtrim(NULL, NULL)", {
        s = ft_strtrim(NULL, NULL);
        if (s) free(s);
    });
    
    printf("\n");

    // ========== ft_substr NULL tests ==========
    printf("Testing ft_substr with NULL parameter:\n");
    
    TEST_NULL("ft_substr(NULL, 0, 5)", {
        s = ft_substr(NULL, 0, 5);
        if (s) free(s);
    });
    
    printf("\n");

    // ========== ft_split NULL tests ==========
    printf("Testing ft_split with NULL parameter:\n");
    
    TEST_NULL("ft_split(NULL, ' ')", {
        char **arr = ft_split(NULL, ' ');
        if (arr) {
            for (int i = 0; arr[i]; i++) free(arr[i]);
            free(arr);
        }
    });
    
    printf("\n");

    // ========== ft_strmapi NULL tests ==========
    printf("Testing ft_strmapi with NULL parameters:\n");
    
    TEST_NULL("ft_strmapi(\"test\", NULL)", {
        s = ft_strmapi("test", NULL);
        if (s) free(s);
    });
    
    TEST_NULL("ft_strmapi(NULL, function)", {
        s = ft_strmapi(NULL, (char (*)(unsigned int, char))toupper);
        if (s) free(s);
    });
    
    printf("\n");

    // ========== ft_striteri NULL tests ==========
    printf("Testing ft_striteri with NULL parameters:\n");
    
    TEST_NULL("ft_striteri(NULL, function)", {
        ft_striteri(NULL, NULL);
    });
    
    printf("\n");

    // ========== ft_putstr_fd NULL tests ==========
    printf("Testing ft_putstr_fd with NULL parameter:\n");
    
    TEST_NULL("ft_putstr_fd(NULL, 1)", {
        ft_putstr_fd(NULL, 1);
    });
    
    printf("\n");

    // ========== ft_putendl_fd NULL tests ==========
    printf("Testing ft_putendl_fd with NULL parameter:\n");
    
    TEST_NULL("ft_putendl_fd(NULL, 1)", {
        ft_putendl_fd(NULL, 1);
    });
    
    printf("\n");

    // ========== Final result ==========
    printf("───────────────────────────────────────────────────────────────\n");
    printf("\n");
    
    if (fail_count == 0) {
        printf("╔════════════════════════════════════════════════════════════════╗\n");
        printf("║  ✅ ALL DEFENSIVE TESTS PASSED (%d/%d)                         ║\n", pass_count, test_count);
        printf("╚════════════════════════════════════════════════════════════════╝\n");
        printf("\n");
        printf("🛡️  Excellent! Your libft handles NULL parameters gracefully.\n");
        printf("   This shows good defensive programming practices.\n");
        printf("\n");
        return 0;
    } else {
        printf("╔════════════════════════════════════════════════════════════════╗\n");
        printf("║  ⚠️  SOME DEFENSIVE TESTS FAILED (%d/%d passed)                ║\n", pass_count, test_count);
        printf("╚════════════════════════════════════════════════════════════════╝\n");
        printf("\n");
        printf("⚠️  Note: These failures are NOT critical!\n");
        printf("   The 42 subject does NOT require NULL handling.\n");
        printf("   However, adding NULL checks would improve code robustness.\n");
        printf("\n");
        printf("💡 Tip: Add simple NULL checks at the start of your functions:\n");
        printf("   if (!s1 || !s2) return (NULL);\n");
        printf("\n");
        return 0;  // Return 0 even on failure - these are optional tests
    }
}
