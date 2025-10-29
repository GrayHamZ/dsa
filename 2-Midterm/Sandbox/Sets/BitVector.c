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
    initSet(A);
    insert(A,1);
    insert(A,2);
    Set B;
    initSet(B);
    insert(B,2);
    insert(B,3);

    printSet(*Difference(A,B));

}

void delete(Set S, int index) {
    if (index >= 0 && index < MAX) {
        S[index] = 0;
    }    
}

void insert(Set S, int index) {
    if (index >= 0 && index < MAX) {
        S[index] |= 1;
    }
}

Set *Difference(Set A, Set B) {
    Set *toReturn = (Set *)malloc(sizeof(Set));
    if (toReturn == NULL) return NULL;
    
    initSet(*toReturn);

    for (int i = 0; i < MAX; i++) {
        (*toReturn)[i] = A[i] & (~B[i]);
    }

    return toReturn;     
}

Set *Intersection(Set A, Set B) {
    Set *toReturn = (Set *)malloc(sizeof(Set));
    if (toReturn == NULL) return NULL;
    
    initSet(*toReturn);

    for (int i = 0; i < MAX; i++) {
        (*toReturn)[i] = A[i] & B[i];
    }

    return toReturn;    
}

Set *Union(Set A, Set B) {
    Set *toReturn = (Set *)malloc(sizeof(Set));
    if (toReturn == NULL) return NULL;
    
    initSet(*toReturn);

    for (int i = 0; i < MAX; i++) {
        (*toReturn)[i] = A[i] | B[i];
    }

    return toReturn;
}

void initSet(Set S) {
    for (int i = 0; i < MAX; i++) {
        S[i] = 0;
    }
}

void printSet(Set S) {
    for (int i = 0; i < MAX; i++) {
        printf("[%d]: %d\n", i, S[i]);
    }    
}