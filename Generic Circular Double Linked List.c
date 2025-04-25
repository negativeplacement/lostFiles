#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node{
    void *isItem;
    struct Node *nextNode, *prevNode;
}Node;

typedef struct CDLL{
    int isSize;
    struct Node *isHead, *isTail;
}CDLL;

void insertItem(CDLL *isCDLL, void *isItem, int typeSize);
void insertItemAt(CDLL *isCDLL, void *isItem, int typeSize, int isIndex);
void removeItem(CDLL *isCDLL);
void removeItemAt(CDLL *isCDLL, int isIndex);
void isReverse(CDLL *isCDLL);
bool containsItem(CDLL *isCDLL, void *isItem);
int isItemIndex(CDLL *isCDLL, void *isItem);
void *isItemAt(CDLL *isCDLL, int isIndex);
int isSize(CDLL *isCDLL);
void displayList(CDLL *isCDLL);
int compareData(void *getData, void *nodeData);
void displayData(void *isItem, bool isLast);

int main(int argc, char *argv[]){
    CDLL *isCDLL = calloc(1, sizeof(CDLL)); if(isCDLL == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return 1;}
    isCDLL->isSize = 0; isCDLL->isHead = NULL; isCDLL->isTail = NULL;
    int a = 4, b = 2, c = 5, d = 1, e = 3;
    insertNode(isCDLL, &a, sizeof(a));
    insertNode(isCDLL, &b, sizeof(b));
    insertNode(isCDLL, &c, sizeof(c));
    insertNode(isCDLL, &d, sizeof(d));
    displayNode(isCDLL);
    insertNodeAt(isCDLL,&e,sizeof(e), 1);
    displayNode(isCDLL);
    reverse(isCDLL);
    displayNode(isCDLL);
    return 0;
}

