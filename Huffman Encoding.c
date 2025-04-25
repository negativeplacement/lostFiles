#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Huffman{
    char **isItem, **itemCode;
    int itemCount, *itemFrequncy, *itemBits, avgItemBit;
}Huffman;

typedef struct Node{
    char *isItem;
    int isFrequency;
    struct Node *isLeft, *isRight;
}Node;

void sortItems(Huffman *isHuffman);
void manualInputItems(Huffman *isHuffman, Node **isRoot);
char *stringInput(int isLimit);
void fileInputItems(Huffman *isHuffman, Node **isRoot);
void insertItem(Node **firstRoot, Node **secondRoot, char **isItem, size_t *isFrequency);
void insertProcedure(Huffman *isHuffman, Node **isRoot);
void morrisTraversal(Huffman *isHuffman, Node **isRoot);
char *encryptMessage(Huffman *isHuffman, char *isMessage);
char *decryptCode(Huffman *isHuffman, char *isCode);
bool containItem(Huffman *isHuffman, char *isItem);
void decimateHuffmanTree(Node **isRoot);

void displayPreOrder(Node **isRoot);
void displayPostOrder(Node **isRoot);
void displayInOrder(Node **isRoot);
void printValue(void *isData);

int main(int argc, char *argv[]){
    Huffman *isHuffman = calloc(1, sizeof(Huffman));
    if(isHuffman == NULL){fprintf(stderr, "Memory Allocation Failed"); exit(EXIT_FAILURE);}
    Node *isRoot = NULL;
    size_t totalBits = 0;
    //manualInputItems(isHuffman, &isRoot);
    fileInputItems(isHuffman, &isRoot);
    for(int thisItem = 0; thisItem < isHuffman->itemCount; totalBits += isHuffman->itemBits[thisItem] * isHuffman->itemFrequncy[thisItem], thisItem++);
    isHuffman->avgItemBit = totalBits / isRoot->isFrequency;
    
    //char *message = calloc(42, sizeof(char));
    //message =  "111100011010011111";
    //printf("%s", decryptCode(isHuffman, message));
    //displayInOrder(&isRoot);

    decimateHuffmanTree(&isRoot);
    for(int thisItem = 0; thisItem < isHuffman->itemCount; thisItem++){
        free(isHuffman->isItem[thisItem]);
        isHuffman->isItem[thisItem] = NULL;
        free(isHuffman->itemCode[thisItem]);
        isHuffman->itemCode[thisItem] = NULL;
    }
    free(isHuffman->isItem); isHuffman->isItem = NULL; free(isHuffman->itemCode); isHuffman->itemCode = NULL;
    free(isHuffman->itemFrequncy); isHuffman->itemFrequncy = NULL; free(isHuffman->itemBits); isHuffman->itemBits = NULL;
    free(isHuffman); isHuffman = NULL;
    return 0;
}

void sortItems(Huffman *isHuffman){
    return;
}

void manualInputItems(Huffman *isHuffman, Node **isRoot){
    fprintf(stdout, "Enter the number of items: "); scanf("%zu", &isHuffman->itemCount);
    fprintf(stdout, "Enter items with frequency in ascending order\n");
    isHuffman->isItem = calloc(isHuffman->itemCount, sizeof(char *));
    if(isHuffman->isItem == NULL){fprintf(stderr, "Memory Allocation Failed"); exit(EXIT_FAILURE);}
    isHuffman->itemFrequncy = calloc(isHuffman->itemCount, sizeof(size_t));
    if(isHuffman->itemFrequncy == NULL){fprintf(stderr, "Memory Allocation Failed"); exit(EXIT_FAILURE);}
    for(size_t thisItem = 0; thisItem < isHuffman->itemCount; thisItem++){
        isHuffman->isItem[thisItem] = calloc(32, sizeof(char)); // Fix to collect string on unknown length
        fprintf(stdout, "\nEnter item %zu: ", (thisItem + 1));
        scanf("%s", isHuffman->isItem[thisItem]);
        fprintf(stdout, "Enter frequnecy for item %zu: ", (thisItem + 1));
        scanf("%zu", &isHuffman->itemFrequncy[thisItem]);
    }
    sortItems(isHuffman);
    insertProcedure(isHuffman, &(*isRoot));
    morrisTraversal(isHuffman, &(*isRoot));
    return;
}

char *stringInput(int isLimit){
    int isIndex = 0;
    int readChar;
    char *userInput = calloc(1, sizeof(char));
    if(userInput == NULL){fprintf(stderr, "Memory Allocation Failed"); exit(EXIT_FAILURE);}
    while((readChar = fgetc(stdin)) != EOF && readChar != '\n'){
        *(userInput + (isIndex++)) = readChar;
        char *extendString = realloc(userInput, sizeof(char) * (isIndex + 1));
        if(extendString == NULL){fprintf(stderr, "Memory Allocation Failed"); exit(EXIT_FAILURE);}
        userInput = extendString;
        if(isLimit > 0 && isIndex == isLimit){break;}
    }
    *(userInput + (isIndex)) = '\0';
    return userInput;
}

