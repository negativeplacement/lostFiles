#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MinHeap{
    void **isItem;
    int isSize, isCapacity;
    bool isSized;
}MinHeap;

int isParent(int isIndex);
int isLeft(int isIndex);
int isRight(int isIndex);
void insertItem(MinHeap *isMin, void *isItem, int typeSize);
void *removeRoot(MinHeap *isMin);
void *removeItemAt(MinHeap *isMin, int isIndex);
void removeItem(MinHeap *isMin, void *isItem);
void updateItemAt(MinHeap *isMin, void *isItem, int typeSize, int isIndex);
void isHeapify_I(MinHeap *isMin, int isIndex);
void isHeapify_R(MinHeap *isMin, int isIndex);
bool containsItem(MinHeap *isMin, void *isItem);
int isItemIndex(MinHeap *isMin, void *isItem);
bool isEmpty(MinHeap *isMin);
bool isFull(MinHeap *isMin);
int isSize(MinHeap *isMin);
void displayMinHeap(MinHeap *isMin);
void displayData(void *isItem, bool isLast);

int compareData(void *getData, void *parentData);

int main(){
    MinHeap *isMin = calloc(1, sizeof(MinHeap)); if(isMin == NULL){fprintf(stdout, "Memory Allocation Failed"); return 1;}
    isMin->isItem = calloc(10, sizeof(void *)); if(isMin->isItem == NULL){fprintf(stdout, "Memory Allocation Failed"); return 1;}
    isMin->isSized = true; isMin->isCapacity = 10; isMin->isSize = 0;
    int a=9, b=8, c=7, d=6, e=5, f=4, g=3, h=2, i=1, j=0;
    insertItem(isMin, &a, sizeof(int));
    insertItem(isMin, &b, sizeof(int));
    insertItem(isMin, &c, sizeof(int));
    insertItem(isMin, &d, sizeof(int));
    insertItem(isMin, &e, sizeof(int));
    insertItem(isMin, &f, sizeof(int));
    insertItem(isMin, &g, sizeof(int));
    insertItem(isMin, &h, sizeof(int));
    insertItem(isMin, &i, sizeof(int));
    //insert(isMin, &j, sizeof(int));
    displayMinHeap(isMin);
    //removeItemAt(isMin, 4);
    removeItem(isMin, &c);
    displayMinHeap(isMin);
    /*
    void *isRoot;
    for(int i = 0; i < 6; i++){
    isRoot = removeRoot(isMin);
    printf("Removed : %d\n", *(int *)isRoot);
    }
    //removeIndex(isMin, 2);
    //removeData(isMin, &f);
    //updateValueAtIndex(isMin, &j, sizeof(int), 2);
    displayMinHeap(isMin);*/
    for(int isIndex = 0; isIndex < isMin->isCapacity; isIndex++){free(isMin->isItem[isIndex]); isMin->isItem[isIndex] = NULL;}
    free(isMin->isItem); isMin->isItem = NULL;
    free(isMin); isMin = NULL;
    return 0;
}

int isParent(int isIndex){return (isIndex - 1)/ 2;}

int isLeft(int isIndex){return (isIndex * 2) + 1;}

int isRight(int isIndex){return (isIndex * 2) + 2;}

void insertItem(MinHeap *isMin, void *isItem, int typeSize){
    if(isMin->isSized && isMin->isSize == isMin->isCapacity){fprintf(stdout, "Heap Is Full.\n"); return;}
    else if(!isMin->isSized && isMin->isSize == isMin->isCapacity){
        isMin->isCapacity *= 2;
        void **expandItem = realloc(isMin->isItem, sizeof(void *) * (isMin->isCapacity));
        if(expandItem == NULL){fprintf(stdout, "Memory Allocation Failed"); return;}
        isMin->isItem = expandItem;
        //memset((isMin->isItem + (isMin->isCapacity - 1)), 0, sizeof(void*));
    }
    isMin->isItem[isMin->isSize] = calloc(1, typeSize); if(isMin->isItem[isMin->isSize] == NULL){fprintf(stderr, "Memory Allocation Failed"); return;}
    memcpy(isMin->isItem[isMin->isSize], isItem, typeSize);
    int isIndex = isMin->isSize;
    while(compareData(isMin->isItem[isIndex], isMin->isItem[isParent(isIndex)]) == -1){
        void *isTemp = isMin->isItem[isIndex];
        isMin->isItem[isIndex] = isMin->isItem[isParent(isIndex)];
        isMin->isItem[isParent(isIndex)] = isTemp;
        isIndex = isParent(isIndex);
    }
    isMin->isSize++;
    return;
}

