#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Item{
  int isPriority, isIndex;
}Item;

typedef struct Priority_Queue{ // Alternative design
    void **isItem;
    Item *isItemProperty;
    int isSize, isCapacity;
    bool isSized;
}Priority_Queue;

typedef struct PriorityQueue{ // Initial Design
    void **isItem;
    int isSize, isCapacity, *isPriority;
    bool isSized;
}PriorityQueue;

int isParent(int isIndex);
int isLeft(int isIndex);
int isRight(int isIndex);
void insertItem_MinHeap(PriorityQueue *isQueue, void *isItem, int isPriority, int typeSize);
void insertItem_MaxHeap(PriorityQueue *isQueue, void *isItem, int isPriority, int typeSize);
void *removeRoot_MinHeap(PriorityQueue *isQueue);
void *removeRoot_MaxHeap(PriorityQueue *isQueue);
void isHeapify_MinHeap(PriorityQueue *isQueue, int isIndex);
void isHeapify_MaxHeap(PriorityQueue *isQueue, int isIndex);
void updateItemPriority_MinHeap(PriorityQueue *isQueue, void *isItem, int isPriority);
void updateItemPriority_MaxHeap(PriorityQueue *isQueue, void *isItem, int isPriority);
void destroyQueue(PriorityQueue *isQueue);
bool containsItem(PriorityQueue *isQueue, void *isItem);
int isPriorityItem(PriorityQueue *isQueue, void *isItem);
int isPriorityIndex(PriorityQueue *isQueue, int isIndex);
bool isEmpty(PriorityQueue *isQueue);
bool isFull(PriorityQueue *isQueue);
int isSize(PriorityQueue *isQueue);
void displayPriorityQueue(PriorityQueue *isQueue);

void _insertItem_MinHeap(Priority_Queue *isQueue, void *isItem, int isPriority, int typeSize);
void _insertItem_MaxHeap(Priority_Queue *isQueue, void *isItem, int isPriority, int typeSize);
void *_removeRoot_MinHeap(Priority_Queue *isQueue);
void *_removeRoot_MaxHeap(Priority_Queue *isQueue);
void _isHeapify_MinHeap(Priority_Queue *isQueue, int isIndex);
void _isHeapify_MaxHeap(Priority_Queue *isQueue, int isIndex);
void _updateItemPriority_MinHeap(Priority_Queue *isQueue, void *isitem, int isPriority);
void _updateItemPriority_MaxHeap(Priority_Queue *isQueue, void *isitem, int isPriority);
void _destroyQueue(Priority_Queue *isQueue);
bool _containsItem(Priority_Queue *isQueue, void *isitem);
int _isPriorityItem(Priority_Queue *isQueue, void *isitem);
int _isPriorityIndex(Priority_Queue *isQueue, int isIndex);
bool _isEmpty(Priority_Queue *isQueue);
bool _isFull(Priority_Queue *isQueue);
int _isSize(Priority_Queue *isQueue);
void _displayPriorityQueue(Priority_Queue *isQueue);

void displayData(void *getData, bool isLast);
int compareData(void *getData, void *parentData);