void insertItem(CDLL *isCDLL, void *isItem, int typeSize){
    Node *newNode = calloc(1, sizeof(Node));if(newNode == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    newNode->nextNode = NULL; newNode->prevNode = NULL;
    newNode->isItem = calloc(1, typeSize); if(newNode->isItem == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    memcpy(newNode->isItem, isItem, typeSize);
    if(isCDLL->isSize == 0){
        isCDLL->isHead = newNode; isCDLL->isTail = newNode;
        newNode->prevNode = newNode; newNode->nextNode = newNode;
    } else{
        isCDLL->isTail->nextNode = newNode;
        newNode->prevNode = isCDLL->isTail;
        isCDLL->isTail = newNode;
        isCDLL->isTail->nextNode = isCDLL->isHead;
        isCDLL->isHead->prevNode = isCDLL->isTail;
    }
    isCDLL->isSize++;
    return;
}

void insertItemAt(CDLL *isCDLL, void *isItem, int typeSize, int isIndex){
    if(isIndex < 0 || isIndex > isCDLL->isSize){fprintf(stdout, "IndexOutOfBounds.\n"); return;}
    Node *newNode = calloc(1, sizeof(Node));if(newNode == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    newNode->nextNode = NULL; newNode->prevNode = NULL;
    newNode->isItem = calloc(1, typeSize); if(newNode->isItem == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    memcpy(newNode->isItem, isItem, typeSize);
    if(isCDLL->isSize == 0){
        isCDLL->isHead = newNode; isCDLL->isTail = newNode;
        newNode->prevNode = newNode; newNode->nextNode = newNode;
    } else if(isIndex == 0){
        isCDLL->isHead->prevNode = newNode;
        newNode->nextNode = isCDLL->isHead;
        isCDLL->isHead = newNode;
        isCDLL->isTail->nextNode = isCDLL->isHead;
        isCDLL->isHead->prevNode = isCDLL->isTail;
    } else if(isIndex == isCDLL->isSize){
        isCDLL->isTail->nextNode = newNode;
        newNode->prevNode = isCDLL->isTail;
        isCDLL->isTail = newNode;
        isCDLL->isTail->nextNode = isCDLL->isHead;
        isCDLL->isHead->prevNode = isCDLL->isTail;
    } else{
        Node *isNode = isCDLL->isHead;
        for(int isIndex = 0; isIndex < isIndex; isIndex++){isNode = isNode->nextNode;}
        Node *isPrev = isNode->prevNode;
        isPrev->nextNode = newNode;
        newNode->prevNode = isPrev;
        newNode->nextNode = isNode;
        isNode->prevNode = newNode;
    }
    isCDLL->isSize++;
    return;
}

void removeItem(CDLL *isCDLL){
    if(isCDLL->isSize == 0){fprintf(stdout, "Empty List.\n"); return;}
    else if(isCDLL->isSize == 1){
        free(isCDLL->isHead->isItem); isCDLL->isHead->isItem = NULL;
        free(isCDLL->isHead); isCDLL->isHead = NULL;
    } else{
        Node *thisNode = isCDLL->isTail;
        isCDLL->isTail = isCDLL->isTail->prevNode;
        isCDLL->isTail->nextNode = isCDLL->isHead;
        isCDLL->isHead->prevNode = isCDLL->isTail;
        free(thisNode->isItem); thisNode->isItem = NULL;
        free(thisNode); thisNode = NULL;
    }
    isCDLL->isSize--;
    return;
}

void removeItemAt(CDLL *isCDLL, int isIndex){
    if(isIndex < 0 || isIndex > isCDLL->isSize){fprintf(stdout, "IndexOutOfBounds.\n"); return;}
    if(isCDLL->isSize == 0){fprintf(stdout, "Empty List.\n"); return;}
    else if(isCDLL->isSize == 1){
        free(isCDLL->isHead->isItem); isCDLL->isHead->isItem = NULL;
        free(isCDLL->isHead); isCDLL->isHead = NULL;
    } else if(isIndex == 0){
        Node *headNode = isCDLL->isHead;
        isCDLL->isHead = isCDLL->isHead->nextNode;
        isCDLL->isHead->prevNode = isCDLL->isTail;
        isCDLL->isTail->nextNode = isCDLL->isHead;
        free(headNode->isItem); headNode->isItem = NULL;
        free(headNode); headNode = NULL;
    } else if(isIndex == isCDLL->isSize - 1){
        Node *thisNode = isCDLL->isTail;
        isCDLL->isTail = isCDLL->isTail->prevNode;
        isCDLL->isTail->nextNode = isCDLL->isHead;
        isCDLL->isHead->prevNode = isCDLL->isTail;
        free(thisNode->isItem); thisNode->isItem = NULL;
        free(thisNode); thisNode = NULL;
    } else{
        Node *isNode = isCDLL->isHead;
        for(int isIndex = 0; isIndex < isIndex; isIndex++) {isNode = isNode->nextNode;}
        Node *prevNode = isNode->prevNode;
        Node *nextNode = isNode->nextNode;
        prevNode->nextNode = nextNode;
        nextNode->prevNode = prevNode;
        free(isNode->isItem); isNode->isItem = NULL;
        free(isNode); isNode = NULL;
    }
    isCDLL->isSize--;
    return;
}

void isReverse(CDLL *isCDLL){
    if(isCDLL->isSize == 0){fprintf(stdout, "Empty List.\n"); return;}
    Node *isCurrent = isCDLL->isHead, *isPlaceholder = NULL;
    do{
        isPlaceholder = isCurrent->prevNode;
        isCurrent->prevNode = isCurrent->nextNode;
        isCurrent->nextNode = isPlaceholder;
        isCurrent = isCurrent->prevNode;
    }while(isCurrent != isCDLL->isHead);
    isCDLL->isHead = isCDLL->isTail;
    isCDLL->isTail = isCDLL->isTail->prevNode;
    return;
}

bool containsItem(CDLL *isCDLL, void *isItem){
    Node *isNode = isCDLL->isHead;
    for(int isIndex = 0; isIndex < isCDLL->isSize; isIndex++){
        if(compareData(isItem, isNode->isItem) == 0){return true;}
        isNode = isNode->nextNode;
    }
    return false;
}

int isItemIndex(CDLL *isCDLL, void *isItem){
    Node *isNode = isCDLL->isHead;
    for(int isIndex = 0; isIndex < isCDLL->isSize; isIndex++){
        if(compareData(isItem, isNode->isItem) == 0){return isIndex;}
        isNode = isNode->nextNode;
    }
    return -1;
}

void *isItemAt(CDLL *isCDLL, int isIndex){
    if(isIndex < 0 || isIndex > isCDLL->isSize){fprintf(stderr, "IndexOutOFBounds.\n"); return NULL;}
    else{
        Node *isNode = isCDLL->isHead;
        for(int thisIndex = 0; thisIndex < isIndex; thisIndex++){// Iterate to the the previous node before the index
            isNode = isNode->nextNode;
        }
        return isNode->isItem;
    }
}

int isSize(CDLL *isCDLL){return isCDLL->isSize;}

void displayList(CDLL *isCDLL){
    Node *isNode = isCDLL->isHead;
    if(isNode == NULL){fprintf(stdout, "Empty List.\n"); return;}
    else{
        for(int thisIndex = 0; thisIndex < isCDLL->isSize; thisIndex++){
            (thisIndex != isCDLL->isSize - 1) ? displayData(isNode->isItem, false) : displayData(isNode->isItem, true);
            isNode = isNode->nextNode;
        }
    }
    return;
}

int compareData(void *getData, void *nodeData){
    int isData = *((int *)getData), currData = *(int *)nodeData;
    if(isData < currData){
        return -1;
    } else if(isData > currData){
        return 1;
    } else{
        return 0;
    }
}

void displayData(void *isItem, bool isLast){
    printf((!isLast) ?"%d -> " : "%d\n", *(int *)isItem); return;
}