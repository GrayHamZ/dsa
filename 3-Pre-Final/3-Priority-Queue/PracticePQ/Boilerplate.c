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

}

void populateTree(Tree *T, int arr[], int size) {

}

void insertTree(Tree *T, int data) {

}

void minHeapify(Tree *T, int index, int heapSize) {

}

void heapSort(Tree *T) {

}

int deleteMin(Tree *T) {

}

void displayTree(Tree T) {

}

