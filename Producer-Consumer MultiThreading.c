#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct critical_section{
    pthread_mutex_t getLock;
    pthread_cond_t isFull, isEmpty;
    bool endConsume;
    int *productQueue, countQueue;
}synchronization;

typedef struct producer_consumer{
    int pFlDsc[2], isFileDescriptor, noProducer, *produceType, *getProducts, currentProducers, consumerThreadExit, pipeConsumers, threadID, logCount;
    synchronization **isSync;
}shared_resources;

shared_resources *init_sr(int noProducer);
void *build_Producer(void *thread_Args);
void *build_Consumer(void *thread_Args);

int main(){
    srand(time(NULL));
    int *noConsumer, *queueSize, noProducer, aggregateConsumers, getThreads, isThread, isPipe, isExecute;
    char *endDigitPtr;
    void *cancelledThread;
    fprintf(stdout, "Enter the number of producer(s): ");
    scanf("%d", &noProducer);
    noConsumer = calloc(noProducer, sizeof(int));
    if(noConsumer == NULL){fprintf(stderr, "Memory Allocation Failed\n"); exit(EXIT_FAILURE);}
    queueSize = calloc(noProducer, sizeof(int));
    if(queueSize == NULL){fprintf(stderr, "Memory Allocation Failed\n"); exit(EXIT_FAILURE);}
    shared_resources *pc_sr = init_sr(noProducer);
    synchronization **getSync = pc_sr->isSync;
    for(int thisProducer = 0; thisProducer < noProducer; thisProducer++){
        fprintf(stdout, "\nEnter the number of products for producer %d: ", (thisProducer + 1));
        scanf("%d", (pc_sr->getProducts + thisProducer));
        fprintf(stdout, "Enter the produce type for producer %d: ", (thisProducer + 1));
        scanf("%d", (pc_sr->produceType + thisProducer));
        fprintf(stdout, "Enter the number of consumer(s) for producer %d: ", (thisProducer + 1));
        scanf("%d", (noConsumer + thisProducer));
        fprintf(stdout, "Enter queue size for producer %d: ", (thisProducer + 1));
        scanf("%d", (queueSize + thisProducer));
        aggregateConsumers += *(noConsumer + thisProducer);
        *(getSync + thisProducer) = calloc(1, sizeof(synchronization));
        if(getSync == NULL){fprintf(stderr, "Memory Allocation Failed\n"); exit(EXIT_FAILURE);}
        (*(getSync + thisProducer))->productQueue = calloc(*(queueSize + thisProducer), sizeof(int));
        if((*(getSync + thisProducer))->productQueue == NULL){fprintf(stderr, "Memory Allocation Failed\n"); exit(EXIT_FAILURE);}
        getThreads += *(noConsumer + thisProducer);
        (*(getSync + thisProducer))->countQueue = 0;
        (*(getSync + thisProducer))->endConsume = false;
        isExecute = pthread_mutex_init(&(*(getSync + thisProducer))->getLock, NULL);
        if(isExecute != 0){fprintf(stderr, "%s\n", strerror(isExecute)); exit(EXIT_FAILURE);}
        isExecute = pthread_cond_init(&(*(getSync + thisProducer))->isFull, NULL);
        if(isExecute != 0){fprintf(stderr, "%s\n", strerror(isExecute)); exit(EXIT_FAILURE);}
        isExecute = pthread_cond_init(&(*(getSync + thisProducer))->isEmpty, NULL);
        if(isExecute != 0){fprintf(stderr, "%s\n", strerror(isExecute)); exit(EXIT_FAILURE);}
    }
    pthread_t *build_PC = calloc(noProducer + getThreads, sizeof(pthread_t));
    if(build_PC == NULL){fprintf(stderr, "Memory Allocation Failed\n"); exit(EXIT_FAILURE);}
    isPipe = pipe(pc_sr->pFlDsc);
    if(isPipe == -1){fprintf(stderr, "%s\n", strerror(errno)); exit(EXIT_FAILURE);}
    for(int isProducer = 0; isProducer < noProducer; isProducer++){
        pc_sr->threadID = isProducer;
        isExecute = pthread_create((build_PC + (isThread++)), NULL, build_Producer, pc_sr);
        if(isExecute != 0){fprintf(stderr, "%s\n", strerror(isExecute)); exit(EXIT_FAILURE);}
        for(int isConsumer = 0; isConsumer < *(noConsumer + isProducer); isConsumer++){
            isExecute = pthread_create((build_PC + (isThread++)), NULL, build_Consumer, pc_sr);
            if(isExecute != 0){fprintf(stderr, "%s\n", strerror(isExecute)); exit(EXIT_FAILURE);}
        }
        sleep(1.5);
    }
    while(1){
        if(pc_sr->pipeConsumers == noProducer){close(pc_sr->pFlDsc[0]); close(pc_sr->isFileDescriptor); break;}
        char *thisProduce = calloc(16, sizeof(char)), *isIdentifier = calloc(16, sizeof(char)), *endDigitPtr;
        if(read(pc_sr->pFlDsc[0], thisProduce, 16) == -1){fprintf(stderr, "%s", strerror(errno)); exit(EXIT_FAILURE);}
        *isIdentifier = *(thisProduce + (strlen(thisProduce) - 1));
        for(int thisProducer = 0; thisProducer < pc_sr->noProducer; thisProducer++){ //For now the identifier product type can only be a single character
            if(pc_sr->produceType[thisProducer] == strtol(isIdentifier, &endDigitPtr, 10)){
                *(thisProduce + (strlen(thisProduce) - 1)) = '\0';
                isExecute = pthread_mutex_lock(&(*(getSync + thisProducer))->getLock);
                if(isExecute != 0){fprintf(stderr, "%s\n", strerror(isExecute)); exit(EXIT_FAILURE);}
                while((*(getSync + thisProducer))->countQueue == queueSize[thisProducer] - 1){
                    isExecute = pthread_cond_wait(&(*(getSync + thisProducer))->isEmpty, &(*(getSync + thisProducer))->getLock);
                    if(isExecute != 0){fprintf(stderr, "%s\n", strerror(isExecute)); exit(EXIT_FAILURE);}
                }
                (*(getSync + thisProducer))->productQueue[(*(getSync + thisProducer))->countQueue] = (*thisProduce == '-') ? -1 : strtol(thisProduce, &endDigitPtr, 10);
                (*(getSync + thisProducer))->countQueue++;
                isExecute = pthread_cond_broadcast(&(*(getSync + thisProducer))->isFull);
                if(isExecute != 0){fprintf(stderr, "%s\n", strerror(isExecute)); exit(EXIT_FAILURE);}
                isExecute = pthread_mutex_unlock(&(*(getSync + thisProducer))->getLock);
                if(isExecute != 0){fprintf(stderr, "%s\n", strerror(isExecute)); exit(EXIT_FAILURE);}
            }
        }
        sleep(0.75);
    }
    while(1){
        if(pc_sr->consumerThreadExit == aggregateConsumers){break;}
    }
    for(int thisThread = 0; thisThread < (noProducer + getThreads); thisThread++){
        isExecute = pthread_join(*(build_PC + thisThread), &cancelledThread);
        if(isExecute != 0){fprintf(stderr, "See %s\n", strerror(isExecute)); exit(EXIT_FAILURE);}
    }
    free(build_PC);
    build_PC = NULL;
    free(pc_sr->produceType);
    pc_sr->produceType = NULL;
    free(pc_sr->getProducts);
    pc_sr->getProducts = NULL;
    for(int thisProducer = 0; thisProducer < noProducer; thisProducer++){
        isExecute = pthread_mutex_destroy(&getSync[thisProducer]->getLock);
        if(isExecute != 0){fprintf(stderr, "%s\n", strerror(isExecute)); exit(EXIT_FAILURE);}
        isExecute = pthread_cond_destroy(&getSync[thisProducer]->isFull);
        if(isExecute != 0){fprintf(stderr, "%s\n", strerror(isExecute)); exit(EXIT_FAILURE);}
        isExecute = pthread_cond_destroy(&getSync[thisProducer]->isEmpty);
        if(isExecute != 0){fprintf(stderr, "%s\n", strerror(isExecute)); exit(EXIT_FAILURE);}
        free((*(getSync + thisProducer))->productQueue);
        (*(getSync + thisProducer))->productQueue = NULL;
        free(*(getSync + thisProducer));
        *(getSync + thisProducer) = NULL;
    }
    free(noConsumer);
    noConsumer = NULL;
    free(queueSize);
    queueSize = NULL;
    free(getSync);
    getSync = NULL;
    free(pc_sr);
    pc_sr = NULL;
    return 0;
}

