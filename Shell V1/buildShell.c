#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <libgen.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

void buildPwd();
void buildCd(char *thisDir);
void buildHelp();
void buildWait();
char *rmSpace(char *thisStr);
char **tokenizeCommandLine(char *thisString);
char **tokenizeString(char *thisString, char *thisDelimiter);
char *buildPath(char *processName);
void buildStructure(char *cmdLine);
void buildRPStructure(char *cmdLine);
void buildExecute(char *thisArg[], bool isBPrc);
void buildSER(char *prcExe[], char *rFl[], char rID, bool isBPrc);
void buildSEP(char ***exeArgs, bool isBPrc);

int main(){
    while (1){
        int status;
        char *linePtr = NULL, *findRP = "<|>";
        size_t getUserLine, bufferSize = _POSIX_ARG_MAX;
        printf("Black_Gallery_$ ");
        getUserLine = getline(&linePtr, &bufferSize, stdin);
        if(getUserLine == -1){
            fprintf(stderr, "%s\n", strerror(errno));
            continue;
        }
        bool isRP = strpbrk(linePtr, findRP) != NULL ? true : false;
        linePtr[(strlen(linePtr) - 1)] = '\0';
        (isRP) ? buildRPStructure(linePtr) : buildStructure(linePtr);
        waitpid(-1, &status, WNOHANG);
    }
}

/*
Shell Functions
*/
void buildPwd(){
    char getPwd[256]; 
    if(getcwd(getPwd, sizeof(getPwd)) != NULL){
        fprintf(stdout, "%s\n", getPwd);
    } else{
        fprintf(stderr, "%s\n", strerror(errno));
    }
    return;
}

void buildCd(char *thisDir){
    int cdDir = chdir(thisDir);
    if(cdDir == -1){
        fprintf(stderr, "%s\n", strerror(errno));
    }
    return;
}

void buildWait(){
    while(1){
        wait(NULL);
        if(errno == ECHILD){
            break;
        }
    }
}

void buildHelp(){
    printf("<Black Gallery TM>\n");
    printf("Shell Commands: \n");
    printf("help\tDisplay the help Manual\n");
    printf("wait\tWait for all background processes to finish\n");
    printf("pwd \tDisplay the current working directory\n");
    printf("cd  \tChange the current working directory\n");
    printf("exit\tExit the shell\n");
}

//Help Functions
char *rmSpace(char *thisStr){
    char *end;
    while(isspace(*thisStr)) thisStr++;
    if(*thisStr == 0)
    return thisStr;
    end = thisStr + strlen(thisStr) - 1;
    while(end > thisStr && isspace((*end)))end--;
    end[1] = '\0';
    return thisStr;
}

char **tokenizeCommandLine(char *thisString){
    int countWords = 0, thisWord = 0, wordLeft = 0, followThis = 0;
    for(int thisChar = 0; thisChar < strlen(thisString); countWords += (isspace(thisString[thisChar]) && isalpha(thisString[thisChar + 1])) ? 1 : 0, countWords += thisString[thisChar] == '\0'  ? 1 : 0, thisChar++);
    char **stringArray = (char **)malloc(sizeof(char **) * countWords + 1);
    char *getWord = (char *)malloc(sizeof(char *));
    for(; followThis < strlen(thisString) + 1; followThis++){
        if(thisString[followThis] == '<' || thisString[followThis] == '>' || thisString[followThis] == '|' || thisString[followThis] == '\0'){
            stringArray[thisWord] = calloc(wordLeft, sizeof(char));
            char *thisCMD = rmSpace(getWord);
            memcpy(stringArray[thisWord], thisCMD, wordLeft);
            thisWord++;
            wordLeft = 0;
            getWord = calloc(1, sizeof(char));
            continue;
        }
        *(getWord + wordLeft) = thisString[followThis];
        getWord = realloc(getWord, sizeof(char));
        wordLeft++;
    }
    stringArray[thisWord] = NULL;
    free(getWord);
    return stringArray;
}

char **tokenizeString(char *thisString, char *thisDelimiter){
    int countWords = 0, thisTkn = 0;
    for(int i = 0; i < strlen(thisString); i++){
        if((isalpha(thisString[i]) && !isalpha(thisString[i + 1])) || (isalpha(thisString[i]) && thisString[i] == '\0')){
            countWords++;
        }
    }
    char *memStr = strdup(thisString);
    char **stringArray = calloc(countWords + 1, sizeof(char *));
    char *getTKn = strtok(memStr, thisDelimiter);
    while(getTKn != NULL){
        stringArray[thisTkn++] = getTKn;
        getTKn = strtok(NULL, thisDelimiter);
    }
    stringArray[thisTkn] = NULL;
    return stringArray;
}

