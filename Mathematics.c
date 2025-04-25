#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool isNumberPalindrome(long long isNumber);
long long reverseNumber(long long isNumber);
void displayMatrix(double **isMatrix, int *isDimension);
double **getRandomMatrix(int *isDimension, double isRandMax, double isRandMin);
void setRandomMatrix(double **isMatrix, int *isDimension, double isRandMax, double isRandMin);
double getMin(double **isMatrix, int *isDimension);
double getMax(double **isMatrix, int *isDimension);
double minWithinRange(double **isMatrix, int *isDimension, int *getMin, int *getMax);
double maxWithinRange(double **isMatrix, int *isDimension, int *getMin, int *getMax);
double indexRowSum(double **isMatrix, int *isDimension, int *getRows);
double indexColumnSum(double **isMatrix, int *isDimension, int *getCols);
void reverseSelectedRangeWithinMatrix(double **isMatrix, int *isDimension, int *getMin, int *getMax);
double *downwardDiagonal(double **isMatrix, int *isDimension);
double *matrixSpiralOrder(double **isMatrix, int *isDimension);
double **matrixMultiplication(double **isMatrixA, double **isMatrixB, int *isDimensions);
double **matrixAddition(double **isMatrixA, double **isMatrixB, int *isDimensions);
double **matrixSubtraction(double **isMatrixA, double **isMatrixB, int *isDimensions);
double **matrixScalarMultiplication(double **isMatrix, int *isDimension, double isScalar);
double **matrixTranspose(double **isMatrix, int *isDimension);
double matrixTrace(double **isMatrix, int *isDimension);
double **kroneckerProduct(double **isMatrixA, double **isMatrixB, int *isDimensions);
double **khatriRaoProduct(double **isMatrixA, double **isMatrixB, int *isDimensions);
double **faceSplittingProduct(double **isMatrixA, double **isMatrixB, int *isDimensions);
double **hadamardProduct(double **isMatrixA, double **isMatrixB, int *isDimensions);
double vectorDistance(double *isVectorA, double *isVectorB, int *entryCount);
double *relativePositionalVector(double *initialVector, double *terminalVector, int *entryCount);
double *vectorAddition(double *isVectorA, double *isVectorB, int *entryCount);
double *vectorSubtraction(double *isVectorA, double *isVectorB, int *entryCount);
double *vectorSalarProduct(double *isVector, double isScalar, int entryCount);
double vectorMagnitude(double *isVector, int entryCount);
double *unitVector(double *isVector, int entryCount);
double dotProduct(double *isVectorA, double *isVectorB, int *entryCount);
double *vectorProjection(double *projectVector, double *baseVector, int *entryCount);
double scalarProjection(double *projectVector, double *baseVector, int *entryCount);


int main(int argc, char*argv[]){
    srand (time(NULL));
    return 0;
}

long isFibonacciSequence(long isNumber){
	if(isNumber <= 1){return isNumber;}
	long isEntry = 0, isIndex = 2, isFirst = 1, isSecond = 0;
	while(isIndex <= isNumber){isEntry = isFirst + isSecond; isSecond = isFirst; isFirst = isEntry; isIndex++;}
	return isEntry;
}

long isFactorial(long isNumber){
	if(isNumber == 0){return 1;}
	long isValue = 1, isIndex = 1;
	while(isIndex <= isNumber){isValue *= isIndex; isIndex++;}
	return isValue;
}

long isDigitSum(long isNumber){
	long isSum = 0, getNumber = isNumber;
	(getNumber < 0) && (getNumber = -getNumber);
	while(getNumber > 0){isSum += getNumber % 10; getNumber /= 10;}
	return isSum;
}

bool isNumberPalindrome(long long isNumber){
    long long getNumber = isNumber, isReverse = 0, isRemainder = 0;
    bool isNegative = false;
    (getNumber < 0) && (isNegative = true, getNumber = -getNumber);
    while(getNumber > 0){isRemainder = getNumber % 10; isReverse = isReverse * 10 + isRemainder; getNumber /= 10;}
    (isNegative) && (isReverse -= isReverse);
    return isReverse == isNumber;
}

long long reverseNumber(long long isNumber){
    long long getNumber = isNumber, isReverse = 0, isRemainder = 0;
    bool isNegative = false;
    (getNumber < 0) && (isNegative = true, getNumber = -getNumber);
    while(getNumber > 0){isRemainder = getNumber % 10; isReverse = isReverse * 10 + isRemainder; getNumber /= 10;}
    (isNegative) && (isReverse -= isReverse);
    return isReverse;
}

