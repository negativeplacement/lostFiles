#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

typedef struct Graph{
    int isNodeCount, **isAdjacencyMatrix;
    char **isNodeList, **isAdjacencyList;
    bool isCyclic;
}Graph;

typedef struct Node{
    struct Node *isLeft, *isRight;
}Node;

char *stringInput(int isSize, int *isLength);
int *inputAdjacencyList(Graph *isGraph, int isLength);
void inputAdjacencyMatrix(Graph *isGraph, int isLength);
void fileInput(Graph *isGraph, char isReference);
void khansAlgorithm(Graph *isGraph);
void breadthFirstSearch(Graph *isGraph, int isNode, int *isNodeAdjacentCount);
void depthFirstSearch(Graph *isGraph, int isNode, int *isNodeAdjacentCount);
void dijkstrasAlgorithm(Graph *isGraph, int isNode);
void dijkstrasAlgorithm_MinHeap(Graph *isGraph, int isNode);
void primsAlgorithm(Graph *isGraph, int isNode);
void kruskalAlgorithm(Graph *isGraph);
void edmundsKarpAlgorithm(Graph *isGraph);
void displayNodeList(Graph *isGraph);
void displayAdjacencyList(Graph *isGraph);
void displayAdjacencyMatrix(Graph *isGraph);
void displayDynamicAdjacencyMatrix(Graph *isGraph, int *isNodeAdjacentCount);

int main(int argc, char *argv[]){
    Graph *isGraph = calloc(1, sizeof(Graph)); if(isGraph == NULL){fprintf(stdout, "Memory Allocation Failed\n"); return 1;}
    fprintf(stdout, "Enter The Number Of Vertices In The Graph: "); scanf(" %d%*c", &isGraph->isNodeCount);
    isGraph->isNodeList = calloc(isGraph->isNodeCount, sizeof(char*)); if(isGraph->isNodeList == NULL){fprintf(stdout, "Memory Allocation Failed\n"); return 1;}
    int isInputLength = 0, isNode = 0, isNodeLength = -1, isOption;
    char *isInput, *isPtr;
    fprintf(stdout, "Enter The Vertices/Nodes In Ascending/Alphabetical Order: "); isInput = stringInput(0, &isInputLength); if(isInput == NULL){return 1;}
    for(char *getNode = strtok_r(isInput, ",", &isPtr); getNode != NULL; getNode = strtok_r(NULL, ",", &isPtr)){
        isNodeLength = strlen(getNode) + 1;
        *(isGraph->isNodeList + isNode) = calloc(isNodeLength, sizeof(char)); if(*(isGraph->isNodeList + isNode) == NULL){fprintf(stdout, "Memory Allocation Failed\n"); return 1;}
        memcpy(*(isGraph->isNodeList + isNode), getNode, isNodeLength); isNode++;
        if(isNode == isGraph->isNodeCount){isNode = 0; break;}
    }
    *isInput = '\0'; isGraph->isCyclic = false;
    int *isNodeAdjacencyCount = NULL;
    fprintf(stdout, "Enter Adjacency List (L) Or Adjacency Matrix (M): "); scanf(" %c", isInput); *(isInput + 1) = '\0';
    if(*isInput == 'l' || *isInput == 'L'){isNodeAdjacencyCount = inputAdjacencyList(isGraph, isInputLength); if(isNodeAdjacencyCount == NULL){fprintf(stdout, "Memory Allocation Failed\n"); return 1;}}
    else if(*isInput == 'm' || *isInput == 'M'){inputAdjacencyMatrix(isGraph, isInputLength);}
    else{fprintf(stdout, "Invalid Option\n"); return 1;} *isInput = '\0';
    fprintf(stdout, "Enter the starting vertice: "); scanf(" %s", isInput);
    while(isNode < isGraph->isNodeCount){if(strcmp(*(isGraph->isNodeList + isNode), isInput) == 0){break;} isNode++;}
    if(isNode == isGraph->isNodeCount){fprintf(stdout, "Error: Node %s doesnt exist in graph\n", isInput); return 1;}
    primsAlgorithm(isGraph, isNode);
    /*fprintf(stdout, "\n<<Graph Theory>>\n1.Breadth First Search\n2.Depth First Search\n3.Dijkstras Algorithm\n4.Prims Algorithm\n5.Kruskal's Algorithm\n6.Adjacency List\n7.Adjacency Matrix\n\n");
    fprintf(stdout, "Select An Option: "); scanf("%d", &isOption);
    switch(isOption){
        case 1: breadthFirstSearch(isGraph, isNode, isNodeAdjacencyCount); break;
        case 2: depthFirstSearch(isGraph, isNode, isNodeAdjacencyCount);
            //free(isNodeAdjacencyCount); isNodeAdjacencyCount = NULL;
        break;
        case 3: dijkstrasAlgorithm(isGraph, isNode); break;
        case 4: primsAlgorithm(isGraph, isNode); break;
        case 5: kruskalAlgorithm(isGraph); break;
        case 6: displayAdjacencyList(isGraph); break;
        case 7: *isInput == 'l' || *isInput == 'L' ? displayDynamicAdjacencyMatrix(isGraph, isNodeAdjacencyCount) : displayAdjacencyMatrix(isGraph); break;
        default: fprintf(stdout, "Invalid Option\n"); break;
    }*/
    free(isInput); isInput = NULL;
    for(int thisNode = 0; thisNode < isGraph->isNodeCount; thisNode++){
        free(*(isGraph->isAdjacencyMatrix + thisNode)); *(isGraph->isAdjacencyMatrix + thisNode) = NULL;
        free(*(isGraph->isNodeList + thisNode)); *(isGraph->isNodeList + thisNode) = NULL;
        free(*(isGraph->isAdjacencyList + thisNode)); *(isGraph->isAdjacencyList + thisNode) = NULL;
    }
    free(isGraph->isAdjacencyMatrix); isGraph->isAdjacencyMatrix = NULL;
    free(isGraph->isNodeList); isGraph->isNodeList = NULL;
    free(isGraph->isAdjacencyList); isGraph->isAdjacencyList = NULL;
    free(isGraph); isGraph = NULL;
    return 0;
}

