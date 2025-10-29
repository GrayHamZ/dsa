#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10

typedef struct {
    int set[MAX];
    int size;
} Set;

void initSet(Set *S);
void insertToSet(Set *S, int data);
void deleteFromSet(Set *S, int data);
bool isMember(Set S, int data);
void populateSet(Set *S);
void printSet(Set S);
Set Union(Set A, Set B);
Set Intersection(Set A, Set B);
Set Difference(Set A, Set B);

int main() {
    Set A;
    Set B;

    initSet(&A);
    initSet(&B);

    insertToSet(&A, 1);
    insertToSet(&A, 2);
    insertToSet(&A, 4);
    insertToSet(&A, 6);
    insertToSet(&A, 7);

    insertToSet(&B, 10);
    insertToSet(&B, 2);
    insertToSet(&B, 9);
    insertToSet(&B, 6);
    insertToSet(&B, 8);

    deleteFromSet(&A, 4);

    // if (isMember(A,2)) {
    //     printf("IS MEMBER\n");
    // }

    printSet(Difference(A,B));
}

bool isMember(Set S, int data) {
    int i;
    for (i = 0; i < S.size && S.set[i] != data; i++) {}
    if (S.set[i] == data) {
        return true;
    }    
    return false;
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

void deleteFromSet(Set *S, int data) {
    int i;
    for (i = 0; i < S->size && S->set[i] != data; i++) {}
    if (S->set[i] == data) {
        --S->size;
        S->set[i] = S->set[S->size];
    }
}

void insertToSet(Set *S, int data) {
    if ((*S).size >= MAX) return;
    int i;
    
    for (i = 0; i < S->size && S->set[i] != data; i++) {}

    if (S->set[i] != data) {
        S->set[S->size] = data;
        S->size++;
    }
}

void printSet(Set S){
    for (int i = 0; i < S.size; i++) {
        printf("[%d]: %d\n",i , S.set[i]);
    }
}

void initSet(Set *S) {
    (*S).size = 0;
}