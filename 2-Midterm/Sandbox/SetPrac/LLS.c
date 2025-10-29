#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node *next;
} *Set;

void populateSet(Set *S);
void insert(Set *S, int data);
void delete(Set *S, int data);
bool isMember(Set S, int data);
void printSet(Set S);
Set Union(Set A, Set B);
Set Intersection(Set A, Set B);
Set Difference(Set A, Set B);

int main() {
    Set A = NULL;
    Set B = NULL;

    insert(&A, 1);
    insert(&A, 2);
    insert(&A, 3);
    insert(&A, 4);

    insert(&B, 1);
    insert(&B, 6);
    insert(&B, 7);
    insert(&B, 8);

    printSet(Difference(A,B));

}

void printSet(Set S) {
    Set trav = S;
    int indx = 0;
    for ( ; trav != NULL ; trav = trav->next) {
        printf("[%d]: %d\n", indx, trav->data);
        indx++;
    }
}

Set Difference(Set A, Set B) {
    Set toReturn = NULL;

    Set trav;

    for (trav = A; trav != NULL; trav = trav->next) {
        if (!isMember(B, trav->data)) {
            insert(&toReturn, trav->data);
        }
    }

    return toReturn;    
}

bool isMember(Set S, int data) {
    Set trav;

    for (trav = S; trav != NULL && trav->data != data; trav = trav->next) {}
    
    if (trav != NULL) {
        return true;
    }
    return false;
}

Set Intersection(Set A, Set B) {
    Set toReturn = NULL;

    Set trav;

    for (trav = A; trav != NULL; trav = trav->next) {
        if (isMember(B, trav->data)) {
            insert(&toReturn, trav->data);
        }
    }

    return toReturn;    
}

Set Union(Set A, Set B) {
    Set toReturn = NULL;

    Set trav;

    for (trav = A; trav != NULL; trav = trav->next) {
        insert(&toReturn, trav->data);
    }

    for (trav = B; trav != NULL; trav = trav->next) {
        insert(&toReturn, trav->data);
    }

    return toReturn;
}

void delete(Set *S, int data) {

    Set *trav;

    for ( trav = S ; (*trav) != NULL && (*trav)->data != data ; trav = &(*trav)->next ) {}

    if ((*trav) != NULL) {
        Set temp = *trav;
        (*trav) = temp->next;
    }
}

void insert(Set *S, int data) {
    Set newNode = (Set)malloc(sizeof(struct node));
    newNode->data = data;
    Set *trav;
    for ( trav = S ; (*trav) != NULL && (*trav)->data < data ; trav = &(*trav)->next ) {}

    if ((*trav) == NULL || (*trav)->data != data) {
        newNode->next = *trav;
        (*trav) = newNode;
    } else {
        free(newNode);
    }
}
