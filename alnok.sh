#!/usr/bin/env bash

set -e  # Stop on compilation error

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
MAGENTA='\033[0;35m'
BOLD='\033[1m'
DIM='\033[2m'
NC='\033[0m' # No Color

# Print header
clear
echo ""
echo -e "${BLUE}╔════════════════════════════════════════════════════════════════╗${NC}"
echo -e "${BLUE}║${NC}                                                                ${BLUE}║${NC}"
echo -e "${BLUE}║${NC}        ${BOLD}🧪 ÁLNOK - Sneaky Tester for libft${NC}                      ${BLUE}║${NC}"
echo -e "${BLUE}║${NC}                                                                ${BLUE}║${NC}"
echo -e "${BLUE}║${NC}  ${DIM}Complete testing suite with Valgrind & ASan/UBSan${NC}             ${BLUE}║${NC}"
echo -e "${BLUE}║${NC}                                                                ${BLUE}║${NC}"
echo -e "${BLUE}╚════════════════════════════════════════════════════════════════╝${NC}"
echo ""

# Options
TEST_BONUS=0
if [[ "$1" == "--bonus" ]] || [[ "$1" == "-b" ]]; then
    TEST_BONUS=1
    echo -e "  ${MAGENTA}●${NC} ${BOLD}BONUS MODE${NC} - Testing linked list functions"
    echo ""
fi

VALGRIND_FAILED=0
ASAN_FAILED=0
CFLAGS_BASE="-g -Wall -Wextra -Werror"
VALGRIND=$(command -v valgrind || true)
LIB="libft.a"
TEST_DIR="tests"
CC=${CC:-cc}

echo -e "${CYAN}┌───────────────────────────────────────────────────────────────┐${NC}"
echo -e "${CYAN}│${NC} ${BOLD}[1/8]${NC} 🔨 Building libft...                                    ${CYAN}│${NC}"
echo -e "${CYAN}└───────────────────────────────────────────────────────────────┘${NC}"
if [ ! -f Makefile ]; then
  exit 1
fi

echo -ne "  ${DIM}Cleaning...${NC}"
CC=${CC} CFLAGS="-Wall -Wextra -Werror" make fclean >/dev/null 2>&1 || true
echo -e "\r  ${GREEN}✓${NC} Cleaned                    "

echo -ne "  ${DIM}Compiling mandatory...${NC}"
CC=${CC} CFLAGS="-Wall -Wextra -Werror" make >/dev/null 2>&1 || { echo -e "\r  ${RED}✗ Make failed${NC}"; exit 2; }
echo -e "\r  ${GREEN}✓${NC} Mandatory compiled         "

if grep -qE '^[[:space:]]*bonus[:[:space:]]' Makefile; then
  echo -ne "  ${DIM}Compiling bonus...${NC}"
  CC=${CC} CFLAGS="-Wall -Wextra -Werror" make bonus >/dev/null 2>&1 || { echo -e "\r  ${RED}✗ Bonus build failed${NC}"; exit 3; }
  echo -e "\r  ${GREEN}✓${NC} Bonus compiled             "
fi

if [ ! -f "${LIB}" ]; then
  echo -e "  ${RED}✗ ${LIB} not created${NC}"
  exit 4
fi
echo ""

echo -e "${CYAN}┌───────────────────────────────────────────────────────────────┐${NC}"
echo -e "${CYAN}│${NC} ${BOLD}[2/8]${NC} 🔍 Checking global variables...                         ${CYAN}│${NC}"
echo -e "${CYAN}└───────────────────────────────────────────────────────────────┘${NC}"
if nm -C --defined-only "${LIB}" | grep -E " [BDG] " >/dev/null 2>&1; then
  echo -e "  ${RED}✗ Global variables detected!${NC}"
  exit 5
else
  echo -e "  ${GREEN}✓${NC} No global variables found"
fi
echo ""

echo -e "${CYAN}┌───────────────────────────────────────────────────────────────┐${NC}"
echo -e "${CYAN}│${NC} ${BOLD}[3/8]${NC} 📋 Preparing tests...                                   ${CYAN}│${NC}"
echo -e "${CYAN}└───────────────────────────────────────────────────────────────┘${NC}"
if [ ! -d "${TEST_DIR}" ]; then
  echo -e "  ${RED}✗ tests/ directory missing${NC}"
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
  echo -e "  ${RED}✗ No test_*.c in ${TEST_DIR}${NC}"
  exit 7
