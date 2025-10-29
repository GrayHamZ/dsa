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
    delete(D, 1);
    insert(D, 21);
    isMember(D, 11) ? printf("11 is member\n") : printf("11 is not member\n");

    printDict(D);
    return 0;
}

void initDict(Dictionary D) {
    for (int i = 0; i < MAX; i++) {
        D[i] = EMPTY;
    }
}

int hash(int data) {
    return data % MAX;
}

bool isMember(Dictionary D, int data) {
    int i;
    int temp = hash(data);
    int stop  = (temp - 1 + MAX) % MAX;

    for (i = temp; i != stop && D[i] != EMPTY && D[i] != data; i++) {}

    if (D[i] == data) {
        return true;
    } else {
        return false;
    }
}

void delete(Dictionary D, int data) {
    int i;
    int temp = hash(data);
    int stop = (temp + MAX - 1) % MAX;

    for (i = temp; i != stop && D[i] != EMPTY && D[i] != data; i++) {}

    if (D[i] == data) {
        D[i] = DELETED;
    }
}

void insert(Dictionary D, int data) {
    int i;
    int temp = hash(data); 
    int firstDelete = -1; // FLAG if its not -1 then the first deleted was found
    int stop = (temp + MAX - 1) % MAX; // this should be the Index right behind the index of temp

    // printf("temp: %d , stop: %d\n", temp, stop);

    // IMPORTANT LOOP: to traverse collisions (Reusable)
    for (i = temp; i != stop && D[i] != EMPTY && D[i] != data; i = (i + 1) % MAX) {

        if (firstDelete == -1 && D[i] == DELETED) {
            // Found the first delete available
            firstDelete = i;
        }
    }

    //Note: if firstDelete is still -1 that means that there were no previously deleted data

    if(D[i] == EMPTY || (D[i] != data && firstDelete != -1)) { // Condition to insert only in EMPTY or DELETED
        // "(D[i] != data && firstDelete != -1)" means current data is not equal to data to insert and firstDelete exists

        if (firstDelete == -1) {
            // if no delete was found then just insert into it which should be empty
            D[i] = data;
        } else {
            // insert in the index of the first DELETED FOUND
            D[firstDelete] = data;
        }
    }
}

void printDict(Dictionary D) {
    for (int i = 0; i < MAX; i++) {
        printf("[%d]:%d\n",i,D[i]);
    }
}