void fileInputItems(Huffman *isHuffman, Node **isRoot){
    int isIndex = 0;
    int isFileDescriptor, bytesRead;
    bool isNewEntry = false;
    fprintf(stdout, "Enter the directory of the file: ");
    char *isDir = stringInput(0);
    if((isFileDescriptor = open(isDir, O_RDONLY)) == -1){fprintf(stderr, "%s", strerror(errno)); exit(EXIT_FAILURE);}
    free(isDir); isDir = NULL;
    char *getItem = calloc(2, sizeof(char));
    FILE *filePtr = fdopen(isFileDescriptor, "r"); if(filePtr == NULL){fprintf(stderr, "%s", strerror(errno)); return;}
    if(setvbuf(filePtr, NULL, _IONBF, 2)){fprintf(stderr, "%s", strerror(errno)); return;}
    isHuffman->isItem = calloc(1, sizeof(char *)); if(isHuffman->isItem == NULL){fprintf(stderr, "Memory Allocation Failed"); exit(EXIT_FAILURE);}
    isHuffman->itemFrequncy = calloc(1, sizeof(size_t)); if(isHuffman->itemFrequncy == NULL){fprintf(stderr, "Memory Allocation Failed"); exit(EXIT_FAILURE);}
    while((bytesRead = read(isFileDescriptor, getItem, 1)) > 0){
        for(int thisItem = 0; thisItem < isHuffman->itemCount + 1; thisItem++){
            if(isHuffman->isItem[thisItem] && strcmp(isHuffman->isItem[thisItem], getItem) == 0){
                isHuffman->itemFrequncy[thisItem] += 1;
                break;
            } else if(thisItem == isHuffman->itemCount){
                isHuffman->isItem[isIndex] = calloc(strlen(getItem) + 1, sizeof(char));
                memcpy(isHuffman->isItem[isIndex], getItem, strlen(getItem) + 1);
                isHuffman->itemFrequncy[isIndex++] += 1;
                char **extendItemStorage = realloc(isHuffman->isItem, sizeof(char *) * (isIndex + 1));
                if(extendItemStorage == NULL){fprintf(stderr, "Memory Allocation Failed"); exit(EXIT_FAILURE);}
                *(extendItemStorage + isIndex) = NULL;
                isHuffman->isItem = extendItemStorage;
                size_t *extendFrequencyStorage = realloc(isHuffman->itemFrequncy, sizeof(size_t) * (isIndex + 1));
                if(extendFrequencyStorage == NULL){fprintf(stderr, "Memory Allocation Failed"); exit(EXIT_FAILURE);}
                *(extendFrequencyStorage + isIndex) = 0;
                isHuffman->itemFrequncy = extendFrequencyStorage;
                isNewEntry = true;
            }
        }
        (isNewEntry) && (isHuffman->itemCount++, isNewEntry = false);
    }
    if(bytesRead == -1){fprintf(stdout, "%s", strerror(errno)); return;}
    fclose(filePtr); close(isFileDescriptor);
    free(getItem); getItem = NULL;
    sortItems(isHuffman);
    insertProcedure(isHuffman, &(*isRoot));
    morrisTraversal(isHuffman, &(*isRoot));
    return;
}