char *buildPath(char *processName){
    char *processPath, *thisFl, *sEnv = getenv("PATH");
    char **envVar = tokenizeString(sEnv, ":");
    while(*envVar != NULL){
        DIR *thisVarDir = opendir(*envVar);
        if(thisVarDir == NULL){
            envVar++;
            continue;
        }
        struct dirent *getVarDir;
        processPath = (char *)malloc(sizeof(char *) * (strlen(*envVar) + 1));
        sprintf(processPath, "%s/", *envVar);
        while((getVarDir = readdir(thisVarDir)) != NULL){
            if(getVarDir -> d_type == DT_DIR){
                continue;
            } else if(getVarDir->d_type == DT_REG){
                thisFl = (char *)malloc(sizeof(char *) * (strlen(getVarDir->d_name) + 1));
                strcpy(thisFl, getVarDir->d_name);
                if(strcmp(thisFl, processName) == 0){
                    processPath = realloc(processPath, sizeof(char *) * strlen(thisFl));
                    strcat(processPath, thisFl);
                    return processPath;
                }
                thisFl = calloc(1, sizeof(char *));
            }
        }
        if(*(envVar + 1) == NULL){
            free(thisFl);
            free(processPath);
            return "?";
        }
        envVar++;
    }
    return "?";
}

void buildStructure(char *cmdLine){
    char *builtCMD[] = {"cd", "exit", "help", "pwd"}, isAmpersand = '&';
    bool isntBuilt = true, isBG = false;
    (strchr(cmdLine, isAmpersand) != NULL) && (isBG = true);
    for(int isAmp = 0; isAmp < strlen(cmdLine); isAmp++){
        if(cmdLine[isAmp] == isAmpersand){
            cmdLine[isAmp] = '\0';
            break;
        }
    }
    for(int thisCmd = 0; thisCmd < sizeof(builtCMD) / sizeof(builtCMD[0]); thisCmd++){
        if(strstr(cmdLine, builtCMD[thisCmd]) != NULL){
            isntBuilt = false;
            break;
        }
    }
    int countWrd = 0;
    for(int thisChar = 0; thisChar <= strlen(cmdLine); countWrd += (isspace(cmdLine[thisChar]) || cmdLine[thisChar] == '\0') ? 1 : 0, thisChar++);
    if(!isntBuilt){
        if(countWrd == 1){
            if(strstr(cmdLine, builtCMD[1])){
                exit(EXIT_SUCCESS);
            } else if(strstr(cmdLine, builtCMD[2])){
                buildHelp();
            } else if(strstr(cmdLine, builtCMD[3])){
                buildPwd();
            }
        }
        if((countWrd > 1 && strstr(cmdLine, builtCMD[1])) || (countWrd > 1 && strstr(cmdLine, builtCMD[2])) || (countWrd > 1 && strstr(cmdLine, builtCMD[3]))){
            fprintf(stderr, "%s\n", strerror(EINVAL));
            return;
        }
        if(countWrd == 2 && strstr(cmdLine, builtCMD[0])){
            char *cpCMD = strdup(cmdLine);
            char *getPath = calloc(strlen(cpCMD + 3), sizeof(char));
            sprintf(getPath, "%s", (cpCMD + 3));
            buildCd(getPath);
            free(getPath);
        }
        if((countWrd < 2 && strstr(cmdLine, builtCMD[0])) || (countWrd > 2 && strstr(cmdLine, builtCMD[0]))){
            fprintf(stderr, "%s\n", strerror(EINVAL));
            return;
        }
    } else{
        char *memArg = strdup(cmdLine);
        if((strchr(strtok(memArg, " "), '/'))){
            char **exeArg = tokenizeString(cmdLine, " ");
            buildExecute(exeArg, isBG);
            free(exeArg);
        } else{
            char *cpArg = strtok(memArg, " "), *buildArg;
            char *getPath = buildPath(cpArg);
            if(strcmp(getPath, "?") == 0){
                fprintf(stderr, "%s: Command not found\n", cpArg);
                return;
            }
            buildArg = calloc((strlen(cmdLine) - strlen(cpArg) + strlen(getPath) + 2), sizeof(char));
            sprintf(buildArg, "%s %s", getPath, (cpArg + (strlen(cpArg) + 1)));
            char **exeArg = tokenizeString(buildArg, " ");
            buildExecute(exeArg, isBG);
            free(buildArg);
            buildArg = NULL;
            free(getPath);
            getPath = NULL;
            free(exeArg);
            exeArg = NULL;
        }
        free(memArg);
        memArg = NULL;
    }
    if(isBG){
        buildWait();
    }
    return;
}