void displayMatrix(double **isMatrix, int *isDimension){
    if(isMatrix == NULL){fprintf(stdout, "Invalid Matrix.\n"); return;}
    if(isDimension == NULL || *isDimension <= 0 || *(isDimension + 1) <= 0){fprintf(stdout, "Invalid Dimensions.\n"); return;}
    for(int isRow = 0; isRow < *isDimension; isRow++){
        fprintf(stdout, "[ ");
        for(int isCol = 0; isCol < *(isDimension + 1); isCol++){
            fprintf(stdout, (isCol != *(isDimension + 1) - 1) ? "%4f, " : "%f ]\n", *(*(isMatrix + isRow) + isCol));
        }
    }
}

double **getRandomMatrix(int *isDimension, double isRandMax, double isRandMin){
    if(isDimension == NULL || *isDimension <= 0 || *(isDimension + 1) <= 0){fprintf(stdout, "Invalid Dimensions.\n"); return NULL;}
    double **isMatrix = calloc(*isDimension, sizeof(double*)); if(isMatrix == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return NULL;}
    for (int isRow = 0; isRow < *isDimension; isRow++){
        *(isMatrix + isRow) = calloc(*(isDimension + 1), sizeof(double)); if(*(isMatrix + isRow) == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return NULL;}
        for(int isCol = 0; isCol < *(isDimension + 1); isCol++){
            //isMatrix[isRow][isCol] = fmod((double)(rand()), isRandMax + isRandMin);
            *(*(isMatrix + isRow) + isCol) = ((double)(rand())) / ((double)RAND_MAX / (isRandMax - isRandMin)) + isRandMin;
        }
    }
    return isMatrix;
}

void setRandomMatrix(double **isMatrix, int *isDimension, double isRandMax, double isRandMin){
    if(isMatrix == NULL){fprintf(stdout, "Invalid Matrix.\n"); return;}
    if(isDimension == NULL || *isDimension <= 0 || *(isDimension + 1) <= 0){fprintf(stdout, "Invalid Dimensions.\n"); return;}
    for(int isRow = 0; isRow < *isDimension; isRow++){
        for(int isCol = 0; isCol < *(isDimension + 1); isCol++){
            //thisArray[isRow][isCol] = fmod((double)(rand()), isRandMax + isRandMin);
            *(*(isMatrix + isRow) + isCol) = ((double)(rand())) / ((double)RAND_MAX / (isRandMax - isRandMin)) + isRandMin;
        }
    }
    return;
}

double getMin(double **isMatrix, int *isDimension){
    if(isMatrix == NULL){fprintf(stdout, "Invalid Matrix.\n"); exit(EXIT_FAILURE);}
    if(isDimension == NULL || *isDimension <= 0 || *(isDimension + 1) <= 0){fprintf(stdout, "Invalid Dimensions.\n"); exit(EXIT_FAILURE);}
    double isMin = DBL_MAX;
    for(int isRow = 0; isRow < *isDimension; isRow++){
        for(int isCol = 0; isCol < *(isDimension + 1); isCol++){
            (*(*(isMatrix + isRow) + isCol) < isMin) && (isMin = *(*(isMatrix + isRow) + isCol));
        }
    }
    return isMin;
}

double getMax(double **isMatrix, int *isDimension){
    if(isMatrix == NULL){fprintf(stdout, "Invalid Matrix.\n"); exit(EXIT_FAILURE);}
    if(isDimension == NULL || *isDimension <= 0 || *(isDimension + 1) <= 0){fprintf(stdout, "Invalid Dimensions.\n"); exit(EXIT_FAILURE);}
    double isMax = DBL_MIN;
    for(int isRow = 0; isRow < *isDimension; isRow++){
        for(int isCol = 0; isCol < *(isDimension + 1); isCol++){
            (*(*(isMatrix + isRow) + isCol) > isMax) && (isMax = *(*(isMatrix + isRow) + isCol));
        }
    }
    return isMax;
}

double minWithinRange(double **isMatrix, int *isDimension, int *getMin, int *getMax){
    if(isMatrix == NULL){fprintf(stdout, "Invalid Matrix.\n"); exit(EXIT_FAILURE);}
    if(isDimension == NULL || *isDimension <= 0 || *(isDimension + 1) <= 0 || *getMin < 0 || *getMin > *isDimension || *(getMin + 1) < 0 || *(getMin + 1) > *(isDimension + 1) || *getMax < 0 || *getMax > *isDimension || *(getMax + 1) < 0 || *(getMax + 1) > *(isDimension + 1)){fprintf(stdout, "Invalid Dimensions.\n"); exit(EXIT_FAILURE);}
    double isMin = DBL_MAX;
    int isColIndex = *(getMin + 1);
    bool isExit = false;
    for(int isRow = *getMin; isRow <= *getMax; isRow++){
        for(int isCol = isColIndex; isCol < *(isDimension + 1); isCol++){
            (*(*(isMatrix + isRow) + isCol) < isMin) && (isMin = *(*(isMatrix + isRow) + isCol));
            if(isRow == *getMax && isCol == *(getMax + 1)){isExit = true; break;}
        }
        isColIndex = 0;
        if(isExit){break;}
    }
    return isMin;
}