void *removeRoot(MinHeap *isMin){
    if(isMin->isSize == 0){fprintf(stdout, "Heap Is Empty"); return NULL;}
    void *getRoot = calloc(1, sizeof(isMin->isItem[0])); if(getRoot == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return NULL;}
    memcpy(getRoot, isMin->isItem[0], sizeof(isMin->isItem[0]));
    free(isMin->isItem[0]); isMin->isItem[0] = NULL;
    isMin->isItem[0] = calloc(1, sizeof(isMin->isItem[isMin->isSize - 1])); if(isMin->isItem[0] == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return NULL;}
    memcpy(isMin->isItem[0], isMin->isItem[isMin->isSize - 1], sizeof(isMin->isItem[isMin->isSize - 1]));
    free(isMin->isItem[isMin->isSize - 1]); isMin->isItem[isMin->isSize - 1] = NULL; isMin->isSize--;
    isHeapify_I(isMin, 0);
    return getRoot;
}

void *removeItemAt(MinHeap *isMin, int isIndex){
    if(isIndex < 0 || isIndex > isMin->isSize){fprintf(stdout, "Index Out Of Bounds"); return NULL;}
    if(isMin->isSize == 0){fprintf(stdout, "Heap Is Empty"); return NULL;}
    void *isItem = calloc(1, sizeof(isMin->isItem[isIndex])); if(isItem == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return NULL;}
    memcpy(isItem, isMin->isItem[isIndex], sizeof(isMin->isItem[isIndex]));
    int thisIndex = isIndex;
    while(compareData(isMin->isItem[thisIndex], isMin->isItem[isParent(thisIndex)]) == 1){
        void *isTemp = isMin->isItem[thisIndex];
        isMin->isItem[thisIndex] = isMin->isItem[isParent(thisIndex)];
        isMin->isItem[isParent(thisIndex)] = isTemp;
        thisIndex = isParent(thisIndex);
    }
    free(isMin->isItem[0]); isMin->isItem[0] = NULL;
    isMin->isItem[0] = calloc(1, sizeof(isMin[isMin->isSize - 1])); if(isMin->isItem[0] == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return NULL;}
    memcpy(isMin->isItem[0], isMin->isItem[isMin->isSize - 1], sizeof(isMin->isItem[isMin->isSize - 1]));
    free(isMin->isItem[isMin->isSize - 1]); isMin->isItem[isMin->isSize - 1] = NULL; isMin->isSize--;
    isHeapify_I(isMin, 0);
    return isItem;
}

void removeItem(MinHeap *isMin, void *isItem){
    int isIndex = -1;
    for(int thisData = 0; thisData < isMin->isSize; thisData++){
        if(compareData(isMin->isItem[thisData], isItem) == 0){isIndex = thisData; break;}
    }
    if(isIndex == -1){fprintf(stderr, "Heap doesn't contain item"); return;}
    while(compareData(isMin->isItem[isIndex], isMin->isItem[isParent(isIndex)]) == 1){
        void *isTemp = isMin->isItem[isIndex];
        isMin->isItem[isIndex] = isMin->isItem[isParent(isIndex)];
        isMin->isItem[isParent(isIndex)] = isTemp;
        isIndex = isParent(isIndex);
    }
    free(isMin->isItem[0]); isMin->isItem[0] = NULL;
    isMin->isItem[0] = calloc(1, sizeof(isMin[isMin->isSize - 1]));
    memcpy(isMin->isItem[0], isMin->isItem[isMin->isSize - 1], sizeof(isMin->isItem[isMin->isSize - 1]));
    free(isMin->isItem[isMin->isSize - 1]); isMin->isItem[isMin->isSize - 1] = NULL; isMin->isSize--;
    isHeapify_I(isMin, 0);
    return;
}

