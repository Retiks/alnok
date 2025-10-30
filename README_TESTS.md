# 🧪 Álnok - Sneaky Tester for libft

**Álnok** This ultra-complete tester detects the most vicious bugs in your libft.

---

## 📊 Overview

- **Tests strictly following 42 subject requirements**
- **5 specialized test files**
- **Valgrind** + **AddressSanitizer/UBSan**
- **Includes optional defensive coding tests** (clearly marked)

### 🛡️ About Defensive Coding Tests

Some tests check for NULL parameter handling and overflow protection. These are marked as **"defensive coding - optional"** because:

- ✅ **Not required by subject** - Passing NULL is undefined behavior
- ✅ **Good practice** - Prevents segfaults during evaluation
- ✅ **Recommended but optional** - Won't cause a 0 if not implemented
- ⚠️ **Subject rule**: "except for undefined behavior" - so segfaults on NULL are technically allowed

**Our recommendation**: Implement these protections (they're just 1-2 lines) to show good coding practices.

---

## 🚀 Usage

### Standard test (without bonus)
```bash
./alnok.sh
```

### Test with bonus (linked lists)
```bash
./alnok.sh --bonus
# or
./alnok.sh -b
```

### Script options
- `--bonus` / `-b`: Enables bonus function tests (linked lists)
- The script automatically runs `make fclean` at the end

---

## 📁 Test Structure

### 1. **test_edge_cases.c**
Tests for edge cases following the subject requirements.

#### Included tests:
- **ft_atoi**: Overflow behavior (matches libc), complete whitespace, multiple signs
- **ft_substr**: Start > strlen, len > strlen, empty strings
- **ft_split**: Multiple delimiters, empty string, single word
- **ft_strjoin**: Empty strings
- **ft_strtrim**: Complete trim, empty set, special characters
- **ft_strlcat**: Full buffer, dstsize = 0, dstsize < strlen(dst)
- **ft_strnstr**: Empty needle, len = 0, needle at boundary
- **ft_memchr**: Search '\0', after null, n = 0
- **ft_calloc**: Zero size behavior (returns valid pointer for free)
- **ft_itoa**: INT_MIN, INT_MAX, 0

**Note**: Overflow protection tests removed (not required). NULL tests included as optional defensive coding.

---

### 2. **test_fd_edge_cases.c**
Tests for writing functions with file descriptors.

#### Included tests:
- **Invalid FDs** : -1, 9999, closed FD
- **Content verification** : Writing to temporary file
- **Empty strings** : "", ft_putnbr_fd with 0, -1, INT_MIN, INT_MAX
- **NULL tests** : ft_putstr_fd(NULL), ft_putendl_fd(NULL) - marked as optional defensive coding

---

### 3. **test_sneaky_bugs.c** (51 tests)
Tests for classic bugs that often break projects.

#### Included tests:
- **ft_strlcpy** : dstsize = 0, dstsize = 1, returns strlen(src)
- **ft_strlcat** : dst not null-terminated, dstsize <= strlen(dst)
- **ft_split** : Allocation failure, very long word, delimiter '\0'
- **ft_substr** : start + len > strlen, start = UINT_MAX
- **ft_strjoin** : NULL + string, string + NULL, NULL + NULL
- **ft_strtrim** : Trim everything, NULL + set, string + NULL
- **ft_atoi** : Complete whitespace, multiple signs, trailing garbage
- **ft_memcpy/memmove** : Overlap forward/backward, n = 0
- **ft_strncmp** : Unsigned char comparison, n = 0
- **ft_strnstr** : Needle at boundary, empty needle
- **ft_strchr/strrchr** : Search '\0', negative character
- **ft_memchr** : After null, negative character, n = 0
- **ft_memcmp** : Unsigned comparison, n = 0, after null
- **ft_itoa** : INT_MIN, INT_MAX, 0
- **ft_calloc** : calloc(0, 0), overflow detection
- **ft_strdup** : Empty string, long string

---

### 4. **test_ultra_sneaky.c** (62 tests)
Ultra-sneaky tests expert level.

#### Included tests:
- **ft_atoi** : All types of whitespace, silent overflow, multiple signs
- **ft_split** : Delimiter '\0', 100 delimiters consecutive, single character
- **ft_substr** : start = UINT_MAX, len very large, overflow
- **ft_strjoin** : Medium strings (500 characters), content verification
- **ft_strtrim** : Set contains all characters, very long set, special characters
- **ft_strlcpy** : dstsize = 0/1, empty source
- **ft_strlcat** : dst not null-terminated, dstsize < dst_len
- **ft_strchr/strrchr** : '\0', multiple occurrences, negative character
- **ft_strncmp** : Unsigned comparison, n = 0, embedded null
- **ft_strnstr** : Empty needle, needle > len, multiple occurrences
- **ft_memchr** : After null, negative character, n = 0
- **ft_memcmp** : Unsigned, n = 0, after null
- **ft_memcpy/memmove** : n = 0, same pointer
- **ft_itoa** : INT_MIN, INT_MAX, multiple digits
- **ft_calloc** : calloc(0, 0), overflow detection
- **ft_strdup** : Long string (1000 characters)
- **Consistency tests** : strlen vs strlcpy, memcpy vs memmove, strchr vs memchr

---

### 5. **test_list_torture.c** (37 tests) 🔥 BONUS
Torture tests for linked lists.

#### Included tests:
- **ft_lstnew** : NULL content, normal content
- **ft_lstadd_front** : Order, NULL list, chaining
- **ft_lstadd_back** : Order, NULL list, last element
- **ft_lstsize** : Empty list, 1 element, 3 elements, 103 elements
- **ft_lstlast** : Empty list, 1 element, multiple elements
- **ft_lstdelone** : del call, del = NULL
- **ft_lstclear** : del call N times, empty list, 1000 nodes
- **ft_lstiter** : No-op function, empty list
- **ft_lstmap** : Creating new list, failure in middle, empty list, 1 element, 100 elements
- **Consistency tests** : lstadd_front + lstlast, lstsize + manual traversal
- **Robustness tests** : Clear then reuse

---

## 🛡️ Detection Tools

### Valgrind
- Memory leak detection
- Invalid read/write
- Use of uninitialized memory

### AddressSanitizer (ASan)
- Buffer overflow
- Use-after-free
- Stack overflow
- Allocation too large

### UndefinedBehaviorSanitizer (UBSan)
- Signed arithmetic overflow
- Division by zero
- Null pointer dereference

---

## 📈 Statistics

| Category | Number of tests |
|-----------|----------------|
| Edge cases | 46 |
| File descriptors | 13 |
| Classic bugs | 51 |
| Expert tests | 62 |
| Linked lists (bonus) | 37 |
| **TOTAL** | **209** |

---

## ✅ Expected Result

```
=== [1] Building libft (clean + make + bonus) ===
✅ libft.a built successfully

=== [2] Global variables check ===
✅ No globals found

=== [3] Preparing tests ===

=== [4] Phase 1: Valgrind tests (without sanitizers) ===
✅ Valgrind PASS: test_edge_cases
✅ Valgrind PASS: test_fd_edge_cases
✅ Valgrind PASS: test_sneaky_bugs
✅ Valgrind PASS: test_ultra_sneaky
✅ Valgrind PASS: test_list_torture

=== [5] Phase 2: ASan/UBSan tests ===
✅ ASan PASS: test_edge_cases
✅ ASan PASS: test_fd_edge_cases
✅ ASan PASS: test_sneaky_bugs
✅ ASan PASS: test_ultra_sneaky
✅ ASan PASS: test_list_torture

=== [6] Cleaning test binaries ===
✅ Test binaries cleaned

=== [7] Cleaning project (make fclean) ===
✅ Project cleaned

=== ✅ ALL TESTS PASSED ===
```

---

## 🎯 Tester Philosophy

**Álnok** does not only test if your code works. It tests if your code **survives** the worst possible conditions :

- ✅ Extreme values (INT_MIN, INT_MAX, SIZE_MAX)
- ✅ NULL pointers everywhere
- ✅ Arithmetic overflows
- ✅ Invalid file descriptors
- ✅ Failing allocations
- ✅ Buffers too small
- ✅ Empty and very long strings
- ✅ Undefined behaviors

**If your libft passes Álnok, it is production-ready.** 🚀

---

**Álnok** - Because bugs hide in dark corners. 💀