double maxWithinRange(double **isMatrix, int *isDimension, int *getMin, int *getMax){
    if(isMatrix == NULL){fprintf(stdout, "Invalid Matrix.\n"); exit(EXIT_FAILURE);}
    if(isDimension == NULL || *isDimension <= 0 || *(isDimension + 1) <= 0 || *getMin < 0 || *getMin > *isDimension || *(getMin + 1) < 0 || *(getMin + 1) > *(isDimension + 1) || *getMax < 0 || *getMax > *isDimension || *(getMax + 1) < 0 || *(getMax + 1) > *(isDimension + 1)){fprintf(stdout, "Invalid Dimensions.\n"); exit(EXIT_FAILURE);}
    double isMax = DBL_MIN;
    int isColIndex = *(getMin + 1);
    bool isExit = false;
    for(int isRow = *getMin; isRow <= *getMax; isRow++){
        for(int isCol = isColIndex; isCol < *(isDimension + 1); isCol++){
            (*(*(isMatrix + isRow) + isCol) > isMax) && (isMax = *(*(isMatrix + isRow) + isCol));
            if(isRow == *getMax && isCol == *(getMax + 1)){isExit = true; break;}
        }
        isColIndex = 0;
        if(isExit){break;}
    }
    return isMax;
}

double indexRowSum(double **isMatrix, int *isDimension, int *getRows){
    if(isMatrix == NULL){fprintf(stdout, "Invalid Matrix.\n"); exit(EXIT_FAILURE);}
    if(isDimension == NULL || *isDimension <= 0 || *(isDimension + 1) <= 0 || *getRows < 0 || *getRows > *isDimension || *(getRows + 1) < 0 || *(getRows + 1) > *isDimension){fprintf(stdout, "Invalid Dimensions.\n"); exit(EXIT_FAILURE);}
    double rowSum = 0;
    for(int isRow = *getRows; isRow < *(getRows + 1); isRow++){
        for(int isCol = 0; isCol < *(isDimension + 1); isCol++){
            rowSum += *(*(isMatrix + isRow) + isCol);
        }
    }
    return rowSum;
}

double indexColumnSum(double **isMatrix, int *isDimension, int *getCols){
    if(isMatrix == NULL){fprintf(stdout, "Invalid Matrix.\n"); exit(EXIT_FAILURE);}
    if(isDimension == NULL || *isDimension <= 0 || *(isDimension + 1) <= 0 || *getCols < 0 || *getCols > *(isDimension + 1) || *(getCols + 1) < 0 || *(getCols + 1) > *(isDimension + 1)){fprintf(stdout, "Invalid Dimensions.\n"); exit(EXIT_FAILURE);}
    double columnSum = 0;
    for(int isCol = *getCols; isCol < *(getCols + 1); isCol++){
        for(int isRow = 0; isRow < *isDimension; isRow++){
            columnSum += *(*(isMatrix + isRow) + isCol);
        }
    }
    return columnSum;
}

void reverseSelectedRangeWithinMatrix(double **isMatrix, int *isDimension, int *getMin, int *getMax){
    if(isMatrix == NULL){fprintf(stdout, "Invalid Matrix.\n"); return;}
    if(isDimension == NULL || isDimension == NULL || *isDimension <= 0 || *(isDimension + 1) <= 0 || *getMin < 0 || *getMin > *isDimension || *(getMin + 1) < 0 || *(getMin + 1) > *(isDimension + 1) || *getMax < 0 || *getMax > *isDimension || *(getMax + 1) < 0 || *(getMax + 1) > *(isDimension + 1)){fprintf(stdout, "Invalid Dimensions.\n"); return;}
    int isColStart = *(getMin + 1), isX = *getMax, isY = *(getMax + 1);
    double isPlaceholder;
    bool isExit = false;
    for(int isRow = *getMin; isRow <= *getMax; isRow++){
        for(int isCol = isColStart; isCol < *(isDimension + 1); isCol++){
            if(isX == isRow && isY == isCol){isExit = true; break;}
            isPlaceholder = *(*(isMatrix + isRow) + isCol);
            *(*(isMatrix + isRow) + isCol) = *(*(isMatrix + isX) + isY);
            *(*(isMatrix + isX) + isY) = isPlaceholder;
            isY--;
            (isY == 0) && (isY = *(isDimension + 1) - 1, isX--);
        }
        isColStart = 0;
        if(isExit){break;}
    }
    return;
}

