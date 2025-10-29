# 🚀 Quick Usage Guide - Álnok

## Installation

```bash
# Clone or copy test files into your libft project
cp -r tests/ /path/to/your/libft/
cp alnok.sh /path/to/your/libft/
chmod +x alnok.sh
```

## Usage

### Standard test (without bonus)
```bash
./alnok.sh
```

**Excludes**: `test_list_torture.c` (linked list tests)

### Complete test with bonus
```bash
./alnok.sh --bonus
```

**Includes**: All tests, including linked lists

## What does the script do?

1. ✅ **Build**: `make fclean` → `make` → `make bonus`
2. ✅ **Verification**: No global variables
3. ✅ **Valgrind Phase**: Memory leak detection
4. ✅ **ASan/UBSan Phase**: Memory error detection
5. ✅ **Cleanup**: Removes test binaries
6. ✅ **Final fclean**: Automatic `make fclean`

## Exit Codes

| Code | Meaning |
|------|---------|
| 0 | ✅ All tests pass |
| 1-7 | ❌ Compilation/setup error |
| 8 | ❌ At least one test failed |

## Output Examples

### ✅ Success
```
=== ✅ ALL TESTS PASSED ===
```

### ❌ Failure
```
❌ Valgrind FAIL: test_edge_cases
❌ ASan FAIL: test_sneaky_bugs
=== ❌ SOME TESTS FAILED ===
```

## Dependencies

- **gcc** or **clang**
- **valgrind** (optional, skipped if absent)
- **make**

## Tips

### Test a single file
```bash
cc -g -Wall -Wextra -Werror tests/test_edge_cases.c libft.a -o test && ./test
```

### With manual Valgrind
```bash
valgrind --leak-check=full ./test
```

### With manual ASan
```bash
cc -g -fsanitize=address tests/test_edge_cases.c libft.a -o test && ./test
```

## File Structure

```
libft/
├── alnok.sh                   # Main Álnok script
├── README_TESTS.md            # Complete documentation
├── USAGE.md                   # This file
├── libft.h
├── Makefile
├── ft_*.c
└── tests/
    ├── test_edge_cases.c      # 46 tests
    ├── test_fd_edge_cases.c   # 13 tests
    ├── test_sneaky_bugs.c     # 51 tests
    ├── test_ultra_sneaky.c    # 62 tests
    └── test_list_torture.c    # 37 tests (bonus)
```

## FAQ

**Q: Is the script too slow?**  
A: Use `./alnok.sh` without `--bonus` to exclude list tests

**Q: Valgrind is not installed?**  
A: The script detects this and automatically skips the Valgrind phase

**Q: A test fails, how to debug?**  
A: Compile and run the test manually with ASan to see the detailed error

**Q: Can I modify the tests?**  
A: Yes! Tests are in `tests/`, modify them as needed

---

**Álnok** - The sneaky tester that reveals all your bugs 🇭🇺💀