void buildRPStructure(char *cmdLine){
    char *cmdLinePtr = cmdLine, rIN = '<', rOUT = '>', prcP = '|', isAmpersand = '&';
    bool isR = false, isRIN = false, isROUT = false, isP = false, isBG = false;
    (strchr(cmdLine, isAmpersand) != NULL) && (isBG = true);
    for(int isAmp = 0; isAmp < strlen(cmdLine); isAmp++){
        if(cmdLine[isAmp] == isAmpersand){
            cmdLine[isAmp] = '\0';
            break;
        }
    }
    int cntPunct = 0, findPunct = 0, setVal = 0;
    for(; *cmdLinePtr != '\0'; cmdLinePtr++){
        if(*cmdLinePtr == rIN || *cmdLinePtr == rOUT || *cmdLinePtr == prcP){
            cntPunct += 1;
            (*cmdLinePtr == rIN || *cmdLinePtr == rOUT) && (isR = true);
            (*cmdLinePtr == rIN) && (isRIN = true);
            (*cmdLinePtr == rOUT) && (isROUT = true);
            (*cmdLinePtr == prcP) && (isP = true);
        }
    }
    if(isR && isP){
        fprintf(stderr, "#This shell is a beta version and currently does not support commands with pipe and redirection\n");
        return;
    }
    cmdLinePtr = cmdLine;
    int *punctIndex = calloc(cntPunct, sizeof(int)); // Free
    while(*cmdLinePtr){
        if(*cmdLinePtr == rIN || *cmdLinePtr == rOUT || *cmdLinePtr == prcP){
            punctIndex[setVal++] = findPunct;
        }
        findPunct++;
        cmdLinePtr++;
    }
    cmdLinePtr = cmdLine;
    if(isR && !isP){
        if((cntPunct == 2 && cmdLine[punctIndex[0]] == cmdLine[punctIndex[1]]) || cntPunct > 2 ){
            if(cmdLine[punctIndex[0]] == rIN){
                fprintf(stderr, "Ambiguous Input Redirect\n");
                return;
            }else{
                fprintf(stderr, "Ambiguous Output Redirect\n");
                return;
            }
        }
    }
    char **cmdLineTkn = tokenizeCommandLine(cmdLine), *thisCmd, *isPrc, **prcArg, punctID;
    if(isR && !isP){
        thisCmd = strtok(cmdLineTkn[0], " ");
        if(strchr(thisCmd, '/') == NULL){
            isPrc = buildPath(thisCmd);
            if(strcmp(isPrc, "?") == 0){
                fprintf(stderr, "%s: Command not found\n", thisCmd);
                return;
            } else{
                char *cmdArg = cmdLineTkn[0];
                int argIndex = strlen(thisCmd) + 1;
                char *prcCmd = calloc((strlen((cmdArg + argIndex)) + strlen(isPrc) + 1), sizeof(char));
                sprintf(prcCmd, "%s %s", isPrc, (cmdArg + argIndex));
                prcArg = tokenizeString(prcCmd, " ");
                punctID = cmdLine[punctIndex[0]];
                if(isRIN && isROUT){
                    if(punctID == rOUT){
                        char **arrangeArg = calloc(4, sizeof(char *));
                        arrangeArg[0] = prcCmd;
                        arrangeArg[1] = cmdLineTkn[2];
                        arrangeArg[2] = cmdLineTkn[1];
                        arrangeArg[3] = NULL;
                        buildSER(prcArg, arrangeArg, '&', isBG);
                    } else{
                        buildSER(prcArg, cmdLineTkn, '&', isBG);
                    }
                } else{
                    buildSER(prcArg, cmdLineTkn, punctID, isBG);
                }
            }
        } else{
            prcArg = tokenizeString(cmdLineTkn[0], " ");
            punctID = cmdLine[punctIndex[0]];
            if(isRIN && isROUT){
                if(punctID == rOUT){
                    char **arrangeArg = calloc(4, sizeof(char *));
                    arrangeArg[0] = cmdLineTkn[0];
                    arrangeArg[1] = cmdLineTkn[2];
                    arrangeArg[2] = cmdLineTkn[1];
                    arrangeArg[3] = NULL;
                    buildSER(prcArg, arrangeArg, '&', isBG);
                }
                else{
                    buildSER(prcArg, cmdLineTkn, '&', isBG);
                }
            } else{
                buildSER(prcArg, cmdLineTkn, punctID, isBG);
            }
        }
    } else if(isP && !isR){
        char ***followCMD = calloc((cntPunct + 2), sizeof(char **));
        for(int thisPrc = 0; thisPrc < cntPunct + 2; thisPrc++){
            if(thisPrc == cntPunct + 1){
                followCMD[thisPrc] =  NULL;
                break;
            }
            char *pPRC = cmdLineTkn[thisPrc];
            char *isCmdPath = strtok(pPRC, " ");
            if(strchr(isCmdPath, '/') == NULL){
                char *getCmdPath = buildPath(isCmdPath);
                if(strcmp(getCmdPath, "?") == 0){
                    fprintf(stderr, "%s: Command not found\n", isCmdPath);
                    return; 
                } else{
                    int getArgs = strlen(isCmdPath) + 1;
                    char *exeCmd = calloc((strlen((pPRC + getArgs)) + strlen(getCmdPath) + 1), sizeof(char));
                    sprintf(exeCmd, "%s %s", getCmdPath, (pPRC + getArgs));
                    followCMD[thisPrc] = tokenizeString(exeCmd, " ");
                }
            } else{
                followCMD[thisPrc] = tokenizeString(pPRC, " ");
            }
        }
        buildSEP(followCMD, isBG);
    } 
    if(isBG){
        buildWait();
    }
    return;    
}

