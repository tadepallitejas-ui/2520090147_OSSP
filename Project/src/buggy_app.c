/*
 * buggy_app.c
 * ------------------------------------------------------------
 * Team 16 - Section 13 - OSSP (25CS2104E)
 * Project: DEBUGGING - Detection and Analysis of Memory Leaks
 *          in Linux Applications Using Debugging Tools
 *
 * This program intentionally contains five classic C memory
 * bugs so that Valgrind (memcheck) and GDB can be used to
 * detect, trace, and fix them:
 *
 *   1. Heap memory leak            -> memory_leak_demo()
 *   2. Use-after-free              -> use_after_free_demo()
 *   3. Heap buffer overflow        -> buffer_overflow_demo()
 *   4. Double free                 -> double_free_demo()
 *   5. Uninitialised value read    -> uninitialised_read_demo()
 *
 * Each function is self-contained and labelled so its output
 * in the Valgrind report can be matched back to this source
 * file line-by-line (compiled with -g for symbol info).
 * ------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Bug 1: allocated memory is never freed */
void memory_leak_demo(void) {
    printf("[1] Memory Leak Demo\n");
    int *record = (int *)malloc(10 * sizeof(int));
    for (int i = 0; i < 10; i++) {
        record[i] = i * i;
    }
    printf("    record[9] = %d (leaked block never freed)\n", record[9]);
    /* BUG: missing free(record); */
}

/* Bug 2: pointer is used after it has been freed */
void use_after_free_demo(void) {
    printf("[2] Use-After-Free Demo\n");
    char *msg = (char *)malloc(32);
    strcpy(msg, "hello from heap");
    free(msg);
    /* BUG: msg is dangling here */
    printf("    msg after free = %s\n", msg);
}

/* Bug 3: writes past the end of an allocated buffer */
void buffer_overflow_demo(void) {
    printf("[3] Heap Buffer Overflow Demo\n");
    int *arr = (int *)malloc(5 * sizeof(int));
    for (int i = 0; i <= 5; i++) {   /* BUG: off-by-one, writes arr[5] */
        arr[i] = i;
    }
    printf("    arr[4] = %d (arr[5] was an out-of-bounds write)\n", arr[4]);
    free(arr);
}

/* Bug 4: the same pointer is freed twice */
void double_free_demo(void) {
    printf("[4] Double Free Demo\n");
    int *val = (int *)malloc(sizeof(int));
    *val = 42;
    free(val);
    /* BUG: freeing again corrupts the heap allocator state */
    free(val);
}

/* Bug 5: a value is read/branched on before being initialised */
void uninitialised_read_demo(void) {
    printf("[5] Uninitialised Value Demo\n");
    int *flag = (int *)malloc(sizeof(int));
    /* BUG: *flag is never assigned before use */
    if (*flag == 1) {
        printf("    flag was 1\n");
    } else {
        printf("    flag was not 1 (value is indeterminate)\n");
    }
    free(flag);
}

int main(int argc, char *argv[]) {
    printf("==== buggy_app: running all bug demonstrations ====\n");

    memory_leak_demo();
    use_after_free_demo();
    buffer_overflow_demo();
    double_free_demo();
    uninitialised_read_demo();

    printf("==== buggy_app: finished (exit code 0) ====\n");
    return 0;
}