void insertItem(Node **firstRoot, Node **secondRoot, char **isItem, size_t *isFrequency){
    Node *getRoot = calloc(1, sizeof(Node));
    if(getRoot == NULL){fprintf(stderr, "Memory Allocation Failed"); exit(EXIT_FAILURE);}
    Node *getLeft = calloc(1, sizeof(Node));
    if(getLeft == NULL){fprintf(stderr, "Memory Allocation Failed"); exit(EXIT_FAILURE);}
    Node *getRight = calloc(1, sizeof(Node));
    if(getRight == NULL){fprintf(stderr, "Memory Allocation Failed"); exit(EXIT_FAILURE);}
    getRoot->isItem = NULL;
    if(*firstRoot == NULL){
        getLeft->isItem = (*isItem) ? calloc(strlen(*isItem) + 1, sizeof(char)) : NULL;
        if(*isItem && getLeft->isItem == NULL){fprintf(stderr, "Memory Allocation Failed"); exit(EXIT_FAILURE);}
        memcpy(getLeft->isItem, *isItem, strlen(*isItem) + 1);
        getLeft->isFrequency = *(isFrequency++);
        getRight->isItem = (*(++isItem)) ? calloc(strlen(*isItem) + 1, sizeof(char)) : NULL;
        if(*isItem && getRight->isItem == NULL){fprintf(stderr, "Memory Allocation Failed"); exit(EXIT_FAILURE);}
        memcpy(getRight->isItem, *isItem, strlen(*isItem) + 1);
        getRight->isFrequency = *isFrequency;
        getRoot->isLeft = getLeft;
        getRoot->isRight = getRight;
        getRoot->isFrequency = getLeft->isFrequency + getRight->isFrequency;
        *firstRoot = getRoot;
    } else{
        if(*isItem){
            memcpy(getRight, *firstRoot, sizeof(**firstRoot));
            getLeft->isItem = calloc(strlen(*isItem) + 1, sizeof(char));
            if(getLeft->isItem == NULL){fprintf(stderr, "Memory Allocation Failed"); exit(EXIT_FAILURE);}
            memcpy(getLeft->isItem, *isItem, strlen(*isItem) + 1);
            getLeft->isFrequency = *isFrequency;
            getRoot->isLeft = getLeft;
            getRoot->isRight = getRight;
            getRoot->isFrequency = getLeft->isFrequency + getRight->isFrequency;
            *firstRoot = getRoot;
        } else if(*(++isItem)){
            memcpy(getLeft, *firstRoot, sizeof(**firstRoot));
            getRight->isItem = calloc(strlen(*isItem) + 1, sizeof(char));
            if(getRight->isItem == NULL){fprintf(stderr, "Memory Allocation Failed"); exit(EXIT_FAILURE);}
            memcpy(getRight->isItem, *isItem, strlen(*isItem) + 1);
            getRight->isFrequency = *(++isFrequency);
            getRoot->isLeft = getLeft;
            getRoot->isRight = getRight;
            getRoot->isFrequency = getLeft->isFrequency + getRight->isFrequency;
            *firstRoot = getRoot;
        } else{
            memcpy(getLeft, *firstRoot, sizeof(**firstRoot));
            memcpy(getRight, *secondRoot, sizeof(**secondRoot));
            getRoot->isLeft = getLeft;
            getRoot->isRight = getRight;
            getRoot->isFrequency = getLeft->isFrequency + getRight->isFrequency;
            *firstRoot = getRoot;
        }
    }
    return;
}

