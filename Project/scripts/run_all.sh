#!/bin/bash
# run_all.sh
# Builds the project and regenerates every report in reports/.
# Run from the project root: ./scripts/run_all.sh
set -e

echo ">> Building project..."
make clean >/dev/null 2>&1 || true
make

echo ">> Running Valgrind on buggy_app..."
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
  --log-file=reports/valgrind_buggy.txt \
  ./bin/buggy_app || true

echo ">> Running Valgrind on buggy_app_fixed..."
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
  --log-file=reports/valgrind_fixed.txt \
  ./bin/buggy_app_fixed

echo ">> Running GDB session on crash_demo..."
gdb -q -batch -x scripts/gdb_commands.txt ./bin/crash_demo > reports/gdb_session.txt 2>&1 || true

echo ">> Running debug_runner (fork/exec/wait) against crash_demo and crash_demo_fixed..."
./bin/debug_runner ./bin/crash_demo || true
./bin/debug_runner ./bin/crash_demo_fixed || true

echo ">> Done. See reports/ for all output."
