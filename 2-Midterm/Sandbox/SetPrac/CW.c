#include <stdio.h>
#include <stdlib.h>
#define MAX (sizeof(unsigned int) * 8)

// LEFT TO RIGHT IMPLEMENTATION FOR SET
typedef unsigned int Set; // 32 bits

void init(Set *S);
void displayBitPattern(Set S);

void insertElem(Set *S, int elem);
void deleteElem(Set *S, int elem);
void displayElem(Set S);
Set Union(Set A, Set B);
Set Intersection(Set A, Set B);
Set Difference(Set A, Set B);

int main() {
    // Initialize two sets
    Set A, B;
    init(&A);
    init(&B);
    
    // Insert elements into Set A
    printf("=== Building Set A ===\n");
    insertElem(&A, 1);
    insertElem(&A, 3);
    insertElem(&A, 5);
    insertElem(&A, 7);
    insertElem(&A, 9);
    
    printf("Set A elements: ");
    displayElem(A);
    printf("\nSet A bit pattern:\n");
    displayBitPattern(A);
    
    // Insert elements into Set B
    printf("\n=== Building Set B ===\n");
    insertElem(&B, 3);
    insertElem(&B, 4);
    insertElem(&B, 5);
    insertElem(&B, 6);
    insertElem(&B, 7);
    
    printf("Set B elements: ");
    displayElem(B);
    printf("\nSet B bit pattern:\n");
    displayBitPattern(B);
    
    return 0;
}

void displayBitPattern(Set S) {
    for (int i = 0; i < MAX; i++) {
        printf("[%d]: %d\n", i, 1 & S >> i);
    }
}

void deleteElem(Set *S, int elem) {
    (*S) &= ~(1 << elem);
}

void insertElem(Set *S, int elem) {
    (*S) |= 1 << elem;
}

void init(Set *S) {
    (*S) = 0;
}

void displayElem(Set S) {
    // TODO: Print elements in set format { 1, 3, 5, ... }
    printf("{ ");
    for (int i = 0; i < MAX; i++) {
        if (S & (1 << i)) {
            printf("%d ", i);
        }
    }
    printf("}");
}

Set Union(Set A, Set B) {
    // TODO: Return A | B (bitwise OR)
    return A | B;
}

Set Intersection(Set A, Set B) {
    // TODO: Return A & B (bitwise AND)
    return A & B;
}

Set Difference(Set A, Set B) {
    // TODO: Return A & ~B (A AND NOT B)
    return A & ~B;
}