void insertProcedure(Huffman *isHuffman, Node **isRoot){
    size_t isIndex = 0, isTree = 0;
    Node **isOrderTrees = calloc((isHuffman->itemCount / 2), sizeof(Node *));
    if(isOrderTrees == NULL){fprintf(stderr, "Memory Allocation Failed"); exit(EXIT_FAILURE);}
    for(size_t procedureCount = 0; procedureCount < isHuffman->itemCount - 1; procedureCount++){
        if(*isRoot == NULL){
            insertItem(&(*isRoot), NULL, (char *[]){isHuffman->isItem[isIndex], isHuffman->isItem[isIndex + 1]}, (size_t[]){isHuffman->itemFrequncy[isIndex], isHuffman->itemFrequncy[isIndex + 1]});
            isIndex += 2;
        } else if(isTree > 1 && (*isRoot)->isFrequency > isHuffman->itemFrequncy[isIndex + 1] && isOrderTrees[1]->isFrequency < isHuffman->itemFrequncy[isIndex + 1] && isIndex < isHuffman->itemCount){ //Two preceding trees
            insertItem(&isOrderTrees[0], &isOrderTrees[1], (char *[]){NULL, NULL}, (size_t[]){isOrderTrees[0]->isFrequency, isOrderTrees[1]->isFrequency});
            free(isOrderTrees[1]);
            isOrderTrees[1] = NULL;
            memmove(isOrderTrees[1], isOrderTrees[2], sizeof(Node *) * (isTree - 2));
            for(size_t thisIndex = 0; thisIndex < (isHuffman->itemCount / 2); thisIndex++){
                if(isOrderTrees[thisIndex] == NULL || isOrderTrees[thisIndex + 1] == NULL){break;}
                else if(isOrderTrees[thisIndex + 1] != NULL && isOrderTrees[thisIndex]->isFrequency > isOrderTrees[thisIndex + 1]->isFrequency && thisIndex != ((isHuffman->itemCount / 2) - 1)){
                    Node *isTemp = isOrderTrees[thisIndex];
                    isOrderTrees[thisIndex] = isOrderTrees[thisIndex + 1];
                    isOrderTrees[thisIndex + 1] = isTemp;
                }
            }
            isTree--;
        } else if(isTree > 0 && (*isRoot)->isFrequency < isHuffman->itemFrequncy[isIndex] && isOrderTrees[0]->isFrequency < isHuffman->itemFrequncy[isIndex] && isIndex < isHuffman->itemCount){ //Two trees have frequencies less than next frequency
            if((*isRoot)->isFrequency > isOrderTrees[0]->isFrequency){ //New tree is first, Main tree is second
                insertItem(&isOrderTrees[0], &(*isRoot), (char *[]){NULL, NULL}, (size_t[]){isOrderTrees[0]->isFrequency, (*isRoot)->isFrequency});
                *isRoot = isOrderTrees[0];
                free(isOrderTrees[0]);
                isOrderTrees[0] = NULL;
                (isTree > 1) && (memmove(isOrderTrees[0], isOrderTrees[1], sizeof(Node *) * (isTree - 2)));
            }else{ //New tree is second, Main tree is first
                insertItem(&(*isRoot), &isOrderTrees[0], (char *[]){NULL, NULL}, (size_t[]){(*isRoot)->isFrequency, isOrderTrees[0]->isFrequency});
                free(isOrderTrees[0]);
                isOrderTrees[0] = NULL;
                (isTree > 1) && (memmove(isOrderTrees[0], isOrderTrees[1], sizeof(Node *) * (isTree - 2)));
            }
            isTree--;
        } else if(isTree > 0 && (*isRoot)->isFrequency > isHuffman->itemFrequncy[isIndex + 1] && isOrderTrees[0]->isFrequency < isHuffman->itemFrequncy[isIndex] && isIndex < isHuffman->itemCount){ //New tree is first;
            insertItem(&isOrderTrees[0], NULL, (char *[]){NULL, isHuffman->isItem[isIndex]}, (size_t[]){isOrderTrees[0]->isFrequency, isHuffman->itemFrequncy[isIndex]});
            for(size_t thisIndex = 0; thisIndex < (isHuffman->itemCount / 2); thisIndex++){
                if(isOrderTrees[thisIndex] == NULL || isOrderTrees[thisIndex + 1] == NULL){break;}
                else if(isOrderTrees[thisIndex + 1] != NULL && isOrderTrees[thisIndex]->isFrequency > isOrderTrees[thisIndex + 1]->isFrequency && thisIndex != ((isHuffman->itemCount / 2) - 1)){
                    Node *isTemp = isOrderTrees[thisIndex];
                    isOrderTrees[thisIndex] = isOrderTrees[thisIndex + 1];
                    isOrderTrees[thisIndex + 1] = isTemp;
                }
            }
            isIndex++;
        } else if(isTree > 0 && (*isRoot)->isFrequency > isHuffman->itemFrequncy[isIndex + 1] && isOrderTrees[0]->isFrequency < isHuffman->itemFrequncy[isIndex + 1] && isIndex < isHuffman->itemCount){ //New tree is second
            insertItem(&isOrderTrees[0], NULL, (char *[]){isHuffman->isItem[isIndex], NULL}, (size_t[]){isHuffman->itemFrequncy[isIndex], isOrderTrees[0]->isFrequency});
            for(size_t thisIndex = 0; thisIndex < (isHuffman->itemCount / 2); thisIndex++){
                if(isOrderTrees[thisIndex] == NULL || isOrderTrees[thisIndex + 1] == NULL){break;}
                else if(isOrderTrees[thisIndex + 1] != NULL && isOrderTrees[thisIndex]->isFrequency > isOrderTrees[thisIndex + 1]->isFrequency && thisIndex != ((isHuffman->itemCount / 2) - 1)){
                    Node *isTemp = isOrderTrees[thisIndex];
                    isOrderTrees[thisIndex] = isOrderTrees[thisIndex + 1];
                    isOrderTrees[thisIndex + 1] = isTemp;
                }
            }
            isIndex++;
        } else if((*isRoot)->isFrequency < isHuffman->itemFrequncy[isIndex] && isIndex < isHuffman->itemCount){ //Main tree is first
            insertItem(&(*isRoot), NULL, (char *[]){NULL, isHuffman->isItem[isIndex]}, (size_t[]){(*isRoot)->isFrequency, isHuffman->itemFrequncy[isIndex]});
            isIndex++;
        } else if((*isRoot)->isFrequency > isHuffman->itemFrequncy[isIndex] && (isIndex == isHuffman->itemCount - 1)){ //Last Frequency: Main tree is second
            insertItem(&(*isRoot), NULL, (char *[]){isHuffman->isItem[isIndex], NULL}, (size_t[]){isHuffman->itemFrequncy[isIndex], (*isRoot)->isFrequency});
            isIndex++;
        } else if((*isRoot)->isFrequency < isHuffman->itemFrequncy[isIndex + 1] && isIndex < isHuffman->itemCount - 1){ //Main tree is second
            insertItem(&(*isRoot), NULL, (char *[]){isHuffman->isItem[isIndex], NULL}, (size_t[]){isHuffman->itemFrequncy[isIndex], (*isRoot)->isFrequency});
            isIndex++;
        } else if((*isRoot)->isFrequency > isHuffman->itemFrequncy[isIndex + 1] && isIndex < isHuffman->itemCount - 1){ //Main tree is past 2nd frequency...Create New Tree
            insertItem(&isOrderTrees[isTree], NULL, (char *[]){isHuffman->isItem[isIndex], isHuffman->isItem[isIndex + 1]}, (size_t[]){isHuffman->itemFrequncy[isIndex], isHuffman->itemFrequncy[isIndex + 1]});
            isIndex += 2;
            isTree++;
        } else if(isIndex >= isHuffman->itemCount){ //Only Trees Remanining
            if(isTree > 1 && isOrderTrees[2]->isFrequency > (*isRoot)->isFrequency){ //Main tree behind 2 smaller trees
                insertItem(&isOrderTrees[0], &isOrderTrees[1], (char *[]){NULL, NULL}, (size_t[]){isOrderTrees[0]->isFrequency, isOrderTrees[1]->isFrequency});
                free(isOrderTrees[1]);
                isOrderTrees[1] = NULL;
                memmove(isOrderTrees[1], isOrderTrees[2], sizeof(Node *) * (isTree - 2));
                for(size_t thisIndex = 0; thisIndex < (isHuffman->itemCount / 2); thisIndex++){
                    if(isOrderTrees[thisIndex] == NULL || isOrderTrees[thisIndex + 1] == NULL){break;}
                    else if(isOrderTrees[thisIndex + 1] != NULL && isOrderTrees[thisIndex]->isFrequency > isOrderTrees[thisIndex + 1]->isFrequency && thisIndex != ((isHuffman->itemCount / 2) - 1)){
                        Node *isTemp = isOrderTrees[thisIndex];
                        isOrderTrees[thisIndex] = isOrderTrees[thisIndex + 1];
                        isOrderTrees[thisIndex + 1] = isTemp;
                    }
                }
                isTree--;
            } else if(isTree > 1 && (*isRoot)->isFrequency < isOrderTrees[0]->isFrequency){ //Main tree is first
                insertItem(&(*isRoot), &isOrderTrees[0], (char *[]){NULL, NULL}, (size_t[]){(*isRoot)->isFrequency, isOrderTrees[0]->isFrequency});
                free(isOrderTrees[0]);
                isOrderTrees[0] = NULL;
                memmove(isOrderTrees[0], isOrderTrees[1], sizeof(Node *) * (isTree - 2));
                for(size_t thisIndex = 0; thisIndex < (isHuffman->itemCount / 2); thisIndex++){
                    if(isOrderTrees[thisIndex] == NULL || isOrderTrees[thisIndex + 1] == NULL){break;}
                    else if(isOrderTrees[thisIndex + 1] != NULL && isOrderTrees[thisIndex]->isFrequency > isOrderTrees[thisIndex + 1]->isFrequency && thisIndex != ((isHuffman->itemCount / 2) - 1)){
                        Node *isTemp = isOrderTrees[thisIndex];
                        isOrderTrees[thisIndex] = isOrderTrees[thisIndex + 1];
                        isOrderTrees[thisIndex + 1] = isTemp;
                    }
                }
                isTree--;
            } else if(isTree > 1 && (*isRoot)->isFrequency < isOrderTrees[2]->isFrequency){ //Main tree is second
                insertItem(&isOrderTrees[0], &(*isRoot), (char *[]){NULL, NULL}, (size_t[]){isOrderTrees[0]->isFrequency, (*isRoot)->isFrequency});
                *isRoot = isOrderTrees[0];
                free(isOrderTrees[0]);
                isOrderTrees[0] = NULL;
                memmove(isOrderTrees[0], isOrderTrees[1], sizeof(Node *) * (isTree - 2));
                for(size_t thisIndex = 0; thisIndex < (isHuffman->itemCount / 2); thisIndex++){
                    if(isOrderTrees[thisIndex] == NULL || isOrderTrees[thisIndex + 1] == NULL){break;}
                    else if(isOrderTrees[thisIndex + 1] != NULL && isOrderTrees[thisIndex]->isFrequency > isOrderTrees[thisIndex + 1]->isFrequency && thisIndex != ((isHuffman->itemCount / 2) - 1)){
                        Node *isTemp = isOrderTrees[thisIndex];
                        isOrderTrees[thisIndex] = isOrderTrees[thisIndex + 1];
                        isOrderTrees[thisIndex + 1] = isTemp;
                    }
                }
                isTree--;
            } else if((*isRoot)->isFrequency < isOrderTrees[0]->isFrequency){ //Merge Final Tree: Main Tree First
                insertItem(&(*isRoot), &isOrderTrees[0], (char *[]){NULL, NULL}, (size_t[]){(*isRoot)->isFrequency, isOrderTrees[0]->isFrequency});
                free(isOrderTrees[0]);
                isOrderTrees[0] = NULL;
                isTree--;
            } else if((*isRoot)->isFrequency > isOrderTrees[0]->isFrequency){ //Merge Final Tree: Main Tree Second
                insertItem(&isOrderTrees[0], &(*isRoot), (char *[]){NULL, NULL}, (size_t[]){isOrderTrees[0]->isFrequency, (*isRoot)->isFrequency});
                *isRoot = isOrderTrees[0];
                free(isOrderTrees[0]);
                isOrderTrees[0] = NULL;
                isTree--;
            }
        }
    }
    free(isOrderTrees);
    isOrderTrees = NULL;
    return;
}

