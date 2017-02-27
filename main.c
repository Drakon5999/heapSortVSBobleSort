#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
// long long - back order by mod - boble - heap
// 10 - 100 - 1000 - 10000
// ordered - back ordered - random x2
#define ll long long
unsigned int compares = 0, swaps = 0;

void genArray(size_t n, ll *arr, int order) {
    if (order != 0) {
        for (size_t i = 0; i < n; ++i) {
            arr[i] = order > 0 ? i : n-i;
        }
    } else {
        srand(time(NULL));
        for (size_t i = 0; i < n ; ++i) {
            arr[i] = rand() * rand() * rand() * rand() * rand();
        }
    }

}
void swap(ll *a, ll *b) {
    ll t = *a;
    *a = *b;
    *b = t;
    swaps++;
}
bool isLess(ll a, ll b) {
    compares++;
    return llabs(a) < llabs(b) ? true : false;
}
void reset(void) {
    compares = 0;
    swaps = 0;
}
void bubbleSort(size_t n, ll *arr) {
    bool flag = false;
    for (size_t i = 0; i < n-1; ++i) {
        if (isLess(arr[i], arr[i + 1])) {
            swap(&arr[i+1], &arr[i]);
            flag = true;
        }
        if(flag && i == n-2) {
            i = -1;
            flag = false;
        }
    }
}

void heapify(size_t i, size_t n, ll *arr) {
    size_t leftChild;
    size_t rightChild;
    size_t lowestChild;
    while (true) {
        leftChild = i*2 + 1;
        rightChild = i*2 + 2;
        lowestChild = i;

        if (leftChild < n && isLess(arr[leftChild], arr[lowestChild])) {
            lowestChild = leftChild;
        }
        if (rightChild < n && isLess(arr[rightChild], arr[lowestChild])) {
            lowestChild = rightChild;
        }
        if (lowestChild == i) break;

        swap(&arr[lowestChild], &arr[i]);
        i = lowestChild;
    }
}

void heapSort(size_t n, ll *arr) {
    for (size_t i = n; i > 0; --i) {
        heapify(i-1, n, arr);
    }
    size_t j = n-1;
    while (j > 0) {
        swap(&arr[0], &arr[j]);
        j--;
        heapify(0, j+1, arr);
    }
}
void printarr(size_t n, ll *arr) {
    for (size_t i = 0; i < n; ++i) {
        printf("%lld\n", llabs(arr[i]));
    }
    printf("\n");
}
int main() {
    printf("Start tests\n");
    for (size_t i = 10; i <= 10000; i*=10) {
        printf("Test for i = %d\n", i);
        printf("Ordered version\n");
        ll *arr1 = malloc(i * sizeof(ll));
        ll *arr2 = malloc(i * sizeof(ll));
        genArray(i, arr1, 1);
        memcpy(arr2, arr1, i* sizeof(ll));
        bubbleSort(i, arr1);
        printf("Result for bubbleSort is %d compares and %d swaps\n", compares, swaps);
        reset();
        heapSort(i, arr2);
        printf("Result for heapSort is %d compares and %d swaps\n", compares, swaps);
        reset();
        printf("\n");

        printf("Back ordered version\n");
        genArray(i, arr1, -1);
        memcpy(arr2, arr1, i* sizeof(ll));
        bubbleSort(i, arr1);
        printf("Result for bubbleSort is %d compares and %d swaps\n", compares, swaps);
        reset();
        heapSort(i, arr2);
        printf("Result for heapSort is %d compares and %d swaps\n", compares, swaps);
        reset();
        printf("\n");

        printf("Random 1 version\n");
        genArray(i, arr1, 0);
        memcpy(arr2, arr1, i* sizeof(ll));
        //printarr(i, arr2);
        bubbleSort(i, arr1);
        //printarr(i, arr1);
        printf("Result for bubbleSort is %d compares and %d swaps\n", compares, swaps);
        reset();
        heapSort(i, arr2);
        //printarr(i, arr2);
        printf("Result for heapSort is %d compares and %d swaps\n", compares, swaps);
        reset();
        printf("\n");

        printf("Random 2 version\n");
        genArray(i, arr1, 0);
        memcpy(arr2, arr1, i* sizeof(ll));
        bubbleSort(i, arr1);
        printf("Result for bubbleSort is %d compares and %d swaps\n", compares, swaps);
        reset();
        heapSort(i, arr2);
        printf("Result for heapSort is %d compares and %d swaps\n", compares, swaps);
        reset();
        printf("\n");
    }
    return 0;
}