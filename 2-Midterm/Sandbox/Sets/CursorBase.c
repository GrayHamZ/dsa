#include <stdio.h>
#include <stdlib.h>
#define MAX 50

typedef int Set;

typedef struct {
    int data;
    int next;
} Nodetype;

typedef struct {
    Nodetype nodes[MAX];
    int avail;
} VHeap;

void initVH(VHeap *V);
int mallocVH(VHeap *V);
void freeVH(VHeap *V, int index);

void populateSet(Set *S, VHeap *V);
void insert(Set *S, int data, VHeap *V);
void printSet(Set S, VHeap V);
Set Union(Set A, Set B, VHeap *V);
Set Intersection(Set A, Set B, VHeap *V);
Set Difference(Set A, Set B, VHeap *V);

int main() {
    VHeap V;
    initVH(&V);

    Set S = mallocVH(&V);
    Set newNode = mallocVH(&V);

    V.nodes[S].next = newNode;

    printf("%d", V.avail);

}

void freeVH(VHeap *V, int index) {
    if (index >= 0 && index < MAX) {
        V->nodes[index].next = V->avail;
        V->avail = index;
    }
}

int mallocVH(VHeap *V) {
    int temp = V->avail;

    if (temp != -1) {
        V->avail = V->nodes[temp].next;
    } else {
        printf("EMPTY");
    }
    
    return temp;
}

void initVH(VHeap *V) {
    for (int i = 1; i < MAX; i++) {
        V->nodes[i - 1].next = i;
    }

    V->avail = 0;
    V->nodes[MAX - 1].next = -1;
}