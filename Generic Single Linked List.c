#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node{
    void *isItem;
    struct Node *nextNode;
}Node; 

typedef struct SLL{
    int isSize;
    struct Node *isHead, *isTail;
}SLL;

void insertItem(SLL *isSLL, void *isItem, int typeSize);
void insertItemAt(SLL *isSLL, void *isItem, int typeSize, int isIndex);
void removeItem(SLL *isSLL);
void removeItemAt(SLL *isSLL, int isIndex);
bool containsItem(SLL *isSLL, void *isItem);
int isItemIndex(SLL *isSLL, void *isItem);
void *isItemAt(SLL *isSLL, int isIndex);
int compareData(void *isData, void *nodeData);
int isSize(SLL *isSLL);
void displayList(SLL *isSLL);
void displayData(void *isItem, bool isLast);

int main(int argc, char *argv[]){
    SLL *isSLL = calloc(1, sizeof(SLL)); if(isSLL == NULL){fprintf(stdout, "Memory Allocation Failed"); return 1;}
    isSLL->isSize = 0; isSLL->isHead = NULL; isSLL->isTail = NULL;
    int a = 4, b = 2, c = 5, d = 1, e = 3;
    insertItem(isSLL, &a, sizeof(a));
    insertItem(isSLL, &b, sizeof(b));
    insertItem(isSLL, &c, sizeof(c));
    insertItem(isSLL, &d, sizeof(d));
    displayList(isSLL);
    insertItemAt(isSLL, &e, sizeof(e), 2);
    displayList(isSLL);
    removeItemAt(isSLL,1);
    displayList(isSLL);
    removeItem(isSLL);
    displayList(isSLL);
    return 0;
}