void morrisTraversal(Huffman *isHuffman, Node **isRoot){
    if(*isRoot == NULL){fprintf(stdout, "Tree is empty"); return;}
    isHuffman->itemCode = calloc(isHuffman->itemCount, sizeof(char *));
    if(isHuffman->itemCode == NULL){fprintf(stderr, "Memory Allocation Failed"); exit(EXIT_FAILURE);}
    isHuffman->itemBits = calloc(isHuffman->itemCount, sizeof(size_t));
    if(isHuffman->itemBits == NULL){fprintf(stderr, "Memory Allocation Failed"); exit(EXIT_FAILURE);}
    Node *currentRoot = *isRoot, *previousRoot = NULL;
    size_t indexingCode = 0, isOneOfTwo = 0, isLeft = 0;
    char *huffmanTreeCode = calloc(isHuffman->itemCount, sizeof(char));
    if(huffmanTreeCode == NULL){fprintf(stderr, "Memory Allocation Failed"); exit(EXIT_FAILURE);}
    while(currentRoot){
        if(currentRoot->isLeft == NULL){
            *(huffmanTreeCode + indexingCode) = '\0';
            for(int thisItem = 0; thisItem < isHuffman->itemCount + 1; thisItem++){
                if(strcmp(isHuffman->isItem[thisItem], currentRoot->isItem) == 0){
                    isHuffman->itemCode[thisItem] = calloc(strlen(huffmanTreeCode) + 1, sizeof(char));
                    if(isHuffman->itemCode[thisItem] == NULL){fprintf(stderr, "Memory Allocation Failed"); exit(EXIT_FAILURE);}
                    strcpy(isHuffman->itemCode[thisItem], huffmanTreeCode);
                    isHuffman->itemBits[thisItem] = strlen(huffmanTreeCode);
                    break;
                }
            }
            currentRoot = currentRoot->isRight;
            --indexingCode;
            (isOneOfTwo  && !isLeft) && (--indexingCode, isOneOfTwo = 0);
            (indexingCode > 0 && currentRoot && currentRoot->isFrequency == (*isRoot)->isFrequency) && (indexingCode = 0);
        } else{
            previousRoot = currentRoot->isLeft;
            while(previousRoot->isRight != NULL && previousRoot->isRight != currentRoot){
                (previousRoot->isLeft && previousRoot->isLeft->isItem) && (isOneOfTwo = 1);
                previousRoot = previousRoot->isRight;
            }
            if(previousRoot->isRight == NULL){
                previousRoot->isRight = currentRoot;
                currentRoot = currentRoot->isLeft;
                *(huffmanTreeCode + (indexingCode++)) = '0';
                isLeft = 1;
            } else{
                previousRoot->isRight = NULL;
                currentRoot = currentRoot->isRight;
                *(huffmanTreeCode + (indexingCode++)) = '1';
                isLeft = 0;
            }
        }
    }
    return;
}