char *stringInput(int isSize, int *isLength){
    int isIndex = 0, isMemorySize = 1, readChar;
    char *userInput = calloc(isMemorySize, sizeof(char)); if(userInput == NULL){fprintf(stdout, "Memory Allocation Failed\n"); return NULL;}
    while((readChar = fgetc(stdin)) != EOF && readChar != '\n'){
        *(userInput + isIndex++) = readChar;
        if(isIndex == isMemorySize){
            isMemorySize *= 2; 
            char *extendString = realloc(userInput, sizeof(char) * isMemorySize); if(extendString == NULL){fprintf(stdout, "Memory Allocation Failed\n"); return NULL;}
            userInput = extendString;
        }
        if(isSize > 0 && isIndex == isSize){break;}
    }
    *(userInput + isIndex) = '\0'; *isLength = isIndex + 1;
    char *resizeString = realloc(userInput, sizeof(char) * (isIndex + 1)); if(resizeString == NULL){fprintf(stdout, "Memory Reallocation Failed\n"); return NULL;} userInput = resizeString;
    return userInput;
}

int *inputAdjacencyList(Graph *isGraph, int isLength){ //Enter - if the node doesnt direct to any node
    int *nodeAdjacencyCount = calloc(isGraph->isNodeCount, sizeof(int)); if(nodeAdjacencyCount == NULL){fprintf(stdout, "Memory Allocation Failed\n"); return NULL;}
    isGraph->isAdjacencyMatrix = calloc(isGraph->isNodeCount, sizeof(int *)); if(isGraph->isAdjacencyMatrix == NULL){fprintf(stdout, "Memory Allocation Failed\n"); return NULL;}
    isGraph->isAdjacencyList = calloc(isGraph->isNodeCount, sizeof(char *)); if(isGraph->isAdjacencyList == NULL){fprintf(stdout, "Memory Allocation Failed\n"); return NULL;}
    int isIndex = 0, isNeighbourNodes = 0, isAdjacencyListLength = -1;
    char *isPtr = NULL;
    for(int isNode = 0; isNode < isGraph->isNodeCount; isNode++){
        char *getAdjacencyList = calloc(isLength, sizeof(char)); if(getAdjacencyList == NULL){fprintf(stdout, "Memory Allocation Failed\n"); return NULL;}
        fprintf(stdout, "Enter the adjacency list for Node[%s]: ", *(isGraph->isNodeList + isNode)); scanf(" %[^\n]", getAdjacencyList);
        (strchr(getAdjacencyList, '-')) && (*getAdjacencyList = '\0', isNeighbourNodes = 1);
        isAdjacencyListLength = snprintf(NULL, 0, "E[%s] = {%s}", *(isGraph->isNodeList + isNode), getAdjacencyList); if(isAdjacencyListLength < 0){fprintf(stdout, "%s\n", strerror(errno)); return;}
        *(isGraph->isAdjacencyList + isNode) = calloc(isAdjacencyListLength + 1, sizeof(char)); if(*(isGraph->isAdjacencyList + isNode) == NULL){fprintf(stdout, "Memory Allocation Failed\n"); return NULL;}
        snprintf(*(isGraph->isAdjacencyList + isNode), isAdjacencyListLength + 1, "E[%s] = {%s}", *(isGraph->isNodeList + isNode), getAdjacencyList);
        *(isGraph->isAdjacencyMatrix + isNode) = calloc(isGraph->isNodeCount, sizeof(int)); if(*(isGraph->isAdjacencyMatrix + isNode) == NULL){fprintf(stdout, "Memory Allocation Failed\n"); return NULL;}
        for(char *getNode = strtok_r(getAdjacencyList, ",", &isPtr); getNode != NULL; getNode = strtok_r(NULL, ",", &isPtr)){
            for(int thisIndex = 0; thisIndex < isGraph->isNodeCount; thisIndex++){if(strcmp(*(isGraph->isNodeList + thisIndex), getNode) == 0){*(*((isGraph)->isAdjacencyMatrix + isNode) + isIndex) = thisIndex; isIndex++; break;}}
            isNeighbourNodes++;
        }
        int *resizeNodeAdjacencyEntry = realloc(*(isGraph->isAdjacencyMatrix + isNode), sizeof(int) * isNeighbourNodes); if(resizeNodeAdjacencyEntry == NULL){fprintf(stdout, "Memory Allocation Failed\n"); return NULL;}
        *(isGraph->isAdjacencyMatrix + isNode) = resizeNodeAdjacencyEntry; *(nodeAdjacencyCount + isNode) = *getAdjacencyList == '\0' ? 0 : isNeighbourNodes; free(getAdjacencyList); getAdjacencyList = NULL;
        isIndex = 0; isNeighbourNodes = 0; isAdjacencyListLength = -1; isPtr = NULL;
    }
    return nodeAdjacencyCount;
}

void inputAdjacencyMatrix(Graph *isGraph, int isLength){
    isGraph->isAdjacencyMatrix = calloc(isGraph->isNodeCount, sizeof(int *)); if(isGraph->isAdjacencyMatrix == NULL){fprintf(stdout, "Memory Allocation Failed\n"); return;}
    isGraph->isAdjacencyList = calloc(isGraph->isNodeCount, sizeof(char *)); if(isGraph->isAdjacencyList == NULL){fprintf(stdout, "Memory Allocation Failed\n"); return;}
    int isAdjacencyListLength = 0;
    for(int isNode = 0; isNode < isGraph->isNodeCount; isNode++){
        *(isGraph->isAdjacencyMatrix + isNode) = calloc(isGraph->isNodeCount, sizeof(int)); if(*(isGraph->isAdjacencyMatrix + isNode) == NULL){fprintf(stdout, "Memory Allocation Failed\n"); return;}
        char *isAdjacencyList = calloc(isLength + 10, sizeof(char)); if(isAdjacencyList == NULL){fprintf(stdout, "Memory Allocation Failed\n"); return;}
        isAdjacencyListLength = snprintf(isAdjacencyList, (isLength + 10), "E[%s] = {", *(isGraph->isNodeList + isNode)); if(isAdjacencyListLength < 0){fprintf(stdout, "%s\n", strerror(errno)); return;}
        for(int thisNode = 0; thisNode < isGraph->isNodeCount; thisNode++){
            fprintf(stdout, "Edge between Node [%s] and Node [%s]: ", *((isGraph)->isNodeList + isNode), *((isGraph)->isNodeList + thisNode)); scanf(" %d", &isGraph->isAdjacencyMatrix[isNode][thisNode]);
            if(*(*((isGraph)->isAdjacencyMatrix + isNode) + thisNode) != 0){isAdjacencyListLength += snprintf(isAdjacencyList + isAdjacencyListLength, (isLength + 10), "%s,", *(isGraph->isNodeList + thisNode));}
        }
        *(isAdjacencyList + (isAdjacencyListLength - 1)) == '{' ? snprintf(isAdjacencyList + isAdjacencyListLength, isLength + 10, "}") : snprintf(isAdjacencyList + (isAdjacencyListLength - 1), isLength + 10, "}"); isAdjacencyListLength++;
        char *resizeAdjacencyList = realloc(isAdjacencyList, sizeof(char) * isAdjacencyListLength); if(resizeAdjacencyList == NULL){fprintf(stdout, "Memory Allocation Failed\n"); return;} isAdjacencyList = resizeAdjacencyList;
        *(isGraph->isAdjacencyList + isNode) = calloc(isAdjacencyListLength, sizeof(char)); if(*(isGraph->isAdjacencyList + isNode) == NULL){fprintf(stdout, "Memory Allocation Failed\n"); return;}
        memcpy(*(isGraph->isAdjacencyList + isNode), isAdjacencyList, isAdjacencyListLength); free(isAdjacencyList); isAdjacencyList = NULL; isAdjacencyListLength = 0;
    }
    return;
}

