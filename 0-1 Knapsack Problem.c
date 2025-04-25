#include <stdio.h>
#include <stdlib.h>

void Knapsack(int **isProcedure, int *itemWeight, int *itemValue, int isSize, int noProcedure);
void KnapsackItems(int isMaxValue, int noItems, int *itemValue, int isIndex, int isSum, int checkItem, int *isItems);
void displayProcedure(int **isProcedure, int noProcedure, int isSize);

int main(int argc, char *argv[]){
    int isSize, noItems, *itemWeight, *itemValue, **isProcedure, noProcedure;
    fprintf(stdout, "Enter the weight of bag: "); scanf("%d", &isSize);
    fprintf(stdout, "Enter the number of items: "); scanf("%d", &noItems);
    itemWeight = calloc(noItems, sizeof(int)); if(itemWeight == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); exit(EXIT_FAILURE);}
    itemValue = calloc(noItems, sizeof(int)); if(itemValue == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); exit(EXIT_FAILURE);}
    noProcedure = (((noItems - 1) * 3) + 1);
    isProcedure = calloc(noProcedure, sizeof(int *)); if(isProcedure == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); exit(EXIT_FAILURE);}
    for(int thisIndex = 0; thisIndex < noProcedure; thisIndex++){
        *(isProcedure + thisIndex) = calloc((isSize + 1), sizeof(int)); if(*(isProcedure + thisIndex) == NULL){fprintf(stdout, "Memory Allocation Failed\n"); exit(EXIT_FAILURE);}
        if(thisIndex < noItems){
            fprintf(stdout, "Enter item %d weight: ", (thisIndex + 1)); scanf("%d", (itemWeight + thisIndex));
            fprintf(stdout, "Enter item %d value: ", (thisIndex + 1)); scanf("%d", (itemValue + thisIndex));
        }
    }
    Knapsack(isProcedure, itemWeight, itemValue, isSize, noProcedure);
    fprintf(stdout, "\nMax Value: %d\n", *(*(isProcedure + (noProcedure - 1)) + isSize));
    KnapsackItems(*(*(isProcedure + (noProcedure - 1)) + isSize), noItems, itemValue, 0, 0, 0, NULL);
    free(itemWeight); itemWeight = NULL;
    free(itemValue); itemValue = NULL;
    for(int thisIndex = 0; thisIndex < noProcedure; free(*(isProcedure + thisIndex)), *(isProcedure + thisIndex) = NULL, thisIndex++);
    free(isProcedure); isProcedure = NULL;
    return 0;
}

void Knapsack(int **isProcedure, int *itemWeight, int *itemValue, int isSize, int noProcedure){
    int isItem = 0, isIndex = 0;
    char isState = 'I';
    while(1){
        switch(isState){
            case 'I':
            for(int thisIndex = 0; thisIndex < isSize + 1; thisIndex++){
                *(*(isProcedure + isIndex) + thisIndex) = (thisIndex >= *(itemWeight + isItem)) ? *(itemValue + isItem) : 0;
            }
            isItem++; isIndex++; isState = 'S'; break;
            
            case 'S':
            int isValue = 0;
            for(int thisIndex = 0; thisIndex < isSize + 1; thisIndex++){
                *(*(isProcedure + isIndex) + thisIndex) = (thisIndex >= *(itemWeight + isItem)) ? *(*(isProcedure + (isIndex - 1)) + isValue) : 0;
                (thisIndex >= *(itemWeight + isItem)) && (isValue++);
            }
            isIndex++; isState = 'A'; break;
            
            case 'A':
            for(int thisIndex = 0; thisIndex < isSize + 1; thisIndex++){
                *(*(isProcedure + isIndex) + thisIndex) = (thisIndex >= *(itemWeight + isItem)) ? *(*(isProcedure + (isIndex - 1)) + thisIndex) + *(itemValue + isItem) : 0;
            }
            isIndex++; isState = 'M'; break;
            
            case 'M':
            for(int thisIndex = 0; thisIndex < isSize + 1; thisIndex++){
                *(*(isProcedure + isIndex) + thisIndex) = (*(*(isProcedure + (isIndex - 3)) + thisIndex) > *(*(isProcedure + (isIndex - 1)) + thisIndex)) ? *(*(isProcedure + (isIndex - 3)) + thisIndex) : *(*(isProcedure + (isIndex - 1)) + thisIndex);
            }
            if(isIndex == noProcedure - 1){return;}
            else{isIndex++; isItem++; isState = 'S';}
            break;
        }
    }
    return;
}

//Subset Sum Problem
void KnapsackItems(int isMaxValue, int noItems, int *itemValue, int isIndex, int isSum, int checkItem, int *isItems){
    if(isSum == isMaxValue){
        printf("\nItems: ");
        int getItem = 0;
        for(int thisIndex = 0; thisIndex < noItems; thisIndex++){
            (*(isItems + getItem) == *(itemValue + thisIndex) && getItem < isIndex) && (printf("%*d", 2, thisIndex + 1), getItem++);
        }
        return;
    }
    for(int thisItem = checkItem; thisItem < noItems; thisItem++){
        if(isItems == NULL){
            int *getItems = calloc(noItems, sizeof(int));
            *(getItems + isIndex) = *(itemValue + thisItem);
            KnapsackItems(isMaxValue, noItems, itemValue, isIndex + 1, isSum + *(itemValue + thisItem), checkItem + 1, getItems);
        } else{
            *(isItems + isIndex) = *(itemValue + thisItem);
            KnapsackItems(isMaxValue, noItems, itemValue, isIndex + 1, isSum + *(itemValue + thisItem), checkItem + 1, isItems);
        }
    }
    return;
}

void displayProcedure(int **isProcedure, int noProcedure, int isSize){
    for(int isRow = 0; isRow < noProcedure; isRow++){
        for(int isCol = 0; isCol < isSize + 1; isCol++){
            printf((isCol != isSize) ? "%5d" : "%5d\n", *(*(isProcedure + isRow) + isCol));
        }
    }
}