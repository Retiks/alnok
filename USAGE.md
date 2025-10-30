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
**Includes**: All individual function tests + integration tests

### Complete test with bonus
```bash
./alnok.sh --bonus
```

**Includes**: All tests, including linked lists

## What does the script do?

1. ✅ **Build**: `make fclean` → `make` → `make bonus`
2. ✅ **Verification**: No global variables
3. ✅ **Valgrind Phase**: Memory leak detection (all individual tests)
4. ✅ **ASan/UBSan Phase**: Memory error detection (all individual tests)
5. ✅ **Defensive NULL tests**: Optional NULL handling (separate, no Valgrind/ASan)
6. ✅ **Cleanup**: Removes test binaries
7. ✅ **Final fclean**: Automatic `make fclean`

**Progress tracking**: Each test displays `[TEST X] test_name` so you know exactly which test is running!

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

### ❌ Failure with detailed info
```
[TEST 15] atoi overflow behavior
✗ test_atoi (floating point exception - division by zero?)
  → Crashed during: [TEST 15] atoi overflow behavior
  → Debug with: gdb tests/run_test_atoi_valgrind (type 'run' then 'backtrace')

=== ❌ SOME TESTS FAILED ===
```

**You see exactly**:
- Which test number crashed (TEST 15)
- What was being tested (atoi overflow behavior)
- How to debug it (gdb command provided)

## Dependencies

- **gcc** or **clang**
- **valgrind** (optional, skipped if absent)
- **make**

## Tips

### Test a single function
```bash
# Test only ft_atoi
cc -g -Wall -Wextra -Werror tests/test_atoi.c libft.a -o test && ./test
```

### With manual Valgrind
```bash
valgrind --leak-check=full ./test
```

### With manual ASan
```bash
cc -g -fsanitize=address tests/test_atoi.c libft.a -o test && ./test
```

### Debug a crash with gdb
When you see a crash message like:
```
✗ test_atoi (floating point exception)
  → Crashed during: [TEST 15] atoi overflow behavior
  → Debug with: gdb tests/run_test_atoi_valgrind
```

Run the gdb command:
```bash
gdb tests/run_test_atoi_valgrind
(gdb) run
(gdb) backtrace  # See where it crashed
(gdb) list        # See the code
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