double *downwardDiagonal(double **isMatrix, int *isDimension){
    if(isMatrix == NULL){fprintf(stdout, "Invalid Matrix.\n"); return NULL;}
    if(isDimension == NULL || *isDimension != *(isDimension + 1)){fprintf(stdout, "Matrix Dimensions Are Not Equal.\n"); return NULL;}
    double *isDiagonal = calloc(*isDimension * *isDimension, sizeof(double)); if(isDiagonal == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return NULL;}
    int isX, isY, isXPlacement, isYPlacement, isDiagonalCount = 0, isPlacementCount = 0, isDiagonalIndex = 0;
    for(int isIndex = 0; isIndex < *isDimension; isIndex++){
        *(isDiagonal + isDiagonalIndex++) = *(*isMatrix + isIndex);
        isX = isIndex - 1; isY = 1;
        while(isIndex > 0 && isDiagonalCount < isIndex){
            *(isDiagonal + isDiagonalIndex++) = *(*(isMatrix + (isIndex - isX)) + (isIndex - isY));
            isDiagonalCount++; isX--; isY++;
        }
        isDiagonalCount = 0;
        if(isIndex == *isDimension - 1){
            for(int isTraverse = 1; isTraverse < *isDimension; isTraverse++){
                *(isDiagonal + isDiagonalIndex++) =  *(*(isMatrix + isTraverse) + isIndex);
                isYPlacement = isIndex; isXPlacement = isTraverse;
                while(isTraverse < *isDimension - 1 && (isPlacementCount < isIndex - isTraverse)) {
                    isXPlacement++; isYPlacement--;
                    *(isDiagonal + isDiagonalIndex++) =  *(*(isMatrix + isXPlacement) + isYPlacement);
                    isPlacementCount++;
                }
                isPlacementCount = 0;
            }
            break;
        }
    }
    return isDiagonal;
}

double *matrixSpiralOrder(double **isMatrix, int *isDimension){
    if(isMatrix == NULL){fprintf(stdout, "Invalid Matrix.\n"); return NULL;}
    if(isDimension == NULL || *isDimension <= 0 || *(isDimension + 1) <= 0){fprintf(stdout, "Invalid Dimensions.\n"); return NULL;}
    double *isSpiralOrder = calloc(*isDimension * *(isDimension + 1), sizeof(double)); if(isSpiralOrder == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return NULL;}
    int isXIndex = 0, isYIndex = 0, isIndex = 0, isPositionCount = 0;
    bool hasSpiralOrder = false;
    char isDirection = 'E';
    while(!hasSpiralOrder){
        switch(isDirection){
            case 'N':
            for(; isXIndex >= 0 + isPositionCount; isXIndex--){*(isSpiralOrder + isIndex++) = *(*(isMatrix + isXIndex) + isYIndex);}
            isXIndex++; isYIndex++; isDirection = 'E';
            break;
            
            case 'W':
            for(; isYIndex >= 0 + isPositionCount; isYIndex--){*(isSpiralOrder + isIndex++) = *(*(isMatrix + isXIndex) + isYIndex);}
            isXIndex--; isYIndex++; isPositionCount++; isDirection = 'N';
            break;

            case 'S':
            for(; isXIndex < *isDimension - isPositionCount; isXIndex++){*(isSpiralOrder + isIndex++) = *(*(isMatrix + isXIndex) + isYIndex);}
            isXIndex--; isYIndex--; isDirection = 'W';
            break;

            case 'E':
            for(; isYIndex < *(isDimension + 1) - isPositionCount; isYIndex++){*(isSpiralOrder + isIndex++) = *(*(isMatrix + isXIndex) + isYIndex);}
            isXIndex++; isYIndex--; isDirection = 'S';
            break;

            default:
            fprintf(stdout, "Error.\n");
            break;
        }
        if(isIndex == *isDimension * *(isDimension + 1)){hasSpiralOrder = true;}
    }
    return isSpiralOrder;
}

double **matrixMultiplication(double **isMatrixA, double **isMatrixB, int *isDimensions){
    if(isMatrixA == NULL || isMatrixB == NULL || isMatrixA == NULL && isMatrixB == NULL){fprintf(stdout, "Invalid Matrix.\n"); return NULL;}
    if(isDimensions == NULL || *(isDimensions + 1) != *(isDimensions + 2)){fprintf(stdout, "Invalid Matrix Dimensions.\n"); return NULL;}
    double **productMatrix = calloc(*isDimensions, sizeof(double *)); if(productMatrix == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return NULL;}
    double isProduct = 0;
    int isIndex = 0, isVertical = 0;
    for(int isRow = 0; isRow < *isDimensions; isRow++){
        *(productMatrix + isRow) = calloc(*(isDimensions + 3), sizeof(double)); if(*(productMatrix + isRow) == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return NULL;}
        for(int isColumn = 0; isColumn < (*(isDimensions + 2) * *(isDimensions + 3)); isColumn++){
            isProduct += *(*(isMatrixA + isRow) + isIndex) * *(*(isMatrixB + isIndex) + isVertical);
            isIndex++;
            if(isIndex == *(isDimensions + 1)){
                *(*(productMatrix + isRow) + isVertical) = isProduct;
                isIndex = 0; isProduct = 0; isVertical++;
            }
        }
        isVertical = 0;
    }
    return productMatrix;
}