char *encryptMessage(Huffman *isHuffman, char *isMessage){
    size_t searchIndex = 0, isChar = 0;
    char *encryptedMessage = calloc(strlen(isMessage) + 1, sizeof(char)), *itemPtr = NULL;
    if(encryptedMessage == NULL){fprintf(stderr, "Memory Allocation Failed"); exit(EXIT_FAILURE);}
    memcpy(encryptedMessage, isMessage, strlen(isMessage) + 1);
    for(size_t thisItem = 0; thisItem < isHuffman->itemCount; thisItem++){
        while((itemPtr = strstr(encryptedMessage + searchIndex, isHuffman->isItem[thisItem])) != NULL){
            ptrdiff_t isIndex = itemPtr - encryptedMessage;
            ptrdiff_t itemEnd = isIndex + strlen(isHuffman->isItem[thisItem]);
            if(strlen(isHuffman->itemCode[thisItem]) > strlen(isHuffman->isItem[thisItem])){
                size_t moveCount = strlen(encryptedMessage) - itemEnd;
                char *isValid = realloc(encryptedMessage, sizeof(char) *(strlen(encryptedMessage) + strlen(isHuffman->itemCode[thisItem]) - strlen(isHuffman->isItem[thisItem]) + 1));
                if(isValid == NULL){fprintf(stderr, "Memory Allocation Failed"); exit(EXIT_FAILURE);}
                encryptedMessage = isValid;
                memmove(encryptedMessage + itemEnd + strlen(isHuffman->itemCode[thisItem]) - strlen(isHuffman->isItem[thisItem]), encryptedMessage + itemEnd,  sizeof(char) * moveCount);
                memcpy(encryptedMessage + isIndex, isHuffman->itemCode[thisItem], strlen(isHuffman->itemCode[thisItem]));
            }else if(strlen(isHuffman->itemCode[thisItem]) < strlen(isHuffman->isItem[thisItem])){
                size_t moveCount = strlen(encryptedMessage) - itemEnd, isResidue = (strlen(isHuffman->isItem[thisItem]) - strlen(isHuffman->itemCode[thisItem]));
                memmove(encryptedMessage + isIndex + strlen(isHuffman->itemCode[thisItem]), encryptedMessage + isIndex + strlen(isHuffman->isItem[thisItem]),  sizeof(char) * moveCount);
                memcpy(encryptedMessage + isIndex, isHuffman->itemCode[thisItem], strlen(isHuffman->itemCode[thisItem]));
                memset(encryptedMessage + strlen(encryptedMessage) - isResidue, '\0', sizeof(char) * isResidue);  // Then realloc?
            } else{
                memcpy(encryptedMessage + isIndex, isHuffman->itemCode[thisItem], strlen(isHuffman->itemCode[thisItem]));
            }
            searchIndex += isIndex + strlen(isHuffman->isItem[thisItem]);
        }
        free(itemPtr);
        itemPtr = NULL;
        searchIndex = 0;
    }
    while(encryptedMessage[isChar]){if(isalpha(encryptedMessage[isChar++])){return NULL;}}
    return encryptedMessage;
}