int main(int argc, char *argv[]){
    /*PriorityQueue *isQueue = calloc(1, sizeof(PriorityQueue)); if(isQueue == NULL){fprintf(stdout, "Memory Allocation Error.\n"); return 1;}
    isQueue->isItem = calloc(10, sizeof(void *)); if(isQueue->isItem == NULL){fprintf(stdout, "Memory Allocation Error.\n"); return 1;}
    isQueue->isPriority = calloc(10, sizeof(int)); if(isQueue->isPriority == NULL){fprintf(stdout, "Memory Allocation Error"); return 1;}
    isQueue->isSized = true; isQueue->isCapacity = 10; isQueue->isSize = 0;*/

    Priority_Queue *isQueue = calloc(1, sizeof(Priority_Queue)); if(isQueue == NULL){fprintf(stdout, "Memory Allocation Error"); return 1;}
    isQueue->isItem = calloc(10, sizeof(void *)); if(isQueue->isItem == NULL){fprintf(stdout, "Memory Allocation Error.\n"); return 1;}
    isQueue->isItemProperty = calloc(10, sizeof(Item)); if(isQueue->isItemProperty == NULL){fprintf(stdout, "Memory Allocation Error.\n"); return 1;}
    isQueue->isSized = true; isQueue->isCapacity = 10; isQueue->isSize = 0;//

    int a=5, b=13, c=11, d=7, e=4, f=3, g=1, h=6, i=8, j=2;
    /*insertItem_MinHeap(isQueue, &a, 3, sizeof(int));
    insertItem_MinHeap(isQueue, &b, 4, sizeof(int));
    insertItem_MinHeap(isQueue, &c, 2, sizeof(int));
    insertItem_MinHeap(isQueue, &d, 8, sizeof(int));
    insertItem_MinHeap(isQueue, &e, 7, sizeof(int));
    insertItem_MinHeap(isQueue, &f, 5, sizeof(int));
    insertItem_MinHeap(isQueue, &g, 0, sizeof(int));
    insertItem_MinHeap(isQueue, &h, 9, sizeof(int));
    insertItem_MinHeap(isQueue, &i, 6, sizeof(int));
    displayPriorityQueue(isQueue);
    updateItemPriority_MinHeap(isQueue, &h, 1);
    displayPriorityQueue(isQueue);
    insertItem_MinHeap(isQueue, &j, 11, sizeof(int));
    for(int i = 0; i < isQueue->isCapacity; i++){
        void *getRoot = removeRoot_MinHeap(isQueue);  
        printf("Removed : %d\n", *(int *)getRoot);
    }
    destroyQueue(isQueue);*/
    
    _insertItem_MinHeap(isQueue, &a, 3, sizeof(int));
    _insertItem_MinHeap(isQueue, &b, 4, sizeof(int));
    _insertItem_MinHeap(isQueue, &c, 2, sizeof(int));
    _insertItem_MinHeap(isQueue, &d, 8, sizeof(int));
    _insertItem_MinHeap(isQueue, &e, 7, sizeof(int));
    _insertItem_MinHeap(isQueue, &f, 5, sizeof(int));
    _insertItem_MinHeap(isQueue, &g, 0, sizeof(int));
    _insertItem_MinHeap(isQueue, &h, 9, sizeof(int));
    _insertItem_MinHeap(isQueue, &i, 6, sizeof(int));
    _displayPriorityQueue(isQueue);
    _updateItemPriority_MinHeap(isQueue, &h, 1);
    _displayPriorityQueue(isQueue);
    _insertItem_MinHeap(isQueue, &j, 11, sizeof(int));
    for(int i = 0; i < isQueue->isCapacity; i++){
      void *getRoot = _removeRoot_MinHeap(isQueue);
      printf("Removed : %d\n", *(int *)getRoot);
    }
    _destroyQueue(isQueue);

    return 0;
}

int isParent(int isIndex){return (isIndex - 1)/ 2;}

int isLeft(int isIndex){return (isIndex * 2) + 1;}

int isRight(int isIndex){return (isIndex * 2) + 2;}

void insertItem_MinHeap(PriorityQueue *isQueue, void *isItem, int isPriority, int typeSize){
    if(isQueue->isSized && isQueue->isSize == isQueue->isCapacity){
        fprintf(stdout, "Full Queue.\n"); return;
    } else if(!isQueue->isSized && isQueue->isSize == isQueue->isCapacity){
        isQueue->isCapacity *= 2;
        void **expandItem = realloc(isQueue->isItem, sizeof(void*) * (isQueue->isCapacity)); if(expandItem == NULL){fprintf(stdout, "Memory Allocation Failed"); return;}
        isQueue->isItem = expandItem;
        //memset((isQueue->isItem + (isQueue->isCapacity - 1)), 0, sizeof(void*));
        int *expandPriority = realloc(isQueue->isPriority, sizeof(int) * (isQueue->isCapacity)); if(expandPriority == NULL){fprintf(stdout, "Memory Allocation Failed"); return;}
        isQueue->isPriority = expandPriority;
        //memset((isQueue->isPriority + (isQueue->isCapacity - 1)), 0, sizeof(int));
    }
    isQueue->isItem[isQueue->isSize] = calloc(1, typeSize); if(isQueue->isItem[isQueue->isSize] == NULL){fprintf(stdout, "Memory Allocation Failed"); return;}
    memcpy(isQueue->isItem[isQueue->isSize], isItem, typeSize);
    isQueue->isPriority[isQueue->isSize] = isPriority;
    int isIndex = isQueue->isSize;
    while(isQueue->isPriority[isIndex] < isQueue->isPriority[isParent(isIndex)]){
        int thisPriority = isQueue->isPriority[isIndex];
        void *isTemp = isQueue->isItem[isIndex];
        isQueue->isPriority[isIndex] = isQueue->isPriority[isParent(isIndex)];
        isQueue->isItem[isIndex] = isQueue->isItem[isParent(isIndex)];
        isQueue->isPriority[isParent(isIndex)] = thisPriority;
        isQueue->isItem[isParent(isIndex)] = isTemp;
        isIndex = isParent(isIndex);
    }
    isQueue->isSize++;
    return;
}

