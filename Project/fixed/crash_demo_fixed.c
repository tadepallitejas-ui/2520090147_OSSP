/*
 * crash_demo_fixed.c
 * Fix: guard against a NULL pointer before dereferencing it,
 * exactly the line GDB's backtrace pointed to in the buggy build.
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
    while (cur != NULL) {
        sum += cur->value;
        cur = cur->next;
    }
    return sum;
}

int main(void) {
    Node n1 = {10, NULL};
    Node n2 = {20, NULL};
    n1.next = &n2;

    Node *broken = NULL;
    printf("Sum of well-formed list: %d\n", compute_sum(&n1));

    printf("Checking broken list safely...\n");
    if (broken == NULL) {                     /* FIX: NULL check */
        printf("broken is NULL - skipping dereference safely\n");
    } else {
        printf("First value of broken list: %d\n", broken->value);
    }

    return 0;
}
