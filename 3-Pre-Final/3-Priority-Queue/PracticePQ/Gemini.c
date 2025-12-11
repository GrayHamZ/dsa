#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// --- Utility Functions ---

/**
 * @brief Swaps the values of two integers.
 */
void swap(int *a, int *b) {
    // TODO: Implement the swap logic
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief Prints the elements of an array.
 */
void print_array(int arr[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i < n - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

// --- Core Heap Functions ---

/**
 * @brief Restores the Max-Heap property in a subtree rooted at index i.
 * * Assumes subtrees rooted at left and right children are already Max-Heaps.
 * * @param arr The array representing the heap.
 * @param n The current size of the logical heap (unsorted part).
 * @param i The index of the root node to start heapifying from.
 */
void max_heapify(int arr[], int n, int i) {
    // TODO: Implement the logic to find the largest among root, left, and right children.
    // TODO: If the largest is not the root, swap and recursively call max_heapify.
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        max_heapify(arr, n, largest);
    }
}

/**
 * @brief Inserts a new element into the Max-Heap and restores the heap property.
 * * @param arr The array representing the Max-Heap.
 * @param n A pointer to the current size of the heap.
 * @param key The value of the element to be inserted.
 */
void insert_key(int arr[], int *n, int key) {
    // Check if the array is full (if you have a fixed-size array limit)
    // For simplicity, we assume the array has space here.

    // 1. Place the new element at the end and increase size
    int i = *n; // Index for the new element
    arr[i] = key;
    (*n)++;

    // 2. Bubble up (Sift-Up) the element to its correct position
    // Formula for parent of node i: floor((i - 1) / 2)
    while (i != 0 && arr[(i - 1) / 2] < arr[i]) {
        // While the parent is smaller than the current node, swap them
        swap(&arr[(i - 1) / 2], &arr[i]);
        // Move up to the parent's index
        i = (i - 1) / 2;
    }
}

/**
 * @brief Sorts an array in ascending order using the Heapsort algorithm.
 * * @param arr The array to be sorted.
 * @param n The total number of elements in the array.
 */
void heapSort(int arr[], int n) {
    // Phase 1: Build a Max-Heap from the array.
    // TODO: Loop from the last non-leaf node (n/2 - 1) down to 0, calling max_heapify.
    for (int i = n / 2 - 1; i >= 0; i--) {
        max_heapify(arr, n, i);
    }

    // Phase 2: Extract elements from the heap one by one.
    // TODO: Loop from n-1 down to 1.
    // TODO: Inside the loop:
    // 1. Swap the root (max element) with the current last element.
    // 2. Call max_heapify on the reduced heap (size i) at the new root (index 0).
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        max_heapify(arr, i, 0);
    }
}

/**
 * @brief Removes and returns the maximum element from a Max-Heap.
 * * @param arr The array representing the Max-Heap.
 * @param n A pointer to the current size of the heap.
 * @return The maximum value removed from the heap, or INT_MIN if the heap is empty.
 */
int extract_max(int arr[], int *n) {
    // TODO: Check for underflow (*n <= 0).
    // TODO: Store the max value (arr[0]).
    // TODO: Move the last element (arr[*n - 1]) to the root (arr[0]).
    // TODO: Decrease the heap size (*n)--.
    // TODO: Call max_heapify on the new root (index 0).
    // TODO: Return the stored max value.
    if (*n <= 0) {
        return INT_MIN;
    }

    int max_value = arr[0];
    arr[0] = arr[(*n) - 1];
    (*n)--;

    max_heapify(arr, *n, 0);

    return max_value;
}


// --- Main Driver Function ---

int main() {
    int arr_sort[] = {12, 11, 13, 5, 6, 7};
    int n_sort = sizeof(arr_sort) / sizeof(arr_sort[0]);

    printf("--- HEAPSORT PRACTICE ---\n");
    printf("Original array: ");
    print_array(arr_sort, n_sort);

    // Call the heapsort function
    heapSort(arr_sort, n_sort);

    printf("Sorted array (Ascending): ");
    print_array(arr_sort, n_sort);

    printf("\n");

    // --- HEAP EXTRACTION PRACTICE ---
    // Note: We need to re-build a heap to practice extraction
    int arr_heap[] = {4, 1, 3, 2, 16, 9};
    int n_heap = sizeof(arr_heap) / sizeof(arr_heap[0]);
    int current_size = n_heap;

    // First, build a Max-Heap (Phase 1 of Heapsort)
    for (int i = current_size / 2 - 1; i >= 0; i--) {
        max_heapify(arr_heap, current_size, i);
    }

    printf("--- EXTRACT-MAX PRACTICE ---\n");
    printf("Initial Max-Heap: ");
    print_array(arr_heap, current_size);

    int extracted = extract_max(arr_heap, &current_size);
    printf("Extracted Max Value: %d\n", extracted);
    printf("Heap after extraction: ");
    print_array(arr_heap, current_size);

    extracted = extract_max(arr_heap, &current_size);
    printf("Extracted Max Value: %d\n", extracted);
    printf("Heap after 2nd extraction: ");
    print_array(arr_heap, current_size);

    return 0;
}