void insertItem_MaxHeap(PriorityQueue *isQueue, void *isItem, int isPriority, int typeSize){
    if(isQueue->isSized && isQueue->isSize == isQueue->isCapacity){
        fprintf(stdout, "Full Queue.\n"); return;
    } else if(!isQueue->isSized && isQueue->isSize == isQueue->isCapacity){
        isQueue->isCapacity *= 2;
        void **expandItem = realloc(isQueue->isItem, sizeof(void *) * (isQueue->isCapacity)); if(expandItem == NULL){fprintf(stdout, "Memory Allocation Failed"); return;}
        isQueue->isItem = expandItem;
        //memset((isQueue->isData + (isQueue->isCapacity - 1)), 0, sizeof(void *));
        int *expandPriority = realloc(isQueue->isPriority, sizeof(int) * (isQueue->isCapacity)); if(expandPriority == NULL){fprintf(stdout, "Memory Allocation Failed"); return;}
        isQueue->isPriority = expandPriority;
        //memset((isQueue->isPriority + (isQueue->isCapacity - 1)), 0, sizeof(int));
    }
    isQueue->isItem[isQueue->isSize] = calloc(1, typeSize); if(isQueue->isItem[isQueue->isSize] == NULL){fprintf(stdout, "Memory Allocation Failed"); return;}
    memcpy(isQueue->isItem[isQueue->isSize], isItem, typeSize);
    isQueue->isPriority[isQueue->isSize] = isPriority;
    int isIndex = isQueue->isSize;
    while(isQueue->isPriority[isIndex] > isQueue->isPriority[isParent(isIndex)]){
        int thisPriority = isQueue->isPriority[isIndex];
        void *isTemp = isQueue->isItem[isIndex];
        isQueue->isPriority[isIndex] = isQueue->isPriority[isParent(isIndex)];
        isQueue->isItem[isIndex] = isQueue->isItem[isParent(isIndex)];
        isQueue->isPriority[isParent(isIndex)] = thisPriority;
        isQueue->isItem[isParent(isIndex)] = isTemp;
        isIndex = isParent(isIndex);
    }
    isQueue->isSize++;
    return;
}

void *removeRoot_MinHeap(PriorityQueue *isQueue){
    if(isQueue->isSize == 0){fprintf(stdout, "Empty Queue"); return NULL;}
    //void *getRoot = isQueue->isData[0];
    //isQueue->isData[0] = isQueue->isData[isQueue->isSize - 1];
    //isQueue->getPriority[0] = isQueue->getPriority[isQueue->isSize - 1];
    //memset((isQueue->isData + (isQueue->isSize - 1)), 0, sizeof(void*));
    //memset((isQueue->getPriority + (isQueue->isSize - 1)), 0, sizeof(int));
    
    void *isRoot = calloc(1, sizeof(isQueue->isItem[0])); if(isRoot == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return NULL;}
    memcpy(isRoot, isQueue->isItem[0], sizeof(isQueue->isItem[0]));
    free(isQueue->isItem[0]); isQueue->isItem[0] = NULL;
    isQueue->isItem[0] = calloc(1, sizeof(isQueue->isItem[isQueue->isSize - 1])); if(isQueue->isItem[0] == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return NULL;}
    memcpy(isQueue->isItem[0], isQueue->isItem[isQueue->isSize - 1], sizeof(isQueue->isItem[isQueue->isSize - 1]));
    free(isQueue->isItem[isQueue->isSize - 1]); isQueue->isItem[isQueue->isSize - 1] = NULL;
    isQueue->isPriority[0] = isQueue->isPriority[isQueue->isSize - 1];
    memset((isQueue->isPriority + (isQueue->isSize - 1)), 0, sizeof(int));
    isQueue->isSize--;
    isHeapify_MinHeap(isQueue, 0);
    return isRoot;
}

