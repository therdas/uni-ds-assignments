#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

void heapify(double arr[], int n, int i) {
    int smallest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if(l < n && arr[l] < arr[smallest])
        smallest = l;
    if(r < n && arr[r] < arr[smallest])
        smallest = r;

    if(smallest != i) {
        double temp = arr[i];
        arr[i] = arr[smallest];
        arr[smallest] = temp;

        heapify(arr, n, smallest);
    }
}

void heapsort(double arr[], int n){
    for(int i = n/2 - 1; i >= 0; --i)
        heapify(arr, n, i);

    for(int i = n - 1; i > 0; i--) {
        double temp = arr[i];
        arr[i] = arr[0];
        arr[0] = temp;

        heapify(arr, i, 0);
    }

    for(int i = 0; i < n/2; ++i) {
        double temp = arr[i];
        arr[i] = arr[n-i-1];
        arr[n-i-1] = temp;
    }
}

void printarr(double arr[], int n) {
    printf("[");
    for(int i = 0; i < n; ++i)
        printf("%lf, ", arr[i]);
    printf("\b\b] ");
}

int main() {
    double arr[] = {12,11,13,5,6,7};
    int n = sizeof(arr)/sizeof(arr[0]);

    heapsort(arr, n);
    printarr(arr, n);
}