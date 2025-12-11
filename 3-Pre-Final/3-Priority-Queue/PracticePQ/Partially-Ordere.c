#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10

// IMPORTANT THINGS TO KNOW
// PARENT = (child - 1) / 2
// Left-Child = (PARENT * 2) + 1
// Right-Child = (PARENT * 2) + 2
// last non-leaf node = (Size - 1) / 2




// prioritized by elements
typedef struct {
    int elements[MAX];
    int lastIndex;
} Tree;

void initTree(Tree *T);
void populateTree(Tree *T, int arr[], int size);
void insertTree(Tree *T, int data);
int deleteMin(Tree *T);
void minHeapify(Tree *T, int index, int heapSize);
void displayTree(Tree T);
void heapSort(Tree *T);

int main() {
    Tree T;
	int arr[] = {10, 20, 5, 1, 30, 40, 50, 60, 70, 80};
	int size = sizeof(arr) / sizeof(arr[0]);

    initTree(&T);
	populateTree(&T, arr, size);

    heapSort(&T);

    // deleteMin(&T);

    printf("Elements in order: ");
    displayTree(T);

    return 0;
}

void initTree(Tree *T) {
    T->lastIndex = -1;
}

void populateTree(Tree *T, int arr[], int size) {
    for (int i = 0; i < size; i++) {
        insertTree(T, arr[i]);
    }
    printf("\n");
}

void insertTree(Tree *T, int data) {
    printf("%d ", data);

    int i = ++T->lastIndex;
    T->elements[i] = data;

    // PARENT = (i - 1) / 2

    // While the PARENT is greater than the child/node to compare
    // for min heap
    // while (i > 0 && T->elements[(i - 1) / 2] > T->elements[i]) {
        
    //     // swap parent and child because parent is greater
    //     int temp = T->elements[(i - 1) / 2];
    //     T->elements[(i - 1) / 2] = T->elements[i];
    //     T->elements[i] = temp;

    //     // index should point to the parent to check in the next iteration
    //     i = (i - 1) / 2;
    // }
}

void minHeapify(Tree *T, int index, int heapSize) {
    int smallest = index; // root
    int left = 2 * smallest + 1;
    int right = 2 * smallest + 2;

    // if left child is smaller then the initial index
    if (left < heapSize && T->elements[left] < T->elements[smallest]) {
        smallest = left;
    }

    if (right < heapSize && T->elements[right] < T->elements[smallest]) {
        smallest = right;
    }

    if (smallest != index) {
        // swap
        int temp = T->elements[index];
        T->elements[index] = T->elements[smallest];
        T->elements[smallest] = temp;

        minHeapify(T, smallest, heapSize);
    }

}



void heapSort(Tree *T) {
    // Build min heap
    int size = T->lastIndex + 1;

    // We do (size - 1) / 2 because it the last parent node. basically the last node's parent
    // we do i >= 0 because we want to heapify the 0 index aswell
    for (int i = (size - 1) / 2; i >= 0; i--) {
        // the reason why we do this is because we need to heapify all the parent starting with the last
        // we pass i in the root parameter because thats the parent we want to heapify
        minHeapify(T, i, size);
    }

    // Extract elements one by one
    for (int i = size - 1; i > 0; i--) {
        // Swap root (min) with last element
        int swap = T->elements[0];
        T->elements[0] = T->elements[i];
        T->elements[i] = swap;
        
        // Heapify the reduced heap
        // "i" is the "fake" size of the heap. we are tricking the heapify function basically
        // it will think its gradually shrinking when its not.
        // if size isnt a parameter you might need to temp the lastindx and reassign after
        minHeapify(T, 0, i);
    }
}

int deleteMin(Tree *T) {
    if (T->lastIndex < 0) {
        return -1;
    }

    int min = T->elements[0];
    T->elements[0] = T->elements[T->lastIndex];
    (T->lastIndex)--;

    minHeapify(T, 0, T->lastIndex + 1);
    return min;
}

void displayTree(Tree T) {
    for (int i = 0; i < T.lastIndex + 1; i++) {
        printf("%d ", T.elements[i]);
    }
}

