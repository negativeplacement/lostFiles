#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node{
    void *isItem;
    struct Node *nextNode, *prevNode;
}Node; 

typedef struct DLL{
    int isSize;
    struct Node *isHead, *isTail;
}DLL;

void insertItem(DLL *isDLL, void *isItem, int typeSize);
void insertItemAt(DLL *isDLL, void *isItem, int typeSize, int isIndex);
void removeItem(DLL *isDLL);
void removeItemAt(DLL *isDLL, int isIndex);
void isReverse(DLL *isDLL);
bool containsItem(DLL *isDLL, void *isItem);
int isItemIndex(DLL *isDLL, void *isItem);
void *isItemAt(DLL *isDLL, int isIndex);
int isSize(DLL *isDLL);
void displayList(DLL *isDLL);
int compareData(void *getData, void *nodeData);
void displayData(void *isItem, bool isLast);

int main(int argc, char *argv[]){
    DLL *isDLL = calloc(1, sizeof(DLL));if(isDLL == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return 1;}
    isDLL->isSize = 0; isDLL->isHead = NULL; isDLL->isTail = NULL;
    int a = 4, b = 2, c = 5, d = 1, e = 3;
    insertItem(isDLL, &a, sizeof(a));
    insertItem(isDLL, &b, sizeof(b));
    insertItem(isDLL, &c, sizeof(c));
    insertItem(isDLL, &d, sizeof(d));
    displayList(isDLL);
    removeItemAt(isDLL, 1);
    displayList(isDLL);
    insertItemAt(isDLL,&e,sizeof(e), 1);
    displayList(isDLL);
    isReverse(isDLL);
    displayList(isDLL);
    //puts(" ");
    //displayNodesBackwards(isDLL);
    return 0;
}

