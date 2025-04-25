#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node{
    void *isItem;
    int isCount;
    struct Node *isLeft, *isRight;
}Node;

void insertItem_I(Node **isRoot, void *isItem, int typeSize);
void insertItem_R(Node **isRoot, void *isItem, int typeSize);
void removeItem_I(Node **isRoot, void *isItem);
void removeItem_R(Node **isRoot, void *isItem);
Node *parentNode(Node **isRoot, void *isItem);
Node *isItem_I(Node **isRoot, void *isItem);
Node *isItem_R(Node **isRoot, void *isItem);
bool containsItem_I(Node **isRoot, void *isItem);
bool containsItem_R(Node **isRoot, void *isItem);
void *isMin(Node **isRoot);
void *isMax(Node **isRoot);
void isRootToLeaf_R(Node **isRoot, void **isItem, int nodeCount);
bool hasPathSum_R(Node **isRoot, int pathSum);
bool isIdenticalTrees_R(Node **firstRoot, Node **secondRoot);
void *isNthSmallest_R(Node **isRoot, int nthValue);
void *isNextGreatestItem_R(Node **isRoot, Node **refRoot, void *isItem);
int isSize_R(Node **isRoot);
int isHeight_R(Node **isRoot);
void isPreOrderTraversal_I(Node **isRoot);
void isPreOrderTraversal_R(Node **isRoot);
void isPostOrderTraversal_I(Node **isRoot);
void isPostOrderTraversal_R(Node **isRoot);
void isInOrderTraversal_I(Node **isRoot);
void isInOrderTraversal_R(Node **isRoot);

int compareData(void *isData, void *nodeData);
void displayData(void *isData, bool isLast);
void printRootToLeaf(void *isData, bool isLast);

int main(int argc, char *argv[]){
    int a=8, b=3, c=10, d=1, e=6, f=14, g=4, h=7, i=13, j =18;
    //int a=4, b=2, c=5, d=1, e=3;
    Node *isRoot = NULL;
    insertItem_I(&isRoot, &a, sizeof(a));
    insertItem_I(&isRoot, &b, sizeof(b));
    insertItem_I(&isRoot, &c, sizeof(c));
    insertItem_I(&isRoot, &d, sizeof(d));
    insertItem_I(&isRoot, &e, sizeof(e));
    insertItem_I(&isRoot, &f, sizeof(f));
    insertItem_I(&isRoot, &g, sizeof(g));
    insertItem_I(&isRoot, &h, sizeof(h));
    insertItem_I(&isRoot, &i, sizeof(i));
    printf("InOrder: \n");
    isInOrderTraversal_I(&isRoot);
    removeItem_I(&isRoot, &b);
    printf("\nInOrder: \n");
    isInOrderTraversal_I(&isRoot);
    //removeItem_R(&isRoot, &b);
    //displayInOrder(&isRoot);
    //printValue(getMin(&isRoot));
    //printf("%zu", getSize(&isRoot));
    //printf("%zu", getHeight(&isRoot));
    //getRootToLeaf(&isRoot, NULL, 0);
    //printValue(nthSmallest(&isRoot, 3));
    //printValue(nextGreatestItem(&isRoot, &isRoot, &f));
    return 0;
}