double **matrixAddition(double **isMatrixA, double **isMatrixB, int *isDimensions){
    if(isMatrixA == NULL || isMatrixB == NULL || isMatrixA == NULL && isMatrixB == NULL){fprintf(stdout, "Invalid Matrix.\n"); return NULL;}
    if(isDimensions == NULL || *isDimensions != *(isDimensions + 2) || *(isDimensions + 1) != *(isDimensions + 3) || *isDimensions != *(isDimensions + 2) && *(isDimensions + 1) != *(isDimensions + 3)){fprintf(stdout, "Invalid Matrix Dimensions.\n"); return NULL;}
    double **summationMatrix = calloc(*isDimensions, sizeof(double *)); if(summationMatrix == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return NULL;}
    for(int isRow = 0; isRow < *isDimensions; isRow++){
        *(summationMatrix + isRow) = calloc(*(isDimensions + 1), sizeof(double)); if(*(summationMatrix + isRow) == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return NULL;}
        for(int isColumn = 0; isColumn < *(isDimensions + 1); isColumn++){
            *(*(summationMatrix + isRow) + isColumn) = *(*(isMatrixA + isRow) + isColumn) + *(*(isMatrixB + isRow) + isColumn);
        }
    }
    return summationMatrix;
}

double **matrixSubtraction(double **isMatrixA, double **isMatrixB, int *isDimensions){
    if(isMatrixA == NULL || isMatrixB == NULL || isMatrixA == NULL && isMatrixB == NULL){fprintf(stdout, "Invalid Matrix.\n"); return NULL;}
    if(isDimensions == NULL || *isDimensions != *(isDimensions + 2) || *(isDimensions + 1) != *(isDimensions + 3) || *isDimensions != *(isDimensions + 2) && *(isDimensions + 1) != *(isDimensions + 3)){fprintf(stdout, "Invalid Matrix Dimensions.\n"); return NULL;}
    double **differenceMatrix = calloc(*isDimensions, sizeof(double *)); if(differenceMatrix == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return NULL;}
    for(int isRow = 0; isRow < *isDimensions; isRow++){
        *(differenceMatrix + isRow) = calloc(*(isDimensions + 1), sizeof(double)); if(*(differenceMatrix + isRow) == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return NULL;}
        for(int isColumn = 0; isColumn < *(isDimensions + 1); isColumn++){
            *(*(differenceMatrix + isRow) + isColumn) = *(*(isMatrixA + isRow) + isColumn) - *(*(isMatrixB + isRow) + isColumn);
        }
    }
    return differenceMatrix;
}

double **matrixScalarMultiplication(double **isMatrix, int *isDimension, double isScalar){
    if(isMatrix == NULL){fprintf(stdout, "Invalid Matrix.\n"); return NULL;}
    if(isDimension == NULL || *isDimension <= 0 || *(isDimension + 1) <= 0){fprintf(stdout, "Invalid Matrix Dimensions.\n"); return NULL;}
    double **scalarMatrix = calloc(*isDimension, sizeof(double *)); if(scalarMatrix == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return NULL;}
    for(int isRow = 0; isRow < *isDimension; isRow++){
        *(scalarMatrix + isRow) = calloc(*(isDimension + 1), sizeof(double)); if(*(scalarMatrix + isRow) == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return NULL;}
        for(int isColumn = 0; isColumn < *(isDimension + 1); isColumn++){
            *(*(scalarMatrix + isRow) + isColumn) = isScalar * *(*(isMatrix + isRow) + isColumn);
        }
    }
    return scalarMatrix;
}

double **matrixTranspose(double **isMatrix, int *isDimension){
    if(isMatrix == NULL){fprintf(stdout, "Invalid Matrix.\n"); return NULL;}
    if(isDimension == NULL || *isDimension <= 0 || *(isDimension + 1) <= 0){fprintf(stdout, "Invalid Matrix Dimensions.\n"); return NULL;}
    double **transposeMatrix = calloc(*isDimension, sizeof(double *)); if(transposeMatrix == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return NULL;}
    int isX = 0, isY = 0;
    for(int isRow = 0; isRow < *isDimension; isRow++){
        *(transposeMatrix + isRow) = calloc(*(isDimension + 1), sizeof(double)); if(*(transposeMatrix + isRow) == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return NULL;}
        for(int isColumn = 0; isColumn < *(isDimension + 1); isColumn++){
            *(*(transposeMatrix + isRow) + isColumn) = *(*(isMatrix + isX) + isY);
            isX++;
        }
        isX = 0; isY++;
    }
    return transposeMatrix;
}