void insertItem(DLL *isDLL, void *isItem, int typeSize){
    Node *newNode = calloc(1, sizeof(Node));
    if(newNode == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    newNode->nextNode = NULL; newNode->prevNode = NULL;
    newNode->isItem = calloc(1, typeSize); if(newNode->isItem == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    memcpy(newNode->isItem, isItem, typeSize);
    if(isDLL->isSize == 0){
        isDLL->isHead = newNode; isDLL->isTail = newNode;
        newNode->prevNode = NULL; newNode->nextNode = NULL;
    } else{
        isDLL->isTail->nextNode = newNode; newNode->prevNode = isDLL->isTail;
        newNode->nextNode = NULL; isDLL->isTail = newNode;
    }
    isDLL->isSize++;
    return;
}

void insertItemAt(DLL *isDLL, void *isItem, int typeSize, int isIndex){
    if(isIndex < 0 || isIndex > isDLL->isSize){fprintf(stdout, "IndexOutOFBounds.\n"); return;}
    Node *newNode = calloc(1, sizeof(Node));
    if(newNode == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    newNode->nextNode = NULL; newNode->prevNode = NULL;
    newNode->isItem = calloc(1, typeSize); if(newNode->isItem == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    memcpy(newNode->isItem, isItem, typeSize);
    if(isDLL->isSize == 0){
        isDLL->isHead = newNode; isDLL->isTail = newNode;
        newNode->prevNode = NULL; newNode->nextNode = NULL;
    } else if(isIndex == 0){
        newNode->nextNode = isDLL->isHead; newNode->prevNode = NULL;
        isDLL->isHead->prevNode = newNode; isDLL->isHead = newNode;
    } else if(isIndex == isDLL->isSize){
        isDLL->isTail->nextNode = newNode; newNode->prevNode = isDLL->isTail;
        newNode->nextNode = NULL; isDLL->isTail = newNode;
    } else{
        Node *isNode = isDLL->isHead;
        for(int thisIndex = 0; thisIndex < isIndex; thisIndex++){isNode = isNode->nextNode;}
        Node *isPrev = isNode->prevNode;
        newNode->nextNode = isNode; newNode->prevNode = isPrev;
        isPrev->nextNode = newNode; isNode->prevNode = newNode;
    }
    isDLL->isSize++;
    return;
}

void removeItem(DLL *isDLL){
    if(isDLL->isSize == 0){fprintf(stdout, "Empty List"); return;}
    else if(isDLL->isSize == 1){
        free(isDLL->isHead->isItem); isDLL->isHead->isItem = NULL;
        free(isDLL->isHead); isDLL->isHead = NULL; isDLL->isTail = NULL;
    }else{
        Node *isNode = isDLL->isTail;
        isDLL->isTail = isNode->prevNode; isDLL->isTail->nextNode = NULL;
        free(isNode->isItem); isNode->isItem  = NULL;
        free(isNode); isNode = NULL;
    }
    isDLL->isSize--;
    return;
}

void removeItemAt(DLL *isDLL, int isIndex){
    if(isIndex < 0 || isIndex > isDLL->isSize){fprintf(stdout, "IndexOutOFBounds"); return;}
    if(isDLL->isSize == 0){fprintf(stdout, "Empty List"); return;}
    Node *isNode;
    if(isDLL->isSize == 1){
        free(isDLL->isHead->isItem); isDLL->isHead->isItem = NULL;
        free(isDLL->isHead); isDLL->isHead = NULL; isDLL->isTail = NULL;
    } else if(isIndex == 0){
        isNode = isDLL->isHead; 
        isDLL->isHead = isNode->nextNode; isDLL->isHead->prevNode = NULL;
        free(isNode->isItem); isNode->isItem = NULL;
        free(isNode); isNode = NULL;
    } else if (isIndex == isDLL->isSize - 1){
        isNode = isDLL->isTail;
        isDLL->isTail = isNode->prevNode; isDLL->isTail->nextNode = NULL;
        free(isNode->isItem); isNode->isItem = NULL;
        free(isNode); isNode = NULL;
    } else{
        isNode = isDLL->isHead;
        for(int thisIndex = 0; thisIndex < isIndex; thisIndex++){isNode = isNode->nextNode;}
        Node *prevNode = isNode->prevNode;
        Node *nextNode = isNode->nextNode;
        prevNode->nextNode = nextNode;
        nextNode->prevNode = prevNode;
        free(isNode->isItem); isNode->isItem = NULL;
        free(isNode); isNode = NULL;
    }
    isDLL->isSize--;
    return;
}

void isReverse(DLL *isDLL){
    if(isDLL->isSize == 0){fprintf(stdout, "Empty List.\n"); return;}
    Node *isTemporary = NULL, *isNode = isDLL->isHead;
    while(isNode != NULL){
        isTemporary = isNode->prevNode; isNode->prevNode = isNode->nextNode;
        isNode->nextNode = isTemporary; isNode = isNode->prevNode;
    }
    isDLL->isHead = isTemporary->prevNode;
    return;
}

bool containsItem(DLL *isDLL, void *isItem){
    if(isDLL->isSize == 0){fprintf(stdout, "Empty List.\n"); return false;}
    Node *isNode = isDLL->isHead;
    for(int thisIndex = 0; thisIndex < isDLL->isSize; thisIndex++){
        if(compareData(isItem, isNode->isItem) == 0){return true;}
        isNode = isNode->nextNode;
    }
    return false;
}

int isItemIndex(DLL *isDLL, void *isItem){
    if(isDLL->isSize == 0){fprintf(stdout, "Empty List.\n"); return -1;}
    Node *isNode = isDLL->isHead;
    for(int thisIndex = 0; thisIndex < isDLL->isSize; thisIndex++){
        if(compareData(isItem, isNode->isItem) == 0){return thisIndex;}
        isNode = isNode->nextNode;
    }
    return -1;
}

void *isItemAt(DLL *isDLL, int isIndex){
    if(isIndex < 0 || isIndex > isDLL->isSize){fprintf(stdout, "IndexOutOFBounds"); return NULL;}
    if(isDLL->isSize == 0){fprintf(stdout, "Empty List.\n"); return NULL;}
    else{
        Node *isNode = isDLL->isHead;
        for(int thisIndex = 0; thisIndex < isIndex; thisIndex++){// Iterate to the the previous node before the index
            isNode = isNode->nextNode;
        }
        return isNode->isItem;
    }
}

int isSize(DLL *isDLL){return isDLL->isSize;}

void displayList(DLL *isDLL){
    if(isDLL->isSize == 0){fprintf(stdout, "Empty List.\n"); return;}
    Node *isNode = isDLL->isHead;
    for(int thisIndex = 0; thisIndex < isDLL->isSize; thisIndex++){
        (thisIndex != isDLL->isSize - 1) ? displayData(isNode->isItem, false) : displayData(isNode->isItem, true);
        isNode = isNode->nextNode;
    }
}

int compareData(void *getData, void *nodeData){
    int isData = *((int *)getData), currData = *(int *)nodeData;
    if(isData < currData){return -1;}
    else if(isData > currData){return 1;}
    else{return 0;}
}

void displayData(void *getItem, bool isLast){
    printf((!isLast) ?"%d -> " : "%d\n", *(int *)getItem);
}