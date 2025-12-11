#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10

typedef struct node {
	int data;
	struct node *left;
	struct node *right;
} *Tree;

typedef struct {
	Tree nodes[MAX];
	int front;
	int rear;
} Queue;

void initTree(Tree *T);
void populateTree(Tree *T, int arr[], int size);
void insertTree(Tree *T, int data); // utilizes BST insertion but not unique
void preOrder(Tree T);
void inOrder(Tree T);
void postOrder(Tree T);
Tree dequeue(Queue *Q);

// for visualizing using BFS
void initQueue(Queue *Q);
bool isEmpty(Queue Q);
bool isFull(Queue Q);
void enqueue(Queue *Q, Tree D); // returns tree
Tree dequeue(Queue *Q);
void visualize(Tree T);

int main()
{
	Tree T;
	int arr[] = {4, 2, 5, 2, 1, 3};
	int size = sizeof(arr) / sizeof(arr[0]);

	initTree(&T);
	populateTree(&T, arr, size);

	printf("Pre-order: ");
	preOrder(T);

	printf("\nIn-order: ");
	inOrder(T);

	printf("\nPost-order: ");
	postOrder(T);

	printf("\n\nVisualization:");
	visualize(T);
	return 0;
}

void initTree(Tree *T) {
    *T = NULL;
}

void populateTree(Tree *T, int arr[], int size) {
    for (int i = 0; i < size; i++) {
        insertTree(T, arr[i]);
    }
}

void insertTree(Tree *T, int data) {
    Tree *trav;
    Tree toInsert = (Tree)malloc(sizeof(struct node));
    for (trav = T; *trav != NULL && (*trav)->data != data; trav = data > (*trav)->data ? &(*trav)->right : &(*trav)->left) {}

    if (*trav == NULL) {
        toInsert->data = data;
        toInsert->left = NULL;
        toInsert->right = NULL;

        *trav = toInsert;
    } else {
        free(toInsert);
    }
}

void preOrder(Tree T) {
    if (T != NULL) {
        printf("%d ", T->data);
        preOrder(T->left);
        preOrder(T->right);
    }
}

void inOrder(Tree T) {

}

void postOrder(Tree T) {

}

// functions for visualization
void initQueue(Queue *Q) {
    Q->front = 1;
    Q->rear = 0;
}

bool isEmpty(Queue Q) {
    return (Q.rear + 1) % MAX == Q.front ? true : false;
}

bool isFull(Queue Q) {
    return (Q.rear + 2) % MAX == Q.front ? true : false;
}

void enqueue(Queue *Q, Tree D) {
    if (!isFull(*Q)) {
        Q->rear = (Q->rear + 1) % MAX;
        Q->nodes[Q->rear] = D;
    }
}

Tree dequeue(Queue *Q) {
    if (!isEmpty(*Q)) {
        Tree toReturn = Q->nodes[Q->front];
        Q->front = (Q->front + 1) % MAX;
        return toReturn;
    } else {
        return NULL;
    }
}

void visualize(Tree T) {
    printf("\n");
    Queue Q;
    initQueue(&Q);
    enqueue(&Q, T);
    int level = 0;
    while (!isEmpty(Q)) {
        printf("Level %d: ", ++level);

        int stopper = (Q.rear + 1) % MAX;

        while (stopper != Q.front) {
            Tree val = dequeue(&Q);
            if (val != NULL) {
                printf("%d ", val->data);

                if (val->left != NULL) {
                    enqueue(&Q, val->left);
                }

                if (val->right != NULL) {
                    enqueue(&Q, val->right);
                }
            }
        }
        printf("\n");
    }
}