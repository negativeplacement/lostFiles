#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
  void *isItem;
  struct Node *nextNode;
}Node;

typedef struct ll_Queue{ // LinkedList Implementation
    int isCapacity, isSize;
    Node *isHead, *isTail;
    bool isSized;
}ll_Queue;

typedef struct arr_Queue{ // Dynamic Array Implementation
    void **isItem;
    int isHead, isTail, isCapacity, isSize;
    bool isSized;
}arr_Queue;

void ll_enqueueItem(ll_Queue *isQueue, void *isItem, int typeSize);
void *ll_dequeueItem(ll_Queue *isQueue);
void *ll_peekItem(ll_Queue *isQueue);
bool ll_isEmpty(ll_Queue *isQueue);
bool ll_isFull(ll_Queue *isQueue);
int ll_isSize(ll_Queue *isQueue);
void ll_clearQueue(ll_Queue *isQueue);
void ll_displayQueue(ll_Queue *isQueue);

void arr_enqueueItem(arr_Queue *isQueue, void *isItem, int typeSize);
void *arr_dequeueItem(arr_Queue *isQueue);
void *arr_peekItem(arr_Queue *isQueue);
bool arr_isEmpty(arr_Queue *isQueue);
bool arr_isFull(arr_Queue *isQueue);
int arr_isSize(arr_Queue *isQueue);
void arr_displayQueue(arr_Queue *isQueue);

void displayItem(void *isItem, bool isLast);

