#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    return 0;
}

// Capitalize All Characters In A String.
void capitalizeString(char *isString){
    if(isString == NULL || *isString == '\0'){return;}
    int isIndex = 0;
    while(*(isString + isIndex) != '\0'){
        (*(isString + isIndex) >= 'a' && *(isString + isIndex) <= 'z') && (*(isString + isIndex) = *(isString + isIndex) - ('a' - 'A'));
        isIndex++;
    }
    return;
}

// 
void minusculeString(char *isString){
    if(isString == NULL || *isString == '\0'){return;}
    int isIndex = 0;
    while(*(isString + isIndex) != '\0'){
        (*(isString + isIndex) >= 'A' && *(isString + isIndex) <= 'Z') && (*(isString + isIndex) = *(isString + isIndex) + ('a' - 'A'));
        isIndex++;
    }
    return;
}

// Shorten A Given String To A Specific Length.
void shortenString(char *isString, int isLength){
    if(isString == NULL || *isString == '\0' || isLength < 0){return;}
    int isIndex = 0;
    while(isIndex < isLength && *(isString + isIndex) != '\0'){isIndex++;}
    *(isString + isIndex) = '\0';
    return;
}

// Shorten A String To It's Last N Characters.
void retainLastN(char *isString, int isCount){
    if(isString == NULL || *isString == '\0' || isCount <= 0){return;}
    int isLength = 0, isPlacement = 0, isIndex = 0;
    while(*(isString + isLength) != '\0'){isLength++;}
    if(isCount >= isLength){return;} isPlacement = isLength - isCount;
    while(isIndex < isCount){*(isString + isIndex++) = *(isString + isPlacement++);}
    *(isString + isIndex) = '\0';
    return;
}

// Returns The Number Of Occurence Of A Character In A String.
int isCharacterCount(char *isString, char isCharacter){
    if(isString == NULL || *isString == '\0'){return 0;}
    int isIndex = 0, isCount = 0;
    while(*(isString + isIndex) != '\0'){(*(isString + isIndex) == isCharacter) && (isCount++); isIndex++;}
    return isCount;
}

