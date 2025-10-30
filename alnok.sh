#!/usr/bin/env bash

# ╔═══════════════════════════════════════════════════════════════════════╗
# ║                           ÁLNOK TESTER                                ║
# ║                                                                       ║
# ║  Complete evaluation script for libft                                 ║
# ║  Compiles and tests with Valgrind AND AddressSanitizer/UBSan         ║
# ║                                                                       ║
# ║  Usage: ./alnok.sh [--bonus|-b]                                       ║
# ╚═══════════════════════════════════════════════════════════════════════╝

set -e  # Stop on compilation error

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Options
TEST_BONUS=0
if [[ "$1" == "--bonus" ]] || [[ "$1" == "-b" ]]; then
    TEST_BONUS=1
    echo -e "${BLUE}=== BONUS mode enabled ===${NC}"
fi

VALGRIND_FAILED=0
ASAN_FAILED=0
CFLAGS_BASE="-g -Wall -Wextra -Werror"
CFLAGS_ASAN="-g -fsanitize=address,undefined -fno-omit-frame-pointer -Wall -Wextra -Werror"
VALGRIND=$(command -v valgrind || true)
LIB="libft.a"
TEST_DIR="tests"
CC=${CC:-cc}

echo "=== [1] Building libft (clean + make + bonus) ==="
if [ ! -f Makefile ]; then
  exit 1
fi

CC=${CC} CFLAGS="-Wall -Wextra -Werror" make fclean >/dev/null 2>&1 || true
CC=${CC} CFLAGS="-Wall -Wextra -Werror" make || { echo "Make failed"; exit 2; }

if grep -qE '^[[:space:]]*bonus[:[:space:]]' Makefile; then
  echo "Found 'bonus' rule → make bonus"
  CC=${CC} CFLAGS="-Wall -Wextra -Werror" make bonus || { echo "Bonus build failed"; exit 3; }
fi

if [ ! -f "${LIB}" ]; then
  echo "❌ libft.a not built"
  exit 4
fi
echo "✅ libft.a built successfully"

echo
echo "=== [2] Global variables check ==="
if nm -C --defined-only "${LIB}" | grep -E " [BDG] " >/dev/null 2>&1; then
  echo "❌ Global variables detected!"
  nm -C --defined-only "${LIB}" | grep -E " [BDG] "
  exit 5
else
  echo "✅ No globals found"
fi

echo
echo "=== [3] Preparing tests ==="
if [ ! -d "${TEST_DIR}" ]; then
  echo "ERROR: tests/ directory missing."
  exit 6
fi

shopt -s nullglob
if [ ${TEST_BONUS} -eq 1 ]; then
  # Include all tests except defensive_null
  TEST_FILES=()
  for f in ${TEST_DIR}/test_*.c; do
    if [[ ! "$(basename "$f")" =~ defensive_null ]]; then
      TEST_FILES+=("$f")
    fi
  done
else
  # Exclude bonus tests (list_torture) and defensive_null
  TEST_FILES=()
  for f in ${TEST_DIR}/test_*.c; do
    if [[ ! "$(basename "$f")" =~ list_torture ]] && [[ ! "$(basename "$f")" =~ defensive_null ]]; then
      TEST_FILES+=("$f")
    fi
  done
fi
shopt -u nullglob

if [ ${#TEST_FILES[@]} -eq 0 ]; then
  echo "ERROR: No test_*.c in ${TEST_DIR}"
  exit 7
fi

FAIL=0

# Phase 1: Valgrind (without sanitizers)
if [ -n "${VALGRIND}" ]; then
  echo
  echo "=== [4] Phase 1: Valgrind tests (without sanitizers) ==="
  for SRC in "${TEST_FILES[@]}"; do
    NAME=$(basename "${SRC}" .c)
    BIN="${TEST_DIR}/run_${NAME}_valgrind"
    echo
    echo "--- Compiling ${NAME} for Valgrind ---"
    if ! ${CC} ${CFLAGS_BASE} "${SRC}" "${LIB}" -o "${BIN}"; then
      echo "❌ Compilation failed for ${SRC}"
      FAIL=1
      continue
    fi
    echo "✅ Compiled ${NAME}"
    echo "--- Running Valgrind on ${NAME} ---"
    if ! ${VALGRIND} --quiet --leak-check=full --error-exitcode=9 "${BIN}"; then
      echo "❌ Valgrind FAIL: ${NAME}"
      FAIL=1
    else
      echo "✅ Valgrind PASS: ${NAME}"
    fi
  done
else
  echo
  echo "=== [4] Phase 1: Valgrind not found → skipping ==="
fi

# Phase 2: ASan/UBSan
echo
echo "=== [5] Phase 2: ASan/UBSan tests ==="
for SRC in "${TEST_FILES[@]}"; do
  NAME=$(basename "${SRC}" .c)
  BIN="${TEST_DIR}/run_${NAME}_asan"
  echo
  echo "--- Compiling ${NAME} with ASan/UBSan ---"
  if ! ${CC} ${CFLAGS_ASAN} "${SRC}" "${LIB}" -o "${BIN}"; then
    echo "❌ Compilation failed for ${SRC}"
    FAIL=1
    continue
  fi
  echo "✅ Compiled ${NAME}"
  echo "--- Running ${NAME} with ASan/UBSan ---"
  if ! "${BIN}"; then
    echo "❌ ASan FAIL: ${NAME}"
    FAIL=1
  else
    echo "✅ ASan PASS: ${NAME}"
  fi
done

echo
echo "=== [6] Defensive NULL tests (optional - no Valgrind/ASan) ==="
echo -e "${YELLOW}⚠️  Testing NULL parameter handling (optional defensive coding)${NC}"
echo -e "${YELLOW}   These tests are NOT required by 42 subject${NC}"
echo

DEFENSIVE_SRC="${TEST_DIR}/test_defensive_null.c"
DEFENSIVE_BIN="${TEST_DIR}/run_test_defensive_null"

if [ -f "${DEFENSIVE_SRC}" ]; then
  echo "--- Compiling defensive NULL test ---"
  if ${CC} ${CFLAGS_BASE} "${DEFENSIVE_SRC}" "${LIB}" -o "${DEFENSIVE_BIN}" 2>/dev/null; then
    echo "✅ Compiled defensive test"
    echo "--- Running defensive NULL test (may segfault if NULL not handled) ---"
    if "${DEFENSIVE_BIN}"; then
      echo "✅ Defensive test completed"
    else
      echo -e "${YELLOW}⚠️  Defensive test had failures (this is OK - not required)${NC}"
    fi
  else
    echo "❌ Compilation failed for defensive test"
  fi
else
  echo "ℹ️  Defensive NULL test not found (optional)"
fi

echo
echo "=== [7] Cleaning test binaries ==="
rm -f "${TEST_DIR}"/run_test_*
echo "✅ Test binaries cleaned"

echo
echo "=== [8] Cleaning project (make fclean) ==="
make fclean >/dev/null 2>&1 || true
echo "✅ Project cleaned"

echo
if [ ${FAIL} -eq 0 ]; then
  echo "=== ✅ ALL TESTS PASSED ==="
  exit 0
else
  echo "=== ❌ SOME TESTS FAILED ==="
  exit 8
fi
