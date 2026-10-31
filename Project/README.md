# DEBUGGING — Detection and Analysis of Memory Leaks in Linux Applications

**OSSP (25CS2104E), 2026–27 Term-I — Section 13, Team 16**
Yaswant H (2520090095) · Dhanvin Goud N (2520090145) · Tadepalli Tejas (2520090147)
Repo: https://github.com/tadepallitejas-ui/OS-PROJECT

This is the working implementation of the approved abstract: a Linux-based debugging
system that uses **Valgrind** and **GDB**, on top of **process management** (`fork`,
`exec`, `wait`/`waitpid`) and **memory management** (`malloc`/`free`), to detect,
analyze, and fix memory leaks and runtime errors in C programs.

## 1. Project layout

```
OS-PROJECT/
├── src/
│   ├── buggy_app.c       # 5 intentional memory/runtime bugs (target for Valgrind)
│   ├── crash_demo.c      # isolated NULL-pointer crash (target for GDB)
│   └── debug_runner.c    # fork()/exec()/waitpid() process-monitoring driver
├── fixed/
│   ├── buggy_app_fixed.c     # buggy_app.c with all 5 bugs corrected
│   └── crash_demo_fixed.c    # crash_demo.c with the NULL check added
├── scripts/
│   ├── gdb_commands.txt  # GDB batch script (breakpoint -> crash -> backtrace)
│   └── run_all.sh        # builds everything and regenerates every report
├── reports/
│   ├── valgrind_buggy.txt     # Valgrind memcheck output on buggy_app
│   ├── valgrind_fixed.txt     # Valgrind memcheck output on buggy_app_fixed (0 errors)
│   ├── gdb_session.txt        # GDB breakpoint/backtrace session on crash_demo
│   └── process_monitor.log    # debug_runner's fork/exec/wait monitoring log
├── Makefile
└── README.md
```

## 2. The five bugs (`src/buggy_app.c`)

| # | Bug | Function | Valgrind finding |
|---|-----|----------|-------------------|
| 1 | Heap memory leak | `memory_leak_demo()` | `40 bytes in 1 blocks are definitely lost` |
| 2 | Use-after-free | `use_after_free_demo()` | `Invalid read of size N ... 0 bytes inside a block of size 32 free'd` |
| 3 | Heap buffer overflow (off-by-one write) | `buffer_overflow_demo()` | `Invalid write of size 4 ... 0 bytes after a block of size 20 alloc'd` |
| 4 | Double free | `double_free_demo()` | `Invalid free() ... Address ... 0 bytes inside a block of size 4 free'd` |
| 5 | Uninitialised value read | `uninitialised_read_demo()` | `Conditional jump or move depends on uninitialised value(s)` |

Running the buggy binary directly (outside Valgrind) actually **aborts** partway
through, because glibc's own allocator (`tcache`) detects the double free and calls
`abort()` — a realistic illustration of why "manual inspection alone" (as the abstract
puts it) is not enough: the program dies with `Aborted` and no indication of *which*
of the five bugs is responsible, or that the other four exist at all. Valgrind, by
contrast, runs the process to completion and reports **all** of them with exact
source lines.

## 3. GDB session (`src/crash_demo.c`)

`crash_demo.c` builds a 2-node linked list correctly, sums it, then dereferences an
uninitialised `Node *broken` pointer — a `SIGSEGV`. `scripts/gdb_commands.txt` drives
GDB in batch mode to:

1. Set a breakpoint on `compute_sum` and inspect the list head (`print *head`).
2. `continue` execution until the real crash.
3. Print a full backtrace (`backtrace full`) and the offending pointer
   (`print broken` → `$2 = (Node *) 0x0`), pinpointing `crash_demo.c:41`.

See `reports/gdb_session.txt` for the captured session.

## 4. Process management layer (`src/debug_runner.c`)

This is the piece that ties the abstract's OS concepts (`fork`, `exec`, `wait`) into
an actual "debugging system" rather than just running tools by hand:

```
./bin/debug_runner <target-program> [args...]
```

It `fork()`s a child, `exec()`s the target under test in the child, and the parent
`waitpid()`s on it, then reports whether the child exited normally or was
**terminated by a signal** (e.g. `SIGSEGV`), logging every run to
`reports/process_monitor.log`. This is how the system would be used to batch-test
many target programs and flag which ones crashed, without a human watching each run.

## 5. Before / after comparison

| Metric (Valgrind) | `buggy_app` | `buggy_app_fixed` |
|---|---|---|
| Errors | 28 errors from 9 contexts | **0 errors** |
| Heap blocks leaked | 40 bytes in 1 block | **0 — all heap blocks freed** |
| Invalid reads/writes | 6 | 0 |
| Invalid free | 1 | 0 |

## 6. How to reproduce

```bash
sudo apt-get install -y valgrind gdb     # if not already installed
make                                      # builds bin/buggy_app, crash_demo, debug_runner, and fixed/ versions
./scripts/run_all.sh                      # rebuilds + regenerates every file in reports/
```

Individually:

```bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./bin/buggy_app
gdb -q -batch -x scripts/gdb_commands.txt ./bin/crash_demo
./bin/debug_runner ./bin/crash_demo
```

## 7. Mapping to the approved objectives

1. *Identify and analyze memory leaks* → `buggy_app.c` bug #1, `reports/valgrind_buggy.txt`.
2. *Use Valgrind and GDB for runtime/memory errors* → sections 2–3 above.
3. *Monitor allocation/deallocation during execution* → Valgrind's heap summary + `--track-origins=yes`.
4. *Generate debugging reports that help locate/fix issues* → `reports/` directory + this README's bug table, with the corrected code in `fixed/`.

## 8. Next steps (for the team)

- Dhanvin: extend `scripts/gdb_commands.txt` with a second scenario (e.g. stepping through `buffer_overflow_demo` under GDB with `watch`) and write up the GDB-side analysis section of the report.
- Yaswant: fold this README, plus the `reports/` outputs, into the final submitted report; push this structure to the GitHub repo.
- Tejas: optionally add 1–2 more bug categories (e.g. stack buffer overflow, integer-overflow-driven under-allocation) to `buggy_app.c` if the team wants a larger bug set.
