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

## 📊 What is Tested

- ✅ **Tests strictly following 42 subject**
- ✅ **Valgrind**: Memory leaks
- ✅ **AddressSanitizer**: Buffer overflow, use-after-free
- ✅ **UBSan**: Undefined behavior
- 🛡️ **Optional defensive coding tests** (NULL checks) - clearly marked as recommended but not required

---

## 📁 Test Files

| File | Description |
|------|-------------|
| `test_edge_cases.c` | Edge cases following subject requirements |
| `test_fd_edge_cases.c` | File descriptor tests |
| `test_sneaky_bugs.c` | Classic bugs that often break |
| `test_ultra_sneaky.c` | Ultra-sneaky expert-level tests |
| `test_list_torture.c` | Linked list torture (bonus) |
| `test_defensive_null.c` | 🛡️ Optional NULL handling tests (no Valgrind/ASan) |

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