void updateItemAt(MinHeap *isMin, void *isItem, int typeSize, int isIndex){
    if(isIndex < 0 || isIndex > isMin->isSize){fprintf(stdout, "Index Out Of Bounds"); return;}
    free(isMin->isItem[isIndex]); isMin->isItem[isIndex] = NULL;
    isMin->isItem[isIndex] = calloc(1, typeSize); if(isMin->isItem[isIndex] == NULL){fprintf(stdout, "Memory Allocation Failed"); return;}
    memcpy(isMin->isItem[isIndex], isItem, typeSize);
    int thisIndex = isIndex;
    while(compareData(isMin->isItem[thisIndex], isMin->isItem[isParent(thisIndex)]) == 1){
        void *isTemp = isMin->isItem[thisIndex];
        isMin->isItem[thisIndex] = isMin->isItem[isParent(thisIndex)];
        isMin->isItem[isParent(thisIndex)] = isTemp;
        thisIndex = isParent(thisIndex);
    }
    isHeapify_I(isMin, 0);
    return;
}

void isHeapify_I(MinHeap *isMin, int isIndex){
    if(isIndex < 0 || isIndex > isMin->isSize){fprintf(stdout, "Index Out Of Bounds.\n"); return;}
    int getIndex = isIndex, isLeftIndex = isLeft(isIndex), isRightIndex = isRight(isIndex);
    while(isLeftIndex < isMin->isSize){
        if(compareData(isMin->isItem[isLeftIndex], isMin->isItem[getIndex]) == -1){getIndex = isLeftIndex;}
        if(isRightIndex < isMin->isSize && compareData(isMin->isItem[isRightIndex], isMin->isItem[getIndex]) == -1){
            getIndex = isRightIndex;
        }
        if(getIndex != isIndex){
            void *isTemp = isMin->isItem[isIndex];
            isMin->isItem[isIndex] = isMin->isItem[getIndex]; isMin->isItem[getIndex] = isTemp;
            isIndex = getIndex; isLeftIndex = isLeft(isIndex); isRightIndex = isRight(isIndex);
        } else{break;}
    }
    return;
}

void isHeapify_R(MinHeap *isMin, int isIndex){
    if(isIndex < 0 || isIndex > isMin->isSize){fprintf(stdout, "Index Out Of Bounds.\n"); return;}
    int getIndex = isIndex;
    (isLeft(isIndex) < isMin->isSize && compareData(isMin->isItem[isLeft(isIndex)], isMin->isItem[isIndex]) == -1) && (getIndex = isLeft(isIndex));
    (isRight(isIndex) < isMin->isSize && compareData(isMin->isItem[isRight(isIndex)], isMin->isItem[getIndex]) == -1) && (getIndex = isRight(isIndex));
    if(getIndex != isIndex){
        void *isTemp = isMin->isItem[isIndex];
        isMin->isItem[isIndex] = isMin->isItem[getIndex];
        isMin->isItem[getIndex] = isTemp;
        isHeapify_R(isMin, getIndex);
    }
    return;
}

bool containsItem(MinHeap *isMin, void *isItem){
    for(int thisData = 0; thisData < isMin->isSize; thisData++){
        if(compareData(isMin->isItem[thisData], isItem) == 0){return true;}
    }
    return false;
}

int isItemIndex(MinHeap *isMin, void *isItem){
    for(int isIndex = 0; isIndex < isMin->isSize; isIndex++){
        if(compareData(isMin->isItem[isIndex], isItem) == 0){return isIndex;}
    }
    return -1;
}

bool isEmpty(MinHeap *isMin){return isMin->isSize == 0;}

bool isFull(MinHeap *isMin){return isMin->isSize == isMin->isCapacity;}

int isSize(MinHeap *isMin){return isMin->isSize;}

void displayMinHeap(MinHeap *isMin){
    fprintf(stdout, "Min-Heap Array: ");
    for(int thisData = 0; thisData < isMin->isSize; thisData++){
        (thisData != isMin->isSize - 1) ? displayData(isMin->isItem[thisData], false) : displayData(isMin->isItem[thisData], true);
    }
    return;
}

void displayData(void *isItem, bool isLast){
    fprintf(stdout, isLast ? "%d\n" : "%d -> ", *(int *)isItem);
    return;
}

int compareData(void *getData, void *parentData){
    int isData = *(int *)getData, pData = *(int *)parentData;
    if(isData < pData){return -1;} else if(isData > pData){return 1;} else{return 0;}
}