void insertItem(SLL *isSLL, void *isItem, int typeSize){
    Node *newNode = calloc(1, sizeof(Node)); if(newNode == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    newNode->isItem = calloc(1, typeSize); if(newNode->isItem == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    memcpy(newNode->isItem, isItem, typeSize); newNode->nextNode = NULL;
    if(isSLL->isSize == 0){
        isSLL->isHead = newNode; isSLL->isTail = newNode;
    } else{
        isSLL->isTail->nextNode = newNode;
        isSLL->isTail = newNode;
    }
    isSLL->isSize++;
    return;
}

void insertItemAt(SLL *isSLL, void *isItem, int typeSize, int isIndex){
    if(isIndex < 0 || isIndex > isSLL->isSize){fprintf(stderr, "IndexOutOfBounds"); return;}
    Node *newNode = calloc(1, sizeof(Node)); if(newNode == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    newNode->isItem = calloc(1, typeSize); if(newNode->isItem == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    memcpy(newNode->isItem, isItem, typeSize); newNode->nextNode = NULL;
    if(isSLL->isSize == 0){
        isSLL->isHead = newNode; isSLL->isTail = newNode;
    } else if(isIndex == 0){
        newNode->nextNode = isSLL->isHead;
        isSLL->isHead = newNode;
    } else if(isIndex == isSLL->isSize){
        isSLL->isTail->nextNode = newNode;
        isSLL->isTail = newNode;
    } else{
        Node *isNode = isSLL->isHead;
        for(int thisIndex = 0; thisIndex < isIndex - 1; thisIndex++){
            isNode = isNode->nextNode;
        }
        newNode->nextNode = isNode->nextNode;
        isNode->nextNode = newNode;
    }
    isSLL->isSize++;
    return;
}

void removeItem(SLL *isSLL){
    if(isSLL->isSize == 0){fprintf(stdout, "Empty List.\n"); return;}
    if(isSLL->isSize == 1){
        free(isSLL->isHead->isItem); isSLL->isHead->isItem = NULL;
        free(isSLL->isHead); isSLL->isHead = NULL; isSLL->isTail = NULL;
    } else{
        Node *isNode = isSLL->isHead;
        while(isNode->nextNode != isSLL->isTail){isNode = isNode->nextNode;}
        free(isSLL->isTail->isItem); isSLL->isTail->isItem = NULL;
        free(isSLL->isTail); isSLL->isTail = NULL;
        isNode->nextNode= NULL;
        isSLL->isTail = isNode;
    }
    isSLL->isSize--;
    return;
}

void removeItemAt(SLL *isSLL, int isIndex){
    if(isIndex < 0 || isIndex > isSLL->isSize){fprintf(stdout, "IndexOutOfBounds"); return;}
    if(isSLL->isSize == 0){fprintf(stdout, "Empty List.\n"); return;}
    Node *isNode = isSLL->isHead;
    if(isSLL->isSize == 1){
        free(isSLL->isHead->isItem); isSLL->isHead->isItem = NULL;
        free(isSLL->isHead); isSLL->isHead = NULL; isSLL->isTail = NULL;
    } else if(isIndex == 0){
        isSLL->isHead = isSLL->isHead->nextNode;
        free(isNode->isItem); isNode->isItem = NULL;
        free(isNode); isNode = NULL;
    } else if(isIndex == isSLL->isSize - 1){
        while(isNode->nextNode != isSLL->isTail){isNode = isNode->nextNode;}
        free(isSLL->isTail->isItem); isSLL->isTail->isItem = NULL;
        free(isSLL->isTail); isSLL->isTail = NULL;
        isNode->nextNode= NULL;
        isSLL->isTail = isNode;
    } else{
        for(int thisIndex = 0; thisIndex < isIndex - 1; thisIndex++){
            isNode = isNode->nextNode;
        }
        Node *thisNode = isNode->nextNode;
        isNode->nextNode = thisNode->nextNode;
        free(thisNode->isItem); thisNode->isItem = NULL;
        free(thisNode); thisNode = NULL;
    }
    isSLL->isSize--;
    return;
}

bool containsItem(SLL *isSLL, void *hasItem){
    if(isSLL->isSize == 0){fprintf(stdout, "Empty List"); return false;}
    Node *isNode = isSLL->isHead;
    for(int thisIndex = 0; thisIndex < isSLL->isSize; thisIndex++){
        if(compareData(hasItem, isNode->isItem) == 0){return true;}
        isNode = isNode->nextNode;
    }
    return false;
}

int isItemIndex(SLL *isSLL, void *hasItem){
    if(isSLL->isSize == 0){fprintf(stdout, "Empty List"); return -1;}
    Node *isNode = isSLL->isHead;
    for(int thisIndex = 0; thisIndex < isSLL->isSize; thisIndex++){
        if(compareData(hasItem, isNode->isItem) == 0){return thisIndex;}
        isNode = isNode->nextNode;
    }
    return -1;
}

void *isItemAt(SLL *isSLL, int getIndex){
    if(getIndex < 0 || getIndex > isSLL->isSize){fprintf(stderr, "IndexOutOFBounds"); return NULL;}
    if(isSLL->isSize == 0){fprintf(stdout, "Empty List");return NULL;}
    Node *isNode = isSLL->isHead;
    for(int thisIndex = 0; thisIndex < getIndex; thisIndex++){// Iterate to the the previous node before the index
        isNode = isNode->nextNode;
    }
    return isNode->isItem;
}

int compareData(void *getData, void *nodeData){
    int isData = *((int *)getData), currData = *(int *)nodeData;
    if(isData < currData){return -1;}
    else if(isData > currData){return 1;}
    else{return 0;}
}

int isSize(SLL *isSLL){
    return isSLL->isSize;
}

void displayList(SLL *isSLL){
    Node *isNode = isSLL->isHead;
    if(isNode == NULL){
        return;
    } else{
        for(int thisIndex = 0; thisIndex < isSLL->isSize; thisIndex++){
            (thisIndex != isSLL->isSize - 1) ? displayData(isNode->isItem, false) : displayData(isNode->isItem, true);
            isNode = isNode->nextNode;
        }
    }
}

void displayData(void *getItem, bool isLast){
    printf((!isLast) ?"%d -> " : "%d\n", *(int *)getItem);
}