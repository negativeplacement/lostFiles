#include <arpa/inet.h>
#include <errno.h>
#include <inttypes.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

typedef struct producer_consumer{
    int socketFd, *produceType, *getProducts, isProducer;
}shared_resources;

shared_resources *init_pc_sr(int noProducer);
void isTerminal(char *isArg[]);
void isManual();
void *build_Producer(void *thread_arg);

// Arg 1: portNo, Arg 2: produceCount, Arg 3: productType, Arg 4: noConsumer, Arg 5: queueSize
int main(int argc, char *argv[]){
    srand(time(NULL));
    if(argc == 6){
        isTerminal(argv);
    } else{
        isManual();
    }
    return 0;
}

shared_resources *init_pc_sr(int noProducer){
    shared_resources *pc_sr = calloc(1, sizeof(shared_resources));
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
    return pc_sr;
}

void isTerminal(char *isArg[]){
    struct sockaddr_in isClient;
    char *serverMessage = calloc(64, sizeof(char)), *isResponse = calloc(64, sizeof(char)), *endDigitPtr;
    long serverPortNo = strtol(isArg[1], &endDigitPtr, 10), getProduct = strtol(isArg[2], &endDigitPtr, 10), productType = strtol(isArg[3], &endDigitPtr, 10), noConsumers = strtol(isArg[4], &endDigitPtr, 10),
    queueSize = strtol(isArg[5], &endDigitPtr, 10);
    int socketFd = socket(AF_INET, SOCK_STREAM, 0), connectFileDescriptor, sendSocket, recvSocket, responseBytes, produceCount = 1, sendBytes;
    if(socketFd == -1){
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    isClient.sin_family = AF_INET;
    isClient.sin_port = htons((uint16_t)serverPortNo);
    isClient.sin_addr.s_addr = inet_addr("127.0.0.1");
    connectFileDescriptor = connect(socketFd, (struct sockaddr *)&isClient, sizeof(isClient));
    if(connectFileDescriptor == -1){
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    recvSocket = recv(socketFd, serverMessage, 64, 0);
    if(recvSocket == -1){
        fprintf(stderr, "%s\n", strerror(errno));
        return;
	}
    responseBytes = snprintf(isResponse, 64, "%ld", noConsumers);
    if(responseBytes < 0){
        fprintf(stderr, "%s\n", strerror(errno));
        return;
    }
    sendSocket = send(socketFd, isResponse, responseBytes + 1, 0);
    if(sendSocket == -1){
        fprintf(stderr, "%s\n", strerror(errno));
        return;
    }
    memset(serverMessage, '\0', sizeof(char)*64);
    memset(isResponse, '\0', sizeof(char)*64);
    recvSocket = recv(socketFd, serverMessage, 64, 0);
    if(recvSocket == -1){
        fprintf(stderr, "%s\n", strerror(errno));
        return;
	}
    responseBytes = snprintf(isResponse, 64, "%ld", queueSize);
    if(responseBytes < 0){
        fprintf(stderr, "%s\n", strerror(errno));
        return;
    }
    sendSocket = send(socketFd, isResponse, responseBytes + 1, 0);
    if(sendSocket == -1){
        fprintf(stderr, "%s\n", strerror(errno));
        return;
    }
    sleep(1.5);
    while(1){
        if(produceCount > getProduct){
            char *endProduce = calloc(16, sizeof(char));
            sendBytes = snprintf(endProduce, 16, "%d%d", -1, productType);
            if(sendBytes < 0){
                fprintf(stderr, "%s", strerror(errno));
                return;
            }
            sendSocket = send(socketFd, endProduce, 16, 0);
            if(sendSocket == -1){
                fprintf(stderr, "%s", strerror(errno));
                return;
            }
            break;
        }
        char *writeProduce = calloc(16, sizeof(char));
        sendBytes = snprintf(writeProduce, 16, "%d%d", produceCount, productType);
        if(sendBytes < 0){
            fprintf(stderr, "%s", strerror(errno));
            return;
        }
        sendSocket = send(socketFd, writeProduce, 16, 0);
        if(sendSocket == -1){
            fprintf(stderr, "%s", strerror(errno));
            return;
        }
        float getSleep = (float)rand()/(float)(RAND_MAX) *(0.2 - 0.01) + 0.01;
        getSleep *= 1000000;
        usleep(getSleep);
        produceCount++;
    }
    close(socketFd);
    return;
}

void isManual(){
    struct sockaddr_in isClient;
    uint16_t serverPortNo;
    int connectFileDescriptor, sendSocket, recvSocket, noProducer, isExecute;
    fprintf(stdout, "Enter the server port number: ");
    scanf("%" SCNu16, &serverPortNo);
    fprintf(stdout, "Enter the number of producer(s): ");
    scanf("%d", &noProducer);
    shared_resources *pc_sr = init_pc_sr(noProducer);
    pthread_t *buildThread = calloc(noProducer, sizeof(pthread_t));
    if(buildThread == NULL){
        fprintf(stderr, "Memory Allocation Failed\n");
        exit(EXIT_FAILURE);
    }
    pc_sr->socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if(pc_sr->socketFd == -1){
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    isClient.sin_family = AF_INET;
    isClient.sin_port = htons(serverPortNo);
    isClient.sin_addr.s_addr = inet_addr("127.0.0.1");
    connectFileDescriptor = connect(pc_sr->socketFd, (struct sockaddr *)&isClient, sizeof(isClient));
    if(connectFileDescriptor == -1){
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    char *serverMessage = calloc(64, sizeof(char));
    char *consumerNoResponse = calloc(64, sizeof(char)), *consumerNoPtr;
    char *queueSizeResponse = calloc(64, sizeof(char)), * queueSizePtr;
    recvSocket = recv(pc_sr->socketFd, serverMessage, 64, 0);
    if(recvSocket == -1){
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
	}
    fprintf(stdout, "%s", serverMessage);
    scanf("%s", consumerNoResponse);
    sendSocket = send(pc_sr->socketFd, consumerNoResponse, strlen(consumerNoResponse) + 1, 0);
    if(sendSocket == -1){
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    memset(serverMessage, '\0', sizeof(char)*64);
    recvSocket = recv(pc_sr->socketFd, serverMessage, 64, 0);
    if(recvSocket == -1){
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
	}
    fprintf(stdout, "%s", serverMessage);
    scanf(" %s", queueSizeResponse);
    sendSocket = send(pc_sr->socketFd, queueSizeResponse, strlen(queueSizeResponse) + 1, 0);
    if(sendSocket == -1){
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    memset(serverMessage, '\0', sizeof(char)*64);
    for(int thisProducer = 0; thisProducer < noProducer; thisProducer++){
        pc_sr->isProducer = thisProducer;
        fprintf(stdout, "\nEnter the number of products for producer %d: ", (thisProducer + 1));
        scanf("%d", &pc_sr->getProducts[thisProducer]);
        fprintf(stdout, "Enter the produce type for producer %d: ", (thisProducer + 1));
        scanf("%d", &pc_sr->produceType[thisProducer]);
        fprintf(stdout, "Consumer(s) for producer %d: %s\n", (thisProducer + 1), (thisProducer) ? __strtok_r(NULL, ",", &consumerNoPtr) : __strtok_r(consumerNoResponse, ",", &consumerNoPtr));
        fprintf(stdout, "Queue size for producer %d: %s\n", (thisProducer + 1), (thisProducer) ? __strtok_r(NULL, ",", &queueSizePtr) : __strtok_r(queueSizeResponse, ",", &queueSizePtr));
        isExecute = pthread_create(&buildThread[thisProducer], NULL, build_Producer, pc_sr);
        if(isExecute != 0){
            fprintf(stderr, "%s\n", strerror(isExecute));
            exit(EXIT_FAILURE);
        }
        sleep(1);
    }
    for(int isProducer = 0; isProducer < noProducer; isProducer++){
        isExecute = pthread_join(buildThread[isProducer], NULL);
        if(isExecute != 0){
            fprintf(stderr, "%s\n", strerror(exitThreads));
            exit(EXIT_FAILURE);
        }
    }
    close(pc_sr->socketFd);
    free(buildThread);
    buildThread = NULL;
    free(pc_sr->getProducts);
    pc_sr->getProducts = NULL;
    free(pc_sr->produceType);
    pc_sr->produceType = NULL;
    free(pc_sr);
    pc_sr = NULL;
    return;
}

void *build_Producer(void *thread_arg){
    shared_resources *pc_sr = (shared_resources *)thread_arg;
    int produceCount = 1, isProducer = pc_sr->isProducer, productType = pc_sr->produceType[isProducer], sendSocket, sendBytes;
    while(1){
        if(produceCount > pc_sr->getProducts[isProducer]){
            char *endProduce = calloc(16, sizeof(char));
            sendBytes = sprintf(endProduce, "%d%d", -1, productType);
            if(sendBytes < 0){
                fprintf(stderr, "%s", strerror(errno));
                exit(EXIT_FAILURE);
            }
            sendSocket = send(pc_sr->socketFd, endProduce, 16, 0);
            if(sendSocket == -1){
                fprintf(stderr, "%s", strerror(errno));
                exit(EXIT_FAILURE);
            }
            break;
        }
        char *writeProduce = calloc(16, sizeof(char));
        sendBytes = snprintf(writeProduce, 16, "%d%d", produceCount, productType);
        if(sendBytes < 0){
            fprintf(stderr, "%s", strerror(errno));
            exit(EXIT_FAILURE);
        }
        sendSocket = send(pc_sr->socketFd, writeProduce, 16, 0);
        if(sendSocket == -1){
            fprintf(stderr, "%s", strerror(errno));
            exit(EXIT_FAILURE);
        }
        float getSleep = (float)rand()/(float)(RAND_MAX) *(0.2 - 0.01) + 0.01;
        getSleep *= 1000000;
        usleep(getSleep);
        produceCount++;
        sleep(0.25);
    }
    pthread_exit(0);
}