int main(int argc, char *argv[]){
    ll_Queue *isQueue = calloc(1, sizeof(ll_Queue)); if(isQueue == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return 1;}
    isQueue->isSized = false; isQueue->isCapacity = 1; isQueue->isSize = 0;
    isQueue->isHead = NULL; isQueue->isTail = NULL;
    /*arr_Queue *isQueue = calloc(1, sizeof(arr_Queue)); if(isQueue == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return 1;}
    isQueue->isItem = calloc(4, sizeof(void *)); if(isQueue->isItem == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return 1;}
    isQueue->isSized = false; isQueue->isCapacity = 4; isQueue->isSize = 0; isQueue->isHead = 0; isQueue->isTail = 0;*/
    int reference[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for(int i = 0; i < 4; i++){
        ll_enqueueItem(isQueue, &reference[i], sizeof(int));
        //arr_enqueueItem(isQueue, &reference[i], sizeof(int));
    }
    ll_displayQueue(isQueue);
    //arr_displayQueue(isQueue);
    //arr_dequeueItem(isQueue);
    //arr_dequeueItem(isQueue);
    //arr_displayQueue(isQueue);
    for(int i = 4; i < 7; i++){
        //arr_enqueueItem(isQueue, &reference[i], sizeof(int));
    }
    //arr_displayQueue(isQueue);
    return 0;
}

void ll_enqueueItem(ll_Queue *isQueue, void *isItem, int typeSize){
    if(isQueue->isSized && isQueue->isSize == isQueue->isCapacity){fprintf(stdout, "Queue Is Full.\n"); return;}
    Node *newNode = calloc(1, sizeof(Node)); if(newNode == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    newNode->isItem = calloc(1, typeSize); if(newNode->isItem == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    memcpy(newNode->isItem, isItem, typeSize); newNode->nextNode = NULL;
    if(isQueue->isSize == 0){isQueue->isHead = newNode; isQueue->isTail = newNode;}
    else{isQueue->isTail->nextNode = newNode; isQueue->isTail = newNode;}
    isQueue->isSize++;
    return;
}

void *ll_dequeueItem(ll_Queue *isQueue){
    if(isQueue->isSize == 0){fprintf(stdout, "Queue is Empty"); return NULL;}
    Node *isHead = isQueue->isHead;
    void *isDeque = calloc(1, sizeof(isQueue->isHead->isItem));
    memcpy(isDeque, isQueue->isHead->isItem, sizeof(isQueue->isHead->isItem));
    if(isQueue->isSize == 1){isQueue->isHead = NULL; isQueue->isTail = NULL;}
    else{isQueue->isHead = isQueue->isHead->nextNode;}
    free(isHead->isItem); isHead->isItem = NULL;
    free(isHead); isHead = NULL;
    isQueue->isSize--;
    return isDeque;
}

void *ll_peekItem(ll_Queue *isQueue){
    if(isQueue->isSize == 0){fprintf(stdout, "Empty Queue.\n"); return NULL;}
    return isQueue->isHead->isItem;
}

bool ll_isEmpty(ll_Queue *isQueue){return isQueue->isSize == 0;}

bool ll_isFull(ll_Queue *isQueue){return isQueue->isSize == isQueue->isCapacity;}

int ll_isSize(ll_Queue *isQueue){return isQueue->isSize;}

void ll_clearQueue(ll_Queue *isQueue){
    if(isQueue->isSize == 0){fprintf(stdout, "Empty Queue.\n"); return;}
    Node *currentNode;
    while(isQueue->isSize > 0){
        currentNode = isQueue->isHead;
        isQueue->isHead = currentNode->nextNode;
        free(currentNode->isItem); currentNode->isItem = NULL;
        free(currentNode); currentNode = NULL;
        isQueue->isSize--;
    }
    isQueue->isHead = NULL; isQueue->isTail = NULL;
    return;
}

void ll_displayQueue(ll_Queue *isQueue){
    if(isQueue->isSize == 0){fprintf(stdout, "Empty Queue.\n"); return;}
    Node *isNode = isQueue->isHead;
    while(isNode != NULL){displayItem(isNode->isItem, isNode->nextNode == NULL); isNode = isNode->nextNode;}
    return;
}

void arr_enqueueItem(arr_Queue *isQueue, void *isItem, int typeSize){
    if(isQueue->isSized && isQueue->isSize == isQueue->isCapacity){fprintf(stdout, "Queue Is Full.\n"); return;}
    isQueue->isItem[isQueue->isTail] = calloc(1, typeSize); if(isQueue->isItem[isQueue->isTail] == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    memcpy(isQueue->isItem[isQueue->isTail], isItem, typeSize);
    isQueue->isSize++;
    if(!isQueue->isSized && isQueue->isSize == isQueue->isCapacity){
        isQueue->isCapacity *= 2;
        void **expandItem = realloc(isQueue->isItem, sizeof(void *) * isQueue->isCapacity); if(expandItem == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
        //memset((expandItem + (isQueue->isCapacity - 1)), 0, sizeof(void*));
        if(isQueue->isHead > isQueue->isTail){
            printf("Entry\n");
            memmove((expandItem + (isQueue->isHead + 1)), (expandItem + (isQueue->isHead)), sizeof(void*) * (isQueue->isCapacity - isQueue->isHead));
            memset((expandItem + (isQueue->isHead)), 0, sizeof(void*));
            printf("Set = %d, Alt = %d", isQueue->isHead + 1, isQueue->isCapacity - isQueue->isHead);
            isQueue->isHead++; //isQueue->isHead = isQueue->isCapacity - isQueue->isHead; ?
        }
        isQueue->isItem = expandItem;
    }
    isQueue->isTail = (isQueue->isTail + 1) % isQueue->isCapacity;
    return;
}

void *arr_dequeueItem(arr_Queue *isQueue){
    if(isQueue->isSize == 0){fprintf(stdout, "Empty Queue.\n"); return NULL;}
    void *isDequeue = isQueue->isItem[isQueue->isHead];
    isQueue->isSize--; isQueue->isHead = (isQueue->isHead + 1) % isQueue->isCapacity;
    return isDequeue;
}

void *arr_peekItem(arr_Queue *isQueue){
    if(isQueue->isSize == 0){fprintf(stdout, "Empty Queue.\n"); return NULL;}
    return isQueue->isItem[isQueue->isHead];
}

bool arr_isEmpty(arr_Queue *isQueue){return isQueue->isSize == 0;}

bool arr_isFull(arr_Queue *isQueue){return isQueue->isSize == isQueue->isCapacity;}

int arr_isSize(arr_Queue *isQueue){return isQueue->isSize;}

void arr_displayQueue(arr_Queue *isQueue){
    if(isQueue->isSize == 0){fprintf(stdout, "Empty Queue.\n"); return;}
    for(int isIndex = 0; isIndex < isQueue->isSize; isIndex++){displayItem(isQueue->isItem[(isQueue->isHead + isIndex) % isQueue->isCapacity], (isIndex == isQueue->isSize - 1));}
    return;
}

void displayItem(void *isItem, bool isLast){fprintf(stdout, isLast ? "%d\n" : "%d -> ", *(int *)isItem); return;}