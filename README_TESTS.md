# 🧪 Álnok - Sneaky Tester for libft

**Álnok** This ultra-complete tester detects the most vicious bugs in your libft.

---

## 📊 Overview

- **Tests strictly following 42 subject requirements**
- **Individual test files per function** + integration tests
- **Valgrind** + **AddressSanitizer/UBSan**
- **Progress tracking**: `[TEST X] test_name` - know exactly which test crashes!
- **Separate optional defensive coding tests** (test_defensive_null.c)

### 🛡️ About Defensive Coding Tests

A separate test file (`test_defensive_null.c`) checks NULL parameter handling:

- ✅ **Not required by subject** - Passing NULL is undefined behavior
- ✅ **Good practice** - Prevents segfaults during evaluation
- ✅ **Runs separately** - Not executed with Valgrind/ASan (would crash)
- ✅ **Optional** - Won't cause a 0 if not implemented
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

### ✨ Individual Function Tests
Each function has its own test file (e.g., `test_atoi.c`, `test_substr.c`, etc.) containing:
- **Basic tests** - Standard functionality
- **Edge cases** - Boundary conditions (empty, zero, overflow)
- **Sneaky tests** - Common bugs (special chars, overflow, underflow)
- **Ultra-sneaky tests** - Expert edge cases (UINT_MAX, negative bytes)

**All tests display**: `[TEST X] test_name` so you know exactly which test crashes!

### 📂 Integration Tests

#### 1. **test_fd_edge_cases.c**
File descriptor integration tests:
- **Invalid FDs**: -1, 9999, closed FD
- **Content verification**: Writing to temporary file
- **Empty strings**: ft_putnbr_fd with 0, -1, INT_MIN, INT_MAX

#### 2. **test_list_torture.c** (bonus)
Linked list torture tests:
- **Memory management**: Proper allocation/deallocation
- **Edge cases**: Empty lists, single node, NULL content
- **lstmap failures**: Allocation failure in middle of mapping

#### 3. **test_defensive_null.c** (optional)
Optional NULL parameter handling tests:
- **Not required by subject** - undefined behavior is allowed
- **Good practice** - shows defensive programming
- **Runs separately** - without Valgrind/ASan
- **Progress tracking**: Shows which test crashes

---

## 🔍 Debug Features

When a test crashes, you see:
```
[TEST 42] calloc(0, 10) returns non-NULL
✗ test_atoi (floating point exception - division by zero?)
  → Crashed during: [TEST 15] atoi overflow behavior
  → Debug with: gdb tests/run_test_atoi_valgrind (type 'run' then 'backtrace')
```

**You know exactly**:
- Which test number crashed
- What the test was checking
- How to debug it with gdb

---

## 📊 Test Coverage

### Individual Function Tests (~200+ tests)
Each function (atoi, substr, split, strjoin, strtrim, etc.) has:
- **Basic functionality** - 2-5 tests
- **Edge cases** - 3-8 tests
- **Sneaky bugs** - 2-5 tests
- **Ultra-sneaky** - 3-10 tests

**Examples**:
- **ft_atoi**: 25+ tests (overflow, underflow, whitespace, signs, trailing)
- **ft_split**: 12+ tests (empty, delimiters, long word, 100 delimiters)
- **ft_substr**: 12+ tests (empty, UINT_MAX, very large len)
- **ft_strlcpy/strlcat**: 13+ tests each (dstsize=0/1, non null-terminated)
- **ft_memchr/memcmp**: 13+ tests (after null, negative bytes, n=0)
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

### 6. **test_defensive_null.c** 🛡️ OPTIONAL
Optional defensive coding tests for NULL parameter handling.

**⚠️ Important**: This test runs separately without Valgrind/ASan (would crash).

#### Included tests:
- **ft_strjoin** : NULL + string, string + NULL, NULL + NULL
- **ft_strtrim** : NULL + set, string + NULL, NULL + NULL
- **ft_substr** : NULL string
- **ft_split** : NULL string
- **ft_strmapi** : NULL string, NULL function
- **ft_striteri** : NULL string, NULL function
- **ft_putstr_fd** : NULL string
- **ft_putendl_fd** : NULL string

**Note**: These tests are NOT required by the 42 subject. They check if your functions handle NULL gracefully instead of segfaulting. Implementing NULL checks is good practice but optional.

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
| Edge cases | 43 |
| File descriptors | 11 |
| Classic bugs | 43 |
| Expert tests | 60 |
| Linked lists (bonus) | 37 |
| **Mandatory TOTAL** | **157** |
| Defensive NULL (optional) | ~15 |
| **TOTAL with optional** | **~172** |

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