double matrixTrace(double **isMatrix, int *isDimension){
    if(isMatrix == NULL){fprintf(stdout, "Invalid Matrix.\n"); exit(EXIT_FAILURE);}
    if(isDimension == NULL || *isDimension <= 0 || *(isDimension + 1) <= 0 || *isDimension != *(isDimension + 1)){fprintf(stdout, "Invalid Matrix Dimensions.\n"); exit(EXIT_FAILURE);}
    double isTrace;
    for(int isRow = 0, isColumn = 0; isRow < *isDimension; isRow++, isColumn++){isTrace += *(*(isMatrix + isRow) + isColumn);}
    return isTrace;
}

void gassianElimination(double **isMatrix, int *isDimension){
    if(isMatrix == NULL){fprintf(stdout, "Invalid Matrix.\n"); return;}
    if(isDimension == NULL || *isDimension <= 0 || *(isDimension + 1) <= 0){fprintf(stdout, "Invalid Matrix Dimensions.\n"); return;}
    return;
}

void gaussjordanElimination(){}
void isDeterminant(){}
void matrixInverse(){}
void matrixRank(){}
void eigenValues(){}
void singularValues(){}
void eigenVectors(){}
void LU_Factorization(){}
void singularValueDecomposition(){}
void getDiagonaization(){}
void QR_Decomposition(){}
void spectralTheorem(){}
void CR_Factorization(){}
void frobeniusNorm(){}
void nuclearNorm(){}

double **kroneckerProduct(double **isMatrixA, double **isMatrixB, int *isDimensions){
    if(isMatrixA == NULL || isMatrixB == NULL || isMatrixA == NULL && isMatrixB == NULL){fprintf(stdout, "Invalid Matrix.\n"); return NULL;}
    if(isDimensions == NULL || *isDimensions <= 0 || *(isDimensions + 1) <= 0){fprintf(stdout, "Invalid Matrix Dimensions.\n"); return NULL;}
    double **blockMatrix = calloc(*isDimensions * *(isDimensions + 2), sizeof(double *)); if(blockMatrix == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return NULL;}
    int isX = 0, isIndex = 0, isRowCount = 0, isColumnCount = 0;
    for(int isRow = 0; isRow < (*isDimensions * *(isDimensions + 2)); isRow++){
        *(blockMatrix + isRow) = calloc(*(isDimensions + 1) * *(isDimensions + 3), sizeof(double)); if(*(blockMatrix + isRow) == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return NULL;}
        for(int isColumn = 0; isColumn < (*(isDimensions + 1) * *(isDimensions + 3)); isColumn++){
            *(*(blockMatrix + isRow) + isColumn) = *(*(isMatrixA + isX) + isIndex) * *(*(isMatrixB + isRowCount) + isColumnCount);
            isColumnCount++; if(isColumnCount == *(isDimensions + 3)){isIndex++; isColumnCount = 0;}
        }
        isIndex = 0; isRowCount++; if(isRowCount == *(isDimensions + 2)){isX++; isRowCount = 0;}
    }
    return blockMatrix;
}

double **khatriRaoProduct(double **isMatrixA, double **isMatrixB, int *isDimensions){
    if(isMatrixA == NULL || isMatrixB == NULL || isMatrixA == NULL && isMatrixB == NULL){fprintf(stdout, "Invalid Matrix.\n"); return NULL;}
    if(isDimensions == NULL || *isDimensions <= 0 || *(isDimensions + 1) <= 0 || *(isDimensions + 1) != *(isDimensions + 3)){fprintf(stdout, "Invalid Matrix Dimensions.\n"); return NULL;}
    double **columnWiseMatrix = calloc(*isDimensions * *(isDimensions + 2), sizeof(double *)); if(columnWiseMatrix == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return NULL;}
    int isX = 0, isRowCount = 0, isRowIndex = 0;
    for(int isRow = 0; isRow < *isDimensions * *(isDimensions + 2); isRow++){
        *(columnWiseMatrix + isRow) = calloc(*(isDimensions + 1), sizeof(double)); if(*(columnWiseMatrix + isRow) == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return NULL;}
        for(int isColumn = 0; isColumn < *(isDimensions + 1); isColumn++){*(*(columnWiseMatrix + isRow) + isColumn) = *(*(isMatrixA + isX) + isColumn) * *(*(isMatrixB + isRowCount) + isColumn);}
        isRowCount++; isRowIndex++; if(isRowIndex == *(isDimensions + 2)){isX++; isRowCount = 0; isRowIndex = 0;}
    }
    return columnWiseMatrix;
}