void fileInput(Graph *isGraph, char isReference){
    if(isReference != 'L' && isReference != 'M'){fprintf(stdout, "Invalid Reference Method.\n"); return;}
    int isFileDescriptor; off_t isOffset = 0;
    if((isFileDescriptor = open("Demo.txt", O_RDONLY)) == -1){fprintf(stdout, "%s\n", strerror(errno)); return;}
    char isCharacter, *isAL = "<..>", *isAM = "<[]>", *isEnd = "<?>", *isConversionPtr;
    char *isStorage = calloc(2, sizeof(char)); if(isStorage == NULL){fprintf(stdout, "Memory Allocation Failed\n"); return;}
    int isBytesRead = 0, isStorageSize = 2, isWriterIndex = 0, isLine = 0, isNode = 0, isInitiateNode = -1, isMatrixIndex = 0, isListIndex = 0, isIdentifierIndex = 0, *isAdjacencyCount = NULL, isAdjacencyListLength = 0, isPlacementCost = 0;
    bool isIndicator = false, isEntry = false;
    FILE *isFilePtr = fdopen(isFileDescriptor, "r"); if(isFilePtr == NULL){fprintf(stdout, "%s\n", strerror(errno)); return;}
    if(setvbuf(isFilePtr, NULL, _IONBF, 2)){fclose(isFilePtr); fprintf(stdout, "%s", strerror(errno)); return;}
    if(lseek(isFileDescriptor, isOffset, SEEK_SET) == -1){close(isFileDescriptor); fprintf(stdout, "%s\n", strerror(errno)); return;}
    while((isBytesRead = read(isFileDescriptor, &isCharacter, 1)) > 0){
        if(isLine == 0){
            if(isCharacter == '\n'){isLine++; continue;}
            if(isIdentifierIndex == 4){isIdentifierIndex = 0; continue;}
            if(isReference == 'L'){
                if(isCharacter == *(isAL + isIdentifierIndex)){isIdentifierIndex++;} 
                else{fprintf(stdout, "Invalid Format Pointer, File Has Been Edited."); return;}
            } else{
                if(isCharacter == *(isAM + isIdentifierIndex)){isIdentifierIndex++;}
                else{fprintf(stdout, "Invalid Format Pointer, File Has Been Edited."); return;}
            }
            continue;
        }
        isCharacter == *(isEnd + isIdentifierIndex) ? (isIdentifierIndex++) : (isIdentifierIndex = 0);
        if(isIdentifierIndex == 3){break;}
        if(isReference == 'L'){
            if(isCharacter == '\n'){
                *(isStorage + isWriterIndex++) = '\0';
                if(isLine == 1){
                    errno = 0; isGraph->isNodeCount = strtol(isStorage, &isConversionPtr, 10);
                    if(errno == EINVAL){fprintf(stdout, "%s\n", strerror(errno)); return;}
                    if(errno == ERANGE){fprintf(stdout, "%s\n", strerror(errno)); return;}
                    if(isConversionPtr == isStorage){fprintf(stdout, "No Digits Were Found\n"); return;}
                    if(*isConversionPtr != '\0'){fprintf(stdout, "Conversion Stopped At '%s'; Non-Numeric Character Detected.\n", isConversionPtr);}
                    isGraph->isNodeList = calloc(isGraph->isNodeCount, sizeof(char*)); if(isGraph->isNodeList == NULL){fprintf(stdout, "Memory Allocation Failed\n"); return;}
                } else if(isLine == 2){
                    if(isIndicator){fprintf(stdout, "Error Invalid Format\n"); return;}
                } else if(isLine == 3){
                    for(int isIndex = 0; isIndex < isGraph->isNodeCount; isIndex++){if(strcmp(*(isGraph->isNodeList + isIndex), isStorage) == 0){isInitiateNode = isIndex; break;}}
                    if(isInitiateNode == -1){fprintf(stdout, "Error: Node %s Doesnt Exist In Graph\n", isStorage); return;}
                } else if(isLine == 4){
                    if(!isIndicator){fprintf(stdout, "Error Invalid Format\n"); return;}
                    isGraph->isAdjacencyList = calloc(isGraph->isNodeCount, sizeof(char *)); if(isGraph->isAdjacencyList == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
                    isGraph->isAdjacencyMatrix = calloc(isGraph->isNodeCount, sizeof(int *)); if(isGraph->isAdjacencyMatrix == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
                    *(isGraph->isAdjacencyList + isNode) = calloc(isGraph->isNodeCount + 10, sizeof(char)); if(*(isGraph->isAdjacencyList + isNode) == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
                    isAdjacencyCount = calloc(isGraph->isNodeCount, sizeof(int)); if(isAdjacencyCount == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
                } else if(isGraph->isNodeCount > 0 && isLine >= 5 && isLine < 5 + isGraph->isNodeCount){
                    if(isIndicator){fprintf(stdout, "Error Invalid Format\n"); return;}
                    char *resizeListEntry = realloc(*(isGraph->isAdjacencyList + isNode), sizeof(char) * isListIndex); if(resizeListEntry == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
                    int *resizeMatrixEntry = realloc(*(isGraph->isAdjacencyMatrix + isNode), sizeof(int) * (isMatrixIndex == 0 ? 1 : isMatrixIndex)); if(resizeMatrixEntry == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
                    *(isGraph->isAdjacencyList + isNode) = resizeListEntry; *(isGraph->isAdjacencyMatrix + isNode) = resizeMatrixEntry; *(isAdjacencyCount + isNode++) = isMatrixIndex;
                    *(isGraph->isAdjacencyList + isNode) = calloc(isGraph->isNodeCount + 10, sizeof(char));if(*(isGraph->isAdjacencyList + isNode) == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
                    isListIndex = 0; isMatrixIndex = 0;
                }
                isLine++; isIndicator = false; isWriterIndex = 0; continue;
            }
            if(isLine == 1){
                if(isCharacter == '='){isIndicator = true; continue;} (isIndicator) && (isCharacter != ' ' && (*(isStorage + isWriterIndex++) = isCharacter));
            } else if(isLine == 2){
                if(isCharacter == '{'){isIndicator = true; continue;}
                if(isIndicator){
                    if(isCharacter == ',' || isCharacter == '}'){
                        *(isStorage + isWriterIndex++) = '\0';
                        *(isGraph->isNodeList + isNode) = calloc(isWriterIndex + 1, sizeof(char)); if(*(isGraph->isNodeList + isNode) == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
                        memcpy(*(isGraph->isNodeList + isNode), isStorage, isWriterIndex + 1);
                        isNode++; isWriterIndex = 0; (isCharacter == '}') && (isIndicator = false, isNode = 0);
                    } else{*(isStorage + isWriterIndex++) = isCharacter;}
                }
            } else if(isLine == 3){
                if(isCharacter == '='){isIndicator = true; continue;} (isIndicator) && (isCharacter != ' ' && (*(isStorage + isWriterIndex++) = isCharacter));
            } else if(isLine == 4){
                if(isCharacter == ':'){isIndicator = true; continue;}
            } else if(isGraph->isNodeCount > 0 && isLine >= 5 && isLine < 5 + isGraph->isNodeCount){
                isGraph->isAdjacencyList[isNode][isListIndex++] = isCharacter;
                if(isCharacter == '['){*(isGraph->isAdjacencyMatrix + isNode) = calloc(isGraph->isNodeCount, sizeof(int)); if(*(isGraph->isAdjacencyMatrix + isNode) == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;} isIndicator = true; continue;}
                if(isIndicator){
                    if(isCharacter == ',' || isCharacter == ']'){
                        *(isStorage + isWriterIndex++) = '\0'; isWriterIndex = 0;// Check in loop if node read isnt part on list :)
                        for(int isIndex = 0; isIndex < isGraph->isNodeCount; isIndex++){if(strcmp(*(isGraph->isNodeList + isIndex), isStorage) == 0){*(*((isGraph)->isAdjacencyMatrix + isNode) + isMatrixIndex++) = isIndex; break;}}
                        (isCharacter == ']') && (isGraph->isAdjacencyList[isNode][isListIndex++] = '\0', isIndicator = false);
                    } else{*(isStorage + isWriterIndex++) = isCharacter;}
                }
            }
        } else{
            if(isCharacter == '\n'){
                *(isStorage + isWriterIndex++) = '\0';
                if(isLine == 1){
                    errno = 0; isGraph->isNodeCount = strtol(isStorage, &isConversionPtr, 10);
                    if(errno == EINVAL){fprintf(stdout, "%s\n", strerror(errno)); return;}
                    if(errno == ERANGE){fprintf(stdout, "%s\n", strerror(errno)); return;}
                    if(isConversionPtr == isStorage){fprintf(stdout, "No Digits Were Found\n"); return;}
                    if(*isConversionPtr != '\0'){fprintf(stdout, "Conversion Stopped At '%s'; Non-Numeric Character Detected.\n", isConversionPtr); return;}
                    isGraph->isNodeList = calloc(isGraph->isNodeCount, sizeof(char*)); if(isGraph->isNodeList == NULL){fprintf(stdout, "Memory Allocation Failed\n"); return;}
                } else if(isLine == 2){
                    if(isIndicator){fprintf(stdout, "Error Invalid Format\n"); return;}
                } else if(isLine == 3){
                    for(int isIndex = 0; isIndex < isGraph->isNodeCount; isIndex++){if(strcmp(*(isGraph->isNodeList + isIndex), isStorage) == 0){isInitiateNode = isIndex; break;}}
                    if(isInitiateNode == -1){fprintf(stdout, "Error: Node %s Doesnt Exist In Graph\n", isStorage); return;}    
                } else if(isLine == 4){
                    if(!isIndicator){fprintf(stdout, "Error Invalid Format\n"); return;}
                } else if(isLine == 5){
                    if(!isIndicator){fprintf(stdout, "Error Invalid Format\n"); return;}
                    isGraph->isAdjacencyList = calloc(isGraph->isNodeCount, sizeof(char *)); if(isGraph->isAdjacencyList == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
                    isGraph->isAdjacencyMatrix = calloc(isGraph->isNodeCount, sizeof(int *)); if(isGraph->isAdjacencyMatrix == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
                    *(isGraph->isAdjacencyList + isNode) = calloc(isGraph->isNodeCount + 10, sizeof(char)); if(*(isGraph->isAdjacencyList + isNode) == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
                    *(isGraph->isAdjacencyMatrix + isNode) = calloc(isGraph->isNodeCount, sizeof(int)); if(*(isGraph->isAdjacencyMatrix + isNode) == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
                    isAdjacencyListLength = snprintf(*(isGraph->isAdjacencyList + isNode), isGraph->isNodeCount + 10, "E[%s] = {", *(isGraph->isNodeList + isNode)); if(isAdjacencyListLength < 0){fprintf(stdout, "%s\n", strerror(errno)); return;}
                }else if(isGraph->isNodeCount > 0 && isLine >= 6 && isLine < 6 + isGraph->isNodeCount){
                    if(isIndicator){fprintf(stdout, "Error Invalid Format\n"); return;}
                    *(*(isGraph->isAdjacencyList + isNode) + (isAdjacencyListLength - 1)) == '{' ? snprintf(*(isGraph->isAdjacencyList + isNode) + isAdjacencyListLength, isGraph->isNodeCount + 10, "}") : snprintf(*(isGraph->isAdjacencyList + isNode) + (isAdjacencyListLength - 1), isGraph->isNodeCount + 10, "}"); isAdjacencyListLength++;
                    char *resizeListEntry = realloc(*(isGraph->isAdjacencyList + isNode), sizeof(char) * isAdjacencyListLength); if(resizeListEntry == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
                    *(isGraph->isAdjacencyList + isNode++) = resizeListEntry;
                    if(isLine < 5 + isGraph->isNodeCount){
                        *(isGraph->isAdjacencyList + isNode) = calloc(isGraph->isNodeCount + 10, sizeof(char)); if(*(isGraph->isAdjacencyList + isNode) == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
                        *(isGraph->isAdjacencyMatrix + isNode) = calloc(isGraph->isNodeCount, sizeof(int)); if(*(isGraph->isAdjacencyMatrix + isNode) == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
                        isAdjacencyListLength = snprintf(*(isGraph->isAdjacencyList + isNode), isGraph->isNodeCount + 10, "E[%s] = {", *(isGraph->isNodeList + isNode)); if(isAdjacencyListLength < 0){fprintf(stdout, "%s\n", strerror(errno)); return;}
                    }
                }
                isLine++; isIndicator = false; isWriterIndex = 0; continue;
            }
            if(isLine == 1){
                if(isCharacter == '='){isIndicator = true; continue;} (isIndicator) && (isCharacter != ' ' && (*(isStorage + isWriterIndex++) = isCharacter));
            } else if(isLine == 2){
                if(isCharacter == '{'){isIndicator = true; continue;}
                if(isIndicator){
                    if(isCharacter == ',' || isCharacter == '}'){
                        *(isStorage + isWriterIndex++) = '\0';
                        *(isGraph->isNodeList + isNode) = calloc(isWriterIndex + 1, sizeof(char)); if(*(isGraph->isNodeList + isNode) == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
                        memcpy(*(isGraph->isNodeList + isNode), isStorage, isWriterIndex + 1);
                        isNode++; isWriterIndex = 0; (isCharacter == '}') && (isIndicator = false, isNode = 0);
                    } else{*(isStorage + isWriterIndex++) = isCharacter;}
                }
            } else if(isLine == 3){
                if(isCharacter == '='){isIndicator = true; continue;} (isIndicator) && (isCharacter != ' ' && (*(isStorage + isWriterIndex++) = isCharacter));
            } else if(isLine == 4){
                if(isCharacter == ':'){isIndicator = true; continue;}
            } else if(isLine == 5){
                (isCharacter == '~') && (isIndicator = true);
            } else if(isGraph->isNodeCount > 0 && isLine >= 6 && isLine < 6 + isGraph->isNodeCount){
                if(isCharacter == '['){isIndicator = true; continue;}
                if(isCharacter == ']'){
                    *(isStorage + isWriterIndex) = '\0'; isWriterIndex = 0;
                    errno = 0; isPlacementCost = strtol(isStorage, &isConversionPtr, 10);
                    if(errno == EINVAL){fprintf(stdout, "%s\n", strerror(errno)); return;}
                    if(errno == ERANGE){fprintf(stdout, "%s\n", strerror(errno)); return;}
                    if(isConversionPtr == isStorage){fprintf(stdout, "No Digits Were Found\n"); return;}
                    if(*isConversionPtr != '\0'){fprintf(stdout, "Conversion Stopped At '%s'; Non-Numeric Character Detected.\n", isConversionPtr); return;}
                    if(isPlacementCost != 0){isAdjacencyListLength += snprintf(*(isGraph->isAdjacencyList + isNode) + isAdjacencyListLength, isGraph->isNodeCount + 10, "%s,", *(isGraph->isNodeList + isMatrixIndex));}
                    *(*((isGraph)->isAdjacencyMatrix + isNode) + isMatrixIndex) = isPlacementCost;
                    isMatrixIndex = 0; isIndicator = false; isEntry = false; continue;
                }
                if(isCharacter == '|'){
                    if(isEntry){
                        *(isStorage + isWriterIndex) = '\0'; isWriterIndex = 0;
                        errno = 0; isPlacementCost = strtol(isStorage, &isConversionPtr, 10);
                        if(errno == EINVAL){fprintf(stdout, "%s\n", strerror(errno)); return;}
                        if(errno == ERANGE){fprintf(stdout, "%s\n", strerror(errno)); return;}
                        if(isConversionPtr == isStorage){fprintf(stdout, "No Digits Were Found\n"); return;}
                        if(*isConversionPtr != '\0'){fprintf(stdout, "Conversion Stopped At '%s'; Non-Numeric Character Detected.\n", isConversionPtr); return;}
                        if(isPlacementCost != 0){isAdjacencyListLength += snprintf(*(isGraph->isAdjacencyList + isNode) + isAdjacencyListLength, isGraph->isNodeCount + 10, "%s,", *(isGraph->isNodeList + isMatrixIndex));}
                        *(*((isGraph)->isAdjacencyMatrix + isNode) + isMatrixIndex++) = isPlacementCost;
                    }
                    isEntry = true; continue;
                }
                if(isEntry){*(isStorage + isWriterIndex++) = isCharacter;}
            }
        }
        if(isWriterIndex == isStorageSize){isStorageSize *= 2; char *expandStorage = realloc(isStorage, sizeof(char) * isStorageSize); if(expandStorage == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;} isStorage = expandStorage;}
    }
    if(isBytesRead == -1){fprintf(stdout, "%s\n", strerror(errno)); return;}
    fclose(isFilePtr); close(isFileDescriptor); free(isStorage); isStorage = NULL;
    return;
}

void khansAlgorithm(Graph *isGraph){
    return;
}

void breadthFirstSearch(Graph *isGraph, int isNode, int *isNodeAdjacentCount){
    int *isQueue = calloc(isGraph->isNodeCount, sizeof(int)); if(isQueue == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    int *isVisited = calloc(isGraph->isNodeCount, sizeof(int));if(isVisited == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    int *isBFS = calloc(isGraph->isNodeCount, sizeof(int)); if(isBFS == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    int isFront = 0, isSize = 0, isCurrentNode = isNode, isIndex = 0, foundNodes = 0;
    *(isQueue + isSize++) = isCurrentNode;
    if(isNodeAdjacentCount == NULL){
        while(true){
            fprintf(stdout, "Queue: "); for(int isEntry = isFront; isEntry < isSize; fprintf(stdout, (isEntry != isSize -1) ? "%s, " : "%s\n", isGraph->isNodeList[isQueue[isEntry]]), isEntry++);
            if(*(isVisited + isCurrentNode) >= 0){
                *(isVisited + isCurrentNode) = 2; *(isBFS + isIndex++) = isCurrentNode; foundNodes++; isFront++;
                fprintf(stdout, "%s Dequeued\n", *(isGraph->isNodeList + isCurrentNode));
            }
            if(isFront > isSize && foundNodes != isGraph->isNodeCount){
                fprintf(stdout, "\nFind Node That Didn't Enter The Queue\n");
                for(int findNode = 0; findNode < isGraph->isNodeCount; findNode++){
                    if(*(isVisited + findNode) == 0){
                        *(isQueue + isSize++) = findNode; isCurrentNode = findNode;
                        fprintf(stdout, "%s Enqueued\n", *(isGraph->isNodeList + findNode));
                        break;
                    }
                }
            }
            if(foundNodes == isGraph->isNodeCount){break;}
            for(int thisAdjacent = 0; thisAdjacent < isGraph->isNodeCount; thisAdjacent++){
                if(*(isVisited + thisAdjacent) == 0 && isGraph->isAdjacencyMatrix[isCurrentNode][thisAdjacent] > 0){
                    *(isQueue + isSize++) = thisAdjacent; *(isVisited + thisAdjacent) = 1;
                    fprintf(stdout, "%s Pushed Onto The Stack\n", *(isGraph->isNodeList + thisAdjacent));
                }
                (thisAdjacent == isGraph->isNodeCount - 1) && (isCurrentNode = *(isQueue + isFront));
            }
        }
    } else{
        while(true){
            fprintf(stdout, "Queue: "); for(int isEntry = isFront; isEntry < isSize; fprintf(stdout, (isEntry != isSize - 1) ? "%s, " : "%s\n", isGraph->isNodeList[isQueue[isEntry]]), isEntry++);
            if(*(isVisited + isCurrentNode) >= 0){
                *(isVisited + isCurrentNode) = 2; *(isBFS + isIndex++) = isCurrentNode; foundNodes++; isFront++;
                fprintf(stdout, "%s Dequeued\n", *(isGraph->isNodeList + isCurrentNode));
            }
            if(isFront > isSize && foundNodes != isGraph->isNodeCount){
                fprintf(stdout, "\nFind Node That Didn't Enter The Queue\n");
                for(int findNode = 0; findNode < isGraph->isNodeCount; findNode++){
                    if(*(isVisited + findNode) == 0){
                        *(isQueue + isSize++) = findNode; isCurrentNode = findNode;
                        fprintf(stdout, "%s Enqueued\n", *(isGraph->isNodeList + findNode));
                        break;
                    }
                }
            }
            if(foundNodes == isGraph->isNodeCount){break;}
            (*(isNodeAdjacentCount + isCurrentNode) == 0) && (isCurrentNode = *(isQueue + isFront));
            for(int thisAdjacent = 0; thisAdjacent < *(isNodeAdjacentCount + isCurrentNode); thisAdjacent++){
                if(isVisited[isGraph->isAdjacencyMatrix[isCurrentNode][thisAdjacent]] == 0){
                    *(isQueue + isSize++) = isGraph->isAdjacencyMatrix[isCurrentNode][thisAdjacent]; isVisited[isGraph->isAdjacencyMatrix[isCurrentNode][thisAdjacent]] = 1;
                    fprintf(stdout, "%s Enqueued\n", isGraph->isNodeList[isGraph->isAdjacencyMatrix[isCurrentNode][thisAdjacent]]);
                }
                (thisAdjacent == *(isNodeAdjacentCount + isCurrentNode) - 1) && (isCurrentNode = *(isQueue + isFront));
            }
        }
    }
    fprintf(stdout, "\n<Procedure Complete>\n");
    fprintf(stdout, "BFS: "); for(int thisIndex = 0; thisIndex < isGraph->isNodeCount; thisIndex++){fprintf(stdout, (thisIndex != isGraph->isNodeCount -1) ? "%s -> " : "%s\n", isGraph->isNodeList[isBFS[thisIndex]]);}
    free(isQueue); isQueue = NULL; free(isVisited); isVisited = NULL; free(isBFS); isBFS = NULL;
    return;
}

void depthFirstSearch(Graph *isGraph, int isNode, int *isNodeAdjacentCount){
    int *isPreOrder = calloc(isGraph->isNodeCount, sizeof(int)); if(isPreOrder == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    int *isPostOrder = calloc(isGraph->isNodeCount, sizeof(int)); if(isPostOrder == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    int *isStack = calloc(isGraph->isNodeCount, sizeof(int)); if(isStack == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    int *isVisited = calloc(isGraph->isNodeCount, sizeof(int)); if(isVisited == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    int *isDFS = calloc(isGraph->isNodeCount, sizeof(int)); if(isDFS == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    int isSize = 0, isIndex = 0, isPrePost = 1, isCurrentNode = isNode, isStartNode = isNode;
    bool isFound = false;
    *(isStack + isSize++) = isCurrentNode;
    if(isNodeAdjacentCount == NULL){
        while(true){
            fprintf(stdout, "Stack: "); for(int isEntry = 0; isEntry < isSize; fprintf(stdout, isEntry == isSize - 1 ? "%s\n" : "%s ", isGraph->isNodeList[isStack[isEntry]]), isEntry++);
            if(*(isVisited + isCurrentNode) == 0){
                *(isVisited + isCurrentNode) = 1; *(isPreOrder + isCurrentNode) = isPrePost; *(isDFS + isIndex) = isCurrentNode; isPrePost++; isIndex++;
                fprintf(stdout, "Node: %s, Pre: %d\n", *(isGraph->isNodeList + isCurrentNode), isPrePost - 1);
            } else if(*(isVisited + isCurrentNode) == 1){
                *(isVisited + isCurrentNode) = 2; *(isPostOrder + isCurrentNode) = isPrePost; isSize--;
                fprintf(stdout, "Node %s Popped Off The Stack, Post: %d\n", *(isGraph->isNodeList + isCurrentNode), isPrePost);
                (isSize != 0) && (isCurrentNode = *(isStack + (isSize - 1)));
                fprintf(stdout, "Current Node: %s\n", *(isGraph->isNodeList + isCurrentNode));
                isPrePost++; continue;
            } else if(*(isVisited + isCurrentNode) == 2 && isCurrentNode != isStartNode){
                isSize--; (isSize != 0) && (isCurrentNode = *(isStack + (isSize - 1)));
            } else if(isCurrentNode == isStartNode && *(isVisited + isCurrentNode) == 2 && isPrePost != (isGraph->isNodeCount * 2) + 1){
                fprintf(stdout, "\nFind Node That Didn't Enter The Stack\n");
                for(int findNode = 0; findNode < isGraph->isNodeCount; findNode++){
                    if(*(isVisited + findNode) == 0){
                        *(isStack + isSize++) = findNode; isCurrentNode = findNode; isStartNode = findNode;
                        fprintf(stdout, "%s Pushed Onto The Stack\n", *((isGraph)->isNodeList + findNode));
                        break;
                    }
                }
            }
            if(isPrePost >= (isGraph->isNodeCount * 2)){break;}
            for(int thisAdjacent = isGraph->isNodeCount - 1; thisAdjacent >= 0; thisAdjacent--){
                if(*(isVisited + thisAdjacent) == 0 && *(*((isGraph)->isAdjacencyMatrix + isCurrentNode) + thisAdjacent) > 0){*(isStack + isSize++) = thisAdjacent; isFound = true; fprintf(stdout, "%s Pushed Onto The Stack\n", *(isGraph->isNodeList + thisAdjacent));}
                (thisAdjacent == 0 && isFound) && (isCurrentNode = *(isStack + (isSize - 1)), isFound = false);
            }
        }
    } else{
        while(true){
            fprintf(stdout, "Stack: "); for(int isEntry = 0; isEntry < isSize; fprintf(stdout, isEntry == isSize - 1 ? "%s\n" : "%s ", isGraph->isNodeList[isStack[isEntry]]), isEntry++);
            if(*(isVisited + isCurrentNode) == 0){
                *(isVisited + isCurrentNode) = 1; *(isPreOrder + isCurrentNode) = isPrePost; *(isDFS + isIndex) = isCurrentNode; isPrePost++; isIndex++;
                fprintf(stdout, "Node: %s, Pre: %d\n", *(isGraph->isNodeList + isCurrentNode), isPrePost - 1);
            } else if(*(isVisited + isCurrentNode) == 1){
                *(isVisited + isCurrentNode) = 2; *(isPostOrder + isCurrentNode) = isPrePost; isSize--;
                fprintf(stdout, "Node %s Popped Off The Stack, Post: %d\n", *(isGraph->isNodeList + isCurrentNode), isPrePost);
                (isSize != 0) && (isCurrentNode = *(isStack + (isSize - 1)));
                fprintf(stdout, "Current Node: %s\n", *(isGraph->isNodeList + isCurrentNode));
                isPrePost++; continue;
            } else if(*(isVisited + isCurrentNode) == 2 && isCurrentNode != isStartNode){
                isSize--; (isSize != 0) && (isCurrentNode = *(isStack + (isSize - 1)));
            } else if(isCurrentNode == isStartNode && *(isVisited + isCurrentNode) == 2 && isPrePost != (isGraph->isNodeCount * 2) + 1){
                fprintf(stdout, "\nFind Node That Didn't Enter The Stack\n");
                for(int findNode = 0; findNode < isGraph->isNodeCount; findNode++){
                    if(*(isVisited + findNode) == 0){
                        *(isStack + isSize++) = findNode; isCurrentNode = findNode; isStartNode = findNode;
                        fprintf(stdout, "%s Pushed Onto The Stack\n", *(isGraph->isNodeList + findNode));
                        break;
                    }
                }
            }
            if(isPrePost >= (isGraph->isNodeCount * 2)){break;}
            for(int thisAdjacent = *(isNodeAdjacentCount + isCurrentNode) - 1; thisAdjacent >= 0; thisAdjacent--){
                if(isVisited[isGraph->isAdjacencyMatrix[isCurrentNode][thisAdjacent]] == 0){
                    *(isStack + isSize++) = *(*((isGraph)->isAdjacencyMatrix + isCurrentNode) + thisAdjacent); isFound = true;
                    fprintf(stdout, "%s Pushed Onto The Stack\n", isGraph->isNodeList[isGraph->isAdjacencyMatrix[isCurrentNode][thisAdjacent]]);
                }
                (thisAdjacent == 0 && isFound) && (isCurrentNode = *(isStack + (isSize - 1)), isFound = false);
            }
        }
    }
    fprintf(stdout, "\n<Procedure Complete>\n");
    fprintf(stdout, "DFS: "); for(int isEntry = 0; isEntry < isGraph->isNodeCount; isEntry++){fprintf(stdout, (isEntry != isGraph->isNodeCount -1) ? "%s -> " : "%s\n", isGraph->isNodeList[isDFS[isEntry]]);}
    if(!isGraph->isCyclic){
        int maxIndex = 0, maxValue = INT_MIN, postIndex = 0, postCount = 0, isSorted = 0;
        fprintf(stdout, "Topological Sort: "); // Only valid for acyclic graphs
        while(!isSorted){
            if(postIndex == isGraph->isNodeCount - 1){
                (isPostOrder[postIndex] > maxValue) && (maxIndex = postIndex, maxValue = isPostOrder[postIndex]);
                isPostOrder[maxIndex] = -1;
                maxValue = INT_MIN;
                postCount++;
                printf((postCount != isGraph->isNodeCount) ? "%s -> " : "%s", isGraph->isNodeList[maxIndex]);
                postIndex = 0;
            }
            (isPostOrder[postIndex] > maxValue) && (maxIndex = postIndex, maxValue = isPostOrder[postIndex]);
            postIndex++;
            (postCount == isGraph->isNodeCount) && (isSorted = 1);
        }
    }
    free(isPreOrder); isPreOrder = NULL; free(isPostOrder); isPostOrder = NULL;
    free(isStack); isStack = NULL; free(isVisited); isVisited = NULL;
    free(isDFS); isDFS = NULL;
    return;
}

void dijkstrasAlgorithm(Graph *isGraph, int isNode){
    int *isCost = calloc(isGraph->isNodeCount, sizeof(int)); if(isCost == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    int *isParent = calloc(isGraph->isNodeCount, sizeof(int)); if(isParent == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    int *shortestPath = calloc(isGraph->isNodeCount, sizeof(int)); if(shortestPath == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    int isIndex = 0, isCurrentNode = isNode, isCurrentCost = 0, isSmallestIndex = 0, isMaximum = INT_MAX;
    *(isCost + isCurrentNode) = -1; *(isParent + isCurrentNode) = isCurrentNode; *(shortestPath + isIndex++) = isCurrentNode;
    while(isIndex != isGraph->isNodeCount){
        for(int thisAdjacent = 0; thisAdjacent < isGraph->isNodeCount; thisAdjacent++){
            if(isGraph->isAdjacencyMatrix[isCurrentNode][thisAdjacent] != 0 && *(isCost + thisAdjacent) == 0){
                *(isCost + thisAdjacent) = isGraph->isAdjacencyMatrix[isCurrentNode][thisAdjacent] + isCurrentCost;
                *(isParent + thisAdjacent) = isCurrentNode;
            } else if(isGraph->isAdjacencyMatrix[isCurrentNode][thisAdjacent] != 0 && isGraph->isAdjacencyMatrix[isCurrentNode][thisAdjacent] + isCurrentCost < *(isCost + thisAdjacent)){
                *(isCost + thisAdjacent) = isGraph->isAdjacencyMatrix[isCurrentNode][thisAdjacent] + isCurrentCost;
                *(isParent + thisAdjacent) = isCurrentNode;
            }
        }
        for(int isEntry = 0; isEntry < isGraph->isNodeCount; isEntry++){(*(isCost + isEntry) < isMaximum && *(isCost + isEntry) > 0) && (isMaximum = *(isCost + isEntry), isSmallestIndex = isEntry);}
        isCurrentCost = *(isCost + isSmallestIndex); *(shortestPath + isIndex++) = isSmallestIndex; isCurrentNode = isSmallestIndex; *(isCost + isSmallestIndex) = -1; isSmallestIndex = 0; isMaximum = INT_MAX;
    }
    fprintf(stdout, "Delete: "); for(int thisNode = 0; thisNode < isGraph->isNodeCount; thisNode++){fprintf(stdout, (thisNode != isGraph->isNodeCount - 1) ? "%s -> " : "%s\n", isGraph->isNodeList[shortestPath[thisNode]]);}
    fprintf(stdout, "Parent: "); for(int thisNode = 0; thisNode < isGraph->isNodeCount; thisNode++){fprintf(stdout, (thisNode != isGraph->isNodeCount - 1) ? "%s -> " : "%s\n", isGraph->isNodeList[isParent[shortestPath[thisNode]]]);}
    free(isCost); isCost = NULL; free(isParent); isParent = NULL; free(shortestPath); shortestPath = NULL;
    return;
}

void dijkstrasAlgorithm_MinHeap(Graph *isGraph, int isNode){
    return;
}

void primsAlgorithm(Graph *isGraph, int isNode){
    int *isCost = calloc(isGraph->isNodeCount, sizeof(int)); if(isCost == NULL){fprintf(stdout, "Memory Allocation Failed/\n"); return;}
    int *isParent = calloc(isGraph->isNodeCount, sizeof(int)); if(isParent == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    int *shortestPath = calloc(isGraph->isNodeCount, sizeof(int)); if(shortestPath == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    int isIndex = 0, isCurrentNode = isNode, isCurrentCost = 0, isSmallestIndex = 0, isMaximum = INT_MAX;
    *(isCost + isCurrentNode) = -1; *(isParent + isCurrentNode) = isCurrentNode; *(shortestPath + isIndex++) = isCurrentNode;
    while(isIndex != isGraph->isNodeCount){
        for(int thisAdjacent = 0; thisAdjacent < isGraph->isNodeCount; thisAdjacent++){
            if(isGraph->isAdjacencyMatrix[isCurrentNode][thisAdjacent] != 0 && *(isCost + thisAdjacent) == 0){
                *(isCost + thisAdjacent) = isGraph->isAdjacencyMatrix[isCurrentNode][thisAdjacent];
                *(isParent + thisAdjacent) = isCurrentNode;
            } else if(isGraph->isAdjacencyMatrix[isCurrentNode][thisAdjacent] != 0 && isGraph->isAdjacencyMatrix[isCurrentNode][thisAdjacent] < isCost[thisAdjacent]){
                *(isCost + thisAdjacent) = isGraph->isAdjacencyMatrix[isCurrentNode][thisAdjacent];
                *(isParent + thisAdjacent) = isCurrentNode;
            }
        }
        for(int isEntry = 0; isEntry < isGraph->isNodeCount; isEntry++){(*(isCost + isEntry) < isMaximum && *(isCost + isEntry) > 0) && (isMaximum = *(isCost + isEntry), isSmallestIndex = isEntry);}
        *(shortestPath + isIndex++) = isSmallestIndex; isCurrentNode = isSmallestIndex; *(isCost + isSmallestIndex) = -1; isSmallestIndex = 0; isMaximum = INT_MAX;
    }
    fprintf(stdout, "Delete: "); for(int thisNode = 0; thisNode < isGraph->isNodeCount; thisNode++){fprintf(stdout, (thisNode != isGraph->isNodeCount - 1) ? "%s -> " : "%s\n", isGraph->isNodeList[shortestPath[thisNode]]);}
    fprintf(stdout, "Parent: "); for(int thisNode = 0; thisNode < isGraph->isNodeCount; thisNode++){fprintf(stdout, (thisNode != isGraph->isNodeCount - 1) ? "%s -> " : "%s\n", isGraph->isNodeList[isParent[shortestPath[thisNode]]]);}
    free(isCost); isCost = NULL; free(isParent); isParent = NULL; free(shortestPath); shortestPath = NULL;
    return;
}

void kruskalAlgorithm(Graph *isGraph){
    return;
}

void edmundsKarpAlgorithm(Graph *isGraph){
    return;
}

void displayNodeList(Graph *isGraph){
    fprintf(stdout, "\nNode List: ");
    for(int isNode = 0; isNode < isGraph->isNodeCount; isNode++){fprintf(stdout, isNode != isGraph->isNodeCount - 1 ? "%s, " : "%s\n", *(isGraph->isNodeList + isNode));}
    return;
}

void displayAdjacencyList(Graph *isGraph){
    fprintf(stdout, "\nAdjacency List: \n");
    for(int isNode = 0; isNode < isGraph->isNodeCount; isNode++){fprintf(stdout, "%s\n", *(isGraph->isAdjacencyList + isNode));}
    return;
}

void displayAdjacencyMatrix(Graph *isGraph){
    fprintf(stdout, "\nAdjacency Matrix :\n");
    fprintf(stdout, "<?> |");
    for(int isNode = 0; isNode < isGraph->isNodeCount; fprintf(stdout, isNode == isGraph->isNodeCount - 1 ? "%4c%s]\n" : "%4c%s]", '[', *(isGraph->isNodeList + isNode)), isNode++);
    for(int isRow = 0; isRow < isGraph->isNodeCount; isRow++){
        fprintf(stdout, "[%s] [ ", *(isGraph->isNodeList + isRow));
        for(int isColumn = 0; isColumn < isGraph->isNodeCount; isColumn++){
            fprintf(stdout, (isColumn != isGraph->isNodeCount - 1) ? "%4d, " : "%4d ]\n", *(*((isGraph)->isAdjacencyMatrix + isRow) + isColumn));
        }
    }
    return;
}

void displayDynamicAdjacencyMatrix(Graph *isGraph, int *isNodeAdjacentCount){
    fprintf(stdout, "\nDynamic Adjacency Matrix :\n");
    for(int isRow = 0; isRow < isGraph->isNodeCount; isRow++){
        fprintf(stdout, "[%s] [ ", *(isGraph->isNodeList + isRow));
        for(int isCol = 0; isCol < *(isNodeAdjacentCount + isRow); isCol++){
            fprintf(stdout, (isCol != *(isNodeAdjacentCount + isRow) - 1) ? "%d, " : "%d ]\n", *(*((isGraph)->isAdjacencyMatrix + isRow) + isCol));
        }
        (*(isNodeAdjacentCount + isRow) == 0) && (fprintf(stdout, " ]\n"));
    }
    return;
}