#include <malloc.h>
#include <iostream>

using namespace std;

#define THRESHOLD 16

static inline void swap(int* a, int* b) {
    int t = *a; *a = *b; *b = t;
}

template<typename CMP>
static inline int pivot(int* a, int lo, int hi, CMP cmp) {
    int mid = lo + ((hi - lo) >> 1);
    if (cmp(a[lo], a[mid])) swap(&a[lo], &a[mid]);
    if (cmp(a[mid], a[hi])) swap(&a[mid], &a[hi]);
    if (cmp(a[lo], a[mid])) swap(&a[lo], &a[mid]);

    swap(&a[mid], &a[hi - 1]);
    return a[hi - 1];
}

template<typename CMP>
static inline void insertion_sort(int* a, int lo, int hi, CMP cmp) {
    for (int i = lo + 1; i <= hi; i++) {
        int key = a[i], j = i - 1;
        while (j >= lo && cmp(key, a[j])) { a[j + 1] = a[j]; --j; }
        a[j + 1] = key;
    }
}

template<typename CMP>
static void qsort_impl(int* a, int lo, int hi, CMP cmp) {
    if (lo >= hi) return;

    if (hi - lo <= THRESHOLD) {
        insertion_sort(a, lo, hi, cmp);
        return;
    }

    int pv = pivot(a, lo, hi, cmp);
    int i = lo, j = hi - 1;

    for (;;) {
        while (cmp(a[++i], pv)) {}
        while (cmp(pv, a[--j])) {}

        if (i >= j) break;
        swap(&a[i], &a[j]);
    }

    swap(&a[i], &a[hi - 1]);

    qsort_impl(a, lo, i - 1, cmp);
    qsort_impl(a, i + 1, hi, cmp);
}

template<typename CMP>
void quick_sort(int* a, int n, CMP cmp) {
    if (n > 1) qsort_impl(a, 0, n - 1, cmp);
}

int main(void) {
    int n;

    cin >> n;

    int* a = new int[n];

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    quick_sort(a, n, [](int a, int b) {
        return a < b;
    });

    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << "\n";

    quick_sort(a, n, [](int a, int b) {
        return a > b;
    });

    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    
}