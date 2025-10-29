#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 5

typedef int Set[MAX]; // only ones and zeroes

void populateSet(Set S);
void initSet(Set S);
void printSet(Set S);
void insert(Set S, int index);
void delete(Set S, int index);
Set *Union(Set A, Set B);
Set *Intersection(Set A, Set B);
Set *Difference(Set A, Set B);

int main() {
    Set A;
    Set B;
    initSet(A);
    initSet(B);
    
    insert(A, 2);
    insert(A, 4);
    insert(A, 3);

    insert(B, 2);
    insert(B, 1);
    insert(B, 0);

    printSet(*Difference(A,B));

    return 0;
}

Set *Difference(Set A, Set B) {
    Set *toReturn = (Set*)malloc(sizeof(Set));
    if (toReturn == NULL) return NULL;

    for (int i = 0; i < MAX; i++) {
        (*toReturn)[i] = A[i] & ~(B[i]);
    }

    return toReturn;     
}

Set *Intersection(Set A, Set B) {
    Set *toReturn = (Set*)malloc(sizeof(Set));
    if (toReturn == NULL) return NULL;

    for (int i = 0; i < MAX; i++) {
        (*toReturn)[i] = A[i] & B[i];
    }

    return toReturn;    
}

Set *Union(Set A, Set B) {
    Set *toReturn = (Set*)malloc(sizeof(Set));
    if (toReturn == NULL) return NULL;

    for (int i = 0; i < MAX; i++) {
        (*toReturn)[i] = A[i] | B[i];
    }

    return toReturn;    
}

void insert(Set S, int index) {
    if (index >= 0 && index < MAX) {
        S[index] = 1;
    }
}

void delete(Set S, int index) {
    if (index >= 0 && index < MAX) {
        S[index] = 0;
    }
}

void printSet(Set S) {
    for (int i = 0; i < MAX; i++) {
        printf("[%d]: %d\n", i, S[i]);
    }
}

void initSet(Set S) {
    for (int i = 0; i < MAX; i++) {
        S[i] = 0;
    }
}

