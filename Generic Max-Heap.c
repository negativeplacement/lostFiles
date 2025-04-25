#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MaxHeap{
    void **isItem;
    int isSize, isCapacity;
    bool isSized;
}MaxHeap;

int isParent(int isIndex);
int isLeft(int isIndex);
int isRight(int isIndex);
void insertItem(MaxHeap *isMax, void *isItem, int typeSize);
void *removeRoot(MaxHeap *isMax);
void *removeItemAt(MaxHeap *isMax, int isIndex);
void removeItem(MaxHeap *isMax, void *isItem);
void updateItemAt(MaxHeap *isMax, void *isItem, int typeSize, int isIndex);
void isHeapify_I(MaxHeap *isMax, int isIndex);
void isHeapify_R(MaxHeap *isMax, int isIndex);
bool containsItem(MaxHeap *isMax, void *isItem);
int isItemIndex(MaxHeap *isMax, void *isItem);
bool isEmpty(MaxHeap *isMax);
bool isFull(MaxHeap *isMax);
int isSize(MaxHeap *isMax);
void displayMaxHeap(MaxHeap *isMax);
void displayData(void *getData, bool isLast);

int compareData(void *getData, void *parentData);

int main(){
    MaxHeap *isMax = calloc(1, sizeof(MaxHeap));if(isMax == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return 1;}
    isMax->isItem = calloc(10, sizeof(void *)); if(isMax->isItem == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return 1;}
    isMax->isSized = true; isMax->isCapacity = 10; isMax->isSize = 0;
    int a=1, b=2, c=3, d=4, e=5, f=6, g=7, h=8, i=9, j=10;
    insertItem(isMax, &a, sizeof(int));
    insertItem(isMax, &b, sizeof(int));
    insertItem(isMax, &c, sizeof(int));
    insertItem(isMax, &d, sizeof(int));
    insertItem(isMax, &e, sizeof(int));
    insertItem(isMax, &f, sizeof(int));
    insertItem(isMax, &g, sizeof(int));
    insertItem(isMax, &h, sizeof(int));
    insertItem(isMax, &i, sizeof(int));
    //insertItem(isMax, &j);
    displayMaxHeap(isMax);
    //removeRoot(isMax);
    //removeItemAt(isMax, 2);
    removeItem(isMax, &c);
    //updateItemAt(isMax, &j, sizeof(int), 2);
    displayMaxHeap(isMax);
    for(int isIndex = 0; isIndex < isMax->isCapacity; isIndex++){free(isMax->isItem[isIndex]); isMax->isItem[isIndex] = NULL;}
    free(isMax->isItem); isMax->isItem = NULL;
    free(isMax); isMax = NULL;
    return 0;
}

int isParent(int isIndex){return (isIndex - 1)/ 2;}

int isLeft(int isIndex){return (isIndex * 2) + 1;}

int isRight(int isIndex){return (isIndex * 2) + 2;}