fi
echo -e "  ${GREEN}✓${NC} Found ${BOLD}${#TEST_FILES[@]}${NC} test files"
echo ""

FAIL=0
VALGRIND_PASS=0
VALGRIND_FAIL=0
ASAN_PASS=0
ASAN_FAIL=0

# Phase 1: Valgrind (without sanitizers)
if [ -n "${VALGRIND}" ]; then
  echo -e "${CYAN}┌───────────────────────────────────────────────────────────────┐${NC}"
  echo -e "${CYAN}│${NC} ${BOLD}[4/8]${NC} 🧪 Running Valgrind tests...                            ${CYAN}│${NC}"
  echo -e "${CYAN}└───────────────────────────────────────────────────────────────┘${NC}"
  echo -e "  ${DIM}Testing for memory leaks and invalid access...${NC}"
  for SRC in "${TEST_FILES[@]}"; do
    NAME=$(basename "${SRC}" .c)
    BIN="${TEST_DIR}/run_${NAME}_valgrind"
    
    if ! ${CC} ${CFLAGS_BASE} "${SRC}" "${LIB}" -o "${BIN}" 2>/dev/null; then
      echo -e "  ${RED}✗${NC} ${NAME} ${DIM}(compilation failed)${NC}"
      FAIL=1
      VALGRIND_FAIL=$((VALGRIND_FAIL + 1))
      continue
    fi
    
    # Run test and capture output (disable exit-on-error for this command)
    set +e
    TEST_OUTPUT=$(${VALGRIND} --quiet --leak-check=full --error-exitcode=9 "${BIN}" 2>&1)
    TEST_EXIT=$?
    set -e
    
    if [ $TEST_EXIT -eq 0 ]; then
      echo -e "  ${GREEN}✓${NC} ${NAME}"
      VALGRIND_PASS=$((VALGRIND_PASS + 1))
    elif [ $TEST_EXIT -eq 136 ]; then
      # Exit code 136 = 128 + 8 (SIGFPE - Floating point exception)
      echo -e "  ${RED}✗${NC} ${NAME} ${DIM}(floating point exception - division by zero?)${NC}"
      # Show last test that was running
      LAST_TEST=$(echo "$TEST_OUTPUT" | grep "^\[TEST" | tail -1)
      if [ -n "$LAST_TEST" ]; then
        echo -e "    ${DIM}→ Crashed during: ${YELLOW}${LAST_TEST}${NC}"
      fi
      echo -e "    ${DIM}→ Debug with: ${CYAN}gdb ${BIN}${NC} ${DIM}(type 'run' then 'backtrace')${NC}"
      FAIL=1
      VALGRIND_FAIL=$((VALGRIND_FAIL + 1))
    elif [ $TEST_EXIT -eq 139 ]; then
      # Exit code 139 = 128 + 11 (SIGSEGV - Segmentation fault)
      echo -e "  ${RED}✗${NC} ${NAME} ${DIM}(segmentation fault)${NC}"
      # Show last test that was running
      LAST_TEST=$(echo "$TEST_OUTPUT" | grep "^\[TEST" | tail -1)
      if [ -n "$LAST_TEST" ]; then
        echo -e "    ${DIM}→ Crashed during: ${YELLOW}${LAST_TEST}${NC}"
      fi
      echo -e "    ${DIM}→ Debug with: ${CYAN}gdb ${BIN}${NC} ${DIM}(type 'run' then 'backtrace')${NC}"
      FAIL=1
      VALGRIND_FAIL=$((VALGRIND_FAIL + 1))
    else
      echo -e "  ${RED}✗${NC} ${NAME} ${DIM}(memory issue or crash - exit code: $TEST_EXIT)${NC}"
      # Show last test that was running
      LAST_TEST=$(echo "$TEST_OUTPUT" | grep "^\[TEST" | tail -1)
      if [ -n "$LAST_TEST" ]; then
        echo -e "    ${DIM}→ Last test: ${YELLOW}${LAST_TEST}${NC}"
      fi
      echo -e "    ${DIM}→ Run manually: ${CYAN}${VALGRIND} ${BIN}${NC}"
      FAIL=1
      VALGRIND_FAIL=$((VALGRIND_FAIL + 1))
    fi
  done
  echo ""
  if [ ${VALGRIND_FAIL} -eq 0 ]; then
    echo -e "  ${GREEN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "  ${GREEN}✓${NC} Valgrind: ${BOLD}${GREEN}All ${VALGRIND_PASS} tests passed${NC}"
  else
    echo -e "  ${RED}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
    echo -e "  ${YELLOW}⚠${NC}  Valgrind: ${GREEN}${VALGRIND_PASS} passed${NC}, ${RED}${VALGRIND_FAIL} failed${NC}"
  fi
  echo ""
