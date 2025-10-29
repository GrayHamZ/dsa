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
void printSet(Set S);
bool isMember(Set S, int data);
Set Union(Set A, Set B);
Set Intersection(Set A, Set B);
Set Difference(Set A, Set B);

int main() {

    Set A = NULL;
    insert(&A, 1);
    insert(&A, 3);
    insert(&A, 2);
    Set B = NULL;
    insert(&B, 1);
    insert(&B, 2);
    insert(&B, 4);
    insert(&B, 5);
    insert(&B, 7);

    Set D = Difference(A,B);

    printSet(A);

    return 0;
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

bool isMember(Set S, int data) {
    Set trav;
    for (trav = S; trav != NULL && trav->data != data; trav = trav->next) {}
    // possible outputs: Trav == NULL trav->data == data    
    if (trav != NULL) {
        return true;
    }
    return false;
}

void delete(Set *S, int data) {
    Set *trav;
    for (trav = S; (*trav) != NULL && (*trav)->data != data; trav = &(*trav)->next) {}
    // possible outputs: (*Trav) == NULL (*trav)->data == data
    if ((*trav) != NULL) {
        Set temp = (*trav);
        (*trav) = temp->next;
        free(temp);
    }
}

void insert(Set *S, int data) {
    Set newNode = (Set)malloc(sizeof(struct node));
    newNode->data = data;
    Set *trav;

    for (trav = S; (*trav) != NULL && (*trav)->data != data && (*trav)->data < data; trav = &(*trav)->next) {}
    // possible outputs: (*Trav) == NULL (*trav)->data == data

    // IF YOU WANT SORTED PLEASE CHECK IF TRAC IS NULL FIRST!!!!!
    if ((*trav) == NULL || (*trav)->data != data) {
        newNode->next = (*trav);
        (*trav) = newNode;
    } else {
        free(newNode);
    }
}

void printSet(Set S) {
    int indx = 0;
    Set trav;
    for (trav = S; trav != NULL; trav = trav->next) {
        printf("[%d]: %d\n", indx++, trav->data);
    }
}