void *removeRoot_MaxHeap(PriorityQueue *isQueue){
    if(isQueue->isSize == 0){fprintf(stdout, "Empty Queue"); return NULL;}
    void *isRoot = calloc(1, sizeof(isQueue->isItem[0])); if(isRoot == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return NULL;}
    memcpy(isRoot, isQueue->isItem[0], sizeof(isQueue->isItem[0]));
    free(isQueue->isItem[0]); isQueue->isItem[0] = NULL;
    isQueue->isItem[0] = calloc(1, sizeof(isQueue->isItem[isQueue->isSize - 1])); if(isQueue->isItem[0] == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return NULL;}
    memcpy(isQueue->isItem[0], isQueue->isItem[isQueue->isSize - 1], sizeof(isQueue->isItem[isQueue->isSize - 1]));
    free(isQueue->isItem[isQueue->isSize - 1]); isQueue->isItem[isQueue->isSize - 1] = NULL;
    isQueue->isPriority[0] = isQueue->isPriority[isQueue->isSize - 1];
    memset((isQueue->isPriority + (isQueue->isSize - 1)), 0, sizeof(int));
    isQueue->isSize--;
    isHeapify_MaxHeap(isQueue, 0);
    return isRoot;
}

void isHeapify_MinHeap(PriorityQueue *isQueue, int isIndex){
    int getIndex = isIndex;
    (isLeft(isIndex) < isQueue->isSize && isQueue->isPriority[isLeft(isIndex)] < isQueue->isPriority[isIndex]) && (getIndex = isLeft(isIndex));
    (isRight(isIndex) < isQueue->isSize && isQueue->isPriority[isRight(isIndex)] < isQueue->isPriority[getIndex]) && (getIndex = isRight(isIndex));
    if(getIndex != isIndex){
        void *isTemp = isQueue->isItem[isIndex];
        int isPriority = isQueue->isPriority[isIndex];
        isQueue->isItem[isIndex] = isQueue->isItem[getIndex];
        isQueue->isPriority[isIndex] = isQueue->isPriority[getIndex];
        isQueue->isItem[getIndex] = isTemp;
        isQueue->isPriority[getIndex] = isPriority;
        isHeapify_MinHeap(isQueue, getIndex);
    }
    return;
}

void isHeapify_MaxHeap(PriorityQueue *isQueue, int isIndex){
    int getIndex = isIndex;
    (isLeft(isIndex) < isQueue->isSize && isQueue->isPriority[isLeft(isIndex)] > isQueue->isPriority[isIndex]) && (getIndex = isLeft(isIndex));
    (isRight(isIndex) < isQueue->isSize && isQueue->isPriority[isRight(isIndex)] > isQueue->isPriority[getIndex]) && (getIndex = isRight(isIndex));
    if(getIndex != isIndex){
        void *isTemp = isQueue->isItem[isIndex];
        int isPriority = isQueue->isPriority[isIndex];
        isQueue->isItem[isIndex] = isQueue->isItem[getIndex];
        isQueue->isPriority[isIndex] = isQueue->isPriority[getIndex];
        isQueue->isItem[getIndex] = isTemp;
        isQueue->isPriority[getIndex] = isPriority;
        isHeapify_MaxHeap(isQueue, getIndex);
    }
    return;
}

void updateItemPriority_MinHeap(PriorityQueue *isQueue, void *isItem, int isPriority){
    if(isQueue->isSize == 0){fprintf(stdout, "Empty Queue"); return;}
    int isIndex = -1;
    for(int thisData = 0; thisData < isQueue->isSize; thisData++){
        if(compareData(isQueue->isItem[thisData], isItem) == 0){isIndex = thisData; break;}
    }
    if(isIndex == -1){fprintf(stdout, "Invalid Item"); return;}
    isQueue->isPriority[isIndex] = isPriority;
    if(isPriority < isQueue->isPriority[isParent(isIndex)]){
        while(isQueue->isPriority[isIndex] < isQueue->isPriority[isParent(isIndex)]){
            int thisPriority = isQueue->isPriority[isIndex];
            void *isTemp = isQueue->isItem[isIndex];
            isQueue->isPriority[isIndex] = isQueue->isPriority[isParent(isIndex)];
            isQueue->isItem[isIndex] = isQueue->isItem[isParent(isIndex)];
            isQueue->isPriority[isParent(isIndex)] = thisPriority;
            isQueue->isItem[isParent(isIndex)] = isTemp;
            isIndex = isParent(isIndex);
        }
    } else{
        isHeapify_MinHeap(isQueue, isIndex);
    }
    return;
}