shared_resources *init_sr(int noProducer){
    shared_resources *pc_sr = calloc(1, sizeof(shared_resources));
    if(pc_sr == NULL){fprintf(stderr, "Memory Allocation Failed\n"); exit(EXIT_FAILURE);}
    pc_sr->produceType = calloc(noProducer, sizeof(int));
    if(pc_sr->produceType == NULL){fprintf(stderr, "Memory Allocation Failed\n"); exit(EXIT_FAILURE);}
    pc_sr->getProducts = calloc(noProducer, sizeof(int));
    if(pc_sr->getProducts == NULL){fprintf(stderr, "Memory Allocation Failed\n"); exit(EXIT_FAILURE);}
    pc_sr->isFileDescriptor = open("File Report.log", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if(pc_sr->isFileDescriptor == -1){fprintf(stderr, "%s\n", strerror(errno)); exit(EXIT_FAILURE);}
    pc_sr->isSync = calloc(pc_sr->noProducer, sizeof(synchronization *));
    if(pc_sr->isSync == NULL){fprintf(stderr, "Memory Allocation Failed\n"); exit(EXIT_FAILURE);}
    pc_sr->noProducer = noProducer;
    pc_sr->currentProducers = noProducer;
    return pc_sr;
}

void *build_Producer(void *thread_Args){
    shared_resources *pc_sr = (shared_resources *)thread_Args;
    ssize_t bytesWritten;
    int countProduce = 1, isProducer = pc_sr->threadID, sendBytes;
    while(1){
        if(countProduce > pc_sr->getProducts[isProducer]){
            char *endProduce = calloc(16, sizeof(char));
            sendBytes = snprintf(endProduce, 16, "%d%d", -1, pc_sr->produceType[isProducer]);
            if(sendBytes < 0){fprintf(stderr, "%s", strerror(errno)); exit(EXIT_FAILURE);}
            bytesWritten = write(pc_sr->pFlDsc[1], endProduce, 16);
            if(bytesWritten == -1){fprintf(stderr, "%s", strerror(errno)); exit(EXIT_FAILURE);}
            pc_sr->currentProducers--;
            if(pc_sr->currentProducers == 0){close(pc_sr->pFlDsc[1]);}
            break;
        }
        char *writeProduce = calloc(16, sizeof(char));
        sendBytes = snprintf(writeProduce, 16, "%d%d", countProduce, pc_sr->produceType[isProducer]);
        if(sendBytes < 0){fprintf(stderr, "%s", strerror(errno)); exit(EXIT_FAILURE);}
        bytesWritten = write(pc_sr->pFlDsc[1], writeProduce, 16);
        if(bytesWritten == -1){fprintf(stderr, "%s", strerror(errno)); exit(EXIT_FAILURE);}
        float getSleep = (float)rand()/(float)(RAND_MAX) *(0.2 - 0.01) + 0.01;
        getSleep *= 1000000;
        usleep(getSleep);
        countProduce++;
    }
    pthread_exit(0);
}

void *build_Consumer(void *thread_Args){
    shared_resources *pc_sr = (shared_resources *)thread_Args;
    int get_Dequeue, consumeProduce = pc_sr->threadID, isExecute, logMessageSize, setLogMessage, bytesWritten;
    while(1){
        if(pc_sr->isSync[consumeProduce]->endConsume){break;}
        isExecute = pthread_mutex_lock(&pc_sr->isSync[consumeProduce]->getLock);
        if(isExecute != 0){fprintf(stderr, "%s\n", strerror(isExecute)); exit(EXIT_FAILURE);}
        while(pc_sr->isSync[consumeProduce]->countQueue == 0){
            isExecute = pthread_cond_wait(&pc_sr->isSync[consumeProduce]->isFull, &pc_sr->isSync[consumeProduce]->getLock);
            if(isExecute != 0){fprintf(stderr, "%s\n", strerror(isExecute)); exit(EXIT_FAILURE);}
        }
        get_Dequeue = pc_sr->isSync[consumeProduce]->productQueue[0];
        printf("Type: %d Dequeue: %d\n", pc_sr->produceType[consumeProduce], get_Dequeue);
        if(get_Dequeue == -1){
            (!pc_sr->isSync[consumeProduce]->endConsume) && (pc_sr->pipeConsumers++);
            pc_sr->isSync[consumeProduce]->endConsume = true;
            pc_sr->consumerThreadExit++;
            isExecute = pthread_mutex_unlock(&pc_sr->isSync[consumeProduce]->getLock);
            if(isExecute != 0){fprintf(stderr, "%s\n", strerror(isExecute)); exit(EXIT_FAILURE);}
            break;
        }
        pc_sr->logCount++;
        pc_sr->isSync[consumeProduce]->countQueue--;
        logMessageSize = snprintf(NULL, 0, "Type: %d\tThread Id: %ld\tProduction No: %d\tConsumption No: %d\n", pc_sr->produceType[consumeProduce], pthread_self(), get_Dequeue, pc_sr->logCount);
		if(logMessageSize < 0){fprintf(stderr, "%s\n", strerror(errno)); exit(EXIT_FAILURE);}
		char *logMessage = calloc(logMessageSize + 1, sizeof(char));
		if(logMessage == NULL){fprintf(stderr, "Memory Allocation Failed\n"); exit(EXIT_FAILURE);}
        setLogMessage = snprintf(logMessage, logMessageSize, "Type: %d\tThread Id: %ld\tProduction No: %d\tConsumption No: %d\n", pc_sr->produceType[consumeProduce], pthread_self(), get_Dequeue, pc_sr->logCount);
		if(setLogMessage < 0){fprintf(stderr, "%s\n", strerror(errno)); exit(EXIT_FAILURE);}
		bytesWritten = write(pc_sr->isFileDescriptor, logMessage, setLogMessage + 1);
		if(bytesWritten == -1){fprintf(stderr, "%s\n", strerror(errno)); exit(EXIT_FAILURE);}
        isExecute = pthread_cond_signal(&pc_sr->isSync[consumeProduce]->isEmpty);
        if(isExecute != 0){fprintf(stderr, "%s\n", strerror(isExecute)); exit(EXIT_FAILURE);}
        isExecute = pthread_mutex_unlock(&pc_sr->isSync[consumeProduce]->getLock);
        if(isExecute != 0){fprintf(stderr, "%s\n", strerror(isExecute)); exit(EXIT_FAILURE);}
        sleep(0.5);
    }
    pthread_exit(0);
}