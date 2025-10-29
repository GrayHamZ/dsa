#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10

typedef struct {
    int set[MAX];
    int size;
} Set;

void insertToSet(Set *S, int data);
void initSet(Set *S);
void deleteFromSet(Set *S, int data);
void populateSet(Set *S);
bool isMember(Set S, int data);
void printSet(Set S);
Set Union(Set A, Set B);
Set Intersection(Set A, Set B);
Set Difference(Set A, Set B);

int main() {

    Set A;
    Set B;

    initSet(&B);
    initSet(&A);

    insertToSet(&A, 1);
    insertToSet(&A, 3);
    insertToSet(&A, 5);
    insertToSet(&A, 7);
    insertToSet(&A, 14);
    insertToSet(&A, 15);
    insertToSet(&A, 190);

    insertToSet(&B, 1);
    insertToSet(&B, 3);
    insertToSet(&B, 5);
    insertToSet(&B, 7);
    insertToSet(&B, 9);
    insertToSet(&B, 10);
    insertToSet(&B, 12);
    insertToSet(&B, 190);

    printSet(Difference(A,B));




    return 0;
}

Set Difference(Set A, Set B) {
    Set toReturn;
    initSet(&toReturn);

    for (int i = 0; i < A.size; i++) {
        if (!isMember(B, A.set[i])) {
            insertToSet(&toReturn, A.set[i]);
        }
    }

    return toReturn;
}

bool isMember(Set S, int data) {
    int i;
    for ( i = 0; i < S.size && S.set[i] != data; i++) {}

    if (i < S.size) {
        return true;
    }

    return false;       
}

Set Intersection(Set A, Set B) {
    Set toReturn;
    initSet(&toReturn);

    for (int i = 0; i < A.size; i++) {
        if (isMember(B, A.set[i])) {
            insertToSet(&toReturn, A.set[i]);
        }
    }

    return toReturn;
}

Set Union(Set A, Set B) {
    Set toReturn;
    initSet(&toReturn);

    for (int i = 0; i < A.size; i++) {
        insertToSet(&toReturn, A.set[i]);
    }

    for (int i = 0; i < B.size; i++) {
        insertToSet(&toReturn, B.set[i]);
    }

    return toReturn;

}

void initSet(Set *S) {
    S->size = 0;
}

void deleteFromSet(Set *S, int data) {
    int i;
    for ( i = 0; i < S->size && S->set[i] != data; i++) {}

    if (i < S->size) {
        S->set[i] = S->set[S->size - 1];
        S->size--;
    }    
}

void insertToSet(Set *S, int data) {
    if (S->size >= MAX) return;
    int i;
    for ( i = 0; i < S->size && S->set[i] != data; i++) {}

    if (i == S->size) {
        S->set[S->size] = data;
        S->size++;
    }
}

void printSet(Set S) {
    for (int i = 0; i < S.size; i++) {
        printf("[%d]: %d\n",i, S.set[i]);
    }
}