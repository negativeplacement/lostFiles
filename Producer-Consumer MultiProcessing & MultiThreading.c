#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#define _SVID_SOURCE
#define _GNU_SOURCE

#include <errno.h>
#include <fcntl.h>  
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>  
#include <sys/wait.h>
#include <unistd.h>

#define get_Bytes 12

typedef struct critical_section{
    pthread_mutex_t getLock;
    pthread_cond_t isFull, isEmpty;
    bool endConsume;
    int *productQueue, countQueue;
}synchronization;

typedef struct producer_consumer{
    int pFlDsc[2], logCount, noProducer, *produceType, *getProducts, currentProducers, exitThread, threadID;
    FILE *getFile;
    synchronization *isSync;
}shared_resources;

void init_sr(shared_resources *pc_sr, int noProducer);
void build_Producer(shared_resources *pc_sr, int isProducer, int productType);
void *build_Consumer(void *thread_Args);

void init_sr(shared_resources *pc_sr, int noProducer){
    pc_sr->produceType = calloc(noProducer, sizeof(int));
    if(pc_sr->produceType == NULL){
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    pc_sr->getProducts = calloc(noProducer, sizeof(int));
    if(pc_sr->getProducts == NULL){
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    pc_sr->logCount = 0;
    pc_sr->noProducer = noProducer;
    pc_sr->currentProducers = noProducer;
    pc_sr->getFile = fopen("File Report.log", "w+");
    if(pc_sr->getFile == NULL){
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    return;
}

int main(){
    /*int isSharedMemory = shm_open("SM", O_CREAT | O_TRUNC| O_RDWR, S_IRWXU); 
    if(isSharedMemory == -1){
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    if(ftruncate(isSharedMemory, sizeof(shared_resources)) == -1){
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    shared_resources *pc_sr = mmap(NULL, sizeof(shared_resources), PROT_READ|PROT_WRITE, MAP_SHARED, isSharedMemory, 0);*/
    srand(time(NULL));
    int *noConsumer, *queueSize, noProducer, getThreads = 0, isThread = 0;
    fprintf(stdout, "Enter the number of producer(s): ");
    scanf("%d", &noProducer);
    noConsumer = calloc(noProducer, sizeof(int));
    queueSize = calloc(noProducer, sizeof(int));
    shared_resources *pc_sr = mmap(NULL, sizeof(shared_resources), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    if(pc_sr == MAP_FAILED){
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    pc_sr->isSync = mmap(NULL, sizeof(synchronization) * noProducer, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    if(pc_sr->isSync == MAP_FAILED){
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    init_sr(pc_sr, noProducer);
    synchronization *getSync = pc_sr -> isSync;
    pthread_mutexattr_t mutexLock;
    pthread_mutexattr_init(&mutexLock);
    pthread_mutexattr_setpshared(&mutexLock, PTHREAD_PROCESS_SHARED);
    pthread_condattr_t mutexFull, mutexEmpty;
    pthread_condattr_init(&mutexFull);
    pthread_condattr_setpshared(&mutexFull, PTHREAD_PROCESS_SHARED);
    pthread_condattr_init(&mutexEmpty);
    pthread_condattr_setpshared(&mutexEmpty, PTHREAD_PROCESS_SHARED);
    for(int thisProducer = 0; thisProducer < noProducer; thisProducer++){
        fprintf(stdout, "\nEnter the number of products for producer %d: ", (thisProducer + 1));
        scanf("%d", &pc_sr->getProducts[thisProducer]);
        fprintf(stdout, "Enter the produce type for producer %d: ", (thisProducer + 1));
        scanf("%d", &pc_sr->produceType[thisProducer]);
        fprintf(stdout, "Enter the number of consumer(s) for producer %d: ", (thisProducer + 1));
        scanf("%d", &noConsumer[thisProducer]);
        fprintf(stdout, "Enter queue size for producer %d: ", (thisProducer + 1));
        scanf("%d", &queueSize[thisProducer]);
        getSync[thisProducer].productQueue = malloc(sizeof(int) * queueSize[thisProducer]);
        getThreads += noConsumer[thisProducer];
        getSync[thisProducer].countQueue = 0;
        pthread_mutex_init(&getSync[thisProducer].getLock, &mutexLock);
        pthread_cond_init(&getSync[thisProducer].isFull, &mutexFull);
        pthread_cond_init(&getSync[thisProducer].isEmpty, &mutexEmpty);
    }
    pthread_t buildThread[getThreads];
    if(pipe(pc_sr->pFlDsc) == -1){
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    pc_sr->exitThread = 0;
    for(int getChild = 0; getChild < noProducer; getChild++){
        pid_t childID = fork();
        if(childID < 0){
            fprintf(stderr, "%s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }else if(childID == 0){
            if(getChild == 0){
                close(pc_sr->pFlDsc[0]);
            }
            build_Producer(pc_sr, getChild, pc_sr->produceType[getChild]);
            _Exit(EXIT_SUCCESS);
        }
    }
    for(int thisProducer = 0; thisProducer < noProducer; thisProducer++){
        pc_sr->threadID = thisProducer;
        for(int isConsumer = 0; isConsumer < noConsumer[thisProducer]; isConsumer++){
            pthread_create(&buildThread[isThread], NULL, build_Consumer, pc_sr);
            isThread++;
            sleep(1);
        }
    }
    while(1){
        if(pc_sr->exitThread == noProducer){
            close(pc_sr->pFlDsc[0]);
            fclose(pc_sr->getFile);
            puts("Exit");
            break;
        }
        char *thisProduce = calloc(get_Bytes, sizeof(char)), *isIdentifier = calloc(get_Bytes, sizeof(char));
        if(read(pc_sr->pFlDsc[0], thisProduce, get_Bytes) == -1){
            fprintf(stderr, "%s", strerror(errno));
            exit(EXIT_FAILURE);
        }
        isIdentifier[0] = thisProduce[strlen(thisProduce) - 1];
        for(int thisProducer = 0; thisProducer < pc_sr->noProducer; thisProducer++){
            //For now the identifier product type can only be a single character
            if(pc_sr->produceType[thisProducer] == atoi(isIdentifier)){
                thisProduce[strlen(thisProduce) - 1] = '\0';
                pthread_mutex_lock(&getSync[thisProducer].getLock);
                while(getSync[thisProducer].countQueue == queueSize[thisProducer] - 1){
                    pthread_cond_wait(&getSync[thisProducer].isEmpty, &getSync[thisProducer].getLock);
                }
                getSync[thisProducer].productQueue[getSync[thisProducer].countQueue] = (*thisProduce == '-') ? -1 : atoi(thisProduce);
                getSync[thisProducer].countQueue++;
                pthread_cond_broadcast(&getSync[thisProducer].isFull);
                pthread_mutex_unlock(&getSync[thisProducer].getLock);
            }
        }
        //printf("Parent : %d\n", pc_sr->exitThread);
    }
    wait(NULL);
    free(noConsumer);
    noConsumer = NULL;
    free(queueSize);
    queueSize = NULL;
    free(pc_sr->produceType);
    pc_sr->produceType = NULL;
    free(pc_sr->getProducts);
    pc_sr->getProducts = NULL;
    pthread_mutexattr_destroy(&mutexLock);
    pthread_condattr_destroy(&mutexFull);
    pthread_condattr_destroy(&mutexEmpty);
    for(int thisProducer = 0; thisProducer < noProducer; thisProducer++){
        pthread_mutex_destroy(&getSync[thisProducer].getLock);
        pthread_cond_destroy(&getSync[thisProducer].isFull);
        pthread_cond_destroy(&getSync[thisProducer].isEmpty);
        free(getSync[thisProducer].productQueue);
    }
    if(munmap(pc_sr->isSync, sizeof(synchronization) * noProducer) == -1){fprintf(stderr, "%s\n", strerror(errno)); exit(EXIT_FAILURE);}
    if(munmap(pc_sr, sizeof(shared_resources)) == -1){fprintf(stderr, "%s\n", strerror(errno)); exit(EXIT_FAILURE);}
    return 0;
}

void build_Producer(shared_resources *pc_sr, int isProducer, int productType){
    int countProduce = 1;
    while(1){
        if(countProduce > pc_sr->getProducts[isProducer]){
            char *endProduce = calloc(get_Bytes, sizeof(char));
            sprintf(endProduce, "%d%d", -1, productType);
            if((write(pc_sr->pFlDsc[1], endProduce, get_Bytes)) == -1){fprintf(stderr, "%s", strerror(errno)); return;}
            pc_sr->currentProducers--;
            if(pc_sr->currentProducers == 0){close(pc_sr->pFlDsc[1]);}
            sleep(0.5);
            break;
        }
        char *writeProduce = calloc(get_Bytes, sizeof(char));
        sprintf(writeProduce, "%d%d", countProduce, productType);
        if((write(pc_sr->pFlDsc[1], writeProduce, get_Bytes)) == -1){fprintf(stderr, "%s", strerror(errno)); break;}
        float getSleep = (float)rand()/(float)(RAND_MAX) *(0.2 - 0.01) + 0.01;
        getSleep *= 1000000;
        usleep(getSleep);
        countProduce++;
    }
    return;
}

void *build_Consumer(void *thread_Args){
    shared_resources *pc_sr = (shared_resources *)thread_Args;
    int get_Dequeue, consumeProduce = pc_sr->threadID, getType = pc_sr->produceType[consumeProduce];
    while(1){
        if(pc_sr->isSync[consumeProduce].endConsume){
            break;
        }
        pthread_mutex_lock(&pc_sr->isSync[consumeProduce].getLock);
        while(pc_sr->isSync[consumeProduce].countQueue == 0){
            pthread_cond_wait(&pc_sr->isSync[consumeProduce].isFull, &pc_sr->isSync[consumeProduce].getLock);
        }
        get_Dequeue = pc_sr->isSync[consumeProduce].productQueue[0];
        //printf("Type: %d Dequeue: %d\n", getType, get_Dequeue);
        if(get_Dequeue == -1){
            pc_sr->isSync[consumeProduce].endConsume = true;
            pc_sr->exitThread++;
            //printf("Current Consumers: %d\n", pc_sr->exitThread);
            break;
        }
        pc_sr->logCount++;
        pc_sr->isSync[consumeProduce].countQueue--;
        fprintf(pc_sr->getFile, "Type: %d\tThread Id: %ld\tProduction No: %d\tConsumption No: %d\n", getType, pthread_self(), get_Dequeue, pc_sr->logCount);
        pthread_cond_signal(&pc_sr->isSync[consumeProduce].isEmpty);
        pthread_mutex_unlock(&pc_sr->isSync[consumeProduce].getLock);
        sleep(0.5);
    }
    pthread_exit(0);
}