void insertItem(MaxHeap *isMax, void *isItem, int typeSize){
    if(isMax->isSized && isMax->isSize >= isMax->isCapacity){fprintf(stdout, "Heap Is Full.\n");return;}
    else if(!isMax->isSized && isMax->isSize == isMax->isCapacity){
        isMax->isCapacity *= 2;
        void **expandItem = realloc(isMax->isItem, sizeof(void *) * (isMax->isCapacity));
        if(expandItem == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
        isMax->isItem = expandItem;
        //memset((isMax->isItem + (isMax->isCapacity - 1)), 0, sizeof(void*));
    }
    isMax->isItem[isMax->isSize] = calloc(1, typeSize); if(isMax->isItem[isMax->isSize] == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    memcpy(isMax->isItem[isMax->isSize], isItem, typeSize);
    int isIndex = isMax->isSize;
    while(compareData(isMax->isItem[isIndex], isMax->isItem[isParent(isIndex)]) == 1){
        void *isTemp = isMax->isItem[isIndex];
        isMax->isItem[isIndex] = isMax->isItem[isParent(isIndex)];
        isMax->isItem[isParent(isIndex)] = isTemp;
        isIndex = isParent(isIndex);
    }
    isMax->isSize++;
    return;
}

void *removeRoot(MaxHeap *isMax){
    if(isMax->isSize == 0){fprintf(stderr, "Heap Is Empty"); return NULL;}
    void *getRoot = calloc(1, sizeof(isMax->isItem[0]));
    if(getRoot = NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return NULL;}
    memcpy(getRoot, isMax->isItem[0], sizeof(isMax->isItem[0]));
    free(isMax->isItem[0]); isMax->isItem[0] = NULL;
    isMax->isItem[0] = calloc(1, sizeof(isMax[isMax->isSize - 1])); if(isMax->isItem[0] == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return NULL;}
    memcpy(isMax->isItem[0], isMax->isItem[isMax->isSize - 1], sizeof(isMax->isItem[isMax->isSize - 1]));
    free(isMax->isItem[isMax->isSize - 1]); isMax->isItem[isMax->isSize - 1] = NULL; isMax->isSize--;
    isHeapify_I(isMax, 0);
    return getRoot;
}

void *removeItemAt(MaxHeap *isMax, int isIndex){
    if(isIndex < 0 || isIndex > isMax->isSize){fprintf(stdout, "Index Out Of Bounds.\n"); return NULL;}
    void *isItem = calloc(1, sizeof(isMax->isItem[isIndex]));
    if(isItem == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return NULL;}
    memcpy(isItem, isMax->isItem[isIndex], sizeof(isMax->isItem[isIndex]));
    int thisIndex = isIndex;
    while(compareData(isMax->isItem[thisIndex], isMax->isItem[isParent(thisIndex)]) == -1){
        void *isTemp = isMax->isItem[thisIndex];
        isMax->isItem[thisIndex] = isMax->isItem[isParent(thisIndex)];
        isMax->isItem[isParent(thisIndex)] = isTemp;
        thisIndex = isParent(thisIndex);
    }
    free(isMax->isItem[0]); isMax->isItem[0] = NULL;
    isMax->isItem[0] = calloc(1, sizeof(isMax[isMax->isSize - 1])); if(isMax->isItem[0] == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return NULL;}
    memcpy(isMax->isItem[0], isMax->isItem[isMax->isSize - 1], sizeof(isMax->isItem[isMax->isSize - 1]));
    free(isMax->isItem[isMax->isSize - 1]); isMax->isItem[isMax->isSize - 1] = NULL; isMax->isSize--;
    isHeapify_I(isMax, 0);
    return isItem;
}

void removeItem(MaxHeap *isMax, void *isItem){
    int isIndex = -1;
    for(int thisData = 0; thisData < isMax->isSize; thisData++){
        if(compareData(isMax->isItem[thisData], isItem) == 0){isIndex = thisData; break;}
    }
    if(isIndex == -1){fprintf(stdout, "Item Doesn't Exist.\n"); return;}
    while(compareData(isMax->isItem[isIndex], isMax->isItem[isParent(isIndex)]) == -1){
        void *isTemp = isMax->isItem[isIndex];
        isMax->isItem[isIndex] = isMax->isItem[isParent(isIndex)];
        isMax->isItem[isParent(isIndex)] = isTemp;
        isIndex = isParent(isIndex);
    }
    free(isMax->isItem[0]); isMax->isItem[0] = NULL;
    isMax->isItem[0] = calloc(1, sizeof(isMax[isMax->isSize - 1])); if(isMax->isItem[0] == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    memcpy(isMax->isItem[0], isMax->isItem[isMax->isSize - 1], sizeof(isMax->isItem[isMax->isSize - 1]));
    free(isMax->isItem[isMax->isSize - 1]); isMax->isItem[isMax->isSize - 1] = NULL; isMax->isSize--;
    isHeapify_I(isMax, 0);
    return;
}

void updateItemAt(MaxHeap *isMax, void *isItem, int typeSize, int isIndex){
    if(isIndex < 0 || isIndex > isMax->isSize){fprintf(stdout, "Index Out Of Bounds"); return;}
    free(isMax->isItem[isIndex]); isMax->isItem[isIndex] = NULL;
    isMax->isItem[isIndex] = calloc(1, typeSize); if(isMax->isItem[isIndex] == NULL){fprintf(stdout, "Memory Allocation Failed"); return;}
    memcpy(isMax->isItem[isIndex], isItem, typeSize);
    int thisIndex = isIndex;
    while(compareData(isMax->isItem[thisIndex], isMax->isItem[isParent(thisIndex)]) == -1){
        void *isTemp = isMax->isItem[thisIndex];
        isMax->isItem[thisIndex] = isMax->isItem[isParent(thisIndex)];
        isMax->isItem[isParent(thisIndex)] = isTemp;
        thisIndex = isParent(thisIndex);
    }
    isHeapify_I(isMax, 0);
    return;
}

void isHeapify_I(MaxHeap *isMax, int isIndex){
    if(isIndex < 0 || isIndex > isMax->isSize){fprintf(stdout, "Index Out Of Bounds"); return;}
    int getIndex = isIndex, isLeftIndex = isLeft(isIndex), isRightIndex = isRight(isIndex);
    while(isLeftIndex < isMax->isSize){
        if(compareData(isMax->isItem[isLeftIndex], isMax->isItem[getIndex]) == 1){getIndex = isLeftIndex;}
        if(isRightIndex < isMax->isSize && compareData(isMax->isItem[isRightIndex], isMax->isItem[getIndex]) == 1){
            getIndex = isRightIndex;
        }
        if(getIndex != isIndex){
            void *isTemp = isMax->isItem[isIndex];
            isMax->isItem[isIndex] = isMax->isItem[getIndex]; isMax->isItem[getIndex] = isTemp;
            isIndex = getIndex; isLeftIndex = isLeft(isIndex); isRightIndex = isRight(isIndex);
        } else{break;}
    }
    return;
}

void isHeapify_R(MaxHeap *isMax, int isIndex){
    if(isIndex < 0 || isIndex > isMax->isSize){fprintf(stdout, "Index Out Of Bounds"); return;}
    int getIndex = isIndex;
    (isLeft(isIndex) < isMax->isSize && compareData(isMax->isItem[isLeft(isIndex)], isMax->isItem[isIndex]) == 1) && (getIndex = isLeft(isIndex));
    (isRight(isIndex) < isMax->isSize && compareData(isMax->isItem[isRight(isIndex)], isMax->isItem[getIndex]) == 1) && (getIndex = isRight(isIndex));
    if(getIndex != isIndex){
        void *isTemp = isMax->isItem[isIndex];
        isMax->isItem[isIndex] = isMax->isItem[getIndex];
        isMax->isItem[getIndex] = isTemp;
        isHeapify_R(isMax, getIndex);
    }
    return;
}

bool containsItem(MaxHeap *isMax, void *isItem){
    for(int thisData = 0; thisData < isMax->isSize; thisData++){
        if(compareData(isMax->isItem[thisData], isItem) == 0){return true;}
    }
    return false;
}

int isItemIndex(MaxHeap *isMax, void *isItem){
    for(int isIndex = 0; isIndex < isMax->isSize; isIndex++){
        if(compareData(isMax->isItem[isIndex], isItem) == 0){return isIndex;}
    }
    return -1;
}

bool isEmpty(MaxHeap *isMax){return isMax->isSize == 0;}

bool isFull(MaxHeap *isMax){return isMax->isSize == isMax->isCapacity;}

int isSize(MaxHeap *isMax){return isMax->isSize;}

void displayMaxHeap(MaxHeap *isMax){
    fprintf(stdout, "Max-Heap Array: ");
    for(int thisData = 0; thisData < isMax->isSize; thisData++){
        (thisData != isMax->isSize - 1) ? displayData(isMax->isItem[thisData], false) : displayData(isMax->isItem[thisData], true);
    }
    return;
}

void displayData(void *getData, bool isLast){
    fprintf(stdout, isLast ? "%d\n" : "%d -> ", *(int *)getData);
    return;
}

int compareData(void *getData, void *parentData){
    int isData = *(int *)getData, pData = *(int *)parentData;
    if(isData < pData){return -1;} else if(isData > pData){return 1;} else{return 0;}
}