void updateItemPriority_MaxHeap(PriorityQueue *isQueue, void *isItem, int isPriority){
    if(isQueue->isSize == 0){fprintf(stdout, "Empty Queue"); return;}
    int isIndex = -1;
    for(int thisData = 0; thisData < isQueue->isSize; thisData++){
        if(compareData(isQueue->isItem[thisData], isItem) == 0){isIndex = thisData; break;}
    }
    if(isIndex == -1){fprintf(stdout, "Invalid Item.\n"); return;}
    isQueue->isPriority[isIndex] = isPriority;
    if(isPriority > isQueue->isPriority[isParent(isIndex)]){
        while(isQueue->isPriority[isIndex] > isQueue->isPriority[isParent(isIndex)]){
            int thisPriority = isQueue->isPriority[isIndex];
            void *isTemp = isQueue->isItem[isIndex];
            isQueue->isPriority[isIndex] = isQueue->isPriority[isParent(isIndex)];
            isQueue->isItem[isIndex] = isQueue->isItem[isParent(isIndex)];
            isQueue->isPriority[isParent(isIndex)] = thisPriority;
            isQueue->isItem[isParent(isIndex)] = isTemp;
            isIndex = isParent(isIndex);
        }
    } else{isHeapify_MaxHeap(isQueue, isIndex);}
    return;
}

void destroyQueue(PriorityQueue *isQueue){
    if(isQueue->isSize == 0){fprintf(stdout, "Empty Queue"); return;}
    for(int isIndex = 0; isIndex < isQueue->isSize; isIndex++){
        free(isQueue->isItem[isIndex]); isQueue->isItem[isIndex] = NULL;
    }
    free(isQueue->isItem); isQueue->isItem = NULL;
    free(isQueue->isPriority); isQueue->isPriority = NULL;
    free(isQueue); isQueue = NULL;
    return;
}

bool containsItem(PriorityQueue *isQueue, void *isItem){
    if(isQueue->isSize == 0){fprintf(stdout, "Empty Queue"); return false;}
    for(int isIndex = 0; isIndex < isQueue->isSize; isIndex++){
        if(compareData(isQueue->isItem[isIndex], isItem) == 0){return true;}
    }
    return false;
}

int isPriorityItem(PriorityQueue *isQueue, void *isItem){
    if(isQueue->isSize == 0){fprintf(stdout, "Empty Queue"); return -1;}
    for(int isIndex = 0; isIndex < isQueue->isSize; isIndex++){
        if(compareData(isQueue->isItem[isIndex], isItem) == 0){return isQueue->isPriority[isIndex];}
    }
    fprintf(stdout, "Invalid Item.\n");
    return -1;
}

int isPriorityIndex(PriorityQueue *isQueue, int isIndex){
    if(isIndex < 0 || isIndex > isQueue->isSize){fprintf(stdout, "IndexOutOfBounds"); return -1;}
    if(isQueue->isSize == 0){fprintf(stdout, "Empty Queue"); return -1;}
    return isQueue->isPriority[isIndex];
}

bool isEmpty(PriorityQueue *isQueue){return isQueue->isSize == 0;}

bool isFull(PriorityQueue *isQueue){return isQueue->isSize == isQueue->isCapacity;}

int isSize(PriorityQueue *isQueue){return isQueue->isSize;}

void displayPriorityQueue(PriorityQueue *isQueue){
    if(isQueue->isSize == 0){fprintf(stdout, "Empty Queue"); return;}
    fprintf(stdout, "Priority Queue: ");
    for(int isIndex = 0; isIndex < isQueue->isSize; isIndex++){
        displayData(isQueue->isItem[isIndex], isIndex == isQueue->isSize - 1);
        //(thisData != isQueue->isSize - 1) ? displayData(isQueue->isData[thisData], 0) : displayData(isQueue->isData[thisData], 1);
    }
    return;
}

