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
    for (size_t i = n/2; i > 0; --i) {
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
void compareSorts(int type, size_t n, unsigned int *resultbc, unsigned int *resulthc,
                  unsigned int *resultbs, unsigned int *resulths) {
            ll *arr1 = malloc(n * sizeof(ll));
            ll *arr2 = malloc(n * sizeof(ll));
            genArray(n, arr1, type);
            memcpy(arr2, arr1, n * sizeof(ll));
            bubbleSort(n, arr1);
            *resultbc = compares;
            *resultbs = swaps;
            reset();
            heapSort(n, arr2);
            *resulthc = compares;
            *resulths = swaps;
            reset();
}
bool test() {
    size_t n = 1000;
    int type = 0;
    for (int i = 0; i < 3; ++i) {
        ll *arr1 = malloc(n * sizeof(ll));
        ll *arr2 = malloc(n * sizeof(ll));
        genArray(n, arr1, type);
        memcpy(arr2, arr1, n * sizeof(ll));
        
        bubbleSort(n, arr1);
        heapSort(n, arr2);
        for (int j = 0; j < n-1; ++j) {
            if(isLess(arr1[j], arr1[j+1]) || isLess(arr2[j], arr2[j+1]))
                return false;
        }
        reset();
        return true;
    }

}
int main(int argc, char* argv[]) {
    srand(time(NULL));
    if (!test()) {
        printf("Error: test array aren't sorted!");
        return 1;
    }
    printf("Start tests\n");
    if(argc > 1)
        for (size_t i = 10; i <= 10000; i*=10) {
            printf("Test for i = %d\n", i);
            printf("Ordered version\n");
            ll *arr1 = malloc(i * sizeof(ll));
            ll *arr2 = malloc(i * sizeof(ll));
            genArray(i, arr1, 1);
            memcpy(arr2, arr1, i* sizeof(ll));
            bubbleSort(i, arr1);
            printf("Result for bubbleSort is %u compares and %u swaps\n", compares, swaps);
            reset();
            heapSort(i, arr2);
            printf("Result for heapSort is %u compares and %u swaps\n", compares, swaps);
            reset();
            printf("\n");

            printf("Back ordered version\n");
            genArray(i, arr1, -1);
            memcpy(arr2, arr1, i* sizeof(ll));
            bubbleSort(i, arr1);
            printf("Result for bubbleSort is %u compares and %u swaps\n", compares, swaps);
            reset();
            heapSort(i, arr2);
            printf("Result for heapSort is %u compares and %u swaps\n", compares, swaps);
            reset();
            printf("\n");

            printf("Random 1 version\n");
            genArray(i, arr1, 0);
            memcpy(arr2, arr1, i* sizeof(ll));
            //printarr(i, arr2);
            bubbleSort(i, arr1);
            //printarr(i, arr1);
            printf("Result for bubbleSort is %u compares and %u swaps\n", compares, swaps);
            reset();
            heapSort(i, arr2);
            //printarr(i, arr2);
            printf("Result for heapSort is %u compares and %u swaps\n", compares, swaps);
            reset();
            printf("\n");

            printf("Random 2 version\n");
            genArray(i, arr1, 0);
            memcpy(arr2, arr1, i* sizeof(ll));
            bubbleSort(i, arr1);
            printf("Result for bubbleSort is %u compares and %u swaps\n", compares, swaps);
            reset();
            heapSort(i, arr2);
            printf("Result for heapSort is %d compares and %d swaps\n", compares, swaps);
            reset();
            printf("\n");
        }
    else {
        unsigned int resultbc[4][4] = {0};
        unsigned int resultbs[4][4] = {0};
        unsigned int resulthc[4][4] = {0};
        unsigned int resulths[4][4] = {0};

        for (size_t i = 10, j = 0; i <= 10000; i *= 10, j++) {
            compareSorts(1, i, &resultbc[j][0], &resulthc[j][0], &resultbs[j][0], &resulths[j][0]);
            compareSorts(-1, i, &resultbc[j][1], &resulthc[j][1], &resultbs[j][1], &resulths[j][1]);
            compareSorts(0, i, &resultbc[j][2], &resulthc[j][2], &resultbs[j][2], &resulths[j][2]);
            compareSorts(0, i, &resultbc[j][3], &resulthc[j][3], &resultbs[j][3], &resulths[j][3]);
        }
        for (size_t i = 0; i < 4; ++i) {
            unsigned int average = 0;
            for (size_t k = 0; k < 4; ++k) {
                printf("%u&", resultbc[i][k]);
                average += resultbc[i][k];
            }
            printf("%u\n", average/4);
            average = 0;
            for (size_t k = 0; k < 4; ++k) {
                printf("%u&", resultbs[i][k]);
                average += resultbs[i][k];
            }
            printf("%u\n", average/4);
        }
        for (size_t i = 0; i < 4; ++i) {
            unsigned int average = 0;
            for (size_t k = 0; k < 4; ++k) {
                printf("%u&", resulthc[i][k]);
                average += resulthc[i][k];
            }
            printf("%u\n", average/4);
            average = 0;
            for (size_t k = 0; k < 4; ++k) {
                printf("%u&", resulths[i][k]);
                average += resulths[i][k];
            }
            printf("%u\n", average/4);
        }
    }
    return 0;
}