void buildExecute(char *thisArg[], bool isBPrc){
    pid_t pID = fork();
    if(pID < 0){
        fprintf(stderr, "%s\n", strerror(errno));
        return;
    } else if(pID == 0){
        int isExe = execv(thisArg[0], thisArg);
        if (isExe == -1){
            fprintf(stderr, "%s\n", strerror(errno));
            return;
        }
    } else{
        if(!isBPrc){
            waitpid(pID, NULL, 0);
        }
        return;
    }
}

void buildSER(char *prcExe[], char *rFl[], char rID, bool isBPrc){
    char rIN = '<', rOUT = '>', rINOUT = '&';
    pid_t pID = fork();
    if(pID < 0){
        fprintf(stderr, "%s\n", strerror(errno));
        return;
    } else if(pID == 0){
        if(rID == rIN){
            int inFlDsc = open(rFl[1], O_RDONLY);
            if(inFlDsc == -1){
                fprintf(stderr, "%s\n", strerror(errno));
                return;
            }
            int getIFD = dup2(inFlDsc, STDIN_FILENO);
            if(getIFD == -1){
                fprintf(stderr, "%s\n", strerror(errno));
                return;
            }
            close(inFlDsc);
        } else if(rID == rOUT){
            int outFlDsc = open(rFl[1], O_WRONLY | O_CREAT | O_TRUNC, 0755);
            if(outFlDsc == -1){
                fprintf(stderr, "%s\n", strerror(errno));
                return;
            }
            int getOFD = dup2(outFlDsc, STDOUT_FILENO);
            if(getOFD == -1){
                fprintf(stderr, "%s\n", strerror(errno));
                return;
            }
            close(outFlDsc);
        } else if(rID == rINOUT){
            int inFlDsc = open(rFl[1], O_RDONLY);
            if(inFlDsc == -1){
                fprintf(stderr, "%s\n", strerror(errno));
                return;
            }
            int getIFD = dup2(inFlDsc, STDIN_FILENO);
            if(getIFD == -1){
                fprintf(stderr, "%s\n", strerror(errno));
                return;
            }
            close(inFlDsc);
            int outFlDsc = open(rFl[2], O_WRONLY | O_CREAT | O_TRUNC, 0755);
            if (outFlDsc == -1){
                fprintf(stderr, "%s\n", strerror(errno));
                return;
            }
            int getOFD = dup2(outFlDsc, STDOUT_FILENO);
            if(getOFD == -1){
                fprintf(stderr, "%s\n", strerror(errno));
                return;
            }
            close(outFlDsc);
        }
        int isExe = execv(prcExe[0], prcExe);
        if(isExe == -1){
            fprintf(stderr, "%s\n", strerror(errno));
            return;
        }
    } else{
        if(!isBPrc){
            waitpid(pID, NULL, 0);
        }
        return;
    }
}

void buildSEP(char ***exeArgs, bool isBPrc){
    int FlDsc[2], thisFlDsc = 0, isP;
    pid_t pID;
    while(*exeArgs != NULL){
        isP = pipe(FlDsc);
        if(isP == -1){
            fprintf(stderr, "%s\n", strerror(errno));
            return;
        }
        pID = fork();
        if(pID < 0){
            fprintf(stderr, "%s\n", strerror(errno));
            return;
        } else if(pID == 0){
            dup2(thisFlDsc, 0);
            if(*(exeArgs + 1) != NULL){
                dup2(FlDsc[1], 1);
            }
            close(FlDsc[0]);
            int isExe = execv(*exeArgs[0], *exeArgs);
            if(isExe == -1){
                fprintf(stderr, "%s\n", strerror(errno));
                return;
            }
        } else{
            if(!isBPrc){
                waitpid(pID, NULL, 0);
            }else if(isBPrc && *(exeArgs + 1) != NULL){
                waitpid(pID, NULL, 0);
            }
            close(FlDsc[1]);
            thisFlDsc = FlDsc[0];
            if(*(exeArgs + 1) == NULL){
                close(FlDsc[0]);
                return;
            }
            exeArgs++;
        }
    }
}