double **faceSplittingProduct(double **isMatrixA, double **isMatrixB, int *isDimensions){
    if(isMatrixA == NULL || isMatrixB == NULL || isMatrixA == NULL && isMatrixB == NULL){fprintf(stdout, "Invalid Matrix.\n"); return NULL;}
    if(isDimensions == NULL || *isDimensions <= 0 || *(isDimensions + 1) <= 0 || *isDimensions != *(isDimensions + 2)){fprintf(stdout, "Invalid Matrix Dimensions.\n"); return NULL;}
    double **tensorDecomposition = calloc(*isDimensions, sizeof(double *)); if(tensorDecomposition == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return NULL;}
    int isY = 0, isColumnCount = 0;
    for(int isRow = 0; isRow < *isDimensions; isRow++){
        *(tensorDecomposition + isRow) = calloc(*(isDimensions + 1) * *(isDimensions + 3), sizeof(double)); if(*(tensorDecomposition + isRow) == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return NULL;}
        for(int isColumn = 0; isColumn < *(isDimensions + 1) * *(isDimensions + 3); isColumn++){
            *(*(tensorDecomposition + isRow) + isColumn) = *(*(isMatrixA + isRow) + isY) * *(*(isMatrixB + isRow) + isColumnCount);
            isColumnCount++; if(isColumnCount == *(isDimensions + 3)){isY++; isColumnCount = 0;}
        }
        isY = 0; isColumnCount = 0;
    }
    return tensorDecomposition;
}

double **hadamardProduct(double **isMatrixA, double **isMatrixB, int *isDimensions){
    if(isMatrixA == NULL || isMatrixB == NULL || isMatrixA == NULL && isMatrixB == NULL){fprintf(stdout, "Invalid Matrix.\n"); return NULL;}
    if(isDimensions == NULL || *isDimensions <= 0 || *(isDimensions + 1) <= 0 || *isDimensions != *(isDimensions + 2) && *(isDimensions + 1) != *(isDimensions + 3)){fprintf(stdout, "Invalid Matrix Dimensions.\n"); return NULL;}
    double **schurProduct = calloc(*isDimensions, sizeof(double *)); if(schurProduct == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return NULL;}
    for(int isRow = 0; isRow < *isDimensions; isRow++){
        *(schurProduct + isRow) = calloc(*(isDimensions + 1), sizeof(double)); if(*(schurProduct + isRow) == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return NULL;}
        for(int isColumn = 0; isColumn < *(isDimensions + 1); isColumn++){*(*(schurProduct + isRow) + isColumn) = *(*(isMatrixA + isRow) + isColumn) * *(*(isMatrixB + isRow) + isColumn);}
    }
    return schurProduct;
}

void cramersRule(){}

void isCombination(){}

void isPermutation(){}

void geometricSeriesSum(){}

void bernoulliDistribution(){}

void binomialDistribution(){}

void geometricDistribution(){}

void hyperGeometricDistribution(){}

void uniformDistribution(){}

void standardNormalDistribution(){}

void standardNormalDistributionWithMeanAndVariance(){}

void poissonDistribution(){}

void exponentialDistribution(){}

void gammaDistribution(){}

void isVariance(){}

void isExpectation(){}

void normalApproximation(){}

void confidenceInterval(){}

void poissonApproximation(){}

void isMoments(){}

void isDiscreteRandomVariable(){}

void isContinuouRandomVariable(){}

double vectorDistance(double *isVectorA, double *isVectorB, int *entryCount){
    if(entryCount[0] != entryCount[1]){fprintf(stdout, "Vectors Do Not Have Equal Entries.\n"); return 1;}
    double isVectorDistance, differenceSquares = 0;
    for(int thisEntry = 0; thisEntry < entryCount[0]; differenceSquares += pow(isVectorB[thisEntry] - isVectorA[thisEntry], 2), thisEntry++);
    isVectorDistance = sqrt(differenceSquares);
    return isVectorDistance;
}

double *relativePositionalVector(double *initialVector, double *terminalVector, int *entryCount){
    if(entryCount[0] != entryCount[1]){
        fprintf(stdout, "Vectors Do Not Have Equal Entries.\n");
        return 1;
    }
    double *relativeVector = calloc(entryCount[0], sizeof(double));
    for(int isEntry = 0; isEntry < entryCount[0]; relativeVector[isEntry] = terminalVector[isEntry] - initialVector[isEntry], isEntry++);
    return relativeVector;
}

