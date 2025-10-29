#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUMPROGRAMS 4
#define YEARLEVELS 4
#define MAXSTUDS 100

typedef struct{
    char fName[64];
    char mi;
    char lName[32];
}studName;

typedef unsigned char personalInfo;

typedef struct{
    char idNum[9];
    studName name;
    personalInfo info;
}student;

typedef struct{
    student studs[MAXSTUDS];
    int numStuds;
}arrListStud;

typedef struct studNode{
    student stud;
    struct studNode* next;
}studNode, *studLL;

typedef studLL studDict[YEARLEVELS];

typedef struct{
    studDict programStuds;
    int studCtr;    
}dcismNode;

typedef dcismNode dcismDict[NUMPROGRAMS];

typedef struct{
    char studID[9];
    studName sName;
}studRec;

typedef struct{
    studRec studs[MAXSTUDS];
    int count;
}sNode, *studSet; 

void insertStudRec(studSet *Set, studRec rec);
studSet *initSet(void);

int main() {
    studSet *S = initSet();
    printf("count %d", S[1]->count);

    return 0;
}

studSet *initSet(void){ // create a pointer array
    studSet *toReturn = (studSet *)malloc(sizeof(studSet) * NUMPROGRAMS);
    if (toReturn == NULL) return NULL;

    for (int i = 0; i < NUMPROGRAMS; i++) {
        toReturn[i] = (studSet)malloc(sizeof(sNode));
        toReturn[i]->count = 0;
    }

    return toReturn;
 }

void insertStudRec(studSet *Set, studRec rec) {

}