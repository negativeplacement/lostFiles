#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
  void *isItem;
  struct Node *nextNode;
}Node;

typedef struct ll_Stack{ //Linked List Implementation
    int isCapacity, isSize;
    Node *isTop;
    bool isSized;
}ll_Stack;

typedef struct arr_Stack{ //Dynamic Array Implementation
    int isCapacity, isSize;
    bool isSized;
    void **isItem;
}arr_Stack;

void ll_pushItem(ll_Stack *isStack, void *isItem, int typeSize);
void *ll_popItem(ll_Stack *isStack);
void *ll_peekItem(ll_Stack *isStack);
int ll_isSize(ll_Stack *isStack);
bool ll_isFull(ll_Stack *isStack);
bool ll_isEmpty(ll_Stack *isStack);
void ll_displayStack(ll_Stack *isStack);

void arr_pushItem(arr_Stack *isStack, void *isItem, int typeSize);
void *arr_popItem(arr_Stack *isStack);
void *arr_peekItem(arr_Stack *isStack);
int arr_isSize(arr_Stack *isStack);
bool arr_isFull(arr_Stack *isStack);
bool arr_isEmpty(arr_Stack *isStack);
void arr_displayStack(arr_Stack *isStack);

void displayItem(void *isItem);

int main(int argc, char *argv[]){
    arr_Stack *isStack = calloc(1, sizeof(arr_Stack)); if(isStack == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return 1;}
    isStack->isItem = calloc(10, sizeof(void *)); if(isStack->isItem == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return 1;}
    isStack->isSized = true; isStack->isCapacity = 10; isStack->isSize = 0;
    /*ll_Stack *isStack = calloc(1, sizeof(ll_Stack)); if(isStack == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return 1;}
    isStack->isSized = true; isStack->isCapacity = 10; isStack->isSize = 0; isStack->isTop = NULL;*/
    int reference[] = {1, 2, 3};
    for(int i = 0; i < 3; i++){
        //ll_pushItem(isStack, &reference[i], sizeof(int));
        arr_pushItem(isStack, &reference[i], sizeof(int));
    }
    //ll_displayStack(isStack);
    //printf("Pop: %d\n", *(int*)ll_popItem(isStack));
    //ll_displayStack(isStack);
    arr_displayStack(isStack);
    printf("Pop: %d\n", *(int*)arr_popItem(isStack));
    arr_displayStack(isStack);
    return 0;
}

void ll_pushItem(ll_Stack *isStack, void *isItem, int typeSize){
    if(isStack->isSized && isStack->isSize == isStack->isCapacity){fprintf(stdout, "Stack Is Full"); return;}
    Node *newNode = calloc(1, sizeof(Node)); if(newNode == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    newNode->isItem = calloc(1, typeSize); if(newNode->isItem == NULL){fprintf(stdout, "Memory Allocation Failed"); return;}
    memcpy(newNode->isItem, isItem, typeSize);
    newNode->nextNode = isStack->isTop; isStack->isTop = newNode;
    isStack->isSize++;
    return;
}

void *ll_popItem(ll_Stack *isStack){
    if(isStack->isSize == 0){fprintf(stdout, "Empty Stack.\n"); return NULL;}
    Node *isTop = isStack->isTop;
    void *isItem = calloc(1, sizeof(isTop->isItem)); if(isItem == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return NULL;}
    memcpy(isItem, isTop->isItem, sizeof(isTop->isItem));
    isStack->isTop = isStack->isTop->nextNode;
    free(isTop->isItem); isTop->isItem = NULL;
    free(isTop); isTop = NULL;
    isStack->isSize--;
    return isItem;
}

void *ll_peekItem(ll_Stack *isStack){
    if(isStack->isSize == 0){fprintf(stdout, "Empty Stack.\n"); return NULL;}
    return isStack->isTop->isItem;
}

int ll_isSize(ll_Stack *isStack){return isStack->isSize;}

bool ll_isFull(ll_Stack *isStack){return isStack->isSize == isStack->isCapacity;}

bool ll_isEmpty(ll_Stack *isStack){return isStack->isSize == 0;}

void ll_displayStack(ll_Stack *isStack){
    if(isStack->isSize == 0){fprintf(stdout, "Empty Stack.\n"); return;}
    Node *getNode = isStack->isTop;
    while(getNode != NULL){displayItem(getNode->isItem); getNode = getNode->nextNode;}
    return;
}

void arr_pushItem(arr_Stack *isStack, void *isItem, int typeSize){
    if(isStack->isSized && isStack->isSize == isStack->isCapacity){fprintf(stdout, "Stack Is Full.\n"); return;}
    isStack->isItem[isStack->isSize] = calloc(1, typeSize); if(isStack->isItem[isStack->isSize] == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    memcpy(isStack->isItem[isStack->isSize], isItem, typeSize); isStack->isSize++;
    if(!isStack->isSized && isStack->isSize == isStack->isCapacity){
        isStack->isCapacity *= 2;
        void **expandItem = realloc(isStack->isItem, sizeof(void *) * isStack->isCapacity); if(expandItem == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
        isStack->isItem = expandItem;
    }
    return;
}

void *arr_popItem(arr_Stack *isStack){
    if(isStack->isSize == 0){fprintf(stdout, "Empty Stack.\n"); return NULL;}
    void *isItem = calloc(1, sizeof(isStack->isItem[isStack->isSize - 1]));if(isItem == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return NULL;}
    memcpy(isItem, isStack->isItem[isStack->isSize - 1], sizeof(isStack->isItem[isStack->isSize - 1]));
    free(isStack->isItem[isStack->isSize - 1]); isStack->isItem[isStack->isSize - 1] = NULL; isStack->isSize--;
    return isItem;
}

void *arr_peekItem(arr_Stack *isStack){
    if(isStack->isSize == 0){fprintf(stdout, "Empty Stack.\n"); return NULL;}
    return isStack->isItem[isStack->isSize - 1];
}

int arr_isSize(arr_Stack *isStack){return isStack->isSize;}

bool arr_isFull(arr_Stack *isStack){return isStack->isSize == isStack->isCapacity;}

bool arr_isEmpty(arr_Stack *isStack){return isStack->isSize == 0;}

void arr_displayStack(arr_Stack *isStack){
    if(isStack->isSize == 0){fprintf(stdout, "Empty Stack.\n"); return;}
    for(int isIndex = isStack->isSize - 1; isIndex >= 0; isIndex--){displayItem(isStack->isItem[isIndex]);}
    return;
}

void displayItem(void *isItem){
    fprintf(stdout, "%d\n", *(int *)isItem); return;
}