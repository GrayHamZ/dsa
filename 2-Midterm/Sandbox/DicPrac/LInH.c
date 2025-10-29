/*
    I PREFER THIS CODE
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 0X5

typedef int Dictionary[MAX];

typedef enum {
    EMPTY = -1,
    DELETED = -2
} Status;

void initDict(Dictionary D);
int hash(int data);
void insert(Dictionary D, int data);
void delete(Dictionary D, int data);
bool isMember(Dictionary D, int data);
void printDict(Dictionary D);

int main() {
    Dictionary D;
    initDict(D);

    insert(D, 1);
    insert(D, 11);
    insert(D, 21);
    insert(D, 21);
    insert(D, 44);

    delete(D, 21);
    delete(D, 11);
    insert(D, 11);
    printDict(D);

    return 0;
}

void delete(Dictionary D, int data) {
    int i;
    int hashIdx = hash(data);
    int stop = (MAX + hashIdx - 1) % MAX;

    for (i = hashIdx; i != stop && D[i] != EMPTY && D[i] != data; i = (i + 1) % MAX) {}

    if (D[i] == data) {
        D[i] = DELETED;
    }    
}

void insert(Dictionary D, int data) {
    int i;
    int firstDelete = -1;
    int hashIdx = hash(data);
    int stop = (MAX + hashIdx - 1) % MAX;

    for (i = hashIdx; i != stop && D[i] != EMPTY && D[i] != data; i = (i + 1) % MAX) {
        if (firstDelete == -1 && D[i] == DELETED) {
            firstDelete = i;
        }
    }

    if (D[i] == EMPTY || (firstDelete != -1 && D[i] != data)) {
        if (firstDelete == -1) {
            D[i] = data;
        } else {
            D[firstDelete] = data;
        }
    }
}

void printDict(Dictionary D) {
    for (int i = 0; i < MAX; i++) {
        printf("[%d]: %d\n", i, D[i]);
    }
}

int hash(int data) {
    return data % MAX;
}

void initDict(Dictionary D) {
    for (int i = 0; i < MAX; i++) {
        D[i] = EMPTY;
    }
}