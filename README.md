# Álnok - Sneaky Tester for libft

An ultra-complete tester that detects the most vicious bugs in your libft.

---

## Quick Start

```bash
# Standard test (without bonus)
./alnok.sh

# Test with bonus (linked lists)
./alnok.sh --bonus
```

---

## What is Tested

- **247 tests** in total
- **Valgrind**: Memory leaks
- **AddressSanitizer**: Buffer overflow, use-after-free
- **UBSan**: Undefined behavior
- **9 critical bugs** detected and fixed

---

## Test Files

| File | Tests | Description |
|------|-------|-------------|
| `test_edge_cases.c` | 46 | Edge cases (INT_MIN, SIZE_MAX, overflow) |
| `test_fd_edge_cases.c` | 13 | Invalid file descriptors, NULL |
| `test_sneaky_bugs.c` | 51 | Classic bugs that often break |
| `test_ultra_sneaky.c` | 62 | Ultra-sneaky expert-level tests |
| `test_list_torture.c` | 37 | Linked list torture (bonus) |

---

## Complete Documentation

- **[README_TESTS.md](README_TESTS.md)** - Detailed documentation of all tests
- **[USAGE.md](USAGE.md)** - Usage guide and FAQ

---

## Expected Result

```
=== ALL TESTS PASSED ===
```

If you see this message, your libft is **production-ready**!

**Álnok** - Because bugs hide in dark corners