char *decryptCode(Huffman *isHuffman, char *isCode){
    size_t searchIndex = 0, isChar = 0;
    char *isMessage = calloc(strlen(isCode) + 1, sizeof(char)), *itemPtr = NULL;
    if(isMessage == NULL){fprintf(stderr, "Memory Allocation Failed"); exit(EXIT_FAILURE);}
    memcpy(isMessage, isCode, strlen(isCode) + 1);
    for(size_t thisItem = 0; thisItem < isHuffman->itemCount; thisItem++){
        while((itemPtr = strstr(isMessage + searchIndex, isHuffman->itemCode[thisItem])) != NULL){
            ptrdiff_t isIndex = itemPtr - isMessage;
            ptrdiff_t itemEnd = isIndex + strlen(isHuffman->itemCode[thisItem]);
            if(strlen(isHuffman->isItem[thisItem]) > strlen(isHuffman->itemCode[thisItem])){
                size_t moveCount = strlen(isMessage) - itemEnd;
                char *isValid = realloc(isMessage, sizeof(char) *(strlen(isMessage) + strlen(isHuffman->isItem[thisItem]) - strlen(isHuffman->itemCode[thisItem]) + 1));
                if(isValid == NULL){fprintf(stderr, "Memory Allocation Failed"); exit(EXIT_FAILURE);}
                isMessage = isValid;
                memmove(isMessage + itemEnd + strlen(isHuffman->isItem[thisItem]) - strlen(isHuffman->itemCode[thisItem]), isMessage + itemEnd,  sizeof(char) * moveCount);
                memcpy(isMessage + isIndex, isHuffman->isItem[thisItem], strlen(isHuffman->isItem[thisItem]));
            }else if(strlen(isHuffman->isItem[thisItem]) < strlen(isHuffman->itemCode[thisItem])){
                size_t moveCount = strlen(isMessage) - itemEnd, isResidue = (strlen(isHuffman->itemCode[thisItem]) - strlen(isHuffman->isItem[thisItem]));
                memmove(isMessage + isIndex + strlen(isHuffman->isItem[thisItem]), isMessage + isIndex + strlen(isHuffman->itemCode[thisItem]),  sizeof(char) * moveCount);
                memcpy(isMessage + isIndex, isHuffman->isItem[thisItem], strlen(isHuffman->isItem[thisItem]));
                memset(isMessage + strlen(isMessage) - isResidue, '\0', sizeof(char) * isResidue); // Then realloc?
            } else{
                memcpy(isMessage + isIndex, isHuffman->isItem[thisItem], strlen(isHuffman->isItem[thisItem]));
            }
            searchIndex += isIndex + strlen(isHuffman->itemCode[thisItem]);
        }
        free(itemPtr);
        itemPtr = NULL;
        searchIndex = 0;
    } // ? Check if there are remaining bits obviously not part of the tree if less than expected bits remove, if equal or greater than expected bit return null.
    while(isMessage[isChar]){
        if(isdigit(isMessage[isChar++])){
            return NULL;
        }
    }
    return isMessage;
}

