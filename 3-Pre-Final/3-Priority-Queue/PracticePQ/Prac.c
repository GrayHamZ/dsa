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
void maxHeapify(Tree *T, int index, int heapSize);
void displayTree(Tree T);
void heapSort(Tree *T);

int main() {
    Tree T;
	int arr[] = {10, 20, 5, 1, 30, 40, 50, 60, 70, 80};
	int size = sizeof(arr) / sizeof(arr[0]);

    initTree(&T);
	populateTree(&T, arr, size);

    // heapSort(&T);

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
}

void insertTree(Tree *T, int data) {
    ++T->lastIndex;
    T->elements[T->lastIndex] = data;

    int i = T->lastIndex;

    while (i > 0 && T->elements[(i - 1) / 2] > T->elements[i]) {
        int temp = T->elements[(i - 1) / 2];
        T->elements[(i - 1) / 2] = T->elements[i];
        T->elements[i] = temp;

        i = (i - 1) / 2;
    }
}

void maxHeapify(Tree *T, int index, int heapSize) {
    int largest = index;
    int left = largest * 2 + 1;
    int right = largest * 2 + 2;

    if (left < heapSize && T->elements[left] > T->elements[largest]) {
        largest = left;
    }

    if (right < heapSize && T->elements[right] > T->elements[largest]) {
        largest = right;
    }

    if (largest != index) {
        int temp = T->elements[index];
        T->elements[index] = T->elements[largest];
        T->elements[largest] = temp;

        maxHeapify(T, largest, heapSize);
    }
}

void heapSort(Tree *T) {
    int size = T->lastIndex + 1;
    for (int i = (size - 1) / 2; i >= 0; i--) {
        maxHeapify(T, i, size);
    }

    for (int i = size - 1; i > 0; i--) {
        int temp = T->elements[0];
        T->elements[0] = T->elements[i];
        T->elements[i] = temp;

        maxHeapify(T, 0, i);
    }
}

int deleteMin(Tree *T) {

}

void displayTree(Tree T) {
    for (int i = 0; i < T.lastIndex + 1; i++) {
        printf("%d ", T.elements[i]);
    }
}

