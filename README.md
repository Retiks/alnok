# 🧪 Álnok - Sneaky Tester for libft

An ultra-complete tester that detects the most vicious bugs in your libft.

**✨ Strictly following 42 subject requirements** + optional defensive coding tests (clearly marked).

---

## 🚀 Quick Start

```bash
# Standard test (without bonus)
./alnok.sh

# Test with bonus (linked lists)
./alnok.sh --bonus
```

**Note**: The script automatically runs an optional defensive NULL test at the end (without Valgrind/ASan) to check if your functions handle NULL parameters gracefully.

---

## 🔍 Enhanced Debugging

When a test fails or crashes, you'll see:
```
[TEST 42] calloc(0, 10) returns non-NULL
❌ FAIL [42]: calloc(0, 10) returns non-NULL
```

For crashes (segfault, floating point exception):
```
✗ test_sneaky_bugs (floating point exception - division by zero?)
  → Crashed during: [TEST 15] atoi overflow behavior
  → Debug with: gdb tests/run_test_sneaky_bugs_valgrind (type 'run' then 'backtrace')
```

**You know exactly which test crashed and how to debug it!**

---

## 📊 What is Tested

- ✅ **Tests strictly following 42 subject**
- ✅ **Valgrind**: Memory leaks
- ✅ **AddressSanitizer**: Buffer overflow, use-after-free
- ✅ **UBSan**: Undefined behavior
- 🛡️ **Optional defensive coding tests** (NULL checks) - clearly marked as recommended but not required

---

## 📁 Test Organization

### ✨ New: Individual Function Tests
Each function now has its own test file with comprehensive coverage:
- **Basic tests** - Standard functionality
- **Edge cases** - Boundary conditions (empty strings, zero sizes, etc.)
- **Sneaky tests** - Common bugs (overflow, underflow, special chars)
- **Ultra-sneaky tests** - Expert-level edge cases (UINT_MAX, negative bytes, etc.)

**All tests display progress**: `[TEST X] test_name` - so you know exactly which test crashes!

### 📂 Test Files Structure
- `test_*.c` - Individual function tests (atoi, substr, split, etc.)
- `test_fd_edge_cases.c` - File descriptor integration tests
- `test_list_torture.c` - Linked list torture tests (bonus)
- `test_defensive_null.c` - 🛡️ Optional NULL handling tests (no Valgrind/ASan)

---

## 📖 Complete Documentation

- **[README_TESTS.md](README_TESTS.md)** - Detailed documentation of all tests
- **[USAGE.md](USAGE.md)** - Usage guide and FAQ

---

## ✅ Expected Result

```
=== ✅ ALL TESTS PASSED ===
```

If you see this message, your libft is **production-ready**! 🚀

**Álnok**