void _insertItem_MinHeap(Priority_Queue *isQueue, void *isItem, int isPriority, int typeSize){
    if(isQueue->isSized && isQueue->isSize == isQueue->isCapacity){
        fprintf(stdout, "Queue Is Full.\n"); return;
    } else if(!isQueue->isSized && isQueue->isSize == isQueue->isCapacity){
        isQueue->isCapacity++;
        void **expandItem = realloc(isQueue->isItem, sizeof(void *) * (isQueue->isCapacity)); if(expandItem == NULL){fprintf(stdout, "Memory Allocation Failed"); return;}
        isQueue->isItem = expandItem;
        //memset((isQueue->isItem + (isQueue->isCapacity - 1)), 0, sizeof(void*));
        Item *expandItemProperty = realloc(isQueue->isItemProperty, sizeof(Item) * (isQueue->isCapacity)); if(expandItemProperty == NULL){fprintf(stdout, "Memory Allocation Failed"); return;}
        isQueue->isItemProperty = expandItemProperty;
        //memset((isQueue->isItemProperty + (isQueue->isCapacity - 1)), 0, sizeof(Item));
    }
    isQueue->isItem[isQueue->isSize] = calloc(1, typeSize); if(isQueue->isItem[isQueue->isSize] == NULL){fprintf(stdout, "Memory Allocation Failed"); return;}
    memcpy(isQueue->isItem[isQueue->isSize], isItem, typeSize);
    isQueue->isItemProperty[isQueue->isSize].isIndex = isQueue->isSize;
    isQueue->isItemProperty[isQueue->isSize].isPriority = isPriority;
    int isIndex = isQueue->isSize;
    while(isQueue->isItemProperty[isIndex].isPriority < isQueue->isItemProperty[isParent(isIndex)].isPriority){
        Item isTemp = isQueue->isItemProperty[isIndex];
        isQueue->isItemProperty[isIndex] = isQueue->isItemProperty[isParent(isIndex)];
        isQueue->isItemProperty[isParent(isIndex)] = isTemp;
        isIndex = isParent(isIndex);
    }
    isQueue->isSize++;
    return;
}

