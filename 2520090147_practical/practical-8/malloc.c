#include <stdio.h>
#include <stdlib.h>

int main() {
    int i;

    int *arr1 = (int *)malloc(5 * sizeof(int));

    printf("malloc() Memory:\n");
    for(i = 0; i < 5; i++) {
        arr1[i] = i + 1;
        printf("%d ", arr1[i]);
    }

    printf("\n\n");

    int *arr2 = (int *)calloc(5, sizeof(int));

    printf("calloc() Memory:\n");
    for(i = 0; i < 5; i++) {
        printf("%d ", arr2[i]);
    }

    printf("\n\n");

    arr1 = (int *)realloc(arr1, 10 * sizeof(int));

    printf("realloc() Memory:\n");
    for(i = 5; i < 10; i++) {
        arr1[i] = i + 1;
    }

    for(i = 0; i < 10; i++) {
        printf("%d ", arr1[i]);
    }

    printf("\n");

    free(arr1);
    free(arr2);

    return 0;
}
