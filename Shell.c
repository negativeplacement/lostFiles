#define _GNU_SOURCE

#include <dirent.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char*argv[]){
    while(true){}
    return 0; // NB!! Make A Structure for each command so the actual function can have recursive calls if needed.

    // command1 || command2 > output.txt  // command2 only execute if command1 fails
    // command1 && command2 > output.txt  // command2 only execute if command1 suceeds
}

void isChangeDirectory(char *isPath){
    int isExecutionReturn = chdir(isPath); if(isExecutionReturn == -1){fprintf(stderr, "%s\n", strerror(errno)); return;}
    return;
}

/* cat [-A | -vET] [-b] [-E | -e == -vE] [-n] [-s] [ -T | -t == -vT] [-u] [-v] [fileName...] */
void isConcatenate(char **isOptionFlag, char **isFile, int isFileEntry){
    struct stat isFileStat; struct dirent *isEntry;
    DIR *isDirectory;
    char *isStorage = calloc(4096, sizeof(char)); if(isStorage == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return;}
    char *isFlag = calloc(11, sizeof(char)); if(isFlag == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    if(snprintf(isFlag, 11, "0000000000") < 0){fprintf(stdout, "%s.\n", strerror(errno); return;)}
    char *isRedirection = calloc(6, sizeof(char)); if(isRedirection == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;} // >, >>, <, 2>, &> OR 2>&1
    if(snprintf(isFlag, 6, "00000") < 0){fprintf(stdout, "%s.\n", strerror(errno); return;)}
    char *isPageNumber = calloc(10, sizeof(char)); if(isPageNumber == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    char *isStartPtr, *isBreakPtr, *isResize, isCharacter, *isDirectoryPath;
    int isFileIndex = 0, isFileDescriptor, isOutputDescriptor, isBytesRead, isBytesWritten, isLineNumber = 1, isStartIndex = 0, isOffset = 0, isNumberLength = 10, isLength, isStorageIndex = 0;
    bool isOccupied = false;
    // No Redirection
    while(isFileIndex < isFileEntry){
        if(stat(*(isFile + isFileIndex), &isFileStat) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
        if(S_ISREG(isFileStat.st_mode) == 0){fprintf(stdout, "%s.\n", strerror(ENOENT)); continue;}
        if((isFileDescriptor = open(*(isFile + isFileIndex), O_RDONLY)) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
        while((isBytesRead = read(isFileDescriptor, isStorage, 4096)) > 0){
            // Implement -b Flag
            for(int isIndex = 0; isIndex < isBytesRead; isIndex++){
                if(*(isStorage + isIndex) == '\n'){
                    isOccupied = false;
                    for(int isPlacement = isStartIndex; isPlacement < isIndex; isPlacement++){
                        if(*(isStorage + isPlacement) != ' ' || *(isStorage + isPlacement) != '\t'){isOccupied = true; break;}
                    }
                    if(isOccupied){
                        isLength = snprintf(NULL, 0, "%d. ", isLineNumber);
                        if(isLength > isNumberLength){
                            isResize = realloc(isPageNumber, sizeof(char) * (isLength + 1)); if(isResize == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
                            isPageNumber = isResize; isNumberLength = isLength + 1;
                        }
                        isLength = snprintf(isPageNumber, isNumberLength, "%d. ", isLineNumber++); if(isLength < 0){fprintf(stdout, "%s.\n", strerror(errno); return;)}
                        isBytesWritten = write(STDOUT_FILENO, isPageNumber, isLength); if(isBytesWritten == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
                    }
                    if(write(STDOUT_FILENO, isStorage + isStartIndex, isIndex - isStartIndex + 1) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
                    isStartIndex = isIndex + 1;
                }
            }
            // Implement -E Flag
            while(isOffset < isBytesRead){
                isStartPtr = isStorage + isOffset;
                isBreakPtr = memchr(isStartPtr, '\n', isBytesRead - isOffset);
                if(isBreakPtr){
                    *isBreakPtr = '\0';
                    isBytesWritten = write(STDOUT_FILENO, isStartPtr, isBreakPtr - isStartPtr); if(isBytesWritten == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
                    isBytesWritten = write(STDOUT_FILENO, "$", 1); if(isBytesWritten == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;} // -E Flag
                    isBytesWritten = write(STDOUT_FILENO, "\n", 1); if(isBytesWritten == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
                    isOffset = (isBreakPtr - isStorage) + 1;
                } else{
                    isBytesWritten = write(STDOUT_FILENO, isStartPtr, isBytesRead - isOffset); if(isBytesWritten == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
                    break;
                }
            }
            // Implement -n Flag
            while(isOffset < isBytesRead){
                isStartPtr = isStorage + isOffset;
                isBreakPtr = memchr(isStartPtr, '\n', isBytesRead - isOffset);
                if(isBreakPtr){
                    *isBreakPtr = '\0';
                    isLength = snprintf(NULL, 0, "%d. ", isLineNumber);
                    if(isLength > isNumberLength){
                        isResize = realloc(isPageNumber, sizeof(char) * (isLength + 1)); if(isResize == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
                        isPageNumber = isResize; isNumberLength = isLength + 1;
                    }
                    isLength = snprintf(isPageNumber, isNumberLength, "%d. ", isLineNumber++); if(isLength < 0){fprintf(stdout, "%s.\n", strerror(errno); return;)}
                    isBytesWritten = write(STDOUT_FILENO, isPageNumber, isLength); if(isBytesWritten == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
                    isBytesWritten = write(STDOUT_FILENO, isStartPtr, isBreakPtr - isStartPtr); if(isBytesWritten == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
                    isBytesWritten = write(STDOUT_FILENO, "\n", 1); if(isBytesWritten == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
                    isOffset = (isBreakPtr - isStorage) + 1;
                } else{
                    isLength = snprintf(NULL, 0, "%d. ", isLineNumber);
                    if(isLength > isNumberLength){
                        isResize = realloc(isPageNumber, sizeof(char) * (isLength + 1)); if(isResize == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
                        isPageNumber = isResize; isNumberLength = isLength + 1;
                    }
                    isLength = snprintf(isPageNumber, isNumberLength, "%d. ", isLineNumber++); if(isLength < 0){fprintf(stdout, "%s.\n", strerror(errno); return;)}
                    isBytesWritten = write(STDOUT_FILENO, isPageNumber, isLength); if(isBytesWritten == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
                    isBytesWritten = write(STDOUT_FILENO, isStartPtr, isBytesRead - isOffset); if(isBytesWritten == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
                    break;
                }
            }
            // Implement -T flag
            for(int isIndex = 0; isIndex < isBytesRead; isIndex++){
               if(*(isStorage + isIndex) == '\t'){*(isStorage + isStorageIndex++) = '^'; *(isStorage + isStorageIndex++) = 'I';}
               else{*(isStorage + isStorageIndex++) = *(isStorage + isIndex);}
            }
            if(write(STDOUT_FILENO, isStorage, isStorageIndex) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
            // Implement -v Flag
            for(int isIndex = 0; isIndex < isBytesRead; isIndex++){
                isCharacter = *(isStorage + isIndex);
                if(isCharacter >= 0 && isCharacter <= 31){*(isStorage + isStorageIndex++) = '^'; *(isStorage + isStorageIndex++) = isCharacter + '@';}
                else if(isCharacter == 127){*(isStorage + isStorageIndex++) = '^'; *(isStorage + isStorageIndex++) = '?';}
                else{*(isStorage + isStorageIndex++) = isCharacter;}
            }
            if(write(STDOUT_FILENO, isStorage, isStorageIndex) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
            // Else
            //isBytesWritten = write(STDOUT_FILENO, isStorage, isBytesRead); if(isBytesWritten == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
            isOffset = 0; isStorageIndex = 0;
        }
        if(isBytesRead == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
        if(isFileEntry > 1){if(write(STDOUT_FILENO, "\n", 1) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}}
        close(isFileDescriptor);
        isFileIndex++;
    }
    if(isFileEntry == 1){
        if(stat(*isFile, &isFileStat) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
        if(S_ISREG(isFileStat.st_mode) == 0){fprintf(stdout, "%s.\n", strerror(ENOENT)); continue;}
        // cat > filename
        if((isFileDescriptor = open(*isFile, O_WRONLY | O_CREAT | O_TRUNC, 0766)) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
        fprintf(stdout, "\n");
        while((isBytesRead = read(STDIN_FILENO, isStorage, 4096) > 0)){
            if(write(isFileDescriptor, isStorage, isBytesRead) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
        }
        // cat >> filename
        if((isFileDescriptor = open(*isFile, O_WRONLY | O_CREAT | O_APPEND, 0766)) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
        fprintf(stdout, "\n");
        while((isBytesRead = read(STDIN_FILENO, isStorage, 4096) > 0)){
            if(write(isFileDescriptor, isStorage, isBytesRead) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
        }
        // cat < filename
        if((isFileDescriptor = open(*isFile, O_RDONLY)) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
        fprintf(stdout, "\n");
        while((isBytesRead = read(isFileDescriptor, isStorage, 4096) > 0)){
            if(write(STDOUT_FILENO, isStorage, isBytesRead) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
        }
        if(isBytesRead == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
        close(isFileDescriptor);
    } else{
        if(stat(*(isFile + (isFileEntry - 1)), &isFileStat) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
        if(S_ISREG(isFileStat.st_mode) == 0){fprintf(stdout, "%s.\n", strerror(ENOENT)); return;}
        // cat filename > filename | cat filename filename > filename | cat dir/* filename > filename || cat filename >> filename | cat filename filename >> filename | cat dir/* filename >> filename
        if((isOutputDescriptor = open(*(isFile + (isFileEntry - 1)), O_WRONLY | O_CREAT | (strcmp(isRedirection, "01000") == 0 ? O_APPEND : O_TRUNC ), 0766)) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
        while(isFileIndex < isFileEntry - 1){
            if(stat(*(isFile + isFileIndex), &isFileStat) == -1){fprintf(stdout, "%s.\n", strerror(errno)); continue;}
            if(S_ISREG(isFileStat.st_mode)){
                if((isFileDescriptor = open(*(isFile + isFileIndex), O_RDONLY)) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
                while((isBytesRead = read(isFileDescriptor, isStorage, 4096) > 0)){
                    if(write(isOutputDescriptor, isStorage, isBytesRead) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
                }
                if(isBytesRead == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
                if(write(STDOUT_FILENO, "\n", 1) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
                close(isFileDescriptor); isFileIndex++;
            } else if(S_ISDIR(isFileStat.st_mode)){
                isDirectory = opendir(*(isFile + isFileIndex)); if(isDirectory == NULL){fprintf(stdout, "%s.\n", strerror(errno)); return;}
                isDirectoryPath = calloc(1025, sizeof(char)); if(isDirectoryPath == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); continue;}
                while((isEntry = readdir(isDirectory)) != NULL){
                    if(strcmp(isEntry->d_name, ".") == 0 || strcmp(isEntry ->d_name, "..") == 0){continue;}
                    if(snprintf(isDirectoryPath, 1025, "%s/%s", *(isFile + isFileIndex), isEntry->d_name) < 0){fprintf(stdout, "%s.\n", strerror(errno)); return;}
                    if(stat(isDirectoryPath, &isEntry) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
                    if(S_ISREG(isEntry.st_mode)){
                        if((isFileDescriptor = open(isDirectoryPath, O_RDONLY)) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
                        while((isBytesRead = read(isFileDescriptor, isStorage, 4096)) > 0){
                            isBytesWritten = write(isOutputDescriptor, isStorage, isBytesRead); if(isBytesWritten == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
                        }
                        if(isBytesRead == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
                        if(write(STDOUT_FILENO, "\n", 1) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
                        close(isFileDescriptor);
                    } else if(S_ISDIR(isEntry.st_mode)){continue;}
                }
                closedir(isSrcDirectory);
            }
            
        }
        close(isOutputDescriptor);
        //only  >> can appear multiple time in the same command call. all others can only appear once
        // USe a string where each char is the index for the signs in order of operation from command. Where the index reference isRedirection
    }
    free(isStorage); isStorage = NULL; free(isFlag); isFlag = NULL; free(isRedirection); isRedirection = NULL; free(isPageNumber); isPageNumber = NULL;
    return;
}

void isCopy(char *isOptionFlag, char **isArgument, int isArgumentCount){ //Make Sure Function is Called it Catches "cp test.txt fish/ demo.txt finder/"
    struct stat isFirst, isLast;
    int isSrcFileDescriptor, isDstFileDescriptor, isBytesRead, isBytesWritten, isPathLength;
    char *isStorage = calloc(4096, sizeof(char)); if(isStorage == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    if(isArgumentCount == 2){
        if(stat(*isArgument, &isFirst) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
        if(stat(*(isArgument + 1), &isLast) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
        if(S_ISREG(isFirst.st_mode) && S_ISREG(isLast.st_mode)){ // cp fileName fileName
            if((isSrcFileDescriptor = open(*isArgument, O_RDONLY)) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
            if((isDstFileDescriptor = open(*(isArgument + 1), O_WRONLY | O_CREAT | O_TRUNC, 0766)) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
            while((isBytesRead = read(isSrcFileDescriptor, isStorage, 4096)) > 0){
                isBytesWritten = write(isDstFileDescriptor, isStorage, isBytesRead); if(isBytesWritten == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
            }
            if(isBytesRead == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
            close(isSrcFileDescriptor); close(isDstFileDescriptor);
        } else if(S_ISREG(isFirst.st_mode) && S_ISDIR(isLast.st_mode)){ // cp fileName directoryName
            if((isSrcFileDescriptor = open(*isArgument, O_RDONLY)) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
            isPathLength = strlen(*isArgument) + strlen(*(isArgument + 1));
            char *isDstFilePath = calloc(isPathLength + 1, sizeof(char)); if(isDstFilePath == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
            if(snprintf(isDstFilePath, isPathLength + 1, "%s/%s", *(isArgument + 1), *isArgument) < 0){fprintf(stdout, "%s.\n", strerror(errno); return;)}
            if((isDstFileDescriptor = open(isDstFilePath, O_WRONLY | O_CREAT | O_TRUNC, 0766)) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
            while((isBytesRead = read(isSrcFileDescriptor, isStorage, 4096)) > 0){
                isBytesWritten = write(isDstFileDescriptor, isStorage, isBytesRead); if(isBytesWritten == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
            }
            if(isBytesRead == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
            free(isDstFilePath); isDstFilePath = NULL;
            close(isSrcFileDescriptor); close(isDstFileDescriptor);
        } else if(S_ISDIR(isFirst.st_mode) && S_ISDIR(isLast.st_mode)){ // cp directoryName directoryName [2] [requires -r flag]
            isCopyDirectory(*isArgument, isSrcFileDescriptor, *(isArgument + 1), isDstFileDescriptor, isStorage);
        } else{fprintf(stdout, "Invalid Operation.\n");}
    } else{
        if(stat(*(isArgument + *(isArgument + (isArgumentCount - 1))), &isLast) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
        bool isSrcFile = false, isSrcDirectory = false, isMultipleOperation;
        for(int isIndex = 0; isIndex < isArgumentCount - 1; isIndex++){
            if(stat(*(isArgument + isIndex), &isFirst) == -1){fprintf(stdout, "%s.\n", strerror(errno)); continue;}
            if(S_ISREG(isFirst.st_mode)){
                if(isSrcDirectory){isSrcDirectory = false; isMultipleOperation = true; break;}
                isSrcFile = true;
            } else if(S_ISDIR(isFirst.st_mode)){
                if(isSrcFile){isSrcFile = false; isMultipleOperation = true; break;}
                isSrcDirectory = true;
            }
        }
        if(isMultipleOperation && isArgumentCount % 2 != 0){fprintf(stdout, "Invalid Operation.\n"); return;}
        if(S_ISDIR(isLast.st_mode) && isSrcFile){ // cp fileName fileName ... directoryName
            for(int isIndex = 0; isIndex < isArgumentCount - 1; isIndex++){
                if((isSrcFileDescriptor = open(*(isArgument + isIndex), O_RDONLY)) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
                isPathLength = strlen(*(isArgument + isIndex)) + strlen(*(isArgument + (isArgumentCount - 1)));
                char *isDstFilePath = calloc(isPathLength + 1, sizeof(char)); if(isDstFilePath == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
                if(snprintf(isDstFilePath, isPathLength + 1, "%s/%s", *(isArgument + (isArgumentCount - 1)), *(isArgument + isIndex)) < 0){fprintf(stdout, "%s.\n", strerror(errno); return;)}
                if((isDstFileDescriptor = open(isDstFilePath, O_WRONLY | O_CREAT | O_TRUNC, 0766)) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
                while((isBytesRead = read(isSrcFileDescriptor, isStorage, 4096)) > 0){
                    isBytesWritten = write(isDstFileDescriptor, isStorage, isBytesRead); if(isBytesWritten == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
                }
                if(isBytesRead == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
                free(isDstFilePath); isDstFilePath = NULL;
                close(isSrcFileDescriptor); close(isDstFileDescriptor);
            }
        } else if(S_ISDIR(isLast.st_mode) && isSrcDirectory && strstr(isOptionFlag, "-r")){ // cp directoryName directoryName ... directoryName
            for(int isIndex = 0; isIndex < isArgumentCount - 1; isIndex++){
                isCopyDirectory(*(isArgument + isIndex), isSrcFileDescriptor, *(isArgument + (isArgumentCount - 1)), isDstFileDescriptor, isStorage);
            }
        } else if(isMultipleOperation){
            int isFirst = 0, isSecond = 1;
            for(int isIndex = 0; isIndex < isArgumentCount / 2; isIndex++){
                if(stat(*(isArgument + isFirst), &isFirst) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
                if(stat(*(isArgument + isSecond), &isLast) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
                if(S_ISREG(isFirst.st_mode) && S_ISREG(isLast.st_mode)){
                    if((isSrcFileDescriptor = open(*(isArgument + isFirst), O_RDONLY)) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
                    if((isDstFileDescriptor = open(*(isArgument + isSecond), O_WRONLY | O_CREAT | O_TRUNC, 0766)) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
                    while((isBytesRead = read(isSrcFileDescriptor, isStorage, 4096)) > 0){
                        isBytesWritten = write(isDstFileDescriptor, isStorage, isBytesRead); if(isBytesWritten == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
                    }
                    if(isBytesRead == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
                    close(isSrcFileDescriptor); close(isDstFileDescriptor);
                } else if(S_ISREG(isFirst.st_mode) && S_ISDIR(isLast.st_mode)){
                    if((isSrcFileDescriptor = open(*(isArgument + isFirst), O_RDONLY)) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
                    isPathLength = strlen(*(isArgument + isFirst)) + strlen(*(isArgument + isSecond));
                    char *isDstFilePath = calloc(isPathLength + 1, sizeof(char)); if(isDstFilePath == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
                    if(snprintf(isDstFilePath, isPathLength + 1, "%s/%s", *(isArgument + 1), *isArgument) < 0){fprintf(stdout, "%s.\n", strerror(errno); return;)}
                    if((isDstFileDescriptor = open(isDstFilePath, O_WRONLY | O_CREAT | O_TRUNC, 0766)) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
                    while((isBytesRead = read(isSrcFileDescriptor, isStorage, 4096)) > 0){
                        isBytesWritten = write(isDstFileDescriptor, isStorage, isBytesRead); if(isBytesWritten == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
                    }
                    if(isBytesRead == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
                    free(isDstFilePath); isDstFilePath = NULL;
                    close(isSrcFileDescriptor); close(isDstFileDescriptor);
                } else if(S_ISDIR(isFirst.st_mode) && S_ISDIR(isLast.st_mode)){
                    isCopyDirectory(*(isArgument + isFirst), isSrcFileDescriptor, *(isArgument + isSecond), isDstFileDescriptor, isStorage);
                }
                if(S_ISDIR(isFirst.st_mode) && S_ISREG(isLast.st_mode)){fprintf(stdout, "Invalid Operation.\n");}
                isFirst += 2; isSecond += 2;
            }
        }
    }
    free(isStorage); isStorage = NULL;
    return;
}

void isCopyDirectory(char *isSrcDir, int isSrcFileDescriptor, char *isDstDir, int isDstFileDescriptor, char *isStorage){
    DIR *isSrcDirectory = opendir(*isArgument); if(isSrcDirectory == NULL){fprintf(stdout, "%s.\n", strerror(errno)); return;}
    struct dirent *isSrcEntry; struct stat isEntry;
    int isBytesRead, isBytesWritten;
    char *isSrcPath = calloc(1025, sizeof(char)); if(isSrcPath == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    char *isDstPath = calloc(1025, sizeof(char)); if(isDstPath == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    while((isSrcEntry = readdir(isSrcDirectory)) != NULL){
        if(strcmp(isSrcEntry->d_name, ".") == 0 || strcmp(isSrcEntry ->d_name, "..") == 0){continue;}
        if(snprintf(isSrcPath, 1025, "%s/%s", isSrcDir, isSrcEntry->d_name) < 0){fprintf(stdout, "%s.\n", strerror(errno)); return;}
        if(snprintf(isDstPath, 1025, "%s/%s", isDstDir, isSrcEntry->d_name) < 0){fprintf(stdout, "%s.\n", strerror(errno)); return;}
        if(stat(isSrcPath, &isEntry) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
        if(S_ISREG(isEntry.st_mode)){
            if((isSrcFileDescriptor = open(isSrcPath, O_RDONLY)) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
            if((isDstFileDescriptor = open(isDstPath, O_WRONLY | O_CREAT | O_TRUNC, 0766)) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
            while((isBytesRead = read(isSrcFileDescriptor, isStorage, 4096)) > 0){
                isBytesWritten = write(isDstFileDescriptor, isStorage, isBytesRead); if(isBytesWritten == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
            }
            if(isBytesRead == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
            close(isSrcFileDescriptor); close(isDstFileDescriptor);
        } else if(S_ISDIR(isEntry.st_mode)){
            isCopyDirectory(isSrcPath, isSrcFileDescriptor, isDstPath, isDstFileDescriptor, isStorage);
        }
    }
    closedir(isSrcDirectory); free(isSrcPath); isSrcPath = NULL; free(isDstPath); isDstPath = NULL;
    return;
}

void isDate(char **isOptionFlag, char *isArgument){
    char *isStorage = calloc(1024, sizeof(char)); if(isStorage == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    return;
}

// echo [-e] [-E] [-n] [String]
void isEcho(char **isOptionFlag, char *isString, int isLength, char *isFile){
    struct stat isFileStat;
    int isFileDescriptor;
    char *isFlag = calloc(4, sizeof(char)); if(isFlag == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    if(snprintf(isFlag, 4, "000") < 0){fprintf(stdout, "%s.\n", strerror(errno); return;)}
    char *isRedirection = calloc(6, sizeof(char)); if(isRedirection == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;} // >, >>, <, 2>, &> OR 2>&1
    if(snprintf(isFlag, 6, "00000") < 0){fprintf(stdout, "%s.\n", strerror(errno); return;)}
    char *isStringPtr = isString, *isEscapeSequence;
    // No Redirection
    // Implement -E  | Other Escape Sequence to Work out: "\c\0NNN\xHH\uHHHH\uHHHHHHHH"
    while((isEscapeSequence = strpbrk(isStringPtr, "\\\'\"\a\b\e\f\n\r\t\v")) != NULL){
        if(write(STDOUT_FILENO, isStringPtr, isEscapeSequence - isStringPtr) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
        switch(*isEscapeSequence){
            case '\\': if(write(STDOUT_FILENO, "\\", 2) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;} break;
            case '\'': if(write(STDOUT_FILENO, "\'", 2) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;} break;
            case '\"': if(write(STDOUT_FILENO, "\"", 2) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;} break;
            case '\a': if(write(STDOUT_FILENO, "\\a", 3) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;} break;
            case '\b': if(write(STDOUT_FILENO, "\\b", 3) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;} break;
            case '\e': if(write(STDOUT_FILENO, "\\e", 3) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;} break;
            case '\f': if(write(STDOUT_FILENO, "\\f", 3) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;} break;
            case '\n': if(write(STDOUT_FILENO, "\\n", 3) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;} break;
            case '\r': if(write(STDOUT_FILENO, "\\r", 3) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;} break;
            case '\t': if(write(STDOUT_FILENO, "\\t", 3) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;} break;
            case '\v': if(write(STDOUT_FILENO, "\\v", 3) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;} break;
            default: fprintf(stdout, "Unexpected Error.\n"); 
        }
    }
    if(isStringPtr == isString){if(write(STDOUT_FILENO, isString, isLength) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}}
    // Implement -n
    if(*(isFlag + 2) == 0){if(write(STDOUT_FILENO, "\n", 1) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}}
    // echo > fileName | echo >> fileName
    if(stat(isFile, &isFileStat) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
    if(S_ISREG(isFileStat.st_mode) == 0){fprintf(stdout, "%s.\n", strerror(ENOENT)); return;}
    if((isFileDescriptor = open(isFile, O_WRONLY | O_CREAT | (strcmp(isRedirection, "01000") == 0 ? O_APPEND : O_TRUNC ), 0766)) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
    if(write(isFileDescriptor, isString, isLength) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
    close(isFileDescriptor);
    free(isFlag); isFlag = NULL; free(isRedirection); isRedirection = NULL;
    return;
}

void isExit(){
    return;
}

void isFileTransferProtocol(){
    return;
}

void isFind(){
    return;
}

void isGlobalRegularExpressionPrint(){
    return;
}

void isHead(){
    return;
}

void isKill(){
    return;
}

void isLess(){
    return;
}

/* ls [-l] [-R] [pathName...] */
void isListDirectory(char *isOptionFlag, char *isPath, int isIndent){
    struct stat isPathStat; if(stat(isPath, &isPathStat) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
    if(S_ISDIR(isPathStat.st_mode) == 0){fprintf(stdout, "%s.\n", strerror(ENOENT)); return;}
    DIR *isDirectory = opendir(isPath); if(isDirectory == NULL){fprintf(stdout, "%s.\n", strerror(errno)); return;}
    struct dirent *isPathEntry;
    while((isPathEntry = readdir(isDirectory)) != NULL){
        if(strcmp(isPathEntry->d_name, ".") == 0 || strcmp(isPathEntry ->d_name, "..") == 0){continue;}
        if(strstr(isOptionFlag, "-l") != NULL){
            char *isFilePath = calloc(1025, sizeof(char)); if(isFilePath == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
            if(snprintf(isFilePath, 1025, "%s/%s", isPath, isPathEntry->d_name) < 0){fprintf(stdout, "%s.\n", strerror(errno)); return;}
            if(stat(isFilePath, &isPathStat) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
            char *isPermission = calloc(11, sizeof(char)); if(isPermission == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
            if(snprintf(isPermission, 11, "%s", "----------") < 0){fprintf(stdout, "%s.\n", strerror(errno)); return;}
            char *isTime = calloc(20, sizeof(char)); if(isTime == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
            struct tm *isFileTime = localtime(&isPathStat.st_mtime);
            strftime(isTime, 20, "%b %d %H:%M", isFileTime);
            if(S_ISDIR(isPathStat.st_mode)){*isPermission = 'd';}
            if(isPathStat.st_mode & S_IRUSR){*(isPermission + 1) = 'r';}
            if(isPathStat.st_mode & S_IWUSR){*(isPermission + 2) = 'w';}
            if(isPathStat.st_mode & S_IXUSR){*(isPermission + 3) = 'x';}
            if(isPathStat.st_mode & S_IRGRP){*(isPermission + 4) = 'r';}
            if(isPathStat.st_mode & S_IWGRP){*(isPermission + 5) = 'w';}
            if(isPathStat.st_mode & S_IXGRP){*(isPermission + 6) = 'x';}
            if(isPathStat.st_mode & S_IROTH){*(isPermission + 7) = 'r';}
            if(isPathStat.st_mode & S_IWOTH){*(isPermission + 8) = 'w';}
            if(isPathStat.st_mode & S_IXOTH){*(isPermission + 9) = 'x';}
            fprintf(stdout, "%s %ld %s %s %lld %s ", isPermission, isPathStat.st_nlink, getpwduid(isPathStat.st_uid).pw_name, getgrgid(isPathStat.st_gid).gr_name, (long long)isPathStat.st_size, isTime);
            free(isFilePath); isFilePath = NULL; free(isPermission); isPermission = NULL; free(isTime); isTime = NULL;
        }
        if(strstr(isOptionFlag, "-R") != NULL){
            if(isPathEntry->d_type == DT_DIR){
                fprintf(stdout, "%*s[%s]\n", isIndent, "",  isPathEntry->d_name);
                char isCurrentPath = calloc(1025, sizeof(char)); if(isCurrentPath == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
                if(snprintf(isCurrentPath, 1025, "%s/%s", isPath, isPathEntry->d_name) < 0){fprintf(stdout, "%s.\n", strerror(errno)); return;}
                isListSubDirectory(isCurrentPath, isIndent + 2);
                free(isCurrentPath); isCurrentPath = NULL;
            } else if(isPathEntry->d_type == DT_UNKNOWN){fprintf(stdout, "The File Type Couldn't Be Determined.\n");}
        }
        if(isPathEntry->d_type == DT_REG){fprintf(stdout, "%*s%s\n", isIndent, "", isPathEntry->d_name);}
    }
    closedir(isDirectory);
    return;
}

void isLocate(){
    return;
}

void isMakeDirectory(){
    return;
}

void isManual(){
    return;
}

void isMove(){
    return;
}

void isPacketInternetGroper(){
    return;
}

void isPipe(char **isProcessPath, char ***isCommand, bool isBackGround){
    int isPipeFileDescriptor[2], isPipe, isProcessIndex = 0, isExecute, isExitStatus;
    pid_t isProcessID;
    while(*isCommand != NULL){
        isPipe = pipe(isPipeFileDescriptor); if(isPipe == -1){fprintf(stderr, "%s.\n", strerror(errno)); return;}
        isProcessID = fork(); if(isProcessID == -1){fprintf(stderr, "%s.\n", strerror(errno)); return;}
        if(isProcessID == 0){
            if(dup2(isPipeFileDescriptor[0], STDIN_FILENO) == -1){fprintf(stderr, "%s.\n", strerror(errno)); return;}
            if(*(isCommand + 1) != NULL){
                if(dup2(isPipeFileDescriptor[1], STDOUT_FILENO) == -1){fprintf(stderr, "%s.\n", strerror(errno)); return;}
            }
            close(isPipeFileDescriptor[0]); close(isPipeFileDescriptor[1]);
            isExecute = execv(*(isProcessPath + isProcessIndex++), *isCommand); if(isExecute == -1){fprintf(stderr, "%s.\n", strerror(errno)); return;}
        } else{
            if(!isBackGround){
                pid_t isChild = waitpid(isProcessID, isExitStatus, 0); if(isChild == -1){fprintf(stderr, "%s.\n", strerror(errno)); return;}
                if(isChild == isProcessID){fprintf(stdout, WIFEXITED(isExitStatus) ? "Child Process %d Terminated Successfully" : "Child Process %d Terminated Unsuccessfully", isChild);}
            }
            if(*(isCommand + 1) == NULL){close(isPipeFileDescriptor[0]);}
            close(isPipeFileDescriptor[1]);
            isCommand++;
        }
    }
    return;
}

void isPipeAndRedirection(){
    return;
}

void isPrintWorkingDirectory(){
    char *isPath = calloc(1025, sizeof(char)); if(isPath == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    if(getcwd(isPath, 1025) != NULL){fprintf(stdout, "%s\n", isPath);} else{fprintf(stdout, "%s\n", strerror(errno)); return;}
    return;
}

void isProcessPath(){
    return;
}

void isProcessStatus(char *isOptionFlag, pid_t isPID){ // Fix order of execution, will probably have to use switch, make sure parsing catches arguments for flags and distinguishes them from flags without a hyphen.
    int isFileDescriptor, isBytesRead;
    struct stat isPathStat;
    char *isStorage = calloc(4096, sizeof(char)); if(isStorage == NULL){fprintf(stdout, "Memory Allocation Failed.\n"); return;}
    if(strstr(isOptionFlag, "-o")){ // "-o cmd" for only command and "-o args" for full command
        if(strstr(isOptionFlag, "cmd")){
            if(snprintf(isStorage, 4096, "/proc/%ld", isPID) < 0){fprintf(stdout, "%s.\n", strerror(errno)); return;}
            if(stat(isStorage, &isPathStat) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
            if(snprintf(isStorage, 4096, "/proc/%ld/cmdline", isPID) < 0){fprintf(stdout, "%s.\n", strerror(errno)); return;}
            if((isFileDescriptor = open(isStorage, O_RDONLY)) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
            isBytesRead = read(isFileDescriptor, isStorage, 4096); if(isBytesRead == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
            *(isStorage + isBytesRead) = '\0'; close(isFileDescriptor);
            fprintf(stdout, "%s\n", isStorage);
        }
        if(strstr(isOptionFlag, "args")){
            if(snprintf(isStorage, 4096, "/proc/%ld", isPID) < 0){fprintf(stdout, "%s.\n", strerror(errno)); return;}
            if(stat(isStorage, &isPathStat) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
            if(snprintf(isStorage, 4096, "/proc/%ld/cmdline", isPID) < 0){fprintf(stdout, "%s.\n", strerror(errno)); return;}
            if((isFileDescriptor = open(isStorage, O_RDONLY)) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
            if((isBytesRead = read(isFileDescriptor, isStorage, 4096)) > 0){
                for(int isIndex = 0; isIndex < isBytesRead; (*(isStorage + isIndex) == '\0') && (*(isStorage + isIndex) = ' '), isIndex++);
                *(isStorage + isBytesRead) = '\0';
            }
            if(isBytesRead == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
            close(isFileDescriptor);
            fprintf(stdout, "%s\n", isStorage);
        }
    }
    if(strstr(isOptionFlag, "-p")){

    }
    if(strstr(isOptionFlag, "-U")){

    }
    if(strstr(isOptionFlag, "v")){ // incomplete
        if(snprintf(isStorage, 4096, "/proc/%ld", isPID) < 0){fprintf(stdout, "%s.\n", strerror(errno)); return;}
        if(stat(isStorage, &isPathStat) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
        if(snprintf(isStorage, 4096, "/proc/%ld/statm", isPID) < 0){fprintf(stdout, "%s.\n", strerror(errno)); return;}
        char *isVMSize, *isVMResidentSetSize, *isPtr = NULL;
        if((isFileDescriptor = open(isStorage, O_RDONLY)) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
        if((isBytesRead = read(isFileDescriptor, isStorage, 4096)) > 0){
            isVMSize = strtok_r(isStorage, " ", &isPtr);
            isVMResidentSetSize = strtok_r(NULL, " ", &isPtr);
        }
        if(isBytesRead == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
        close(isFileDescriptor);
        fprintf(stdout, "Virtual Memory Size: %s\n", isVMSize);
        fprintf(stdout, "Resident Set Size: %s\n", isVMResidentSetSize);
    }
    return;
}

void isRedirect(char *isProcessPath, char **isCommand, char **isArgument, char *isRedirection, bool isBackGround){
    int isInputFileDescriptor, isInputDUP, isOutputFileDescriptor, isOutputDUP, isStandardFileDescriptor, isStandardDUP, isExecute, isExitStatus;
    pid_t isProcessID = fork(); if(isProcessID == -1){fprintf(stderr, "%s.\n", strerror(errno)); return;}
    if(isProcessID == 0){
        // <
        isInputFileDescriptor = open(*isArgument, O_RDONLY); if(isInputFileDescriptor == -1){fprintf(stderr, "%s.\n", strerror(errno)); return;}
        isInputDUP = dup2(isInputFileDescriptor, STDIN_FILENO); if(isInputDUP == -1){fprintf(stderr, "%s.\n", strerror(errno)); return;}
        close(isInputFileDescriptor);
        // > | >>
        isOutputFileDescriptor = open(*isArgument, O_WRONLY | O_CREAT | O_TRUNC /*O_APPEND*/, 0766); if(isOutputFileDescriptor == -1){fprintf(stderr, "%s.\n", strerror(errno)); return;}
        isOutputDUP = dup2(isOutputFileDescriptor, STDOUT_FILENO); if(isOutputDUP == -1){fprintf(stderr, "%s.\n", strerror(errno)); return;}
        close(isOutputFileDescriptor);
        // < >
        isInputFileDescriptor = open(*isArgument, O_RDONLY); if(isInputFileDescriptor == -1){fprintf(stderr, "%s.\n", strerror(errno)); return;}
        isInputDUP = dup2(isInputFileDescriptor, STDIN_FILENO); if(isInputDUP == -1){fprintf(stderr, "%s.\n", strerror(errno)); return;}
        close(isInputFileDescriptor);
        isOutputFileDescriptor = open(*(isArgument + 1), O_WRONLY | O_CREAT | O_TRUNC, 0766); if(isOutputFileDescriptor == -1){fprintf(stderr, "%s.\n", strerror(errno)); return;}
        isOutputDUP = dup2(isOutputFileDescriptor, STDOUT_FILENO); if(isOutputDUP == -1){fprintf(stderr, "%s.\n", strerror(errno)); return;}
        close(isOutputFileDescriptor);
        // &> | >& | > fileName 2>&1 | Format: command &> fileName Redirect both stdout and stderr to the file
        isStandardFileDescriptor = open(*isArgument, O_WRONLY | O_CREAT | O_TRUNC, 0766); if(isOutputFileDescriptor == -1){fprintf(stderr, "%s.\n", strerror(errno)); return;}
        isStandardDUP = dup2(isStandardFileDescriptor, STDOUT_FILENO); if(isStandardDUP == -1){fprintf(stderr, "%s.\n", strerror(errno)); return;}
        isStandardDUP = dup2(isStandardFileDescriptor, STDERR_FILENO); if(isStandardDUP == -1){fprintf(stderr, "%s.\n", strerror(errno)); return;}
        close(isStandardFileDescriptor);
        // 0>
        isStandardFileDescriptor = open(*isArgument, O_RDONLY); if(isOutputFileDescriptor == -1){fprintf(stderr, "%s.\n", strerror(errno)); return;}
        isStandardDUP = dup2(isStandardFileDescriptor, STDIN_FILENO); if(isStandardDUP == -1){fprintf(stderr, "%s.\n", strerror(errno)); return;}
        close(isStandardFileDescriptor);
        // 1> | 1>>
        isStandardFileDescriptor = open(*isArgument, O_WRONLY | O_CREAT | O_TRUNC /*O_APPEND*/, 0766); if(isOutputFileDescriptor == -1){fprintf(stderr, "%s.\n", strerror(errno)); return;}
        isStandardDUP = dup2(isStandardFileDescriptor, STDOUT_FILENO); if(isStandardDUP == -1){fprintf(stderr, "%s.\n", strerror(errno)); return;}
        close(isStandardFileDescriptor);
        // 2> | 2>>
        isStandardFileDescriptor = open(*isArgument, O_WRONLY | O_CREAT | O_TRUNC /*O_APPEND*/, 0766); if(isOutputFileDescriptor == -1){fprintf(stderr, "%s.\n", strerror(errno)); return;}
        isStandardDUP = dup2(isStandardFileDescriptor, STDERR_FILENO); if(isStandardDUP == -1){fprintf(stderr, "%s.\n", strerror(errno)); return;}
        close(isStandardFileDescriptor);
        // 0>&1
        isStandardDUP = dup2(STDOUT_FILENO, STDIN_FILENO); if(isStandardDUP == -1){fprintf(stderr, "%s.\n", strerror(errno)); return;}
        // 1>&2
        isStandardDUP = dup2(STDERR_FILENO, STDOUT_FILENO); if(isStandardDUP == -1){fprintf(stderr, "%s.\n", strerror(errno)); return;}

        if(isBackGround){if(setsid() == -1){fprintf(stderr, "%s.\n", strerror(errno)); return;}}
        if(freopen("/dev/null", "r", stdin) == NULL){fprintf(stderr, "%s.\n", strerror(errno)); return;}
        isExecute = execv(isProcessPath, isCommand); if(isExecute == -1){fprintf(stderr, "%s.\n", strerror(errno)); return;}
    } else{
        if(!isBackGround){
            pid_t isChild = waitpid(isProcessID, isExitStatus, 0); if(isChild == -1){fprintf(stderr, "%s.\n", strerror(errno)); return;}
            if(isChild == isProcessID){fprintf(stdout, WIFEXITED(isExitStatus) ? "Child Process %d Terminated Successfully" : "Child Process %d Terminated Unsuccessfully", isChild);}
        }
    }
    return;
}

/* rm [-d] [-f] [-i] [-I] [-r] [fileName...] */
void isRemove(char **isOptionFlag, char **isPath, int isPathEntry){
    struct stat isPathStat; struct dirent *isPathEntry;
    int isPathIndex = 0;
    char isChoice;
    while(isPathIndex < isPathEntry){
        // Implement -f FLag
        if(unlink(*isPath) == -1){if(errno != ENOENT){fprintf(stderr, "Cannot Remove %s", *(isPath + isPathIndex)); continue;}
        // Implement -i Flag
        fprintf(stdout, "Remove %s (Y/N): "); scanf("%c", &isChoice);
        if(isChoice == 'y' || isChoice == 'Y'){
            if(unlink(*isPath) == -1){fprintf(stderr, "%s.\n", strerror(errno)); continue;}
        }
        // Implement -I Flag
        if(isPathEntry > 3){
            if(isPathIndex == 0){fprintf(stdout, "Remove Files (Y/N): "); scanf("%c", &isChoice);}
            if(isChoice == 'y' || isChoice == 'Y'){
                if(unlink(*isPath) == -1){fprintf(stderr, "%s.\n", strerror(errno)); continue;}
            }   
        }
        // Implement -r Flag
        if(stat(isPath, &isPathStat) == -1){fprintf(stderr, "%s.\n", strerror(errno)); return;}
        DIR *isDirectory = opendir(isPath); if(isDirectory == NULL){fprintf(stderr, "%s.\n", strerror(errno)); return;}
        if(S_ISDIR(isPathStat.st_mode)){
            while((isPathEntry = readdir(isDirectory)) != NULL){
                if(strcmp(isPathEntry->d_name, ".") == 0 || strcmp(isPathEntry ->d_name, "..") == 0){continue;}
                char *isStorage = calloc(1025, sizeof(char)); if(isStorage == NULL){fprintf(stderr, "Memory Allocation Failed.\n"); return;}
                if(snprintf(isStorage, 1025, "%s/%s", *(isPath + isPathIndex), isPathEntry->d_name) < 0){fprintf(stderr, "%s.\n", strerror(errno)); return;}
                if(stat(isStorage, &isPathStat) == -1){fprintf(stderr, "%s.\n", strerror(errno)); return;}
                if(S_ISDIR(isPathStat.st_mode)){ /*recall function*/}else{if(unlink(*isPath) == -1){fprintf(stderr, "%s.\n", strerror(errno)); return;}}
            }
        }
        closedir(isPath);
        // Implement rmdir for -r flag to remove the dir after removing all files.

    }
    return;
}

void isRemoveDirectory(){
    return;
}

void isSecureShell(){
    return;
}

void isSleep(){
    return;
}

void isTail(){
    return;
}

void isTapeArchive(){
    return;
}

void isTouch(char **isFile, int isFileEntry){
    int isFileIndex = 0, isFileDescriptor;
    while(isFileIndex < isFileEntry){
        if((isFileDescriptor = open(*(isFile + isFileIndex), O_WRONLY | O_CREAT | O_TRUNC, 0766)) == -1){fprintf(stdout, "%s.\n", strerror(errno)); return;}
        isFileIndex++;
    }
    return;
}

void isWordCount(){
    return;
}

void isWorldWideWebGet(){
    return;
}