#include <stdio.h>
#include <stdlib.h>

#define BUCKET_SIZE 3  // Maximum elements per small bucket before sorting

// Structure to represent a bucket
typedef struct bucket {
    int count;             // Number of elements currently in the bucket
    int values[BUCKET_SIZE]; // Array to store elements
} Bucket;

// Insertion sort used to sort elements inside a bucket
void insertionSort(int *arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Bucket Sort function
void bucketSort(int *arr, int n) {
    if (n <= 0) return;

    int max = arr[0], min = arr[0];

    // Find minimum and maximum elements in the array
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
        if (arr[i] < min) min = arr[i];
    }

    // Calculate number of buckets needed
    int nBuckets = (max - min) / BUCKET_SIZE + 1;

    // Allocate memory for buckets
    Bucket *buckets = (Bucket *)malloc(nBuckets * sizeof(Bucket));
    for (int i = 0; i < nBuckets; i++)
        buckets[i].count = 0; // Initialize bucket counts

    // Distribute array elements into buckets
    for (int i = 0; i < n; i++) {
        int pos = (arr[i] - min) / BUCKET_SIZE;
        if (buckets[pos].count < BUCKET_SIZE) {
            buckets[pos].values[buckets[pos].count++] = arr[i];
        } else {
            // If bucket is full, you could dynamically expand, 
            // but here we assume BUCKET_SIZE is enough
            printf("Bucket overflow! Increase BUCKET_SIZE.\n");
            free(buckets);
            return;
        }
    }

    // Sort individual buckets and merge back into original array
    int idx = 0;
    for (int i = 0; i < nBuckets; i++) {
        insertionSort(buckets[i].values, buckets[i].count);
        for (int j = 0; j < buckets[i].count; j++)
            arr[idx++] = buckets[i].values[j];
    }

    free(buckets);
}

int main() {
    int n;
    printf("Enter the size of the array: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid array size.\n");
        return 0;
    }

    int *arr = (int *)malloc(n * sizeof(int));

    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; i++) {
        printf("Element %d: ", i + 1);
        scanf("%d", &arr[i]);
    }

    printf("Unsorted array:\n");
    for (int i = 0; i < n; i++)
        printf("%d\t", arr[i]);
    printf("\n");

    bucketSort(arr, n);

    printf("Sorted array:\n");
    for (int i = 0; i < n; i++)
        printf("%d\t", arr[i]);
    printf("\n");

    free(arr);
    return 0;
}
