/*
 * buggy_app_fixed.c
 * ------------------------------------------------------------
 * Corrected version of src/buggy_app.c.
 * Each fix is commented with "FIX:" next to the original bug.
 * Re-running Valgrind on this binary should report:
 *   "All heap blocks were freed -- no leaks are possible"
 *   "ERROR SUMMARY: 0 errors from 0 contexts"
 * ------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Fix 1: free the allocated block before returning */
void memory_leak_demo(void) {
    printf("[1] Memory Leak Demo (fixed)\n");
    int *record = (int *)malloc(10 * sizeof(int));
    if (!record) { perror("malloc"); return; }
    for (int i = 0; i < 10; i++) {
        record[i] = i * i;
    }
    printf("    record[9] = %d\n", record[9]);
    free(record);   /* FIX: release the block */
}

/* Fix 2: don't touch the pointer after free(); null it out */
void use_after_free_demo(void) {
    printf("[2] Use-After-Free Demo (fixed)\n");
    char *msg = (char *)malloc(32);
    if (!msg) { perror("malloc"); return; }
    strcpy(msg, "hello from heap");
    printf("    msg before free = %s\n", msg);  /* FIX: read before free */
    free(msg);
    msg = NULL;   /* FIX: avoid dangling pointer */
}

/* Fix 3: keep the loop bound inside the allocated size */
void buffer_overflow_demo(void) {
    printf("[3] Heap Buffer Overflow Demo (fixed)\n");
    int *arr = (int *)malloc(5 * sizeof(int));
    if (!arr) { perror("malloc"); return; }
    for (int i = 0; i < 5; i++) {   /* FIX: strict '<' instead of '<=' */
        arr[i] = i;
    }
    printf("    arr[4] = %d\n", arr[4]);
    free(arr);
}

/* Fix 4: free once, then null the pointer */
void double_free_demo(void) {
    printf("[4] Double Free Demo (fixed)\n");
    int *val = (int *)malloc(sizeof(int));
    if (!val) { perror("malloc"); return; }
    *val = 42;
    free(val);
    val = NULL;   /* FIX: prevents accidental second free */
}

/* Fix 5: initialise before use */
void uninitialised_read_demo(void) {
    printf("[5] Uninitialised Value Demo (fixed)\n");
    int *flag = (int *)malloc(sizeof(int));
    if (!flag) { perror("malloc"); return; }
    *flag = 0;   /* FIX: explicit initial value */
    if (*flag == 1) {
        printf("    flag was 1\n");
    } else {
        printf("    flag was not 1\n");
    }
    free(flag);
}

int main(void) {
    printf("==== buggy_app_fixed: running all corrected demonstrations ====\n");

    memory_leak_demo();
    use_after_free_demo();
    buffer_overflow_demo();
    double_free_demo();
    uninitialised_read_demo();

    printf("==== buggy_app_fixed: finished (exit code 0) ====\n");
    return 0;
}