void _insertItem_MaxHeap(Priority_Queue *isQueue, void *isItem, int isPriority, int typeSize){
    if(isQueue->isSized && isQueue->isSize == isQueue->isCapacity){
        fprintf(stdout, "Queue Is Full.\n"); return;
    } else if(!isQueue->isSized && isQueue->isSize == isQueue->isCapacity){
        isQueue->isCapacity *= 2;
        void **expandItem = realloc(isQueue->isItem, sizeof(void *) * (isQueue->isCapacity)); if(expandItem == NULL){fprintf(stdout, "Memory Allocation Failed"); return;}
        isQueue->isItem = expandItem;
        //memset((isQueue->isItem + (isQueue->isCapacity - 1)), 0, sizeof(void*));
        Item *expandItemProperty = realloc(isQueue->isItemProperty, sizeof(Item) * (isQueue->isCapacity)); if(expandItemProperty == NULL){fprintf(stdout, "Memory Allocation Failed"); return;}
        isQueue->isItemProperty = expandItemProperty;
        //memset((isQueue->isItemProperty + (isQueue->isCapacity - 1)), 0, sizeof(Item));
    }
    isQueue->isItem[isQueue->isSize] = calloc(1, typeSize); if(isQueue->isItem[isQueue->isSize] == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    memcpy(isQueue->isItem[isQueue->isSize], isItem, typeSize);
    isQueue->isItemProperty[isQueue->isSize].isIndex = isQueue->isSize;
    isQueue->isItemProperty[isQueue->isSize].isPriority = isPriority;
    int isIndex = isQueue->isSize;
    while(isQueue->isItemProperty[isIndex].isPriority > isQueue->isItemProperty[isParent(isIndex)].isPriority){
        Item isTemp = isQueue->isItemProperty[isIndex];
        isQueue->isItemProperty[isIndex] = isQueue->isItemProperty[isParent(isIndex)];
        isQueue->isItemProperty[isParent(isIndex)] = isTemp;
        isIndex = isParent(isIndex);
    }
    isQueue->isSize++;
    return;
}

void *_removeRoot_MinHeap(Priority_Queue *isQueue){
    if(isQueue->isSize == 0){fprintf(stdout, "Empty Queue.\n"); return NULL;}
    void *isRoot = calloc(1, sizeof(isQueue->isItem[isQueue->isItemProperty[0].isIndex]));
    memcpy(isRoot, isQueue->isItem[isQueue->isItemProperty[0].isIndex], sizeof(isQueue->isItem[isQueue->isItemProperty[0].isIndex]));
    int isIndex = isQueue->isItemProperty[0].isIndex; isQueue->isItemProperty[0] = isQueue->isItemProperty[isQueue->isSize - 1];
    free(isQueue->isItem[isIndex]); isQueue->isItem[isIndex] = NULL;
    memmove(isQueue->isItem + isIndex, isQueue->isItem + (isIndex + 1), sizeof(void *) * (isQueue->isSize - (isIndex + 1)));
    //memset((isQueue->isItem + (isQueue->isSize - 1)), 0, sizeof(void*));
    for(int getIndex = 0; getIndex < isQueue->isSize; (isQueue->isItemProperty[getIndex].isIndex > isIndex) && (isQueue->isItemProperty[getIndex].isIndex--), getIndex++);
    isQueue->isSize--;
    _isHeapify_MinHeap(isQueue, 0);
    return isRoot;
}

void *_removeRoot_MaxHeap(Priority_Queue *isQueue){
    if(isQueue->isSize == 0){fprintf(stdout, "Empty Queue.\n"); return NULL;}
    void *isRoot = calloc(1, sizeof(isQueue->isItem[isQueue->isItemProperty[0].isIndex]));
    memcpy(isRoot, isQueue->isItem[isQueue->isItemProperty[0].isIndex], sizeof(isQueue->isItem[isQueue->isItemProperty[0].isIndex]));
    int isIndex = isQueue->isItemProperty[0].isIndex; isQueue->isItemProperty[0] = isQueue->isItemProperty[isQueue->isSize - 1];
    free(isQueue->isItem[isIndex]); isQueue->isItem[isIndex] = NULL;
    memmove(isQueue->isItem + isIndex, isQueue->isItem + (isIndex + 1), sizeof(void *) * (isQueue->isSize - (isIndex + 1)));
    //memset((isQueue->isItem + (isQueue->isSize - 1)), 0, sizeof(void*));
    for(int getIndex = 0; getIndex < isQueue->isSize; (isQueue->isItemProperty[getIndex].isIndex > isIndex) && (isQueue->isItemProperty[getIndex].isIndex--), getIndex++);
    isQueue->isSize--;
    _isHeapify_MaxHeap(isQueue, 0);
    return isRoot;
}

void _isHeapify_MinHeap(Priority_Queue *isQueue, int isIndex){
    int getIndex = isIndex;
    (isLeft(isIndex) < isQueue->isSize && isQueue->isItemProperty[isLeft(isIndex)].isPriority < isQueue->isItemProperty[isIndex].isPriority) && (getIndex = isLeft(isIndex));
    (isRight(isIndex) < isQueue->isSize && isQueue->isItemProperty[isRight(isIndex)].isPriority < isQueue->isItemProperty[getIndex].isPriority) && (getIndex = isRight(isIndex));
    if(getIndex != isIndex){
        Item isTemp = isQueue->isItemProperty[isIndex];
        isQueue->isItemProperty[isIndex] = isQueue->isItemProperty[getIndex];
        isQueue->isItemProperty[getIndex] = isTemp;
        _isHeapify_MinHeap(isQueue, getIndex);
    }
    return;
}

void _isHeapify_MaxHeap(Priority_Queue *isQueue, int isIndex){
    int getIndex = isIndex;
    (isLeft(isIndex) < isQueue->isSize && isQueue->isItemProperty[isLeft(isIndex)].isPriority > isQueue->isItemProperty[isIndex].isPriority) && (getIndex = isLeft(isIndex));
    (isRight(isIndex) < isQueue->isSize && isQueue->isItemProperty[isRight(isIndex)].isPriority > isQueue->isItemProperty[getIndex].isPriority) && (getIndex = isRight(isIndex));
    if(getIndex != isIndex){
        Item isTemp = isQueue->isItemProperty[isIndex];
        isQueue->isItemProperty[isIndex] = isQueue->isItemProperty[getIndex];
        isQueue->isItemProperty[getIndex] = isTemp;
        _isHeapify_MaxHeap(isQueue, getIndex);
    }
    return;
}

void _updateItemPriority_MinHeap(Priority_Queue *isQueue, void *isItem, int isPriority){
    if(isQueue->isSize == 0){fprintf(stdout, "Empty Queue.\n"); return;}
    int isIndex = -1;
    for(int thisData = 0; thisData < isQueue->isSize; thisData++){
        if(compareData(isQueue->isItem[isQueue->isItemProperty[thisData].isIndex], isItem) == 0){isIndex = thisData; break;}
    }
    if(isIndex == -1){fprintf(stdout, "Invalid Item.\n"); return;}
    isQueue->isItemProperty[isIndex].isPriority = isPriority;
    if(isPriority < isQueue->isItemProperty[isParent(isIndex)].isPriority){
        while(isQueue->isItemProperty[isIndex].isPriority < isQueue->isItemProperty[isParent(isIndex)].isPriority){
            Item isItem = isQueue->isItemProperty[isIndex];
            isQueue->isItemProperty[isIndex] = isQueue->isItemProperty[isParent(isIndex)];
            isQueue->isItemProperty[isParent(isIndex)] = isItem;
            isIndex = isParent(isIndex);
        }
    } else{_isHeapify_MinHeap(isQueue, isIndex);}
    return;
}

void _updateItemPriority_MaxHeap(Priority_Queue *isQueue, void *isItem, int isPriority){
    if(isQueue->isSize == 0){fprintf(stdout, "Empty Queue.\n"); return;}
    int isIndex = -1;
    for(int thisData = 0; thisData < isQueue->isSize; thisData++){
        if(compareData(isQueue->isItem[isQueue->isItemProperty[thisData].isIndex], isItem) == 0){isIndex = thisData; break;}
    }
    if(isIndex == -1){fprintf(stdout, "Invalid Item.\n"); return;}
    isQueue->isItemProperty[isIndex].isPriority = isPriority;
    if(isPriority > isQueue->isItemProperty[isParent(isIndex)].isPriority){
        while(isQueue->isItemProperty[isIndex].isPriority > isQueue->isItemProperty[isParent(isIndex)].isPriority){
            Item isItem = isQueue->isItemProperty[isIndex];
            isQueue->isItemProperty[isIndex] = isQueue->isItemProperty[isParent(isIndex)];
            isQueue->isItemProperty[isParent(isIndex)] = isItem;
            isIndex = isParent(isIndex);
        }
    } else{_isHeapify_MaxHeap(isQueue, isIndex);}
    return;
}

void _destroyQueue(Priority_Queue *isQueue){
    if(isQueue->isSize == 0){fprintf(stdout, "Empty Queue.\n"); return;}
    for(int thisBlock = 0; thisBlock < isQueue->isSize; thisBlock++){
        free(isQueue->isItem[thisBlock]); isQueue->isItem[thisBlock] = NULL;
    }
    free(isQueue->isItem); isQueue->isItem = NULL;
    free(isQueue->isItemProperty); isQueue->isItemProperty = NULL;
    free(isQueue); isQueue = NULL;
    return;
}

bool _containsItem(Priority_Queue *isQueue, void *isItem){
    if(isQueue->isSize == 0){fprintf(stdout, "Empty Queue.\n"); return false;}
    for(int thisData = 0; thisData < isQueue->isSize; thisData++){
        if(compareData(isQueue->isItem[thisData], isItem) == 0){return true;}
    }
    return false;
}

int _isPriorityItem(Priority_Queue *isQueue, void *isItem){
    if(isQueue->isSize == 0){fprintf(stdout, "Empty Queue.\n"); return -1;}
    for(int thisItem = 0; thisItem < isQueue->isSize; thisItem++){
        if(compareData(isQueue->isItem[isQueue->isItemProperty[thisItem].isIndex], isItem) == 0){return isQueue->isItemProperty[thisItem].isPriority;}
    }
    fprintf(stdout, "Invalid Item.\n");
    return -1;
}

int _isPriorityIndex(Priority_Queue *isQueue, int isIndex){
    if(isIndex < 0 || isIndex > isQueue->isSize){fprintf(stdout, "Index Out Of Bounds"); return -1;}
    if(isQueue->isSize == 0){fprintf(stdout, "Empty Queue.\n"); return -1;}
    return isQueue->isItemProperty[isIndex].isPriority;
}

bool _isEmpty(Priority_Queue *isQueue){return isQueue->isSize == 0;}

bool _isFull(Priority_Queue *isQueue){return isQueue->isSize == isQueue->isCapacity;}

int _isSize(Priority_Queue *isQueue){return isQueue->isSize;}

void _displayPriorityQueue(Priority_Queue *isQueue){
    if(isQueue->isSize == 0){fprintf(stdout, "Empty Queue.\n"); return;}
    fprintf(stdout, "Priority Queue: ");
    for(int isIndex = 0; isIndex < isQueue->isSize; isIndex++){
        displayData(isQueue->isItem[isQueue->isItemProperty[isIndex].isIndex], isIndex == isQueue->isSize - 1);
        //(thisData != isQueue->isSize - 1) ? (displayData(isQueue->isItem[isQueue->isItems[thisData].isIndex], false)) : (displayData(isQueue->isItem[isQueue->isItems[thisData].isIndex], true));
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