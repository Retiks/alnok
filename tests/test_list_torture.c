// test_list_torture.c - Torture tests for linked lists
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>
#include "../libft.h"

static int test_count = 0;
static int fail_count = 0;
static int malloc_count = 0;
static int free_count = 0;

#define TEST(name, cond) do { \
    test_count++; \
    fprintf(stderr, "[TEST %d] %s\n", test_count, name); \
    fflush(stderr); \
    if (!(cond)) { \
        fprintf(stderr, "❌ FAIL [%d]: %s\n", test_count, name); \
        fail_count++; \
    } \
} while(0)

void count_del(void *content) {
    free_count++;
    free(content);
}

void *count_dup(void *content) {
    malloc_count++;
    return strdup((char*)content);
}

void *fail_on_second(void *content) {
    static int call_count = 0;
    call_count++;
    if (call_count == 2) return NULL;
    return strdup((char*)content);
}

void do_nothing(void *content) {
    (void)content;
}

int main(void)
{
    // ========== ft_lstnew: Tests basic ==========
    
    t_list *node = ft_lstnew(NULL);
    TEST("lstnew with NULL content", node != NULL && node->content == NULL && node->next == NULL);
    free(node);
    
    char *str = strdup("test");
    node = ft_lstnew(str);
    TEST("lstnew with content", node && node->content == str && node->next == NULL);
    free(str);
    free(node);
    
    // ========== ft_lstadd_front: Tests sneaky ==========
    
    t_list *list = NULL;
    ft_lstadd_front(&list, ft_lstnew(strdup("3")));
    ft_lstadd_front(&list, ft_lstnew(strdup("2")));
    ft_lstadd_front(&list, ft_lstnew(strdup("1")));
    TEST("lstadd_front order", list && strcmp(list->content, "1") == 0);
    TEST("lstadd_front chain", list->next && strcmp(list->next->content, "2") == 0);
    ft_lstclear(&list, free);
    
    // Ajouter à une liste NULL
    list = NULL;
    ft_lstadd_front(&list, ft_lstnew(strdup("first")));
    TEST("lstadd_front to NULL", list && strcmp(list->content, "first") == 0);
    ft_lstclear(&list, free);
    
    // ========== ft_lstadd_back: Tests sneaky ==========
    
    list = NULL;
    ft_lstadd_back(&list, ft_lstnew(strdup("1")));
    ft_lstadd_back(&list, ft_lstnew(strdup("2")));
    ft_lstadd_back(&list, ft_lstnew(strdup("3")));
    TEST("lstadd_back order", list && strcmp(list->content, "1") == 0);
    t_list *last = ft_lstlast(list);
    TEST("lstadd_back last", last && strcmp(last->content, "3") == 0);
    ft_lstclear(&list, free);
    
    // Ajouter à une liste NULL
    list = NULL;
    ft_lstadd_back(&list, ft_lstnew(strdup("only")));
    TEST("lstadd_back to NULL", list && strcmp(list->content, "only") == 0);
    ft_lstclear(&list, free);
    
    // ========== ft_lstsize: Tests sneaky ==========
    
    list = NULL;
    TEST("lstsize empty", ft_lstsize(list) == 0);
    
    ft_lstadd_back(&list, ft_lstnew(strdup("1")));
    TEST("lstsize one", ft_lstsize(list) == 1);
    
    ft_lstadd_back(&list, ft_lstnew(strdup("2")));
    ft_lstadd_back(&list, ft_lstnew(strdup("3")));
    TEST("lstsize three", ft_lstsize(list) == 3);
    
    // Very long list
    for (int i = 0; i < 100; i++) {
        ft_lstadd_back(&list, ft_lstnew(strdup("x")));
    }
    TEST("lstsize 103", ft_lstsize(list) == 103);
    ft_lstclear(&list, free);
    
    // ========== ft_lstlast: Tests sneaky ==========
    
    list = NULL;
    TEST("lstlast empty", ft_lstlast(list) == NULL);
    
    ft_lstadd_back(&list, ft_lstnew(strdup("only")));
    TEST("lstlast single", ft_lstlast(list) == list);
    
    ft_lstadd_back(&list, ft_lstnew(strdup("last")));
    last = ft_lstlast(list);
    TEST("lstlast multiple", last && strcmp(last->content, "last") == 0);
    TEST("lstlast next is NULL", last->next == NULL);
    ft_lstclear(&list, free);
    
    // ========== ft_lstdelone: Tests sneaky ==========
    
    free_count = 0;
    node = ft_lstnew(strdup("delete_me"));
    ft_lstdelone(node, count_del);
    TEST("lstdelone calls del", free_count == 1);
    
    // lstdelone with del = NULL (should not crash, but leak)
    node = ft_lstnew(strdup("leak"));
    char *leaked_content = node->content;
    ft_lstdelone(node, NULL);
    TEST("lstdelone with NULL del doesn't crash", 1);
    free(leaked_content);  // We manually free the content
    
    // ========== ft_lstclear: Tests sneaky ==========
    
    free_count = 0;
    list = NULL;
    ft_lstadd_back(&list, ft_lstnew(strdup("1")));
    ft_lstadd_back(&list, ft_lstnew(strdup("2")));
    ft_lstadd_back(&list, ft_lstnew(strdup("3")));
    ft_lstclear(&list, count_del);
    TEST("lstclear calls del 3 times", free_count == 3);
    TEST("lstclear sets list to NULL", list == NULL);
    
    // lstclear sur liste vide
    list = NULL;
    ft_lstclear(&list, free);
    TEST("lstclear empty list", list == NULL);
    
    // lstclear with very long list
    free_count = 0;
    list = NULL;
    for (int i = 0; i < 1000; i++) {
        ft_lstadd_back(&list, ft_lstnew(strdup("x")));
    }
    ft_lstclear(&list, count_del);
    TEST("lstclear 1000 nodes", free_count == 1000 && list == NULL);
    
    // ========== ft_lstiter: Tests sneaky ==========
    
    list = NULL;
    ft_lstadd_back(&list, ft_lstnew(strdup("a")));
    ft_lstadd_back(&list, ft_lstnew(strdup("b")));
    ft_lstadd_back(&list, ft_lstnew(strdup("c")));
    
    // lstiter with function that does nothing
    ft_lstiter(list, do_nothing);
    TEST("lstiter do_nothing doesn't crash", 1);
    
    // lstiter sur liste vide
    t_list *empty = NULL;
    ft_lstiter(empty, do_nothing);
    TEST("lstiter empty list doesn't crash", 1);
    
    ft_lstclear(&list, free);
    
    // ========== ft_lstmap: Tests ultra-sneaky ==========
    
    // lstmap normal
    malloc_count = 0;
    list = NULL;
    ft_lstadd_back(&list, ft_lstnew(strdup("a")));
    ft_lstadd_back(&list, ft_lstnew(strdup("b")));
    ft_lstadd_back(&list, ft_lstnew(strdup("c")));
    
    t_list *mapped = ft_lstmap(list, count_dup, free);
    TEST("lstmap creates new list", mapped != NULL && mapped != list);
    TEST("lstmap calls f 3 times", malloc_count == 3);
    TEST("lstmap preserves order", mapped && strcmp(mapped->content, "a") == 0);
    
    ft_lstclear(&list, free);
    ft_lstclear(&mapped, free);
    
    // lstmap with failure in middle
    list = NULL;
    ft_lstadd_back(&list, ft_lstnew(strdup("1")));
    ft_lstadd_back(&list, ft_lstnew(strdup("2")));
    ft_lstadd_back(&list, ft_lstnew(strdup("3")));
    
    mapped = ft_lstmap(list, fail_on_second, free);
    TEST("lstmap fails and returns NULL", mapped == NULL);
    
    ft_lstclear(&list, free);
    
    // lstmap on an empty list
    list = NULL;
    mapped = ft_lstmap(list, count_dup, free);
    TEST("lstmap empty list returns NULL", mapped == NULL);
    
    // lstmap with single element list
    list = ft_lstnew(strdup("single"));
    mapped = ft_lstmap(list, count_dup, free);
    TEST("lstmap single element", mapped && strcmp(mapped->content, "single") == 0 && mapped->next == NULL);
    ft_lstclear(&list, free);
    ft_lstclear(&mapped, free);
    
    // lstmap with very long list
    list = NULL;
    for (int i = 0; i < 100; i++) {
        ft_lstadd_back(&list, ft_lstnew(strdup("x")));
    }
    mapped = ft_lstmap(list, count_dup, free);
    TEST("lstmap 100 elements", ft_lstsize(mapped) == 100);
    ft_lstclear(&list, free);
    ft_lstclear(&mapped, free);
    
    // ========== Tests of consistency ==========
    
    // Verify that lstadd_front + lstlast works
    list = NULL;
    ft_lstadd_front(&list, ft_lstnew(strdup("first")));
    ft_lstadd_back(&list, ft_lstnew(strdup("last")));
    TEST("front+back consistency", strcmp(list->content, "first") == 0);
    last = ft_lstlast(list);
    TEST("front+back last", strcmp(last->content, "last") == 0);
    ft_lstclear(&list, free);
    
    // Verify that lstsize is consistent with lstlast
    list = NULL;
    for (int i = 0; i < 50; i++) {
        ft_lstadd_back(&list, ft_lstnew(strdup("x")));
    }
    int size = ft_lstsize(list);
    last = ft_lstlast(list);
    TEST("size and last consistency", size == 50 && last != NULL);
    
    // Manually traverse and count
    int manual_count = 0;
    t_list *tmp = list;
    while (tmp) {
        manual_count++;
        tmp = tmp->next;
    }
    TEST("manual count matches lstsize", manual_count == size);
    
    ft_lstclear(&list, free);
    
    // ========== Tests of robustness ==========
    
    // Create a list, clear it, then reuse the pointer
    list = ft_lstnew(strdup("test"));
    ft_lstclear(&list, free);
    TEST("list is NULL after clear", list == NULL);
    ft_lstadd_back(&list, ft_lstnew(strdup("new")));
    TEST("can reuse cleared list", list && strcmp(list->content, "new") == 0);
    ft_lstclear(&list, free);
    
    // ========== Final result ==========
    if (fail_count == 0) {
        printf("test_list_torture: OK (%d tests passed) 💀⛓️💀\n", test_count);
        return 0;
    } else {
        fprintf(stderr, "\n❌ %d/%d tests failed\n", fail_count, test_count);
        return 1;
    }
}