bool containItem(Huffman *isHuffman, char *isItem){
    if(*isItem == '\0'){return false;}
    for(size_t isIndex = 0; isIndex < isHuffman->itemCount; isIndex++){if(strcmp(isHuffman->isItem[isIndex], isItem) == 0){return true;}}
    return false;
}

void decimateHuffmanTree(Node **isRoot){
    if(*isRoot == NULL){fprintf(stdout, "Tree is empty"); return;}
    Node *currentRoot = *isRoot, *previousRoot = NULL, *skewedRight = NULL;
    int isOneOfTwo = 0;
    while(currentRoot){
        if(currentRoot->isLeft == NULL){
            /*if(currentRoot->isRight == NULL){ Not Working?? Node isn't nulled out as frequency now has a random value.
                currentRoot->isFrequency = 0;
                free(currentRoot->isItem);
                currentRoot->isItem = NULL;
                free(currentRoot);
                currentRoot = NULL;
                break;
            }*/ 
            currentRoot = currentRoot->isRight;
            (isOneOfTwo) && (isOneOfTwo = 0);
        } else{
            previousRoot = currentRoot->isLeft;
            while(previousRoot->isRight != NULL && previousRoot->isRight != currentRoot){
                (previousRoot->isLeft && previousRoot->isLeft->isItem) && (isOneOfTwo = 1);
                previousRoot = previousRoot->isRight;
            }
            if(previousRoot->isRight == NULL){
                previousRoot->isRight = currentRoot;
                currentRoot = currentRoot->isLeft;
            } else{
                previousRoot->isRight = NULL;
                previousRoot->isLeft = NULL;
                free(previousRoot->isItem);
                previousRoot->isItem = NULL;
                free(previousRoot);
                previousRoot = NULL;
                if(isOneOfTwo && currentRoot->isLeft->isRight->isItem == NULL){
                    currentRoot->isLeft->isRight->isLeft = NULL;
                    currentRoot->isLeft->isRight->isRight = NULL;
                    free(currentRoot->isLeft->isRight);
                    currentRoot->isLeft->isRight = NULL;
                }
                if(isOneOfTwo && currentRoot->isLeft->isItem == NULL){
                    currentRoot->isLeft->isLeft = NULL;
                    currentRoot->isLeft->isRight = NULL;
                    free(currentRoot->isLeft);
                    currentRoot->isLeft = NULL;
                }
                currentRoot = currentRoot->isRight;
            }
        }
    }
    while(*isRoot){
        skewedRight = (*isRoot)->isRight;
        (*isRoot)->isRight = NULL;
        (*isRoot)->isLeft = NULL;
        ((*isRoot)->isItem) && (free((*isRoot)->isItem), (*isRoot)->isItem = NULL); // Alternative to solve issue
        free(*isRoot);
        *isRoot = NULL;
        *isRoot = skewedRight;
    }
    return;
}

size_t getHeight(Node **isRoot){
    if(*isRoot == NULL){return 0;}
    size_t lHeight = getHeight(&(*isRoot)->isLeft);
    size_t rHeight = getHeight(&(*isRoot)->isRight);
    return (lHeight > rHeight) ? lHeight + 1 : rHeight + 1;
}

void displayPreOrder(Node **isRoot){
    if(*isRoot == NULL){return;}
    printValue((*isRoot)->isItem);
    displayPreOrder(&(*isRoot)->isLeft);
    displayPreOrder(&(*isRoot)->isRight);
    return;
}

void displayPostOrder(Node **isRoot){
    if(*isRoot == NULL){return;}
    displayPostOrder(&(*isRoot)->isLeft);
    displayPostOrder(&(*isRoot)->isRight);
    printValue((*isRoot)->isItem);
    return;
}

void displayInOrder(Node **isRoot){
    if(*isRoot == NULL){return;}
    displayInOrder(&(*isRoot)->isLeft);
    printValue((*isRoot)->isItem);
    displayInOrder(&(*isRoot)->isRight);
    return;
}

void printValue(void *isData){
    (isData) ? printf("%s\n", (char *)isData) : printf("NULL\n");
}