else
  echo -e "${YELLOW}⚠${NC}  Valgrind not found, skipping memory tests"
  echo ""
fi

# Phase 2: ASan/UBSan
echo -e "${CYAN}┌───────────────────────────────────────────────────────────────┐${NC}"
echo -e "${CYAN}│${NC} ${BOLD}[5/8]${NC} 🛡️  Running ASan/UBSan tests...                          ${CYAN}│${NC}"
echo -e "${CYAN}└───────────────────────────────────────────────────────────────┘${NC}"
echo -e "  ${DIM}Testing for buffer overflows and undefined behavior...${NC}"
for SRC in "${TEST_FILES[@]}"; do
  NAME=$(basename "${SRC}" .c)
  BIN="${TEST_DIR}/run_${NAME}_asan"
  
  if ! ${CC} ${CFLAGS_ASAN} "${SRC}" "${LIB}" -o "${BIN}" 2>/dev/null; then
    echo -e "  ${RED}✗${NC} ${NAME} ${DIM}(compilation failed)${NC}"
    FAIL=1
    ASAN_FAIL=$((ASAN_FAIL + 1))
    continue
  fi
  
  # Run test and capture output (disable exit-on-error for this command)
  set +e
  TEST_OUTPUT=$("${BIN}" 2>&1)
  TEST_EXIT=$?
  set -e
  
  if [ $TEST_EXIT -eq 0 ]; then
    echo -e "  ${GREEN}✓${NC} ${NAME}"
    ASAN_PASS=$((ASAN_PASS + 1))
  elif [ $TEST_EXIT -eq 136 ]; then
    # Exit code 136 = 128 + 8 (SIGFPE - Floating point exception)
    echo -e "  ${RED}✗${NC} ${NAME} ${DIM}(floating point exception - division by zero?)${NC}"
    # Show last test that was running
    LAST_TEST=$(echo "$TEST_OUTPUT" | grep "^\[TEST" | tail -1)
    if [ -n "$LAST_TEST" ]; then
      echo -e "    ${DIM}→ Crashed during: ${YELLOW}${LAST_TEST}${NC}"
    fi
    echo -e "    ${DIM}→ Debug with: ${CYAN}gdb ${BIN}${NC} ${DIM}(type 'run' then 'backtrace')${NC}"
    FAIL=1
    ASAN_FAIL=$((ASAN_FAIL + 1))
  elif [ $TEST_EXIT -eq 139 ]; then
    # Exit code 139 = 128 + 11 (SIGSEGV - Segmentation fault)
    echo -e "  ${RED}✗${NC} ${NAME} ${DIM}(segmentation fault)${NC}"
    # Show last test that was running
    LAST_TEST=$(echo "$TEST_OUTPUT" | grep "^\[TEST" | tail -1)
    if [ -n "$LAST_TEST" ]; then
      echo -e "    ${DIM}→ Crashed during: ${YELLOW}${LAST_TEST}${NC}"
    fi
    echo -e "    ${DIM}→ Debug with: ${CYAN}gdb ${BIN}${NC} ${DIM}(type 'run' then 'backtrace')${NC}"
    FAIL=1
    ASAN_FAIL=$((ASAN_FAIL + 1))
  else
    echo -e "  ${RED}✗${NC} ${NAME} ${DIM}(sanitizer error - exit code: $TEST_EXIT)${NC}"
    # Show last test that was running
    LAST_TEST=$(echo "$TEST_OUTPUT" | grep "^\[TEST" | tail -1)
    if [ -n "$LAST_TEST" ]; then
      echo -e "    ${DIM}→ Last test: ${YELLOW}${LAST_TEST}${NC}"
    fi
    echo -e "    ${DIM}→ Run manually: ${CYAN}${BIN}${NC}"
    FAIL=1
    ASAN_FAIL=$((ASAN_FAIL + 1))
  fi