double *vectorAddition(double *isVectorA, double *isVectorB, int *entryCount){
    if(entryCount[0] != entryCount[1]){
        fprintf(stdout, "Vectors Do Not Have Equal Entries.\n");
        return 0;
    }
    double *vectorSum = calloc(entryCount[0], sizeof(double));
    for(int isEntry = 0; isEntry < entryCount[0]; vectorSum[isEntry] = isVectorA[isEntry] + isVectorB[isEntry], isEntry++);
    return vectorSum;
}

double *vectorSubtraction(double *isVectorA, double *isVectorB, int *entryCount){
    if(entryCount[0] != entryCount[1]){
        fprintf(stdout, "Vectors Do Not Have Equal Entries.\n");
        return 0;
    }
    double *vectorDifference = calloc(entryCount[0], sizeof(double));
    for(int isEntry = 0; isEntry < entryCount[0]; vectorDifference[isEntry] = isVectorA[isEntry] - isVectorB[isEntry], isEntry++);
    return vectorDifference;
}
double *vectorSalarProduct(double *isVector, double isScalar, int entryCount){
    double *scalarProduct = calloc(entryCount, sizeof(double));
    for(int isEntry = 0; isEntry < entryCount; scalarProduct[isEntry] = isScalar * isVector[isEntry], isEntry++);
    return scalarProduct;
}

double vectorMagnitude(double *isVector, int entryCount){
    double isNorm, isSquareSum;
    for(int thisEntry = 0; thisEntry < entryCount; isSquareSum += pow(isVector[thisEntry], 2), thisEntry++);
    isNorm = sqrt(isSquareSum);
    return isNorm;
}

double *unitVector(double *isVector, int entryCount){
    double *isUnitVector = calloc(entryCount, sizeof(double)), isMagnitude, isSquareSum = 0;
    for(int thisEntry = 0; thisEntry < entryCount; isSquareSum += pow(isVector[thisEntry], 2), thisEntry++);
    isMagnitude = sqrt(isSquareSum);
    for(int isEntry = 0; isEntry < entryCount; isUnitVector[isEntry] = isVector[isEntry]/isMagnitude, isEntry++);
    return isUnitVector;
}

double dotProduct(double *isVectorA, double *isVectorB, int *entryCount){
    if(entryCount[0] != entryCount[1]){fprintf(stdout, "Vectors Do Not Have Equal Entries.\n"); return 1;}
    double isDotProduct = 0;
    for(int thisEntry = 0; thisEntry < entryCount[0]; isDotProduct += isVectorA[thisEntry] * isVectorB[thisEntry], thisEntry++);
    return isDotProduct;
}

double *vectorProjection(double *projectVector, double *baseVector, int *entryCount){
    if(entryCount[0] != entryCount[1]){fprintf(stdout, "Vectors Do Not Have Equal Entries.\n"); return 0;}
    double *isVectorProjection = calloc(entryCount[0], sizeof(double)), isDotProduct = 0, isSquareSum = 0, isFactor;
    for(int thisEntry = 0; thisEntry < entryCount[0]; thisEntry++){isDotProduct += projectVector[thisEntry] * baseVector[thisEntry]; isSquareSum += pow(baseVector[thisEntry], 2);}
    isFactor = isDotProduct/isSquareSum;
    for(int isEntry = 0; isEntry < entryCount[0]; isVectorProjection[isEntry] = isFactor * baseVector[isEntry], isEntry++);
    return isVectorProjection;
}

double scalarProjection(double *projectVector, double *baseVector, int *entryCount){
    if(entryCount[0] != entryCount[1]){fprintf(stdout, "Vectors Do Not Have Equal Entries.\n"); return 0;}
    double isScalarProjection, isDotProduct = 0, isSquareSum = 0;
    for(int thisEntry = 0; thisEntry < entryCount[0]; thisEntry++){isDotProduct += projectVector[thisEntry] * baseVector[thisEntry]; isSquareSum += pow(baseVector[thisEntry], 2);}
    isScalarProjection =  isDotProduct/sqrt(isSquareSum);
    return isScalarProjection;
}

void crossProduct(){}

void greensTheorem(){}

void curl(){}

void divergence(){}

void stokesTheorem(){}

void derivative(){}

void partialDerivative(){}

void integral(){}

void chainRule(){}

void gradientVector(){}

void directionalDerivative(){}

void doubleIntegral(){}

void doubleIntegralPolar(){}

void surfaceIntegral(){}

void tripleIntegral(){}

void tripleIntegralCylindrical(){}

void tripleIntegralSpherical(){}

void fubinisTheorem(){}

void lineIntegral(){}

void isWronskian(){}

void navierStokesTheorem(){}