void insertItem_I(Node **isRoot, void *isItem, int typeSize){
    Node *newNode = calloc(1, sizeof(Node)); if(newNode == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    newNode->isItem = calloc(1, typeSize); if(newNode->isItem == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return;}
    memcpy(newNode->isItem, isItem, typeSize);
    newNode->isLeft = NULL; newNode->isRight = NULL;
    if(*isRoot == NULL){*isRoot = newNode; newNode->isCount++; return;}
    Node *isCurrent = *isRoot, *isParent = NULL;
    while(isCurrent != NULL){
        isParent = isCurrent;
        if(compareData(isItem, isCurrent->isItem) == -1){isCurrent = isCurrent->isLeft;}
        else if(compareData(isItem, isCurrent->isItem) == 1){isCurrent = isCurrent->isRight;}
    }
    if(compareData(isItem, isParent->isItem) == -1){isParent->isLeft = newNode;}
    else if(compareData(isItem, isParent->isItem) == 1){isParent->isRight = newNode;}
    newNode->isCount++;
}

void insertItem_R(Node **isRoot, void *isItem, int typeSize){
    if(*isRoot == NULL){
        Node *newNode = calloc(1, sizeof(Node)); if(newNode == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
        newNode->isItem = calloc(1, typeSize); if(newNode->isItem == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return;}
        memcpy(newNode->isItem, isItem, typeSize);
        newNode->isCount = 1; newNode->isLeft = NULL; newNode->isRight = NULL;
        *isRoot = newNode;
    }else{
        if(compareData(isItem, (*isRoot)->isItem) == -1){return insertItem_R(&((*isRoot)->isLeft), isItem, typeSize);}
        else if(compareData(isItem, (*isRoot)->isItem) == 1){return insertItem_R(&((*isRoot)->isRight), isItem, typeSize);}
        else if(compareData(isItem, (*isRoot)->isItem) == 0){(*isRoot)->isCount++;}
    }
    return;
}

void removeItem_I(Node **isRoot, void *isItem){
    Node *isCurrent = *isRoot, *isParent = NULL;
    while(isCurrent != NULL && compareData(isCurrent->isItem, isItem) != 0){
        isParent = isCurrent;
        if(compareData(isItem, isCurrent->isItem) == -1){isCurrent = isCurrent->isLeft;}
        else if(compareData(isItem, isCurrent->isItem) == 1){isCurrent = isCurrent->isRight;}
    }
    if(isCurrent == NULL){return;}
    if(isCurrent->isLeft == NULL && isCurrent->isRight == NULL){
        if(isParent == NULL){
            free(isCurrent->isItem); isCurrent->isItem = NULL;
            free(isCurrent); isCurrent = NULL; return;
        }
        if(isParent->isLeft == isCurrent){isParent->isLeft = NULL;}
        else if(isParent->isRight == isCurrent){isParent->isRight = NULL;}
        free(isCurrent->isItem); isCurrent->isItem = NULL;
        free(isCurrent); isCurrent = NULL;
    } else if(isCurrent->isLeft == NULL || isCurrent->isRight == NULL){
        Node *isChild = isCurrent->isLeft != NULL ? isCurrent->isLeft : isCurrent->isRight;
        if(isParent == NULL){
            free(isCurrent->isItem); isCurrent->isItem = NULL;
            free(isCurrent); isCurrent = NULL;
        }
        if(isParent->isLeft == isCurrent){isParent->isLeft = isChild;}
        else if(isParent->isRight == isCurrent){isParent->isRight = isChild;}
        free(isCurrent->isItem); isCurrent->isItem = NULL;
        free(isCurrent); isCurrent = NULL;
    } else{
        Node *isSuccessor = isCurrent->isRight;
        isParent = isCurrent;
        while(isSuccessor->isLeft != NULL){isParent = isSuccessor; isSuccessor = isSuccessor->isLeft;}
        memcpy(isCurrent->isItem, isSuccessor->isItem, sizeof(isSuccessor->isItem));
        if(isParent->isLeft == isSuccessor){isParent->isLeft = isSuccessor->isRight;}
        else if(isParent->isRight == isSuccessor){isParent->isRight = isSuccessor->isRight;}
        free(isSuccessor->isItem); isSuccessor->isItem = NULL; free(isSuccessor); isSuccessor = NULL;
    }
    return;
}

void removeItem_R(Node **isRoot, void *isItem){
    if(*isRoot == NULL){fprintf(stdout, "Tree Is Empty.\n"); return;}
    if(compareData(isItem, (*isRoot)->isItem) == -1){removeItem_R(&((*isRoot)->isLeft), isItem);}
    else if(compareData(isItem, (*isRoot)->isItem) == 1){removeItem_R(&((*isRoot)->isRight), isItem);}
    else{
        Node *thisNode = *isRoot;
        if((*isRoot)->isLeft == NULL && (*isRoot)->isRight == NULL){
            if((*isRoot)->isCount == 1){
                free((*isRoot)->isItem); (*isRoot)->isItem = NULL;
                free(*isRoot); *isRoot = NULL;
            }
            else{(*isRoot)->isCount--;}
        } else if((*isRoot)->isLeft != NULL && (*isRoot)->isRight != NULL){
            if((*isRoot)->isCount == 1){
                Node *findNode = thisNode->isRight;
                bool hasChildren = (findNode->isLeft) ? true : false;
                while(findNode->isLeft != NULL){findNode = findNode->isLeft;}
                Node *isParent = parentNode(&thisNode, findNode->isItem);
                free((*isRoot)->isItem); (*isRoot)->isItem = NULL;
                (*isRoot)->isItem = calloc(1, sizeof(findNode->isItem)); if((*isRoot)->isItem == NULL){fprintf(stdout, "Memeory Allocation Failed.\n"); return;}
                memcpy((*isRoot)->isItem, findNode->isItem, sizeof(findNode->isItem));
                (*isRoot)->isCount = findNode->isCount;
                removeItem_R(&findNode, findNode->isItem);
                (hasChildren) ? (isParent->isLeft = NULL) : ((*isRoot)->isRight = NULL);
            }
            else{(*isRoot)->isCount--;}
        } else if((*isRoot)->isLeft != NULL && (*isRoot)->isRight == NULL){
            if((*isRoot)->isCount == 1){
                *isRoot = (*isRoot)->isLeft;
                free(thisNode->isItem); thisNode->isItem = NULL;
                free(thisNode); thisNode = NULL;
            }
            else{(*isRoot)->isCount--;}
        }else if((*isRoot)->isLeft == NULL && (*isRoot)->isRight != NULL){
            if((*isRoot)->isCount == 1){
                *isRoot = (*isRoot)->isRight;
                free(thisNode->isItem); thisNode->isItem = NULL;
                free(thisNode); thisNode = NULL;
            }
            else{(*isRoot)->isCount--;}
        }
    }
    return;
}

Node *parentNode(Node **isRoot, void *isItem){
    if(*isRoot == NULL){fprintf(stdout, "Tree is empty"); return NULL;}
    if(((*isRoot)->isLeft != NULL && compareData(isItem, (*isRoot)->isLeft->isItem) == 0) || ((*isRoot)->isRight != NULL && compareData(isItem, (*isRoot)->isRight->isItem) == 0)){return (*isRoot);}
    if(compareData(isItem, (*isRoot)->isItem) == -1){return parentNode(&(*isRoot)->isLeft, isItem);}
    else if(compareData(isItem, (*isRoot)->isItem) == 1){return parentNode(&(*isRoot)->isRight, isItem);}
    return NULL;
}

Node *isItem_I(Node **isRoot, void *isItem){
    if(*isRoot == NULL){fprintf(stdout, "Tree Is Empty.\n"); return false;}
    Node *isCurrent = *isRoot;
    while(isCurrent != NULL){
        if(compareData(isItem, isCurrent->isItem) == -1){isCurrent = isCurrent->isLeft;}
        else if(compareData(isItem, isCurrent->isItem) == 1){isCurrent = isCurrent->isRight;}
        else if(compareData(isItem, isCurrent->isItem) == 0){return isCurrent;}
    }
    return NULL;
}

Node *isItem_R(Node **isRoot, void *isItem){
    if(*isRoot == NULL){fprintf(stdout, "Tree is empty"); return NULL;}
    if(compareData(isItem, (*isRoot)->isItem) == 0){return *isRoot;}
    else if(compareData(isItem, (*isRoot)->isItem) == -1){return isItem_R(&(*isRoot)->isLeft, isItem);}
    else if(compareData(isItem, (*isRoot)->isItem) == 1){return isItem_R(&(*isRoot)->isRight, isItem);}
    return NULL;
}

bool containsItem_I(Node **isRoot, void *isItem){
    if(*isRoot == NULL){fprintf(stdout, "Tree Is Empty.\n"); return false;}
    Node *isCurrent = *isRoot;
    while(isCurrent != NULL){
        if(compareData(isItem, isCurrent->isItem) == -1){isCurrent = isCurrent->isLeft;}
        else if(compareData(isItem, isCurrent->isItem) == 1){isCurrent = isCurrent->isRight;}
        else if(compareData(isItem, isCurrent->isItem) == 0){return true;}
    }
    return false;
}

bool containsItem_R(Node **isRoot, void *isItem){
    if(*isRoot == NULL){fprintf(stdout, "Tree Is Empty.\n"); return false;}
    if(compareData(isItem, (*isRoot)->isItem) == 0){return true;}
    else if(compareData(isItem, (*isRoot)->isItem) == -1){containsItem_R(&((*isRoot)->isLeft), isItem);}
    else if(compareData(isItem, (*isRoot)->isItem) == 1){containsItem_R(&((*isRoot)->isRight), isItem);}
    return false;
}

void *isMin(Node **isRoot){
    if(*isRoot == NULL){fprintf(stdout, "Tree is empty"); return NULL;}
    Node *thisNode = *isRoot;
    while(thisNode->isLeft != NULL){thisNode = thisNode->isLeft;}
    return thisNode->isItem;
}

void *isMax(Node **isRoot){
    if(*isRoot == NULL){fprintf(stdout, "Tree is empty"); return NULL;}
    Node *thisNode = *isRoot;
    while(thisNode->isRight != NULL){thisNode = thisNode->isRight;}
    return thisNode->isItem;
}

void isRootToLeaf_R(Node **isRoot, void **isItem, int nodeCount){
    if(*isRoot == NULL){fprintf(stdout, "Tree is empty"); return;}
    (nodeCount == 0) && (isItem = calloc(isSize_R(&(*isRoot)), sizeof(void *)));
    isItem[nodeCount] = calloc(1,sizeof((*isRoot)->isItem));
    memcpy(isItem[nodeCount++], (*isRoot)->isItem, sizeof((*isRoot)->isItem));
    if((*isRoot)->isLeft == NULL && (*isRoot)->isRight == NULL){
        for(int thisIndex = 0; thisIndex < nodeCount; thisIndex++){
            (thisIndex != nodeCount - 1) ? printRootToLeaf(isItem[thisIndex], false) : printRootToLeaf(isItem[thisIndex], true);
        }
        printf("\n");
    } else{
        isRootToLeaf_R(&((*isRoot)->isLeft), isItem, nodeCount);
        isRootToLeaf_R(&((*isRoot)->isRight), isItem, nodeCount);
    }
    return;
}

bool hasPathSum_R(Node **isRoot, int pathSum){
    if(*isRoot == NULL){return (pathSum == 0);}
    else{
        int getSum = pathSum - *(int*)(*isRoot)->isItem;
        return(hasPathSum_R(&(*isRoot)->isLeft, getSum) || hasPathSum_R(&(*isRoot)->isRight, getSum));
    }
}

bool isIdenticalTrees_R(Node **firstRoot, Node **secondRoot){
    if(*firstRoot == NULL && *secondRoot == NULL){return true;}
    else if(*firstRoot != NULL && *secondRoot == NULL || *firstRoot == NULL && *secondRoot != NULL){return false;}
    else if(*firstRoot != NULL && *secondRoot != NULL){return(compareData((*firstRoot)->isItem, (*secondRoot)->isItem) == 0 && isIdenticalTrees_R(&(*firstRoot)->isLeft, &(*secondRoot)->isLeft) && isIdenticalTrees_R(&(*firstRoot)->isRight, &(*secondRoot)->isRight));}
    return true;
}

void *isNthSmallest_R(Node **isRoot, int nthValue){
    if(*isRoot == NULL){fprintf(stdout, "Tree is empty"); return NULL;}
    int lSize = isSize_R(&(*isRoot)->isLeft) + 1;
    if(nthValue == lSize){return (*isRoot)->isItem;}
    else if( nthValue < lSize){return isNthSmallest_R(&(*isRoot)->isLeft, nthValue);}
    else if(nthValue > lSize){return isNthSmallest_R(&(*isRoot)->isRight, nthValue - lSize);}
    return NULL;
}

void *isNextGreatestItem_R(Node **isRoot, Node **refRoot, void *isItem){
    if(*isRoot == NULL){fprintf(stdout, "Tree is empty"); return NULL;}
    if(compareData(isItem, (*isRoot)->isItem) == 0){
        Node *isParent = parentNode(&(*refRoot), (*isRoot)->isItem);
        if((*isRoot)->isRight != NULL){
            (*isRoot) = (*isRoot)->isRight;
            while((*isRoot)->isLeft != NULL){(*isRoot) = (*isRoot)->isLeft;}
            return (*isRoot)->isItem;
        }
        else if(isParent->isLeft != NULL && compareData(isParent->isLeft->isItem, (*isRoot)->isItem) == 0){return isParent->isItem;}
        else if(isParent->isRight != NULL && compareData(isParent->isRight->isItem, (*isRoot)->isItem) == 0){
            bool foundNextGreatest = false;
            isParent = parentNode(&(*refRoot), isParent->isItem);
            while(!foundNextGreatest){
                if(compareData(isParent->isItem, (*isRoot)->isItem) == 1 || compareData(isParent->isItem, (*refRoot)->isItem) == 0){break;}
                isParent = parentNode(&(*refRoot), isParent->isItem);
            }
            return (compareData((*isRoot)->isItem, isParent->isItem) == 1) ? NULL : isParent->isItem;
        }
        else{return NULL;}
    }
    else if(compareData(isItem, (*isRoot)->isItem) == -1){return isNextGreatestItem_R(&(*isRoot)->isLeft, &(*refRoot), isItem);}
    else if(compareData(isItem, (*isRoot)->isItem) == 1){return isNextGreatestItem_R(&(*isRoot)->isRight, &(*refRoot), isItem);}
    return NULL;
}

int isSize_R(Node **isRoot){
    if(*isRoot == NULL){return 0;} else{return isSize_R(&(*isRoot)->isLeft) + isSize_R(&(*isRoot)->isRight) + 1;}
}

int isHeight_R(Node **isRoot){
    if(*isRoot == NULL){return 0;}
    int lHeight = isHeight_R(&(*isRoot)->isLeft);
    int rHeight = isHeight_R(&(*isRoot)->isRight);
    return (lHeight > rHeight) ? ++lHeight: ++rHeight;
}

void isPreOrderTraversal_I(Node **isRoot){
    if(*isRoot == NULL){return;}
    Node *isCurrent = NULL;
    Node **isEntry = calloc((*isRoot)->isCount, sizeof(Node *)); if(isEntry == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    int isIndex = 0;
    *isEntry = *isRoot;
    while(isIndex != -1){
        isCurrent = *(isEntry + (isIndex--)); displayData(isCurrent->isItem, false);
        if(isCurrent->isRight != NULL){*(isEntry + (++isIndex)) = isCurrent->isRight;}
        if(isCurrent->isLeft != NULL){*(isEntry + (++isIndex)) = isCurrent->isLeft;}
    }
    free(isEntry); isEntry = NULL;
    return;
}

void isPreOrderTraversal_R(Node **isRoot){
    if(*isRoot == NULL){return;}
    displayData((*isRoot)->isItem, false);
    isPreOrderTraversal_R(&(*isRoot)->isLeft);
    isPreOrderTraversal_R(&(*isRoot)->isRight);
    return;
}

void isPostOrderTraversal_I(Node **isRoot){
    if(*isRoot == NULL){return;}
    Node *isCurrent = NULL;
    Node **isEntry = calloc((*isRoot)->isCount, sizeof(Node *)); if(isEntry == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    Node **isOrder = calloc((*isRoot)->isCount, sizeof(Node *)); if(isOrder == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    int isEntryIndex = 0, isOrderIndex = -1;
    *isEntry = *isRoot;
    while(isEntryIndex != -1){
        isCurrent = *(isEntry + (isEntryIndex--));
        *(isOrder + (++isOrderIndex)) = isCurrent;
        if(isCurrent->isLeft != NULL){*(isEntry + (++isEntryIndex)) = isCurrent->isLeft;}
        if(isCurrent->isRight != NULL){*(isEntry + (++isEntryIndex)) = isCurrent->isRight;}
    }
    while(isOrderIndex != -1){displayData((*(isOrder + (isOrderIndex--)))->isItem, false);}
    free(isEntry); isEntry = NULL; free(isOrder); isOrder = NULL;
    return;
}

void isPostOrderTraversal_R(Node **isRoot){
    if(*isRoot == NULL){return;}
    isPostOrderTraversal_R(&(*isRoot)->isLeft);
    isPostOrderTraversal_R(&(*isRoot)->isRight);
    displayData((*isRoot)->isItem, false);
    return;
}

void isInOrderTraversal_I(Node **isRoot){
    if(*isRoot == NULL){return;}
    Node *isCurrent = *isRoot;
    Node **isEntry = calloc((*isRoot)->isCount, sizeof(Node *)); if(isEntry == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    int isIndex = -1;
    while(isCurrent != NULL || isIndex != -1){
        while(isCurrent != NULL){*(isEntry + (++isIndex)) = isCurrent; isCurrent = isCurrent->isLeft;}
        isCurrent = *(isEntry + (isIndex--)); displayData(isCurrent->isItem, false);
        isCurrent = isCurrent->isRight;
    }
    free(isEntry); isEntry = NULL;
    return;
}

void isInOrderTraversal_R(Node **isRoot){
    if(*isRoot == NULL){return;}
    isInOrderTraversal_R(&(*isRoot)->isLeft);
    displayData((*isRoot)->isItem, false);
    isInOrderTraversal_R(&(*isRoot)->isRight);
    return;
}

int compareData(void *getData, void *parentData){
    int isItem = *(int *)getData, pData = *(int *)parentData;
    if(isItem < pData){return -1;}
    else if(isItem > pData){return 1;}
    else{return 0;}
}

void printRootToLeaf(void *isData, bool isLast){
    printf((!isLast) ? "%d -> " : "%d\n", *(int *)isData);
}

void displayData(void *isData, bool isLast){
    (isData) ? printf((!isLast) ? "%d -> " : "%d\n", *(int *)isData) : printf("NULL\n");
}