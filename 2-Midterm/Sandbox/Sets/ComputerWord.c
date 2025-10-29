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

int main() {
    Set S;
    init(&S);
    insertElem(&S,3);
    insertElem(&S,4);
    insertElem(&S,4);
    insertElem(&S,6);
    // displayBitPattern(S);
    displayElem(S);
    return 0;
}

void init(Set *S) {
    *S = 0;
}

void displayElem(Set S) {
    for (int i = 0; i < MAX; i++) {
        if (1 & (S >> i)) {
            printf("%d,", i);
        }
    }    
}

void deleteElem(Set *S, int elem) {
    *S &= ~(1 << elem);
    // ~(1 << elem) pushes the 1 to the right elem times and inverses it
    // Ex: 1 << 3 = 00001000,
    // ~(1 << 3) = 11110111
    // so when you want to remove the 4 in *S which is also 00001000
    // it intersects them 00001000 & 11110111
}

void insertElem(Set *S, int elem) {
    *S |= (1 << elem);
}

void displayBitPattern(Set S) {
    for (int i = 0; i < MAX; i++) {
        printf("[%d]: ", i);
        if (1 & (S >> i)) {
            printf("1\n");
        } else {
            printf("0\n");
        }
    }
}