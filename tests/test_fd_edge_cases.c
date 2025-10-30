// test_fd_edge_cases.c - Tests for file descriptors
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
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
    // ========== Tests with invalid FDs (should not crash) ==========
    
    // Test 1: Negative FD (should not crash)
    ft_putchar_fd('A', -1);
    TEST("putchar_fd with fd=-1 doesn't crash", 1);
    
    ft_putstr_fd("test", -1);
    TEST("putstr_fd with fd=-1 doesn't crash", 1);
    
    ft_putendl_fd("test", -1);
    TEST("putendl_fd with fd=-1 doesn't crash", 1);
    
    ft_putnbr_fd(42, -1);
    TEST("putnbr_fd with fd=-1 doesn't crash", 1);
    
    // Test 2: Very large FD (probably invalid)
    ft_putchar_fd('A', 9999);
    TEST("putchar_fd with fd=9999 doesn't crash", 1);
    
    ft_putstr_fd("test", 9999);
    TEST("putstr_fd with fd=9999 doesn't crash", 1);
    
    // Test 3: Closed FD
    int fd = open("/tmp/test_libft_fd.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd >= 0) {
        close(fd);
        // Writing to Closed FD should not crash
        ft_putchar_fd('A', fd);
        TEST("putchar_fd on closed fd doesn't crash", 1);
    }
    
    // ========== Tests avec NULL (defensive coding - optional but recommended) ==========
    // Note: The subject doesn't require NULL protection, but it's good practice
    // to avoid segfaults during evaluation. These tests are OPTIONAL.
    
    ft_putstr_fd(NULL, 1);
    TEST("putstr_fd with NULL doesn't crash (defensive)", 1);
    
    ft_putendl_fd(NULL, 1);
    TEST("putendl_fd with NULL doesn't crash (defensive)", 1);
    
    // ========== Functional tests with temporary file ==========
    
    fd = open("/tmp/test_libft_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        fprintf(stderr, "Cannot create temp file\n");
        return 1;
    }
    
    // Test normal write
    ft_putchar_fd('H', fd);
    ft_putchar_fd('i', fd);
    ft_putchar_fd('\n', fd);
    
    ft_putstr_fd("Hello", fd);
    ft_putchar_fd('\n', fd);
    
    ft_putendl_fd("World", fd);
    
    ft_putnbr_fd(42, fd);
    ft_putchar_fd('\n', fd);
    
    ft_putnbr_fd(-2147483648, fd);
    ft_putchar_fd('\n', fd);
    
    close(fd);
    
    // Verify content
    fd = open("/tmp/test_libft_output.txt", O_RDONLY);
    if (fd >= 0) {
        char buffer[100];
        ssize_t bytes = read(fd, buffer, sizeof(buffer) - 1);
        if (bytes > 0) {
            buffer[bytes] = '\0';
            const char *expected = "Hi\nHello\nWorld\n42\n-2147483648\n";
            TEST("fd output matches expected", strcmp(buffer, expected) == 0);
            if (strcmp(buffer, expected) != 0) {
                fprintf(stderr, "Expected:\n%s\nGot:\n%s\n", expected, buffer);
            }
        }
        close(fd);
    }
    
    // Cleanup
    unlink("/tmp/test_libft_output.txt");
    unlink("/tmp/test_libft_fd.txt");
    
    // ========== Tests with empty strings ==========
    
    ft_putstr_fd("", 1);
    TEST("putstr_fd with empty string doesn't crash", 1);
    
    ft_putendl_fd("", 1);
    TEST("putendl_fd with empty string doesn't crash", 1);
    
    // ========== Tests ft_putnbr_fd limites ==========
    
    fd = open("/tmp/test_libft_numbers.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd >= 0) {
        ft_putnbr_fd(0, fd);
        ft_putchar_fd('\n', fd);
        ft_putnbr_fd(-1, fd);
        ft_putchar_fd('\n', fd);
        ft_putnbr_fd(2147483647, fd);
        ft_putchar_fd('\n', fd);
        close(fd);
        
        fd = open("/tmp/test_libft_numbers.txt", O_RDONLY);
        if (fd >= 0) {
            char buffer[100];
            ssize_t bytes = read(fd, buffer, sizeof(buffer) - 1);
            if (bytes > 0) {
                buffer[bytes] = '\0';
                TEST("putnbr_fd edge cases", strcmp(buffer, "0\n-1\n2147483647\n") == 0);
            }
            close(fd);
        }
        unlink("/tmp/test_libft_numbers.txt");
    }
    
    // ========== Final result ==========
    if (fail_count == 0) {
        printf("test_fd_edge_cases: OK (%d tests passed)\n", test_count);
        return 0;
    } else {
        fprintf(stderr, "\n❌ %d/%d tests failed\n", fail_count, test_count);
        return 1;
    }
}