done
echo ""
if [ ${ASAN_FAIL} -eq 0 ]; then
  echo -e "  ${GREEN}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
  echo -e "  ${GREEN}✓${NC} ASan/UBSan: ${BOLD}${GREEN}All ${ASAN_PASS} tests passed${NC}"
else
  echo -e "  ${RED}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${NC}"
  echo -e "  ${YELLOW}⚠${NC}  ASan/UBSan: ${GREEN}${ASAN_PASS} passed${NC}, ${RED}${ASAN_FAIL} failed${NC}"
fi
echo ""

echo -e "${CYAN}┌───────────────────────────────────────────────────────────────┐${NC}"
echo -e "${CYAN}│${NC} ${BOLD}[6/8]${NC} 🛡️  Defensive NULL tests ${DIM}(optional)${NC}                      ${CYAN}│${NC}"
echo -e "${CYAN}└───────────────────────────────────────────────────────────────┘${NC}"
echo -e "  ${DIM}⚠  These tests are NOT required by 42 subject${NC}"
echo ""

DEFENSIVE_SRC="${TEST_DIR}/test_defensive_null.c"
DEFENSIVE_BIN="${TEST_DIR}/run_test_defensive_null"

if [ -f "${DEFENSIVE_SRC}" ]; then
  if ${CC} ${CFLAGS_BASE} "${DEFENSIVE_SRC}" "${LIB}" -o "${DEFENSIVE_BIN}" 2>/dev/null; then
    # Run and show output (keep stderr visible for progress)
    set +e
    "${DEFENSIVE_BIN}" 2>&1
    DEFENSIVE_EXIT=$?
    set -e
    
    echo ""
    if [ $DEFENSIVE_EXIT -eq 0 ]; then
      echo -e "  ${GREEN}✓${NC} All defensive NULL tests passed"
    else
      echo -e "  ${YELLOW}⚠${NC} Some defensive NULL tests failed ${DIM}(optional - not required)${NC}"
    fi
  else
    echo -e "  ${RED}✗${NC} Defensive test compilation failed"
  fi
else
  echo -e "  ${DIM}ℹ  Defensive NULL test not found (optional)${NC}"
fi
echo ""

echo -e "${CYAN}┌───────────────────────────────────────────────────────────────┐${NC}"
echo -e "${CYAN}│${NC} ${BOLD}[7/8]${NC} 🧹 Cleaning test binaries...                            ${CYAN}│${NC}"
echo -e "${CYAN}└───────────────────────────────────────────────────────────────┘${NC}"
rm -f "${TEST_DIR}"/run_test_*
echo -e "  ${GREEN}✓${NC} Test binaries cleaned"
echo ""

echo -e "${CYAN}┌───────────────────────────────────────────────────────────────┐${NC}"
echo -e "${CYAN}│${NC} ${BOLD}[8/8]${NC} 🧹 Cleaning project...                                  ${CYAN}│${NC}"
echo -e "${CYAN}└───────────────────────────────────────────────────────────────┘${NC}"
make fclean >/dev/null 2>&1 || true
echo -e "  ${GREEN}✓${NC} Project cleaned"
echo ""

echo ""
if [ ${FAIL} -eq 0 ]; then
  echo -e "${GREEN}╔════════════════════════════════════════════════════════════════╗${NC}"
  echo -e "${GREEN}║${NC}  ${BOLD}✅ ALL TESTS PASSED${NC}                                           ${GREEN}║${NC}"
  echo -e "${GREEN}╚════════════════════════════════════════════════════════════════╝${NC}"
  echo ""
  exit 0
else
  echo -e "${RED}╔════════════════════════════════════════════════════════════════╗${NC}"
  echo -e "${RED}║${NC}  ${BOLD}❌ SOME TESTS FAILED${NC}                                          ${RED}║${NC}"
  echo -e "${RED}╚════════════════════════════════════════════════════════════════╝${NC}"
  echo ""
  echo -e "${DIM}  Run individual tests to see detailed errors${NC}"
  echo ""
  exit 8
fi
