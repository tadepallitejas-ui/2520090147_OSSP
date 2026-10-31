/*
 * crash_demo.c
 * ------------------------------------------------------------
 * Small, isolated crash used purely to demonstrate GDB usage:
 * breakpoints, stepping, variable inspection, and backtrace
 * on a genuine NULL-pointer dereference (SIGSEGV).
 * ------------------------------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

int compute_sum(Node *head) {
    int sum = 0;
    Node *cur = head;
    /* BUG: loop condition should check cur, but dereferences
     * cur->next first on a node whose 'next' was never linked,
     * eventually landing on a NULL node pointer. */
    while (cur != NULL) {
        sum += cur->value;
        cur = cur->next;
    }
    return sum;
}

int main(void) {
    Node n1 = {10, NULL};
    Node n2 = {20, NULL};   /* n2.next intentionally left dangling-looking */
    n1.next = &n2;
    /* n2.next is NULL, so compute_sum should stop safely -- but we
     * now force a crash by dereferencing a node pointer that was
     * never initialised, simulating a broken list build step. */
    Node *broken = NULL;
    printf("Sum of well-formed list: %d\n", compute_sum(&n1));

    printf("Now triggering the bug (NULL dereference)...\n");
    printf("First value of broken list: %d\n", broken->value); /* SIGSEGV here */

    return 0;
}