// Count The Letters In A String.
int *isAlphabetCount(char *isString){
    if(isString == NULL || *isString == '\0'){return;}
    char isAlphabetLetters[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    int *isLetterCount = calloc(26, sizeof(int)); if(isLetterCount == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return;}
    int isIndex = 0, isLetter = 0;
    while(*(isString + isIndex) != '\0'){
        if(*(isString + isIndex) >= 'A' && *(isString + isIndex) <= 'Z' || *(isString + isIndex) >= 'a' && *(isString + isIndex) <= 'z'){
            isLetter = *(isString + isIndex) >= 'A' && *(isString + isIndex) <= 'Z' ? *(isString + isIndex) + ('a' - 'A') - 'a' : *(isString + isIndex) - 'a';
            *(isLetterCount + isLetter) += 1;
        }
        isIndex++;
    }
    return isLetterCount;
}

// Remove Leading Spaces In A String.
void condenseLeadingSpace(char *isString){
    if(isString == NULL || *isString == '\0'){return;}
    int isCharacter = 0, isIndex = 0;
    while(*(isString + isCharacter) == ' '){isCharacter++;}
    while(*(isString + isCharacter) != '\0'){*(isString + isIndex++) = *(isString + isCharacter++);}
    *(isString + isIndex) = '\0';
    return;
}

// Remove Trailing Spaces In A String.
void condenseTrailingSpace(char *isString){
    if(isString == NULL || *isString == '\0'){return;}
    int isIndex = 0;
    while(*(isString + isIndex) != '\0'){isIndex++;}
    while(isIndex > 0 && *(isString + (isIndex - 1)) == ' '){isIndex--;}
    *(isString + isIndex) = '\0';
    return;
}

// Remove Leading And Trailing Spaces In A String. The Words Are Separated By A Single Space.
void condenseSpacing(char *isString){
    if(isString == NULL || *isString == '\0'){return;}
    int isIndex = 0, isPlacement = 0;
    bool isSpacing = true;
    while(*(isString + isIndex) != '\0'){
        if(isSpacing){
            while(*(isString + isPlacement) == ' ' && *(isString + isPlacement) != '\0'){isPlacement++;}
            isSpacing = false;
        }
        if(isIndex > 0 && *(isString + (isIndex - 1)) == ' ' && *(isString + isPlacement) == '\0'){*(isString + (isIndex - 1)) = '\0'; break;}
        *(isString + isIndex) = *(isString + isPlacement++);
        (*(isString + isIndex) == ' ') && (isSpacing = true);
        isIndex++;
    }
    return;
}

// Sort The Array, In-Place By All Non-Empty Strings Followed By A NULL Sentinel Identifier
void isFiltering(char **isArray, int *isSize){
	int isIndex = 0, isPlacement = 0;
	while(*(isArray + isIndex) != NULL){
		if(**(isArray + isIndex) != '\0'){*(isArray + isPlacement++) = *(isArray + isIndex);}
		isIndex++;
	}
	*(isArray + isPlacement) = NULL; *isSize = isPlacement;
	return;
}

// Return True If A String Is A Palindrome, Otherwise False.
bool isPalindrome(char* isString){
    if(isString == NULL || *isString == '\0'){return false;}
    bool isStringPalindrome = true;
    int isFrontIndex = 0, isBackIndex = 0;
    while(*(isString + isBackIndex) != '\0'){isBackIndex++;}
    isBackIndex--;
    while(isFrontIndex < isBackIndex){
        if(!isalnum(*(isString + isFrontIndex))){isFrontIndex++; continue;}
        if(!isalnum(*(isString + isBackIndex))){isBackIndex--; continue;}
        if(tolower(*(isString + isFrontIndex)) != tolower(*(isString + isBackIndex))){isStringPalindrome = false; break;}
        isFrontIndex++; isBackIndex--;
    }
    return isStringPalindrome;
}

// Compare The First To Second String. If Greater Return 1, If Equal Return 0, Otherwise If Lesser Return -1
int compareStringIgnoreCase(char *isFirstString, char *isSecondString){
    if(isFirstString == NULL || isSecondString == NULL){return -2;}
	int isFirstIndex = 0, isSecondIndex = 0;
	char isFirst, isSecond;
	while(*(isFirstString + isFirstIndex) != '\0' && *(isSecondString + isSecondIndex) != '\0'){
		isFirst = *(isFirstString + isFirstIndex); isSecond = *(isSecondString + isSecondIndex);
		(isFirst >= 'A' && isFirst <= 'Z') && (isFirst = isFirst + ('a' - 'A'));
		(isSecond >= 'A' && isSecond <= 'Z') && (isSecond = isSecond + ('a' - 'A'));
		if(isFirst != isSecond){return isFirst > isSecond ? 1 : -1;}
		isFirstIndex++; isSecondIndex++;
	}
	return *(isFirstString + isFirstIndex) == '\0' && *(isSecondString + isSecondIndex) == '\0' ? 0 : *(isFirstString + isFirstIndex) != '\0' ? 1 : -1;
}

// Return The Length Of The Last Word In A String.
int isLengthOfLastWord(char *isString){
    if(isString == NULL || *isString == '\0'){return false;}
    int isLength = 0, isWordLength = 0;
    while(*(isString + isLength) != '\0'){isLength++;} isLength--;
    while(isLength >= 0 && *(isString + isLength) == ' '){isLength--;}
    while(isLength >= 0 && *(isString + isLength) != ' '){ isWordLength++; isLength--;}
    return isWordLength;
}

//You are given two strings word1 and word2. Merge the strings by adding letters in alternating order, starting with word1. If a string is longer than the other, append the additional letters onto the end of the merged string. Return the merged string.
char *isInterleaved(char *isFirstString, char *isSecondString){
	if(isFirstString == NULL || isSecondString == NULL){fprintf(stderr, "Invalid String.\n"); return NULL;}
	if(*isFirstString == '\0' && *isSecondString != '\0'){return isSecondString;}
    if(*isFirstString != '\0' && *isSecondString == '\0'){return isFirstString;}
	int isIndex = strlen(isFirstString) + strlen(isSecondString), isEntry = 0, isFirstIndex = 0, isSecondIndex = 0;
	char *isMerge = calloc(isIndex + 1, sizeof(char));if(isMerge == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
	while(isEntry < isIndex){
		(*(isFirstString + isFirstIndex) != '\0') && (*(isMerge + isEntry++) = *(isFirstString + isFirstIndex++));
		(*(isSecondString + isSecondIndex) != '\0') && (*(isMerge + isEntry++) = *(isSecondString + isSecondIndex++));
	}
	*(isMerge + isEntry) = '\0';
	return isMerge;
}

// Returns A String Where All Characters Are Unique.
char *isUniqueCharacterString(char *isString){
	if(isString == NULL || *isString == '\0'){return NULL;}
	int isIndex = 0, isPlacement = 0, isEntry = 0;
	while(*(isString + isIndex) != '\0'){isIndex++;}
	char *isEdit = calloc(isIndex + 1, sizeof(char)); if(isEdit == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
	int isVisited[256] = {0};
	while(isPlacement < isIndex){
		if(*(isVisited + *(isString +isPlacement)) == 0){*(isEdit + isEntry++) = *(isString + isPlacement); *(isVisited + *(isString +isPlacement)) = 1;}
		isPlacement++;
	}
	*(isEdit + isEntry) = '\0';
	if(isEntry < isIndex){
		char *resizeEdit = realloc(isEdit, sizeof(char) *(isEntry + 1)); if(resizeEdit == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
		isEdit = resizeEdit;
	}
	return isEdit;
}

// Reverse A String (In-Place). // Complete
void reverseString(char *isString){
    if(isString == NULL || *isString == '\0'){return;}
    int isSize = 0, isLeftIndex = 0, isRightIndex = 0;
    char isPlaceholder;
    while(*(isString + isSize) != '\0'){isSize++;}
    isRightIndex = isSize - 1;
    while(isLeftIndex < isRightIndex) {
        isPlaceholder = *(isString + isLeftIndex);
        *(isString + isLeftIndex) = *(isString + isRightIndex); *(isString + isRightIndex) = isPlaceholder;
        isLeftIndex++; isRightIndex--;
    }
    return;
}

// Returns A String Reversed. Leading And Trailing Spaces Are Removed. The Words Are Separated By A Single Space.
char *isReverseString(char *isString){
    if(isString == NULL || *isString == '\0'){return NULL;}
    bool isFirstWord = false;
    int isSize = 0, isLeftIndex = 0, isRightIndex = 0, isReverseIndex = 0;
    while(*(isString + isSize) != '\0'){(*(isString + isSize) != ' ') && (isFirstWord = true); if(!isFirstWord && *(isString + isLeftIndex) == ' '){isLeftIndex++;} isSize++;}
    isRightIndex = isSize - 1;
    while(isRightIndex >= 0 && *(isString + isRightIndex) == ' '){isRightIndex--;}
    isSize = isRightIndex - isLeftIndex + 2;
    char *isReverseString = calloc(isSize, sizeof(char)); if(isReverseString == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
    while(isRightIndex >= isLeftIndex){if(isRightIndex - 1 >= 0 && *(isString + isRightIndex) == ' ' && *(isString + (isRightIndex - 1)) == ' '){isRightIndex--; continue;} *(isReverseString + isReverseIndex++) = *(isString + isRightIndex--);}
    *(isReverseString + isReverseIndex) = '\0';
    return isReverseString;
}

// Returns A String With The Order Of Word(s) Reversed. Leading And Trailing Spaces Are Removed. The Words Are Separated By A Single Space.
char *isReverseWordString(char *isString){
    if(isString == NULL || *isString == '\0'){return NULL;}
    bool isFirstWord = false, isLastWord = false;
    int isSize = 0, isLeftIndex = 0, isRightIndex = 0, isReverseIndex = 0, isWordLeft = 0, isWordRight = 0;
    while(*(isString + isSize) != '\0'){(*(isString + isSize) != ' ') && (isFirstWord = true); if(!isFirstWord && *(isString + isLeftIndex) == ' '){isLeftIndex++;} isSize++;}
    isRightIndex = isSize - 1;
    while(isRightIndex >= 0 && *(isString + isRightIndex) == ' '){isRightIndex--;}
    isSize = isRightIndex - isLeftIndex + 2;
    char *isReverseWordString = calloc(isSize + 1, sizeof(char)); if(isReverseWordString == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
    while(isRightIndex >= isLeftIndex){if(isRightIndex - 1 >= 0 && *(isString + isRightIndex) == ' ' && *(isString + (isRightIndex - 1)) == ' '){isRightIndex--; continue;} *(isReverseWordString + isReverseIndex++) = *(isString + isRightIndex--);}
    *(isReverseWordString + isReverseIndex) = '\0';
    isLeftIndex = 0; isRightIndex = 0;
    char isPlaceholder;
    while(isLeftIndex < isSize){
        while(*(isReverseWordString + isLeftIndex) == ' '){isLeftIndex++; continue;}
        isRightIndex = isLeftIndex;
        while(isRightIndex < isSize && *(isReverseWordString + isRightIndex) != ' '){if(*(isReverseWordString + isRightIndex) == '\0'){isLastWord = true; break;} isRightIndex++;}
        isWordLeft = isLeftIndex; isWordRight = isRightIndex - 1;
        while(isWordLeft < isWordRight){
            isPlaceholder = *(isReverseWordString + isWordRight);
            *(isReverseWordString + isWordRight) = *(isReverseWordString + isWordLeft); *(isReverseWordString + isWordLeft) = isPlaceholder;
            isWordLeft++, isWordRight--;
        }
        (isLastWord) && (isRightIndex++); isLeftIndex = isRightIndex;
    }
    return isReverseWordString;
}

// Return The Index Of The First Occurrence Of The SubString In The String If Found, Otherwise Return -1.
int isFirstSubstringOccurence(char *isString, char *isSubString){
    if(isString == NULL || *isString == '\0' || isSubString == NULL || *isSubString == '\0'){return -1;}
    int isIndex = 0, isSubIndex = 0, isMatchIndex = -1;
    while(*(isString + isIndex) != '\0'){
        if(*(isString + isIndex) == *(isSubString + isSubIndex)){
			isMatchIndex = isIndex;
			while(*(isString + isIndex) == *(isSubString + isSubIndex) && *(isSubString + isSubIndex) != '\0'){isMatchIndex++; isSubIndex++;}
			if(*(isSubString + isSubIndex) == '\0'){return isIndex;}
			isSubIndex = 0;
		}
		isIndex++;
    }
    return -1;
}

// Return The Number Of Substrings In A String.
int isSubStringCount(char *isString, char *isSubString){
    if(isString == NULL || *isString == '\0' || isSubString == NULL || *isSubString == '\0'){return 0;}
    int isIndex = 0, isSubIndex = 0, isMatchIndex = -1, isCount = 0;
    while(*(isString + isIndex) != '\0'){
		isMatchIndex = isIndex;
		while(*(isString + (isMatchIndex + isSubIndex)) == *(isSubString + isSubIndex) && *(isSubString + isSubIndex) != '\0'){isSubIndex++;}
		if(*(isSubString + isSubIndex) == '\0'){isCount++;} isSubIndex = 0; isIndex++;
    }
    return isCount;
}

// Returns A Pointer To The SubString If Found Otherwise Return NULL.
char *isSubStringPtr(char *isString, char *isSubString){
	if(isString == NULL || *isString == '\0' || isSubString == NULL || *isSubString == '\0'){return NULL;}
	int isIndex = 0, isSubIndex = 0;
	while(*(isString + isIndex) != '\0'){
		if(*(isString + isIndex) == *(isSubString + isSubIndex)){
			isSubIndex++;
			while(*(isSubString + isSubIndex) != '\0' && *(isString + (isIndex + isSubIndex)) == *(isSubString + isSubIndex)){isSubIndex++;}
			if(*(isSubString + isSubIndex) == '\0'){return (isString + isIndex);} else{isSubIndex = 0;}
		}
		isIndex++;
	}
	return NULL;
}

// Returns True If The SubString Is The Prefix Of The String, Otherwise Return False.
bool isStringSuffix(char *isString, char *isSubString){
	if(isString == NULL || *isString == '\0' || isSubString == NULL || *isSubString == '\0'){return false;}
	int isIndex = 0, isSubIndex = 0, isPlacement = 0;
	while(*(isString + isIndex) != '\0'){isIndex++;} while(*(isSubString + isSubIndex) != '\0'){isSubIndex++;}
	if(isSubIndex > isIndex){return 0;} isPlacement = isIndex - isSubIndex; isIndex = 0;
	char isStr, isSubStr;
	while(isIndex < isSubIndex){
		isStr = (*(isString + (isPlacement + isIndex)) >= 'A' && *(isString + (isPlacement + isIndex)) <= 'Z') ? *(isString + (isPlacement + isIndex)) + ('a' - 'A') : *(isString + (isPlacement + isIndex));
		isSubStr = (*(isSubString + isIndex) >= 'A' && *(isSubString + isIndex) <= 'Z') ? *(isSubString + isIndex) + ('a' - 'A') : *(isSubString + isIndex);
		if(isStr != isSubStr){return false;} isIndex++;
	}
	return true;
}

// Returns The Longest Common Prefix String Amongst An Array Of Strings If Found, Otherwise Return An Empty String.
char *isLongestCommonPrefix(char **isArray, int isSize){
    if(isArray == NULL || isSize <= 0){fprintf(stderr, "Invalid Array.\n"); return NULL;}
    int initialPrefixSize = strlen(*isArray) + 1;
    char *isPrefix = calloc(initialPrefixSize, sizeof(char)); if(isPrefix == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
    strlcpy(isPrefix, *isArray, initialPrefixSize);
    if(isSize == 1){return isPrefix;}
    int isLength = 0, isMatch = -1, isFollow = 0;
    for(int isIndex = 1; isIndex < isSize; isIndex++){
        for(; *(*(isArray + isIndex) + isLength) != '\0'; isLength++){
            if(*(isPrefix + isFollow) == *(*(isArray + isIndex) + isLength)){isFollow++;} else{break;}
        }
        isMatch = isMatch == -1 ? isFollow : isFollow > isMatch ? isMatch : isFollow;
        isLength = 0; isFollow = 0;
    }
    char *shortenPrefix = realloc(isPrefix, sizeof(char) * (isMatch + 1)); if(shortenPrefix == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
    isPrefix = shortenPrefix; *(isPrefix + isMatch) = '\0';
    return isPrefix;
}

// Return True If A Sequence Is A Subsequence Of A String, Otherwise Return False.
bool isStringSubSequence(char *isString, char *isSequence){
    if(isString == NULL){fprintf(stderr, "Invalid String.\n"); return false;}
    if(*isString == '\0' && *isSequence == '\0' || *isSequence == '\0' && *isString != '\0'){return true;}
    else if(*isString == '\0' && *isSequence != '\0'){return false;}
    int isLength = 0, isIndex = 0;
    bool isSubSequence = false;
    for(; *(isString + isLength) != '\0'; isLength++){
        (*(isString + isLength) == *(isSequence + isIndex)) && (isIndex++); if(*(isSequence + isIndex) == '\0'){isSubSequence = true; break;}
    }
    return isSubSequence;
}

// Return The Longest Substring Without Repeating Characters.
char *isLongestDistinctSubString(char *isString, int *isSubStringLength){
	if(isString == NULL || *isString == '\0'){fprintf(stderr, "Invalid String\n"); return 0;}
	int isIndex = 0, isFront = 0, isBack = 0, isLength = 0, isIterate = -1;
	while(*(isString + isIndex) != '\0'){
		if(isIndex > 0){
			isIterate = isIndex - 1;
			while(isIterate >= isFront){
				if(*(isString + isIterate) == *(isString + isIndex)){
					(isIndex - isFront > isLength) && (isLength = isIndex - isFront);
					isFront = isIterate + 1; isBack = isIndex; break;
				}
				isIterate--;
			}
			if(*(isString + (isIndex + 1)) == '\0' && isFront != isIndex){(isIndex - isFront + 1 > isLength) && (isLength = isIndex - isFront + 1, isBack = isIndex);}
		}
		isIndex++;
	}
	(isLength == 0 && isIndex > 0) && (isLength = isIndex == 1 ? isIndex : isIndex - 1);
	char *isSubString = calloc(isLength + 1, sizeof(char)); if(isSubString == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
	*isSubStringLength = isLength; isIndex = 0;
	while(isFront <= isBack){*(isSubString + isIndex++) = *(isString + isFront++);}
	*(isSubString + isIndex) = '\0';
	return isSubString;
}

// Returns The Smallest, Second Smallest, Second Largest And Largest Values In An Array
int *isSmallestAndLargestPair(int *isArray, int isSize){
    if(isArray == NULL || isSize <= 0){fprintf(stderr, "Invalid Array.\n"); return NULL;}
    int *isPair = calloc(4, sizeof(int)); if(isPair == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
    int isLargest = INT_MIN, isSecondLargest = INT_MIN, isSmallest = INT_MAX, isSecondSmallest = INT_MAX;
    for(int isIndex = 0; isIndex < isSize; isIndex++){
        (*(isArray + isIndex) > isLargest) && (isSecondLargest = isLargest, isLargest = *(isArray + isIndex));
        (*(isArray + isIndex) > isSecondLargest && *(isArray + isIndex) < isLargest) && (isSecondLargest = *(isArray + isIndex));
        (*(isArray + isIndex) < isSmallest) && (isSecondSmallest = isSmallest, isSmallest = *(isArray + isIndex));
        (*(isArray + isIndex) < isSecondSmallest && *(isArray + isIndex) > isSmallest) && (isSecondSmallest = *(isArray + isIndex));
    }
    *isPair = isSmallest; *(isPair + 1) = isSecondSmallest; *(isPair + 2) = isSecondLargest; *(isPair + 3) = isLargest;
    return isPair;
}

// Rotate An Array To Either Right Or Left By N.
void rotateArray(int *isArray, int isSize, char isDirection, int isCount){
    if(isArray == NULL || isSize <= 0){fprintf(stderr, "Invalid Array.\n"); return;}
    if(isDirection != 'R' && isDirection != 'L' || isCount < 0){fprintf(stderr, "Invalid Rotation.\n"); return;}
    int *isRotationIndex = calloc(isSize, sizeof(int)); if(isRotationIndex == NULL){return;}
    for(int isIndex = 0; isIndex < isSize; isIndex++){
		int isWarp = isDirection == 'R' ? (isIndex + isCount) % isSize : (isIndex + (isSize - isCount)) % isSize;
        *(isRotationIndex + isWarp) = *(isArray + isIndex);
    }
    int isAssignment = 0;
    while(isAssignment < isSize){*(isArray + isAssignment) = *(isRotationIndex + isAssignment); isAssignment++;}
    free(isRotationIndex); isRotationIndex = NULL;
    return;
}

// Merge The Contents Of The Sorted Arrays, SubSet And Container Into The Container.
void mergeSortedArray(int *isContainer, int *isSubset, int isContainerSize, int isContainerCount, int isSubsetSize, int isSubsetCount){
    if(isContainer == NULL || isContainerSize <= 0){fprintf(stderr, "Invalid Array.\n"); return -1;}
    if(isContainerSize < isSubsetSize){fprintf(stderr, "Invalid Operation.\n"); return -1;}
    int isIndex = isContainerSize - 1, isContainerIndex = isContainerCount - 1, isSubsetIndex = isSubsetCount - 1;
    while(isIndex >= 0){
        if(isContainerIndex >= 0 && isSubsetIndex >= 0){
            if(*(isContainer + isContainerIndex) > *(isSubset + isSubsetIndex)){*(isContainer + isIndex--) = *(isContainer + isContainerIndex--);}
            else{*(isContainer + isIndex--) = *(isSubset + isSubsetIndex--);}
        } else{
            if(isContainerIndex < 0){*(isContainer + isIndex--) = *(isSubset + isSubsetIndex--);}
            else if(isSubsetIndex < 0){*(isContainer + isIndex--) = *(isContainer + isContainerIndex--);}
        }
    }
    return;
}

// Sort An Array That Contains 3 Type Of Element So That Each Element Is Grouped.
void dutchNationalFlag(int *isArray, int isSize, int isMiddle){
    if(isArray == NULL || isSize <= 0){fprintf(stderr, "Invalid Array.\n"); return;}
    int isFirstIndex = 0, isMiddleIndex = 0, isLastIndex = isSize - 1, isPlaceholder = -1;
    while(isMiddleIndex <= isLastIndex){
        if(*(isArray + isMiddleIndex) < isMiddle){
            isPlaceholder = *(isArray + isMiddleIndex); *(isArray + isMiddleIndex) = *(isArray + isFirstIndex); *(isArray + isFirstIndex) = isPlaceholder;
            isFirstIndex++; isMiddleIndex++;
        } else if(*(isArray + isMiddleIndex) > isMiddle){
            isPlaceholder = *(isArray + isMiddleIndex); *(isArray + isMiddleIndex) = *(isArray + isLastIndex); *(isArray + isLastIndex) = isPlaceholder;
            isLastIndex--;
        } else{isMiddleIndex++;}
    }
    return;
}

// Sorts An Array, In-Place With Insertion-Sort Algorithm.
void insertionSort(int *isArray, int isSize){
    if(isArray == NULL || isSize <= 0){fprintf(stderr, "Invalid Array.\n"); return;} if(isSize == 1){return;}
	int isElement, isIndex = 1, isSearchIndex = -1;
	while(isIndex < isSize){
		isElement = *(isArray + isIndex); isSearchIndex = isIndex;
		while(isSearchIndex > 0  && *(isArray + (isSearchIndex - 1)) > isElement){
			*(isArray + isSearchIndex) = *(isArray + (isSearchIndex - 1));
			isSearchIndex--;
		}
		*(isArray + isSearchIndex) = isElement;
		isIndex++;
	}
	return;
}

// Sorts An Array, In-Place With Selection-Sort Algorithm.
void selectionSort(int *isArray, int isSize){
    if(isArray == NULL || isSize <= 0){fprintf(stderr, "Invalid Array.\n"); return;} if(isSize == 1){return;}
	int isIndex = 0, isSearchIndex = -1, isElementIndex = -1, isPlaceholder = -1;
	while(isIndex < isSize - 1){
		isElementIndex = isIndex; isSearchIndex = isIndex + 1;
		while(isSearchIndex < isSize){
			(*(isArray + isSearchIndex) < *(isArray + isElementIndex)) && (isElementIndex = isSearchIndex);
			isSearchIndex++;
		}
		if(isElementIndex != isIndex){
			isPlaceholder = *(isArray + isElementIndex);
			*(isArray + isElementIndex) = *(isArray + isIndex); *(isArray + isIndex) = isPlaceholder;
		}
		isIndex++;
	}
	return;
}

// Sorts An Array, In-Place With Merge-Sort Algorithm.
void mergeSort(int *isArray, int isSize){
    if(isArray == NULL || isSize <= 0){fprintf(stderr, "Invalid Array.\n"); return;} if(isSize == 1){return;}
	int *isContainer = calloc(isSize, sizeof(int)); if(isContainer == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return;}
	int isIndex = 1, isLeft, isMiddle, isRight, isLeftPlacement, isMiddlePlacement, isPlacement;
	while(isIndex < isSize){
		isLeft = 0;
		while(isLeft + isIndex < isSize){
			isMiddle = isLeft + isIndex;
			isRight = isMiddle + isIndex > isSize ? isSize : isMiddle + isIndex;
			isPlacement = isLeft; isLeftPlacement = isLeft; isMiddlePlacement = isMiddle;
			while(isLeftPlacement < isMiddle && isMiddlePlacement < isRight){
				*(isContainer + isPlacement++) = *(isArray + isLeftPlacement) <= *(isArray + isMiddlePlacement) ? *(isArray + isLeftPlacement++) : *(isArray + isMiddlePlacement++);
			}
			while(isLeftPlacement < isMiddle){*(isContainer + isPlacement++) = *(isArray + isLeftPlacement++);}
			while(isMiddlePlacement < isRight){*(isContainer + isPlacement++) = *(isArray + isMiddlePlacement++);}
			isPlacement = isLeft;
			while(isPlacement < isRight){*(isArray + isPlacement) = *(isContainer + isPlacement); isPlacement++;}
			isLeft += isIndex * 2;
		}
		isIndex *= 2;
	}
	free(isContainer); isContainer = NULL;
	return;
}

// Sorts An Array, In-Place With Quick-Sort Algorithm.
void quickSort(int *isArray, int isSize, char isOrder){
    if(isArray == NULL || isSize <= 0){fprintf(stderr, "Invalid Array.\n"); return;} if(isSize == 1){return;}
    if(isOrder != 'A' && isOrder != 'D'){fprintf(stderr, "Invalid Oder.\n"); return;}
    int *isStack = calloc(isSize, sizeof(int)); if(isStack == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return;}
    int isLow = 0, isHigh = isSize - 1, isTop = 0, isPartition = -1, isPivot = -1, isPlacement = -1, isPlaceholder;
    *(isStack + isTop++) = isLow; *(isStack + isTop) = isHigh;
    while(isTop >= 0){
        isHigh = *(isStack + isTop--); isLow = *(isStack + isTop--);
        isPivot = *(isArray + isHigh); isPlacement = isLow;
        for(int isIndex = isLow; isIndex < isHigh; isIndex++){
            if(isOrder == 'A' ? *(isArray + isIndex) < isPivot : *(isArray + isIndex) > isPivot){
                isPlaceholder = *(isArray + isPlacement); *(isArray + isPlacement) = *(isArray + isIndex);
                *(isArray + isIndex) = isPlaceholder; isPlacement++;
            }
        }
        isPlaceholder = *(isArray + isPlacement); *(isArray + isPlacement) = *(isArray + isHigh); 
        *(isArray + isHigh) = isPlaceholder; isPartition = isPlacement;
        if(isPartition - 1 > isLow){isTop++; *(isStack + isTop++) = isLow; *(isStack + isTop) = isPartition - 1;}
        if(isPartition + 1 < isHigh){isTop++; *(isStack + isTop++) = isPartition + 1; *(isStack + isTop) = isHigh;}
    }
    free(isStack); isStack = NULL;
    return;
}

// Sorts An Array, In-Place With Shell-Sort Algorithm.
void shellSort(int *isArray, int isSize){
    if(isArray == NULL || isSize <= 0){fprintf(stderr, "Invalid Array.\n"); return;} if(isSize == 1){return;}
	int isIndex = isSize/2, isPlacement = -1, isSearchIndex = -1, isPlaceholder = -1;
	while(isIndex > 0){
		isPlacement = isIndex;
		while(isPlacement < isSize){
			isPlaceholder = *(isArray + isPlacement); isSearchIndex = isPlacement;
			while(isSearchIndex >= isIndex && *(isArray + (isSearchIndex - isIndex)) > isPlaceholder){
				*(isArray + isSearchIndex) = *(isArray + (isSearchIndex - isIndex));
				isSearchIndex -= isIndex;
			}
			*(isArray + isSearchIndex) = isPlaceholder; isPlacement++;
		}
		isIndex /= 2;
	}
	return;
}

// Sorts An Array, In-Place With Comb-Sort Algorithm.
void combSort(int *isArray, int isSize){
    if(isArray == NULL || isSize <= 0){fprintf(stderr, "Invalid Array.\n"); return;} if(isSize == 1){return;}
	int isIndex = isSize, isSearchIndex, isPlaceholder;
	double isShrinkFactor = 1.3;
	bool isSorted = false;
	while(!isSorted){
		isIndex = isIndex/isShrinkFactor;
		(isIndex <= 1) && (isIndex = 1, isSorted = true);
		(isIndex == 9  || isIndex == 10) && (isIndex = 11);
		isSearchIndex = 0;
		while(isSearchIndex + isIndex < isSize){
			if(*(isArray + isSearchIndex) > *(isArray + (isSearchIndex + isIndex))){
				isPlaceholder = *(isArray + isSearchIndex); isSorted = false;
				*(isArray + isSearchIndex) = *(isArray + (isSearchIndex + isIndex));
				*(isArray + (isSearchIndex + isIndex)) = isPlaceholder;
			}
			isSearchIndex++;
		}
	}
	return;
}

// Sorts An Array, In-Place With Tim-Sort Algorithm.
void timSort(int *isArray, int isSize){
    if(isArray == NULL || isSize <= 0){fprintf(stderr, "Invalid Array.\n"); return;} if(isSize == 1){return;}
    int isSegmentSize = 32, isIndex = 0, isLeft = 0, isRight = 0, isPlacement = 0, isPlaceholder, isMiddle;
    while(isIndex < isSize){
        isLeft = isIndex + 1; isRight = isIndex + isSegmentSize < isSize ? isIndex + isSegmentSize : isSize;
        while(isLeft < isRight){
            isPlaceholder = *(isArray + isLeft); isPlacement = isLeft - 1;
            while(isPlacement >= isIndex && *(isArray + isPlacement) > isPlaceholder){
                *(isArray + (isPlacement + 1)) = *(isArray + isPlacement); isPlacement--;
            }
            *(isArray + (isPlacement + 1)) = isPlaceholder; isLeft++;
        }
        isIndex += isSegmentSize;
    }
    isIndex = isSegmentSize;
    int *isLeftArray = calloc(1, sizeof(int)); if(isLeftArray == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return;} 
    int *isRightArray = calloc(1, sizeof(int)); if(isRightArray == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return;}
    int isLeftSize = 1, isRightSize = 1, deriveLeftSize, deriveRightSize, isLeftIndex, isRightIndex, *resizeArray = NULL;
    while(isIndex < isSize){
        isLeft = 0;
        while(isLeft < isSize){
            isMiddle = isLeft + isSize;
            isRight = isMiddle + isSize < isSize ? isMiddle + isSize : isSize;
            if(isMiddle < isRight){
                deriveLeftSize = isMiddle - isLeft;
                deriveRightSize = isRight - isMiddle;
                if(deriveLeftSize > isLeftSize){
                    resizeArray = realloc(isLeftArray, sizeof(int) * deriveLeftSize); if(resizeArray == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return;}
                    isLeftArray = resizeArray; isLeftSize = deriveLeftSize;
                }
                if(deriveRightSize > isRightSize){
                    resizeArray = realloc(isRightArray, sizeof(int) * deriveRightSize); if(resizeArray == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return;}
                    isRightArray = resizeArray; isRightSize = deriveRightSize;
                }
                for(int isEntry = 0; isEntry < deriveLeftSize; isEntry++){*(isLeftArray + isEntry) = *(isArray + (isLeft + isEntry));}
                for(int isEntry = 0; isEntry < deriveRightSize; isEntry++){*(isRightArray + isEntry) = *(isArray + (isMiddle + isEntry));}
                isLeftIndex = 0; isRightIndex = 0, isPlacement = isLeft;
                while(isLeftIndex < deriveLeftSize && isRightIndex < deriveRightSize){
                    *(isArray + isPlacement++) = *(isLeftArray + isLeftIndex) <= *(isRightArray + isRightIndex) ? *(isLeftArray + isLeftIndex++) : *(isRightArray + isRightIndex++);
                }
                while(isLeftIndex < deriveLeftSize){*(isArray + isPlacement++) = *(isLeftArray + isLeftIndex++);}
                while(isRightIndex < deriveRightSize){*(isArray + isPlacement++) = *(isRightArray + isRightIndex++);}
            }
            isLeft += isSize * 2;
        }
        isIndex *= 2;
    }
    free(isLeftArray); isLeftArray = NULL; free(isRightArray); isRightArray = NULL;
	return;
}

// Returns The Two Indices Of The Element That Add Up To The Sum If Found, Otherwise Returns [-1,-1].
int *isTwoSumIndex(int *isArray, int isSize, int isSum){
    if(isArray == NULL || isSize <= 0){fprintf(stderr, "Invalid Array.\n"); return NULL;} if(isSize == 1){return NULL;}
    int *isStack = calloc(isSize, sizeof(int)); if(isStack == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
    int isLow = 0, isHigh = isSize - 1, isTop = 0, isPartition = -1, isPivot = -1, isPlacement = -1, isPlaceholder;
    *(isStack + isTop++) = isLow; *(isStack + isTop) = isHigh;
    while(isTop >= 0){
        isHigh = *(isStack + isTop--); isLow = *(isStack + isTop--);
        isPivot = *(isArray + isHigh); isPlacement = isLow;
        for(int isIndex = isLow; isIndex < isHigh; isIndex++){
            if(*(isArray + isIndex) < isPivot){
                isPlaceholder = *(isArray + isPlacement); *(isArray + isPlacement) = *(isArray + isIndex);
                *(isArray + isIndex) = isPlaceholder; isPlacement++;
            }
        }
        isPlaceholder = *(isArray + isPlacement); *(isArray + isPlacement) = *(isArray + isHigh); 
        *(isArray + isHigh) = isPlaceholder; isPartition = isPlacement;
        if(isPartition - 1 > isLow){isTop++; *(isStack + isTop++) = isLow; *(isStack + isTop) = isPartition - 1;}
        if(isPartition + 1 < isHigh){isTop++; *(isStack + isTop++) = isPartition + 1; *(isStack + isTop) = isHigh;}
    }
    free(isStack); isStack = NULL;
    int *isIndices = calloc(2, sizeof(int)); if(isIndices == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
    int isLeft = 0, isRight = isSize - 1;
    bool hasSum = false;
    while(isLeft < isRight){
        (*(isArray + isLeft) + *(isArray + isRight) < isSum) && (isLeft++);
        (*(isArray + isLeft) + *(isArray + isRight) > isSum) && (isRight--);
        if(*(isArray + isLeft) + *(isArray + isRight) == isSum){hasSum = true; break;}
    }
    hasSum ? (*isIndices = isLeft, *(isIndices + 1) = isRight) : (*isIndices = -1, *(isIndices + 1) = -1);
    return isIndices;
}

// Return All The Unique Index Triplets Where For Each Set The Indices Are Unique, And The Summation Of Their ELement Add up to 0.
int **isThreeSumIndex(int *isArray, int isSize){
	if(isArray == NULL || isSize < 3){fprintf(stderr, "Invalid Array.\n"); return NULL;}
    int *isStack = calloc(isSize, sizeof(int)); if(isStack == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
    int isLow = 0, isHigh = isSize - 1, isTop = 0, isPartition = -1, isPivot = -1, isPlacement = -1, isPlaceholder;
    *(isStack + isTop++) = isLow; *(isStack + isTop) = isHigh;
    while(isTop >= 0){
        isHigh = *(isStack + isTop--); isLow = *(isStack + isTop--);
        isPivot = *(isArray + isHigh); isPlacement = isLow;
        for(int isIndex = isLow; isIndex < isHigh; isIndex++){
            if(*(isArray + isIndex) < isPivot){
                isPlaceholder = *(isArray + isPlacement); *(isArray + isPlacement) = *(isArray + isIndex);
                *(isArray + isIndex) = isPlaceholder; isPlacement++;
            }
        }
        isPlaceholder = *(isArray + isPlacement); *(isArray + isPlacement) = *(isArray + isHigh); 
        *(isArray + isHigh) = isPlaceholder; isPartition = isPlacement;
        if(isPartition - 1 > isLow){isTop++; *(isStack + isTop++) = isLow; *(isStack + isTop) = isPartition - 1;}
        if(isPartition + 1 < isHigh){isTop++; *(isStack + isTop++) = isPartition + 1; *(isStack + isTop) = isHigh;}
    }
    free(isStack); isStack = NULL;
	int isLargestPossible = (isSize * (isSize - 1) * (isSize - 2)) / 6;
	int **isIndices = calloc(isLargestPossible, sizeof(int *)); if(isIndices == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
	int isLeft = 0, isRight = 0, isSummation = 0, isEntry = 0;
	for(int isIndex = 0; isIndex < isSize - 2 ; isIndex++){
		if(isIndex > 0 && *(isArray + isIndex) == *(isArray + (isIndex - 1))){continue;} // change (isIndex - 1) -> (Index + 1) for no repeating element
		isLeft = isIndex + 1; isRight = isSize - 1;
		while(isLeft < isRight){
			isSummation = *(isArray + isIndex) + *(isArray + isLeft) + *(isArray + isRight);
			if(isSummation == 0){
				*(isIndices + isEntry) = calloc(3, sizeof(int)); if(*(isIndices + isEntry) == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
				**(isIndices + isEntry) = isIndex; *(*(isIndices + isEntry) + 1) = isLeft; *(*(isIndices + isEntry) + 2) = isRight; isEntry++;
				while(isLeft < isRight && *(isArray + isLeft) == *(isArray + (isLeft + 1))){isLeft++;}
				while(isLeft < isRight && *(isArray + isRight) == *(isArray + (isRight - 1))){isRight--;}
				isLeft++; isRight--;
			} else if(isSummation < 0){isLeft++;} else if(isSummation > 0){isRight--;}
		}
	}
    if(isEntry < isLargestPossible || isEntry > isLargestPossible){
        int **resizeIndices = realloc(isIndices, sizeof(int *) * isEntry); if(resizeIndices == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
        isIndices = resizeIndices;
    }
	return isIndices;
}

// Remove All Occurrences Of A Given Element In An Array In-Place. Return The Number Of Remaining Elements In The Array.
int removeElement(int *isArray, int isSize, int isElement){
    if(isArray == NULL || isSize <= 0){fprintf(stderr, "Invalid Array.\n"); return -1;}
    int isDistinctCount = 0;
    for(int isIndex = 0; isIndex < isSize; isIndex++){
        if(*(isArray + isIndex) != isElement){*(isArray + isDistinctCount++) = *(isArray + isIndex);}
    }
    for(int isPlacement = isDistinctCount; isPlacement < isSize; isPlacement++){*(isArray + isPlacement) = 0;}
    return isDistinctCount;
}

// Returns An Array Of Elements That Have Duplicates If Found, Otherwise Returns Null.
int *isDuplicates(int *isArray, int isSize, int *isDuplicateCount){
    if(isArray == NULL || isSize <= 0){fprintf(stderr, "Invalid Array.\n"); return NULL;} if(isSize == 1){*isDuplicateCount = 0; return NULL;}
    int *isStack = calloc(isSize, sizeof(int)); if(isStack == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
    int isLow = 0, isHigh = isSize - 1, isTop = 0, isPartition = -1, isPivot = -1, isPlacement = -1, isPlaceholder;
    *(isStack + isTop++) = isLow; *(isStack + isTop) = isHigh;
    while(isTop >= 0){
        isHigh = *(isStack + isTop--); isLow = *(isStack + isTop--);
        isPivot = *(isArray + isHigh); isPlacement = isLow;
        for(int isIndex = isLow; isIndex < isHigh; isIndex++){
            if(*(isArray + isIndex) < isPivot){
                isPlaceholder = *(isArray + isPlacement); *(isArray + isPlacement) = *(isArray + isIndex);
                *(isArray + isIndex) = isPlaceholder; isPlacement++;
            }
        }
        isPlaceholder = *(isArray + isPlacement); *(isArray + isPlacement) = *(isArray + isHigh); 
        *(isArray + isHigh) = isPlaceholder; isPartition = isPlacement;
        if(isPartition - 1 > isLow){isTop++; *(isStack + isTop++) = isLow; *(isStack + isTop) = isPartition - 1;}
        if(isPartition + 1 < isHigh){isTop++; *(isStack + isTop++) = isPartition + 1; *(isStack + isTop) = isHigh;}
    }
    free(isStack); isStack = NULL;
    int *isDuplicateElements = calloc(isSize/2, sizeof(int)); if(isDuplicateElements == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
    int isElement = *isArray, isEntry = 0;
    bool isDuplicate = false;
    for(int isIndex = 1; isIndex < isSize; isIndex++){
        (*(isArray + isIndex) == isElement && !isDuplicate) && (*(isDuplicateElements + isEntry++) = isElement, isDuplicate = true);
        (*(isArray + isIndex) != isElement) && (isElement = *(isArray + isIndex), isDuplicate = false);
    }
	*isDuplicateCount = isEntry;
    if(isEntry == 0){free(isDuplicateElements); isDuplicateElements = NULL;}
    return isDuplicateElements;
}

// Remove Duplicate Of Elements In An Array In-Place And Return The Number Of Distinct Elements.
int removeDuplicates(int *isArray, int isSize){
    if(isArray == NULL || isSize <= 0){fprintf(stderr, "Invalid Array.\n"); return -1;} if(isSize == 1){ return -1;}
    int *isStack = calloc(isSize, sizeof(int)); if(isStack == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return -1;}
    int isLow = 0, isHigh = isSize - 1, isTop = 0, isPartition = -1, isPivot = -1, isPlacement = -1, isPlaceholder;
    *(isStack + isTop++) = isLow; *(isStack + isTop) = isHigh;
    while(isTop >= 0){
        isHigh = *(isStack + isTop--); isLow = *(isStack + isTop--);
        isPivot = *(isArray + isHigh); isPlacement = isLow;
        for(int isIndex = isLow; isIndex < isHigh; isIndex++){
            if(*(isArray + isIndex) < isPivot){
                isPlaceholder = *(isArray + isPlacement); *(isArray + isPlacement) = *(isArray + isIndex);
                *(isArray + isIndex) = isPlaceholder; isPlacement++;
            }
        }
        isPlaceholder = *(isArray + isPlacement); *(isArray + isPlacement) = *(isArray + isHigh); 
        *(isArray + isHigh) = isPlaceholder; isPartition = isPlacement;
        if(isPartition - 1 > isLow){isTop++; *(isStack + isTop++) = isLow; *(isStack + isTop) = isPartition - 1;}
        if(isPartition + 1 < isHigh){isTop++; *(isStack + isTop++) = isPartition + 1; *(isStack + isTop) = isHigh;}
    }
    free(isStack); isStack = NULL; isPlacement = 0;
    for(int isIndex = 1; isIndex < isSize; isIndex++){
        if(*(isArray + isIndex) != *(isArray + isPlacement)){isPlacement++; *(isArray + isPlacement) = *(isArray + isIndex);}
    }
    for(isPlaceholder = isPlacement + 1; isPlaceholder < isSize; isPlaceholder++){*(isArray + isPlaceholder) = 0;}
    return isPlacement + 1;
}

//  Returns The Majority Element.
int majorityElement(int *isArray, int isSize){
    if(isArray == NULL || isSize <= 0){fprintf(stderr, "Invalid Array.\n"); return -1;}
    int isMajority = -1, isEntry = 0, isEntrySize = 1, hasEntry = -1, isHighestOccurence = 0, isOccurence = 1;
    int **isElements = calloc(2, sizeof(int *)); if(isElements == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return -1;}
    *isElements = calloc(1, sizeof(int)); if(*isElements == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return -1;} *(*isElements + isEntry) = *isArray;
    *(isElements + 1) = calloc(1, sizeof(int)); if(*(isElements + 1) == NULL){fprintf(stderr, "Memory Allocation Failed.\n");return -1;} *(*(isElements + 1) + isEntry++) = 1;
    for(int isIndex = 1; isIndex < isSize; isIndex++){
        if(*(isArray + isIndex) != *(*(isElements) + isHighestOccurence)){
            for(int thisEntry = 0; thisEntry < isEntry; thisEntry++){if(*(*isElements + thisEntry) == *(isArray + isIndex)){hasEntry = thisEntry; break;}}
            if(hasEntry == -1){
                isEntrySize++;
                int *extendElementIndex = realloc(*isElements, sizeof(int) * isEntrySize); if(extendElementIndex == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return -1;}
                int *extendElementCount = realloc(*(isElements + 1), sizeof(int) * isEntrySize); if(extendElementCount == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return -1;}
                *isElements = extendElementIndex; *(isElements + 1) = extendElementCount; *(*(isElements) + isEntry) = *(isArray + isIndex); *(*(isElements + 1) + isEntry++) = 1;
            } else{*(*(isElements + 1) + hasEntry) += 1; (*(*(isElements + 1) + hasEntry) > isOccurence) && (isHighestOccurence = hasEntry, isOccurence = *(*(isElements + 1) + hasEntry));}
            hasEntry = -1;
        }
        else{*(*(isElements + 1) + isHighestOccurence) += 1; isOccurence++;}
    }
    isMajority = *(*isElements + isHighestOccurence);
    free(*isElements); *isElements = NULL;
    free(*(isElements + 1)); *(isElements + 1) = NULL;
    free(isElements); isElements = NULL;
    return isMajority;
}

// Return The Largest SubArray Sum In The Array.
int kadanesAlgorithm(int *isArray, int isSize){
    if(isArray == NULL || isSize <= 0){fprintf(stderr, "Invalid Array.\n"); return -1;} if(isSize == 1){return *isArray;}
    int isMaxSum = *isArray, isCurrentSum = *isArray, isIndex = 1;
    while(isIndex < isSize){
		isCurrentSum = *(isArray + isIndex) > isCurrentSum + *(isArray + isIndex) ? *(isArray + isIndex) : isCurrentSum + *(isArray + isIndex); 
		if(isCurrentSum > isMaxSum){isMaxSum = isCurrentSum;} isIndex++;
	}
    return isMaxSum;
}

// Return The Minimal Length Of A Subarray In A Positive Array, Whose Sum Is Greater Than Or Equal To A Target Value If Found, Otherwise Return 0.
int isMininumSubSumLength(int *isArray, int isSize, int isSum){
    if(isArray == NULL || isSize <= 0){fprintf(stderr, "Invalid Array.\n"); return 0;}
    if(isSum < 0){fprintf(stderr, "Negative Sum.\n"); return NULL;}
    int isSubSumLength = 0, isNearestSum = 0, isFront = 0;
    for(int isIndex = 0; isIndex < isSize; isIndex++){
        isNearestSum += *(isArray + isIndex);
        while(isNearestSum >= isSum){
            isSubSumLength = isSubSumLength == 0 ? isIndex - isFront + 1 : ((isIndex - isFront + 1) < isSubSumLength) ? isIndex - isFront + 1 : isSubSumLength;
            isNearestSum -= *(isArray + (isFront++));
        }
    }
    return isSubSumLength;
}

// Given an unsorted array A of size N that contains only non-negative integers, find a continuous sub-array which adds to a given number S and return the starting and ending indexes
int *isContinuousSubSumIndex(int *isArray, int isSize, int isSum){
	if(isArray == NULL || isSize <= 0){fprintf(stderr, "Invalid Array.\n"); return NULL;}
	if(isSum < 0){fprintf(stderr, "Negative Sum.\n"); return NULL;}
	int *isIndices = calloc(2, sizeof(int)); if(isIndices == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
	int isIndex = 0, isCurrentSum = 0, isLeft = 0, isLength = -1;
	while(isIndex < isSize){
		isCurrentSum += *(isArray + isIndex);
		while(isCurrentSum >= isSum){
			if(isCurrentSum == isSum){
				if(isLength == -1 || isIndex - isLeft < isLength){
                    *isIndices = isLeft; *(isIndices + 1) = isIndex; isLength = isIndex - isLeft;
                }
			}
			isCurrentSum -= *(isArray + isLeft++);
		}
		isIndex++;
	}
	if(isLength == -1){*isIndices = -1, *(isIndices + 1) = -1;}
	return isIndices;
}

// Return The Minimum Path Sum From Top To Bottom In A Triangle Array. Movement Is Restricted To Adjacent Elements Being Either Index OR Index + 1 From The Current Row.
int triangleMinimumHeight(int **isTriangle, int *isDimension){
    int isMinimumCost = 0, isFollow = *(isDimension + 1);
    for(int isRow = *isDimension - 2; isRow >= 0; isRow--){
        for(int isColumn = 0; isColumn < isFollow; isColumn++){
            *(*(isTriangle + isRow) + isColumn) += *(*(isTriangle + (isRow + 1)) + isColumn) < *(*(isTriangle + (isRow + 1)) + (isColumn + 1)) ? *(*(isTriangle + (isRow + 1)) + isColumn) : *(*(isTriangle + (isRow + 1)) + (isColumn + 1));
        }
        isFollow--;
    }
    isMinimumCost = **isTriangle;
    return isMinimumCost;
}

// ====================================================================================================================================================================================================================================== //

// Return The Area Of The Largest Rectangle Only Containing 1s In A Binary Matrix Filled With 0's And 1's.
int maximalRectangle(int **isMatrix, int *isDimension){
    int isMaxArea = 0;
    int *isHeight = calloc(*(isDimension + 1), sizeof(int)); if(isHeight == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return 0;}
    for(int isRow = 0; isRow < *isDimension; isRow++){
        for(int isColumn = 0; isColumn < *(isDimension + 1); isColumn++){
            (*(*(isMatrix + isRow) + isColumn) == 0) ? (*(isHeight + isColumn) = 0) : (*(isHeight + isColumn) += *(*(isMatrix + isRow) + isColumn));
        }
        int *isStack = calloc(*(isDimension + 1) + 1, sizeof(int)); if(isStack == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return 0;}
        int hasArea = 0, isTop = -1;
        for(int isIndex = 0; isIndex <= *(isDimension + 1); isIndex++){
            while(isTop >= 0 && (isIndex == *(isDimension + 1) || *(isHeight + *(isStack + isTop)) > *(isHeight + isIndex))){
                int hasHeight = *(isHeight + *(isStack + isTop)); isTop--;
                int hasWidth = isTop == -1 ? isIndex : isIndex - *(isStack + isTop) - 1;
                hasArea = (hasArea > hasHeight * hasWidth) ? hasArea : hasHeight * hasWidth;
            }
            *(isStack + (++isTop)) = isIndex;
        }
        free(isStack); isStack = NULL;
        isMaxArea = isMaxArea > hasArea ? isMaxArea : hasArea;
    }
    return isMaxArea;
}

/*
You are given an array prices where prices[i] is the price of a given stock on the ith day.
You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.
Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.
*/
int timelyBuyAndSellStocks(int *isPrices, int isSize){
    int isPossibleProfit = 0, isBuyIndex = 0, isSellIndex = -1, isAltBuyIndex = -1, isAltSellIndex = -1;
    for(int isIndex = 0; isIndex < isSize; isIndex++){
        (*(isPrices + isIndex) < *(isPrices + isBuyIndex)) && ((isSellIndex == -1) ? (isBuyIndex = isIndex) : (isAltBuyIndex = (isAltBuyIndex == -1) ? isIndex : (*(isPrices + isIndex) < *(isPrices + isAltBuyIndex)) ? isAltSellIndex = -1, isIndex : isAltBuyIndex));
        (isSellIndex == -1) ? ((*(isPrices + isIndex) > *(isPrices + isBuyIndex)) && (isSellIndex = isIndex)) : ((isAltBuyIndex == -1) ? ((*(isPrices + isIndex) > *(isPrices + isSellIndex)) && (isSellIndex = isIndex)) : ((*(isPrices + isIndex) > *(isPrices + isAltBuyIndex)) && (isAltSellIndex = (isAltSellIndex == -1) ? (isIndex) : (*(isPrices + isIndex) > *(isPrices + isAltSellIndex)) ? isIndex : isAltSellIndex)));
        (isAltBuyIndex != -1 && isAltSellIndex != -1 && ((*(isPrices + isAltSellIndex) - *(isPrices + isAltBuyIndex)) > (*(isPrices + isSellIndex) - *(isPrices + isBuyIndex)))) && (isBuyIndex = isAltBuyIndex, isSellIndex = isAltSellIndex);
    }
    (isSellIndex != -1) && (isPossibleProfit = *(isPrices + isSellIndex) - *(isPrices + isBuyIndex));
    return isPossibleProfit;
}

/*
You are given a sorted unique integer array nums.
A range [a,b] is the set of all integers from a to b (inclusive).
Return the smallest sorted list of ranges that cover all the numbers in the array exactly. That is, each element of nums is covered by exactly one of the ranges, and there is no integer x such that x is in one of the ranges but not in nums.
*/
char **summaryRanges(int *isArray, int isSize){
    if(isArray == NULL || isSize <= 0){fprintf(stderr, "Invalid Array.\n"); return NULL;}
    char **isRange = calloc(1, sizeof(char *));
    if(isSize == 1){
        int isLength = snprintf(NULL, 0, "%d", *isArray);
        *isRange = calloc(isLength + 1, sizeof(char));
        snprintf(*isRange, isLength + 1, "%d", *isArray);
        return isRange;
    }
    int isEntry = 0, isSequenceStart = 0, isSequenceEnd = -1;
    for(int isIndex = 1; isIndex < isSize; isIndex++){
        if((long long)*(isArray + isIndex) - (long long)*(isArray + (isIndex -1)) == 1){isSequenceEnd = isIndex;}
        else{
            int startLength, endLength;
            startLength = snprintf(NULL, 0, "%d", *(isArray + isSequenceStart));
            (isSequenceEnd != -1) && (endLength = snprintf(NULL, 0, "%d", *(isArray + isSequenceEnd)));
            *(isRange + isEntry) = isSequenceEnd == -1 ? calloc(startLength + 1, sizeof(char)) : calloc(startLength + endLength + 3, sizeof(char)); if(*(isRange + isEntry) == NULL){return NULL;}
            isSequenceEnd == -1 ? snprintf(*(isRange + isEntry), startLength + 1, "%d", *(isArray + isSequenceStart)) : snprintf(*(isRange + isEntry), startLength + endLength + 3, "%d->%d", *(isArray + isSequenceStart), *(isArray + isSequenceEnd));
            isEntry++;
            char **extendRange = realloc(isRange, sizeof(char *) * (isEntry + 1)); if(extendRange == NULL){return NULL;} isRange = extendRange;
            isSequenceStart = isIndex; isSequenceEnd = -1;
        }
        if(isIndex == isSize - 1){
            int startLength, endLength;
            startLength = snprintf(NULL, 0, "%d", *(isArray + isSequenceStart));
            (isSequenceEnd != -1) && (endLength = snprintf(NULL, 0, "%d", *(isArray + isSequenceEnd)));
            *(isRange + isEntry) = isSequenceEnd == -1 ? calloc(startLength + 1, sizeof(char)) : calloc(startLength + endLength + 3, sizeof(char)); if(*(isRange + isEntry) == NULL){return NULL;}
            isSequenceEnd == -1 ? snprintf(*(isRange + isEntry), startLength + 1, "%d", *(isArray + isSequenceStart)) : snprintf(*(isRange + isEntry), startLength + endLength + 3, "%d->%d", *(isArray + isSequenceStart), *(isArray + isSequenceEnd));
        }
    }
    return isRange;
}

//Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals, and return an array of the non-overlapping intervals that cover all the intervals in the input.
int **mergeIntervals(int **isMatrix, int isSize, int *isResize){
	if(isMatrix == NULL || isSize <= 0){fprintf(stderr, "Invalid Array.\n"); return NULL;} if(isSize == 1){return isMatrix;}
	int *isStack = calloc(isSize, sizeof(int)); if(isStack == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
	int isLow = 0, isHigh = isSize - 1, isTop = 0, isPartition = -1, isPivot = -1, isPlacement = -1, *isPlaceholder;
	*(isStack + isTop++) = isLow; *(isStack + isTop) = isHigh;
	while(isTop >= 0){
        isHigh = *(isStack + isTop--); isLow = *(isStack + isTop--);
        isPivot = **(isMatrix + isHigh); isPlacement = isLow;
        for(int isIndex = isLow; isIndex < isHigh; isIndex++){
            if(**(isMatrix + isIndex) < isPivot){
                isPlaceholder = *(isMatrix + isPlacement); *(isMatrix + isPlacement) = *(isMatrix + isIndex);
                *(isMatrix + isIndex) = isPlaceholder; isPlacement++;
            }
        }
        isPlaceholder = *(isMatrix + isPlacement); *(isMatrix + isPlacement) = *(isMatrix + isHigh); 
        *(isMatrix + isHigh) = isPlaceholder; isPartition = isPlacement;
        if(isPartition - 1 > isLow){isTop++; *(isStack + isTop++) = isLow; *(isStack + isTop) = isPartition - 1;}
        if(isPartition + 1 < isHigh){isTop++; *(isStack + isTop++) = isPartition + 1; *(isStack + isTop) = isHigh;}
    }
    free(isStack); isStack = NULL;
	int **isIntervals = calloc(isSize, sizeof(int *)); if(isIntervals == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
	int isIndex = 0, isEnd = -1, isIteration = 0, isEntry = 0;
	while(isIndex < isSize){
		isEnd = *(*(isMatrix + isIndex) + 1); isIteration = isIndex + 1;
		if(isIteration < isSize){
			while(isEnd >= **(isMatrix + isIteration)){isEnd = *(*(isMatrix + isIteration) + 1); isIteration++;}
			*(isIntervals + isEntry) = calloc(2, sizeof(int)); if(*(isIntervals + isEntry) == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
			**(isIntervals + isEntry) = **(isMatrix + isIndex); *(*(isIntervals + isEntry) + 1) = isEnd; isEntry++; isIndex = isIteration;
		} else{
			*(isIntervals + isEntry) = calloc(2, sizeof(int)); if(*(isIntervals + isEntry) == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
			**(isIntervals + isEntry) = **(isMatrix + isIndex); *(*(isIntervals + isEntry) + 1) = isEnd; isEntry++; isIndex++;
		}
	}
	if(isEntry < isSize || isEntry > isSize){
		int **resizeIntervals = realloc(isIntervals, sizeof(int *) * isEntry); if(resizeIntervals == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
		isIntervals = resizeIntervals; *isResize = isEntry;
	}
	return isIntervals;
}

//Insert newInterval into intervals such that intervals is still sorted in ascending order by starti and intervals still does not have any overlapping intervals (merge overlapping intervals if necessary).
int **insertIntervals(int **isMatrix, int isSize, int *isEntryInterval, int *isResize, bool isDisjoint){
    if(isMatrix == NULL){fprintf(stderr, "Invalid Array.\n"); return NULL;}
	if(isDisjoint){
		if(isSize == 0){
			int **isIntervals = calloc(1, sizeof(int *)); if(isIntervals == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
			*isIntervals = calloc(2, sizeof(int)); if(*isIntervals == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
			**isIntervals = *isEntryInterval; *(*isIntervals + 1) = *(isEntryInterval + 1); *isResize = 1; return isIntervals;
		}
		int **isIntervals = calloc(isSize, sizeof(int *)); if(isIntervals == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
		int isIndex = 0, isStart = -1, isEnd = -1, isIteration = 0, isEntry = 0;
		while(isIndex < isSize){
			isStart = **(isMatrix + isIndex); isEnd = *(*(isMatrix + isIndex) + 1);
			if(*isEntryInterval <= isStart || *isEntryInterval <= isEnd){
				isIteration = isIndex + 1; if(*(isEntryInterval + 1) < **(isMatrix + isIndex)){isIteration = -1;}
				while(isIteration > 0 && isIteration < isSize && *(isEntryInterval + 1) > **(isMatrix + isIteration)){isIteration++;}
				if(isIteration == isSize){isIteration--;} else if(isIteration > 0 && *(isEntryInterval + 1) < **(isMatrix + isIteration)){isIteration--;}
				*(isIntervals + isEntry) = calloc(2, sizeof(int)); if(*(isIntervals + isEntry) == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
				**(isIntervals + isEntry) = *isEntryInterval <= isStart ? *isEntryInterval : **(isMatrix + isIndex);
				*(*(isIntervals + isEntry++) + 1) = isIteration == -1 ? isIteration++, *(isEntryInterval + 1) : *(isEntryInterval + 1) > *(*(isMatrix + isIteration) + 1) ? isIteration++, *(isEntryInterval + 1) : *(*(isMatrix + isIteration++) + 1);
				while(isIteration < isSize){
					*(isIntervals + isEntry) = calloc(2, sizeof(int)); if(*(isIntervals + isEntry) == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
					**(isIntervals + isEntry) = **(isMatrix + isIteration); *(*(isIntervals + isEntry++) + 1) = *(*(isMatrix + isIteration++) + 1);
				}
				break;
			}
			*(isIntervals + isEntry) = calloc(2, sizeof(int)); if(*(isIntervals + isEntry) == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
			**(isIntervals + isEntry) = isStart; *(*(isIntervals + isEntry++) + 1) = isEnd; isIndex++;
			if(isIndex == isSize){
				*(isIntervals + isEntry) = calloc(2, sizeof(int)); if(*(isIntervals + isEntry) == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
				**(isIntervals + isEntry) = *isEntryInterval; *(*(isIntervals + isEntry++) + 1) = *(isEntryInterval + 1);
			}
		}
		if(isEntry < isSize || isEntry > isSize){
			int **resizeIntervals = realloc(isIntervals, sizeof(int *) * isEntry); if(resizeIntervals == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
			isIntervals = resizeIntervals; *isResize = isEntry;
		}
		return isIntervals;
	} else{
		if(isSize == 0){
			int **isIntervals = calloc(1, sizeof(int *)); if(isIntervals == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
			*isIntervals = calloc(2, sizeof(int)); if(*isIntervals == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
			**isIntervals = *isEntryInterval; *(*isIntervals + 1) = *(isEntryInterval + 1); *isResize = 1; return isIntervals;
		}
		int *isStack = calloc(isSize, sizeof(int)); if(isStack == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
		int isLow = 0, isHigh = isSize - 1, isTop = 0, isPartition = -1, isPivot = -1, isPlacement = -1, *isPlaceholder;
		*(isStack + isTop++) = isLow; *(isStack + isTop) = isHigh;
		while(isTop >= 0){
			isHigh = *(isStack + isTop--); isLow = *(isStack + isTop--);
			isPivot = **(isMatrix + isHigh); isPlacement = isLow;
			for(int isIndex = isLow; isIndex < isHigh; isIndex++){
				if(**(isMatrix + isIndex) < isPivot){
					isPlaceholder = *(isMatrix + isPlacement); *(isMatrix + isPlacement) = *(isMatrix + isIndex);
					*(isMatrix + isIndex) = isPlaceholder; isPlacement++;
				}
			}
			isPlaceholder = *(isMatrix + isPlacement); *(isMatrix + isPlacement) = *(isMatrix + isHigh); 
			*(isMatrix + isHigh) = isPlaceholder; isPartition = isPlacement;
			if(isPartition - 1 > isLow){isTop++; *(isStack + isTop++) = isLow; *(isStack + isTop) = isPartition - 1;}
			if(isPartition + 1 < isHigh){isTop++; *(isStack + isTop++) = isPartition + 1; *(isStack + isTop) = isHigh;}
		}
		free(isStack); isStack = NULL;
		int **isIntervals = calloc(isSize, sizeof(int *)); if(isIntervals == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
		int isIndex = 0, isEnd = -1, isIteration = 0, isEntry = 0;
		bool isEntryInsert = false;
		while(isIndex < isSize){
			isEnd = *(*(isMatrix + isIndex) + 1); isIteration = isIndex + 1;
			if(*isEntryInterval < **(isMatrix + isIndex) && *(isEntryInterval + 1) < **(isMatrix + isIndex) && !isEntryInsert){
				*(isIntervals + isEntry) = calloc(2, sizeof(int)); if(*(isIntervals + isEntry) == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
				**(isIntervals + isEntry) = *isEntryInterval; *(*(isIntervals + isEntry) + 1) = *(isEntryInterval + 1); isEntry++; isEntryInsert = true;
			} else if((*isEntryInterval < **(isMatrix + isIndex) && *(isEntryInterval + 1) >= **(isMatrix + isIndex)) || (*isEntryInterval <= isEnd && *(isEntryInterval + 1) > isEnd)){
				(*(isEntryInterval + 1) > isEnd) && (isEnd = *(isEntryInterval + 1)); isEntryInsert = true;
			}
			if(isIteration < isSize){
				while(isEnd >= **(isMatrix + isIteration)){
					isEnd = *(*(isMatrix + isIteration) + 1);
					if((*isEntryInterval < **(isMatrix + isIteration) && *(isEntryInterval + 1) >= **(isMatrix + isIteration)) || (*isEntryInterval <= isEnd && *(isEntryInterval + 1) > isEnd)){
						(*(isEntryInterval + 1) > isEnd) && (isEnd = *(isEntryInterval + 1)); isEntryInsert = true;
					}
					isIteration++;
				}
				*(isIntervals + isEntry) = calloc(2, sizeof(int)); if(*(isIntervals + isEntry) == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
				**(isIntervals + isEntry) = *isEntryInterval < **(isMatrix + isIndex) && *(isEntryInterval + 1) >= **(isMatrix + isIndex) ? *isEntryInterval : **(isMatrix + isIndex);
				*(*(isIntervals + isEntry) + 1) = isEnd; isEntry++; isIndex = isIteration;
			} else{
				*(isIntervals + isEntry) = calloc(2, sizeof(int)); if(*(isIntervals + isEntry) == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
				**(isIntervals + isEntry) = *isEntryInterval < **(isMatrix + isIndex) && *(isEntryInterval + 1) >= **(isMatrix + isIndex) ? *isEntryInterval : **(isMatrix + isIndex);
				*(*(isIntervals + isEntry) + 1) = isEnd; isEntry++; isIndex++;
			}
		}
		if(!isEntryInsert){
			*(isIntervals + isEntry) = calloc(2, sizeof(int)); if(*(isIntervals + isEntry) == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
			**(isIntervals + isEntry) = *isEntryInterval; *(*(isIntervals + isEntry) + 1) = *(isEntryInterval + 1); isEntry++;
		}
		if(isEntry < isSize || isEntry > isSize){
			int **resizeIntervals = realloc(isIntervals, sizeof(int *) * isEntry); if(resizeIntervals == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
			isIntervals = resizeIntervals; *isResize = isEntry;
		}
		return isIntervals;
	}
}

// Return The Maximum Possible Number Of A Numeric String.
char *maximizeNumber(char *isNumber){ // Fix, Needs Optimization Doesnt work with large inputs.
    if(isNumber == NULL || *isNumber == '\0'){fprintf(stderr, "Invalid String.\n"); return NULL;}
    int isIndex = 0, isNoDigit = -1, isEvenIndex = 0, isEvenSize = 1, isOddIndex = 0, isOddSize = 1, isSortTraverse = 0;
    bool isDigitEven = false, insertionMove = false;
    char isPlacementHolder, updatePlacementHolder;
    char *isEven = calloc(1, sizeof(char)); if(isEven == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
    char *isOdd = calloc(1, sizeof(char)); if(isOdd == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return NULL;}
    while(*(isNumber + isIndex) != '\0'){
        isNoDigit = *(isNumber + isIndex) - '0';
        isDigitEven = isNoDigit % 2 == 0 ? true : false;
        if(isEvenIndex > 0 || isOddIndex > 0){
            while(isSortTraverse <= (isDigitEven ? isEvenIndex : isOddIndex)){
                if((isDigitEven ? isNoDigit > (*(isEven + isSortTraverse) - '0') : isNoDigit > (*(isOdd + isSortTraverse) - '0')) && !insertionMove){
                    isPlacementHolder = isDigitEven ? *(isEven + isSortTraverse) : *(isOdd + isSortTraverse);
                    isDigitEven ? (*(isEven + isSortTraverse) = *(isNumber + isIndex)) : (*(isOdd + isSortTraverse) = *(isNumber + isIndex));
                    insertionMove = true; isSortTraverse++; continue;
                }
                if(insertionMove){
                    updatePlacementHolder = isDigitEven ? *(isEven + isSortTraverse) : *(isOdd + isSortTraverse);
                    isDigitEven ? (*(isEven + isSortTraverse) = isPlacementHolder) : (*(isOdd + isSortTraverse) = isPlacementHolder);
                    isPlacementHolder = updatePlacementHolder;
                }
                if((isDigitEven ? (isSortTraverse == isEvenIndex) : (isSortTraverse == isOddIndex)) && !insertionMove){
                    isDigitEven ? (*(isEven + isSortTraverse) = *(isNumber + isIndex)) : (*(isOdd + isSortTraverse) = *(isNumber + isIndex));
                }
                isSortTraverse++;
            }
            isSortTraverse = 0; insertionMove = false; isDigitEven ? isEvenIndex++ : isOddIndex++; isPlacementHolder = '\0'; updatePlacementHolder = '\0';
        }
        (isEvenIndex == 0 && isDigitEven) && (*(isEven + isEvenIndex++) = *(isNumber + isIndex));
        (isOddIndex == 0 && !isDigitEven) && (*(isOdd + isOddIndex++) = *(isNumber + isIndex));
        if(isEvenIndex == isEvenSize || isOddIndex == isOddSize){
            (isEvenIndex == isEvenSize) && (isEvenSize *= 2); (isOddIndex == isOddSize) && (isOddSize *= 2);
            char *expandParity = (isEvenIndex == isEvenSize) ? realloc(isEven, sizeof(char) * isEvenSize) : realloc(isOdd, sizeof(char) * isOddSize); if(expandParity == NULL){fprintf(stderr, "Memory Allocation Failed\n"); exit(EXIT_FAILURE);}
            (isEvenIndex == isEvenSize) ? (isEven = expandParity) : (isOdd = expandParity);
        }
        if(*(isNumber + (isIndex + 1)) == '\0'){
            char *resizeEven = realloc(isEven, sizeof(char) * (isEvenIndex + 1)); if(resizeEven == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); exit(EXIT_FAILURE);} isEven = resizeEven;
            *(isEven + isEvenIndex) = '\0'; isEvenSize = isEvenIndex + 1; isEvenIndex = 0;
            char *resizeOdd = realloc(isOdd, sizeof(char) * (isOddIndex + 1)); if(resizeOdd == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); exit(EXIT_FAILURE);} isOdd = resizeOdd;
            *(isOdd + isOddIndex) = '\0'; isOddSize = isOddIndex + 1; isOddIndex = 0;
        }
        isIndex++;
    }
    char *isMaximizedNumber = calloc(isIndex + 1, sizeof(char)); if(isMaximizedNumber == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); exit(EXIT_FAILURE);}
    while(isSortTraverse < isIndex){
        *(isEven + isEvenIndex) > *(isOdd + isOddIndex) ? (*(isMaximizedNumber + isSortTraverse) = *(isEven + isEvenIndex), isEvenIndex++) : (*(isMaximizedNumber + isSortTraverse) = *(isOdd + isOddIndex), isOddIndex++);
        isSortTraverse++;
    }
    *(isMaximizedNumber + isSortTraverse) = '\0';
    free(isEven); isEven = NULL; free(isOdd); isOdd = NULL;
    return isMaximizedNumber;
}

char *isLargestNumber(char *isNumber){
    int isIndex = 0, isNoDigit = -1, isSectionEntry = 0, isSectionSize = 1, isContentIndex = 0, isContentSize = 1, isContentLength = 0, isSortTraverse = 0;
    bool isNewSection = false, isDigitEven = false, isParityState = false, insertionMove = false;
    char isPlacementHolder, updatePlacementHolder;
    char **isSection = calloc(1, sizeof(char *)); if(isSection == NULL){fprintf(stderr, "Memory Allocation Failed\n"); exit(EXIT_FAILURE);}
    char **isSectionEntrySize = calloc(1, sizeof(char *)); if(isSectionEntrySize == NULL){fprintf(stderr, "Memory Allocation Failed\n"); exit(EXIT_FAILURE);}
    char *isContent = calloc(1, sizeof(char)); if(isContent == NULL){fprintf(stderr, "Memory Allocation Failed\n"); exit(EXIT_FAILURE);}
    char **resizeSection, **resizeSectionEntrySize, *resizeContent;
    while(*(isNumber + isIndex) != '\0'){
        isNoDigit = *(isNumber + isIndex) - '0';
        isDigitEven = isNoDigit % 2 == 0 ? true : false;
        (isIndex == 0) && (isParityState = isDigitEven);
        (isParityState != isDigitEven) && (isNewSection = true, isParityState = isDigitEven);
        if(isNewSection){
            *(isContent + isContentIndex) = '\0'; isContentLength = snprintf(NULL, 0, "%d", isContentIndex) + 1;
            if(isSectionEntry == isSectionSize){
                isSectionSize *= 2; 
                resizeSection = realloc(isSection, sizeof(char *) * isSectionSize); if(resizeSection == NULL){fprintf(stderr, "Memory Allocation Failed\n"); exit(EXIT_FAILURE);} isSection = resizeSection;
                resizeSectionEntrySize = realloc(isSectionEntrySize, sizeof(char *) * isSectionSize); if(resizeSectionEntrySize == NULL){fprintf(stderr, "Memory Allocation Failed\n"); exit(EXIT_FAILURE);} isSectionEntrySize = resizeSectionEntrySize;
            }
            *(isSection + isSectionEntry) = calloc(isContentIndex + 1, sizeof(char)); if(*(isSection + isSectionEntry) == NULL){fprintf(stderr, "Memory Allocation Failed\n"); exit(EXIT_FAILURE);}
            *(isSectionEntrySize + isSectionEntry) = calloc(isContentLength, sizeof(char)); if(*(isSectionEntrySize + isSectionEntry) == NULL){fprintf(stderr, "Memory Allocation Failed\n"); exit(EXIT_FAILURE);}
            snprintf(*(isSection + isSectionEntry), isContentIndex + 1, "%s", isContent);
            snprintf(*(isSectionEntrySize + isSectionEntry), isContentLength, "%d", isContentIndex);
            isSectionEntry++; *(isContent + isContentIndex) = ' '; isContentIndex = 0; isNewSection = false;
        }
        if(isContentIndex > 0 && !insertionMove && !isNewSection){
            while(isSortTraverse <=  isContentIndex){
                if(isdigit(*(isContent + isSortTraverse)) != 0 && isNoDigit > (*(isContent + isSortTraverse) - '0') && !insertionMove){
                    isPlacementHolder = *(isContent + isSortTraverse); *(isContent + isSortTraverse) = *(isNumber + isIndex);
                    insertionMove = true; isSortTraverse++; continue;
                }
                (insertionMove) && (updatePlacementHolder = *(isContent + isSortTraverse), *(isContent + isSortTraverse) = isPlacementHolder, isPlacementHolder = updatePlacementHolder);
                (isSortTraverse == isContentIndex && !insertionMove) && (*(isContent + isSortTraverse) = *(isNumber + isIndex));
                isSortTraverse++;
            }
            isSortTraverse = 0; insertionMove = false; isContentIndex++; isPlacementHolder = '\0'; updatePlacementHolder = '\0';
        }
        (isContentIndex == 0) && (*(isContent + isContentIndex++) = *(isNumber + isIndex));
        if(isContentIndex == isContentSize){isContentSize *= 2; resizeContent = realloc(isContent, sizeof(char) * isContentSize); if(resizeContent == NULL){fprintf(stderr, "Memory Allocation Failed\n"); exit(EXIT_FAILURE);} isContent = resizeContent;}
        isIndex++;
    }
    *(isContent + isContentIndex) = '\0'; isContentLength = snprintf(NULL, 0, "%d", isContentIndex) + 1;
    *(isSection + isSectionEntry) = calloc(isContentIndex + 1, sizeof(char)); if(*(isSection + isSectionEntry) == NULL){fprintf(stderr, "Memory Allocation Failed\n"); exit(EXIT_FAILURE);}
    *(isSectionEntrySize + isSectionEntry) = calloc(isContentLength, sizeof(char)); if(*(isSectionEntrySize + isSectionEntry) == NULL){fprintf(stderr, "Memory Allocation Failed\n"); exit(EXIT_FAILURE);}
    snprintf(*(isSection + isSectionEntry), isContentIndex + 1, "%s", isContent);
    snprintf(*(isSectionEntrySize + isSectionEntry), isContentLength, "%d", isContentIndex);
    isSectionEntry++; *(isContent + isContentIndex) = ' '; isContentIndex = 0, isContentSize = isIndex + 1;
    //Issue starts here
    //printf("lAst Value = %s\n", isSection[isSectionEntry - 1]);
    resizeSection = realloc(isSection, sizeof(char *) * isSectionEntry + 1); if(resizeSection == NULL){fprintf(stderr, "Memory Allocation Failed\n"); exit(EXIT_FAILURE);} isSection = resizeSection;
    //printf("lAst Value = %s\n", isSection[isSectionEntry - 1]);
    resizeSectionEntrySize = realloc(isSectionEntrySize, sizeof(char *) * isSectionEntry); if(resizeSectionEntrySize == NULL){fprintf(stderr, "Memory Allocation Failed\n"); exit(EXIT_FAILURE);} isSectionEntrySize = resizeSectionEntrySize;
    resizeContent = realloc(isContent, sizeof(char) * isContentSize); if(resizeContent == NULL){fprintf(stderr, "Memory Allocation Failed\n"); exit(EXIT_FAILURE);} isContent = resizeContent;
    while(isSortTraverse < isSectionEntry){
        snprintf(isContent + isContentIndex, isContentSize, "%s", *(isSection + isSortTraverse));
        isContentIndex += strtol(*(isSectionEntrySize + isSortTraverse), NULL, 10);
        free(*(isSection + isSortTraverse)); *(isSection + isSortTraverse) = NULL;
        free(*(isSectionEntrySize + isSortTraverse)); *(isSectionEntrySize + isSortTraverse) = NULL;
        isSortTraverse++;
    }
    free(isSection); isSection = NULL; free(isSectionEntrySize); isSectionEntrySize = NULL;
    *(isContent + isContentIndex) = '\0';
    printf("Largest = %s\n", isContent);
    return isContent;
}

/*
You are given an integer array nums. You are initially positioned at the array's first index, and each element in the array represents your maximum jump length at that position.
Return true if you can reach the last index, or false otherwise.
*/
bool isMaxEndJumpGame(int *isArray, int isSize){
    if(isArray == NULL || isSize <= 0){fprintf(stderr, "Invalid Array.\n"); return false;}
    int isIndex = 0, isPlacement = 0;
    while(isIndex < isSize){
        if(isIndex > isPlacement){return false;}
        isPlacement = isPlacement > isIndex + *(isArray + isIndex) ? isPlacement : isIndex + *(isArray + isIndex);
        if(isPlacement >= isSize - 1){return true;} isIndex++;
    }
    return isPlacement >= isSize - 1;
}

/*
You are given a 0-indexed array of integers nums of length n. You are initially positioned at nums[0].
Each element nums[i] represents the maximum length of a forward jump from index i. In other words, if you are at nums[i], you can jump to any nums[i + j] where:
    0 <= j <= nums[i] and
    i + j < n
Return the minimum number of jumps to reach nums[n - 1]
*/
int isMinEndJumpGame(int *isArray, int isSize){
    if(isArray == NULL || isSize <= 0){fprintf(stderr, "Invalid Array.\n"); return -1;}
    int isIndex = 0, isPlacement = 0, isCurrentPlacement = 0, isJumps = 0;
    while(isIndex < isSize - 1){
        isPlacement = isPlacement > isIndex + *(isArray + isIndex) ? isPlacement : isIndex + *(isArray + isIndex);
        if(isIndex == isCurrentPlacement){
            isJumps++; isCurrentPlacement = isPlacement;
            if(isCurrentPlacement >= isSize - 1){break;}
        }
        isIndex++;
    }
    return isJumps;
}

/*
Given an integer array nums, return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i].
*/
int *productIndexException(int *isArray, int isSize){
    if(isArray == NULL || isSize <= 0){return NULL;}
    int *isProduct = calloc(isSize, sizeof(int)); if(isProduct == NULL){fprintf(stderr, "Memory Allocation Failed\n"); exit(EXIT_FAILURE);}
    for(int isPrefixIndex = 0; isPrefixIndex < isSize; isPrefixIndex++){*(isProduct + isPrefixIndex) = isPrefixIndex == 0 ? 1 : *(isProduct + (isPrefixIndex - 1)) * *(isArray + (isPrefixIndex - 1));}
    for(int isSuffixIndex = isSize - 1, isRight = 1; isSuffixIndex >= 0; isSuffixIndex--){*(isProduct + isSuffixIndex) *= isRight; isRight *= *(isArray + isSuffixIndex);}
    return isProduct;
}

/*
There are n children standing in a line. Each child is assigned a rating value given in the integer array ratings.
You are giving candies to these children subjected to the following requirements:
    Each child must have at least one candy.
    Children with a higher rating get more candies than their neighbors.
Return the minimum number of candies you need to have to distribute the candies to the children.
*/
int candyDistribution(int *isArray, int isSize){
    if(isArray == NULL || isSize <= 0){fprintf(stderr, "Invalid Array.\n"); return -1;}
    if(isSize == 1){return 1;}
    int isMininumCandy = 0, isEntry = 0, isBacktrack = -1;
    bool isNeighbourLesser = false;
    int *isCandyDistribution = calloc(isSize, sizeof(int));if(isCandyDistribution == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return -1;}
    for(int isIndex = 0; isIndex < isSize; isIndex++){
        if(isIndex == 0){
            *(isCandyDistribution + isEntry) = 1; isMininumCandy++;
            (*(isArray + isIndex) > *(isArray + (isIndex + 1))) && (*(isCandyDistribution + isEntry) += 1, isMininumCandy++);
            isEntry++;
        } else if(isIndex > 0 && isIndex < isSize - 1){
            (*(isArray + isIndex) <= *(isArray + (isIndex - 1))) && (*(isCandyDistribution + isEntry) = 1, isMininumCandy++);
            (*(isArray + isIndex) > *(isArray + (isIndex - 1))) && (*(isCandyDistribution + isEntry) = *(isCandyDistribution + (isEntry - 1)) + 1, isMininumCandy += *(isCandyDistribution + isEntry), isNeighbourLesser = true);
            (*(isArray + isIndex) > *(isArray + (isIndex + 1)) && !isNeighbourLesser) && (*(isCandyDistribution + isEntry) += 1, isMininumCandy++);
            if(*(isCandyDistribution + isEntry) == *(isCandyDistribution + (isEntry - 1)) && *(isArray + (isIndex - 1)) > *(isArray + isIndex)){
                *(isCandyDistribution + (isEntry - 1)) += 1; isMininumCandy++;
                isBacktrack = isEntry - 1;
                while(isBacktrack > 0){
                    if(*(isCandyDistribution + isBacktrack) == *(isCandyDistribution + (isBacktrack - 1)) && *(isArray + (isBacktrack - 1)) > *(isArray + isBacktrack)){
                        *(isCandyDistribution + (isBacktrack - 1)) += 1; isMininumCandy++;
                    } else{
                        break;
                    }
                    isBacktrack--;
                }
            }
            isNeighbourLesser = false; isEntry++;
        } else{
            (*(isArray + isIndex) <= *(isArray + (isIndex - 1))) && (*(isCandyDistribution + isEntry) = 1, isMininumCandy++);
            (*(isArray + isIndex) > *(isArray + (isIndex - 1))) && (*(isCandyDistribution + isEntry) += *(isCandyDistribution + (isEntry - 1)) + 1, isMininumCandy += *(isCandyDistribution + isEntry));
            if(*(isCandyDistribution + isEntry) == *(isCandyDistribution + (isEntry - 1)) && *(isArray + (isIndex - 1)) > *(isArray + isIndex)){
                *(isCandyDistribution + (isEntry - 1)) += 1; isMininumCandy++;
                isBacktrack = isEntry - 1;
                while(isBacktrack > 0){
                    if(*(isCandyDistribution + isBacktrack) == *(isCandyDistribution + (isBacktrack - 1)) && *(isArray + (isBacktrack - 1)) > *(isArray + isBacktrack)){
                        *(isCandyDistribution + (isBacktrack - 1)) += 1; isMininumCandy++;
                    } else{
                        break;
                    }
                    isBacktrack--;
                }
            }
        }
    }
    return isMininumCandy;
}

// Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.
int trappingRainWater(int *isArray, int isSize){
    if(isArray == NULL || isSize <= 0){fprintf(stderr, "Invalid Array.\n"); return -1;}
    if(isSize <= 2){return 0;}
    int isTrappedWater = 0, isLeftIndex = 0, isLeftHeight = 0, isRightIndex = isSize - 1, isRightHeight = 0;
    while(isLeftIndex <= isRightIndex){
        if(*(isArray + isLeftIndex) <= *(isArray + isRightIndex)){
            *(isArray + isLeftIndex) >= isLeftHeight ? (isLeftHeight = *(isArray + isLeftIndex)) : (isTrappedWater += isLeftHeight - *(isArray + isLeftIndex));
            isLeftIndex++;
        }else{
            *(isArray + isRightIndex) >= isRightHeight ? (isRightHeight = *(isArray + isRightIndex)) : (isTrappedWater += isRightHeight - *(isArray + isRightIndex));
            isRightIndex--;
        }
    }
    return isTrappedWater;
}

/*
You are given an integer array height of length n. There are n vertical lines drawn such that the two endpoints of the ith line are (i, 0) and (i, height[i]).
Find two lines that together with the x-axis form a container, such that the container contains the most water.
Return the maximum amount of water a container can store
*/
int isLargestContainer(int *isArray, int isSize){
    if(isArray == NULL || isSize < 2){fprintf(stderr, "Invalid Array.\n"); return -1;}
    int isLargest = -1, isLeft = 0, isRight = isSize - 1, isSmallestHeight = -1;
    while(isLeft <= isRight){
		if(*(isArray + isLeft) != 0 && *(isArray + isRight) != 0){
            isSmallestHeight = *(isArray + isLeft) == *(isArray + isRight) ? *(isArray + isLeft) : *(isArray + isLeft) < *(isArray + isRight) ? *(isArray + isLeft) : *(isArray + isRight);
            ((isRight - isLeft) * isSmallestHeight > isLargest) && (isLargest = (isRight - isLeft) * isSmallestHeight);
        }
        if(*(isArray + isLeft) <= *(isArray + isRight)){isLeft++;}
		else if (*(isArray + isRight) <= *(isArray + isLeft)){isRight--;}
    }
    return isLargest;
}

/*
You are climbing a staircase. It takes n steps to reach the top.
Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
*/
int isClimbStairCombination(int isSteps){
	if(isSteps <= 0){fprintf(stderr, "Invalid Input.\n"); return 0;}
	if(isSteps == 1){return 1;} if(isSteps == 2){return 2;}
	int isCombination = 0, isPreviousFirst = 2, isPreviousSecond = 1;
	for(int isIndex = 3; isIndex <= isSteps; isIndex++){isCombination = isPreviousFirst + isPreviousSecond; isPreviousSecond = isPreviousFirst; isPreviousFirst = isCombination;}
	return isCombination;
}

/*
You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security systems connected and it will automatically contact the police if two adjacent houses were broken into on the same night.
Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.
*/
int isHouseRobber(int *isArray, int isSize){
	if(isSize <= 0){fprintf(stderr, "Empty Street.\n"); return 0;}
	if(isSize == 1){return *isArray;}
	if(isSize <= 0){return *isArray > *(isArray + 1) ? *isArray : *(isArray + 1);}
	int isCurrent = 0, isPreviousFirst = *isArray > *(isArray + 1) ? *isArray : *(isArray + 1), isPreviousSecond = *isArray;
	for(int isIndex = 2; isIndex < isSize; isIndex++){
		isCurrent = *(isArray + isIndex) + isPreviousSecond > isPreviousFirst ? *(isArray + isIndex) + isPreviousSecond : isPreviousFirst; 
        isPreviousSecond = isPreviousFirst; isPreviousFirst = isCurrent;
	}
	return isPreviousFirst;
}

/*
Given an array of integers citations where citations[i] is the number of citations a researcher received for their ith paper, return the researcher's h-index.
According to the definition of h-index on Wikipedia: The h-index is defined as the maximum value of h such that the given researcher has published at least h papers that have each been cited at least h times.
*/
int isHthIndex(int *isArray, int isSize){
	if(isArray == NULL || isSize <= 0){fprintf(stderr, "Invalid Array.\n"); return -1;} if(isSize == 1){return *isArray == 0 ? 0 : 1;}
    int *isStack = calloc(isSize, sizeof(int)); if(isStack == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return -1;}
    int isLow = 0, isHigh = isSize - 1, isTop = 0, isPartition = -1, isPivot = -1, isPlacement = -1, isPlaceholder;
    *(isStack + isTop++) = isLow; *(isStack + isTop) = isHigh;
    while(isTop >= 0){
        isHigh = *(isStack + isTop--); isLow = *(isStack + isTop--);
        isPivot = *(isArray + isHigh); isPlacement = isLow;
        for(int isIndex = isLow; isIndex < isHigh; isIndex++){
            if(*(isArray + isIndex) > isPivot){
                isPlaceholder = *(isArray + isPlacement); *(isArray + isPlacement) = *(isArray + isIndex);
                *(isArray + isIndex) = isPlaceholder; isPlacement++;
            }
        }
        isPlaceholder = *(isArray + isPlacement); *(isArray + isPlacement) = *(isArray + isHigh); 
        *(isArray + isHigh) = isPlaceholder; isPartition = isPlacement;
        if(isPartition - 1 > isLow){isTop++; *(isStack + isTop++) = isLow; *(isStack + isTop) = isPartition - 1;}
        if(isPartition + 1 < isHigh){isTop++; *(isStack + isTop++) = isPartition + 1; *(isStack + isTop) = isHigh;}
    }
    free(isStack); isStack = NULL;
    for(int isIndex = 0; isIndex < isSize; isIndex++){if(*(isArray + isIndex) < isIndex + 1){return isIndex;}}
    return isSize;
}


/*
Give a N * N square matrix A, return all the elements of its anti-diagonals from top to bottom. 
class Solution{
    static ArrayList<Integer> downwardDiagonal(int N, int yourArray[][])
    {
        ArrayList<Integer> getDiagonal = new ArrayList<Integer>();
		int moveThisY, moveThisX, countDiagonal = 0;
		int watchThisY, watchThisX, newCount = 0;
		for (int i = 0; i < yourArray.length; i++) {
			getDiagonal.add(yourArray[0][i]);
			moveThisX = i - 1;
			moveThisY = 1;
			while (i > 0 && countDiagonal < i) {
				getDiagonal.add(yourArray[i - moveThisX][i - moveThisY]);
				countDiagonal++;
				moveThisX--;
				moveThisY++;
			}
			countDiagonal = 0;
			if (i == yourArray.length - 1) {
				for (int k = 1; k < yourArray.length; k++) {
					getDiagonal.add(yourArray[k][i]);
					watchThisY = i;
					watchThisX = k;
					while (k < yourArray.length - 1 && (newCount < i - k)) {
						watchThisX++;
						watchThisY--;
						getDiagonal.add(yourArray[watchThisX][watchThisY]);
						newCount++;
					}
					newCount = 0;
				}
				break;
			}
		}
		return getDiagonal;
    }
}
*/
