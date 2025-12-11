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
	int arr[] = {4, 2, 5, 2, 1};
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

}

void populateTree(Tree *T, int arr[], int size) {

}

void insertTree(Tree *T, int data) {

}

void preOrder(Tree T) {

}

void inOrder(Tree T) {

}

void postOrder(Tree T) {

}

// functions for visualization
void initQueue(Queue *Q) {

}

bool isEmpty(Queue Q) {

}

bool isFull(Queue Q) {

}

void enqueue(Queue *Q, Tree D) {

}

Tree dequeue(Queue *Q) {

}

void visualize(Tree T) {

}