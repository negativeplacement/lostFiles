#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <netinet/in.h>
#include <netinet/ip6.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

typedef struct critical_section{
    pthread_mutex_t getLock;
    pthread_cond_t isFull, isEmpty;
	int *productQueue, queueSize, indexQueue;
    bool endConsume;
}synchronization;

typedef struct producer_consumer{
    int *clientSockets, *produceType, noClients, productTypeCount, clientProductIndex, hasProductIndex, isFileDescriptor, *clientConsumers, activeHandlers;
	size_t logCount;
    synchronization **isSync;
}shared_resources;

shared_resources *init_sr();
void *connect_client(void *thread_Args);
void *client_consumer(void *thread_Args);

int main(int argc, char *argv[]){
	shared_resources *pc_sr = init_sr();
	synchronization **getSync = pc_sr->isSync;
	uint16_t isPort;
	int getClients, isExecute;
	fprintf(stdout, "Enter the hosting server port number: ");
    scanf("%" SCNu16, &isPort);
	fprintf(stdout, "How many connecting client(s): ");
	scanf("%d", &getClients);
	struct sockaddr_in isServer;
    int socketFd = socket(AF_INET, SOCK_STREAM, 0), isBind, isListen, clientSocket;
    if(socketFd == -1){
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    isServer.sin_family = AF_INET;
    isServer.sin_port = htons(isPort);
    isServer.sin_addr.s_addr = INADDR_ANY;
	isBind = bind(socketFd, (struct sockaddr *)&isServer, sizeof(isServer));
	if(isBind == -1){
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
	isListen = listen(socketFd, 16);
	if(isListen == -1){
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
	ssize_t sendSocket, recvSocket, socketSize = sizeof(struct sockaddr_in);
	long spawnThreads = 0, isThread = 0;
	char *getResponse = calloc(64, sizeof(char)), *endDigitPtr;
	if(getResponse == NULL){
		fprintf(stderr, "Memory Allocation Failed\n");
		exit(EXIT_FAILURE);
	}
	pthread_t *isClient = calloc(spawnThreads + 1, sizeof(pthread_t));
	if(isClient == NULL){
		fprintf(stderr, "Memory Allocation Failed\n");
		exit(EXIT_FAILURE);
	}
	while((clientSocket = accept(socketFd, (struct sockaddr *)&isServer, (socklen_t *)&(socketSize))) != -1){
		size_t *produceConsumers, indexConsumer, tokenCount;
		long spawnConsumers, aggregateConsumer;
		bool isMultipleProduce = false, isError = false;
		sendSocket = send(clientSocket, "Enter The Number Of Consumer(s): ", 34, 0);
		if(sendSocket == -1){
            fprintf(stderr, "%s\n", strerror(errno));
            return 0;
        }
		recvSocket = recv(clientSocket, getResponse, sizeof(char)*64, 0);
		if(recvSocket == -1){
			fprintf(stderr, "%s\n", strerror(errno));
            return 0;
		}
		if(strchr(getResponse, ',')){
			isMultipleProduce = true;
			produceConsumers = calloc(1, sizeof(size_t));
			if(produceConsumers == NULL){
				fprintf(stderr, "Memory Allocation Failed\n");
				exit(EXIT_FAILURE);
			}
			for(char *isToken = strtok(getResponse,","); isToken != NULL; tokenCount++, isToken = strtok(NULL, ",")){
				if(strspn(isToken, " 0123456789") == strlen(isToken)){
					spawnConsumers = strtol(isToken, &endDigitPtr, 10);
					spawnThreads += spawnConsumers;
					produceConsumers[indexConsumer++] = spawnConsumers;
					size_t *extendProduceConsumers = realloc(produceConsumers, sizeof(int) * (indexConsumer + 1));
					if(extendProduceConsumers == NULL){
						fprintf(stderr, "Memory Allocation Failed\n");
						exit(EXIT_FAILURE);
					}
					produceConsumers = extendProduceConsumers;
					aggregateConsumer += spawnConsumers;
				} else{
					sendSocket = send(clientSocket, "Invalid Response", 17, 0);
					if(sendSocket == -1){
						fprintf(stderr, "%s\n", strerror(errno));
						return 0;
					}
					free(produceConsumers);
					produceConsumers = NULL;
					isError = true;
					isMultipleProduce = false;
					break;
				}
			}
			if(isError){
				continue;
			}
			spawnConsumers++;
		} else{
			if(strspn(getResponse, " 0123456789") == strlen(getResponse)){
				spawnConsumers = strtol(getResponse, &endDigitPtr, 10);
				spawnConsumers++;
				spawnThreads += spawnConsumers;
			} else{
				sendSocket = send(clientSocket, "Invalid Response", 17, 0);
				if(sendSocket == -1){
					fprintf(stderr, "%s\n", strerror(errno));
					return 0;
				}
				continue;
			}
		}
		memset(getResponse, '\0', sizeof(char)*64);
		sendSocket = send(clientSocket, "Enter Queue Size(s): ", 22, 0);
		if(sendSocket == -1){ 
            fprintf(stderr, "%s\n", strerror(errno));
            return 0;
        }
		recvSocket = recv(clientSocket, getResponse, sizeof(char)*64, 0);
		if(recvSocket == -1){
			fprintf(stderr, "%s\n", strerror(errno));
            return 0;
		}
		if(isMultipleProduce && strchr(getResponse, ',') == NULL){
			sendSocket = send(clientSocket, "Queue Sizes Do Not Correspond With The No Of Producers", 55, 0);
				if(sendSocket == -1){
					fprintf(stderr, "%s\n", strerror(errno));
					return 0;
				}
				continue;
		} else if(isMultipleProduce && strchr(getResponse, ',')){
			tokenCount = 0;
			for(char *isToken = strtok(getResponse,","); isToken != NULL; tokenCount++, isToken = strtok(NULL, ",")){
				if(strspn(isToken, " 0123456789") == strlen(isToken)){
					getSync[pc_sr->productTypeCount] = calloc(1, sizeof(synchronization));
					if(getSync[pc_sr->productTypeCount] == NULL){
						fprintf(stderr, "Memory Allocation Failed\n");
						exit(EXIT_FAILURE);
					}
					isExecute = pthread_mutex_init(&getSync[pc_sr->productTypeCount]->getLock, NULL);
					if(isExecute != 0){
						fprintf(stderr, "%s\n", strerror(isExecute));
						return 0;
					}
					isExecute = pthread_cond_init(&getSync[pc_sr->productTypeCount]->isFull, NULL);
					if(isExecute != 0){
						fprintf(stderr, "%s\n", strerror(isExecute));
						return 0;
					}
					isExecute = pthread_cond_init(&getSync[pc_sr->productTypeCount]->isEmpty, NULL);
					if(isExecute != 0){
						fprintf(stderr, "%s\n", strerror(isExecute));
						return 0;
					}
					getSync[pc_sr->productTypeCount]->queueSize = strtol(isToken, &endDigitPtr, 10);
					getSync[pc_sr->productTypeCount]->productQueue = calloc(getSync[pc_sr->productTypeCount]->queueSize, sizeof(int));
					if(getSync[pc_sr->productTypeCount]->productQueue == NULL){
						fprintf(stderr, "Memory Allocation Failed\n");
						exit(EXIT_FAILURE);
					}
					getSync[pc_sr->productTypeCount]->indexQueue = 0;
					getSync[pc_sr->productTypeCount++]->endConsume = false;
					synchronization **resizeSync = realloc(getSync, sizeof(synchronization *) * (pc_sr->productTypeCount + 1));
					if(resizeSync == NULL){
						fprintf(stderr, "Memory Allocation Failed\n");
						exit(EXIT_FAILURE);
					}
					getSync = resizeSync;
				} else{
					sendSocket = send(clientSocket, "Invalid Response", 17, 0);
					if(sendSocket == -1){
						fprintf(stderr, "%s\n", strerror(errno));
						return 0;
					}
					pc_sr->productTypeCount -= tokenCount;
					memset((getSync + pc_sr->productTypeCount), 0, sizeof(synchronization *) * tokenCount); // null out the entered memory
					isError = true;
					break;
				}
			}
			if(isError){
				continue;
			}
		} else{
			if(strspn(getResponse, " 0123456789") == strlen(getResponse)){
				getSync[pc_sr->productTypeCount] = calloc(1, sizeof(synchronization));
				if(getSync[pc_sr->productTypeCount] == NULL){
					fprintf(stderr, "Memory Allocation Failed\n");
					exit(EXIT_FAILURE);
				}
				isExecute = pthread_mutex_init(&getSync[pc_sr->productTypeCount]->getLock, NULL);
				if(isExecute != 0){
					fprintf(stderr, "%s\n", strerror(isExecute));
					return 0;
				}
				isExecute = pthread_cond_init(&getSync[pc_sr->productTypeCount]->isFull, NULL);
				if(isExecute != 0){
					fprintf(stderr, "%s\n", strerror(isExecute));
					return 0;
				}
				isExecute = pthread_cond_init(&getSync[pc_sr->productTypeCount]->isEmpty, NULL);
				if(isExecute != 0){
					fprintf(stderr, "%s\n", strerror(isExecute));
					return 0;
				}
				getSync[pc_sr->productTypeCount]->queueSize = strtol(getResponse, &endDigitPtr, 10);
				getSync[pc_sr->productTypeCount]->productQueue = calloc(getSync[pc_sr->productTypeCount]->queueSize, sizeof(int));
				if(getSync[pc_sr->productTypeCount]->productQueue == NULL){
					fprintf(stderr, "Memory Allocation Failed\n");
					exit(EXIT_FAILURE);
				}
				getSync[pc_sr->productTypeCount]->indexQueue = 0;
				getSync[pc_sr->productTypeCount++]->endConsume = false;
				synchronization **resizeSync = realloc(getSync, sizeof(synchronization *) * (pc_sr->productTypeCount + 1));
				if(resizeSync == NULL){
					fprintf(stderr, "Memory Allocation Failed\n");
					exit(EXIT_FAILURE);
				}
				getSync = resizeSync;
			} else{
				sendSocket = send(clientSocket, "Invalid Response", 17, 0);
				if(sendSocket == -1){
					fprintf(stderr, "%s\n", strerror(errno));
					return 0;
				}
				continue;
			}
		}
		memset(getResponse, '\0', sizeof(char)*64);
		pthread_t *resizeClientThreads = realloc(isClient, sizeof(pthread_t) * (spawnThreads + 1));
		if(resizeClientThreads == NULL){
			fprintf(stderr, "Memory Allocation Failed\n");
			exit(EXIT_FAILURE);
		}
		isClient = resizeClientThreads;
		*(pc_sr->clientSockets + pc_sr->noClients) = clientSocket;
		*(pc_sr->clientConsumers + pc_sr->noClients) = (isMultipleProduce) ? aggregateConsumer : spawnConsumers - 1;
		if(isMultipleProduce){
			isExecute = pthread_create(&isClient[isThread++], NULL, connect_client, pc_sr);
			if(isExecute != 0){
				fprintf(stderr, "%s\n", strerror(isExecute));
				exit(EXIT_FAILURE);
			}
			sleep(1.5);
			for(int consumerCount = 0; consumerCount < indexConsumer; consumerCount++){
				for(int isConsumers = 0; isConsumers < produceConsumers[consumerCount]; isConsumers++){
					isExecute = pthread_create(&isClient[isThread++], NULL, client_consumer, pc_sr);
					if(isExecute != 0){
						fprintf(stderr, "%s\n", strerror(isExecute));
						exit(EXIT_FAILURE);
					}
					sleep(1.5);
				}
				pc_sr->hasProductIndex++;
			}
		} else{
			isExecute = pthread_create(&isClient[isThread++], NULL, connect_client, pc_sr);
			if(isExecute != 0){
				fprintf(stderr, "%s\n", strerror(isExecute));
				exit(EXIT_FAILURE);
			}
			sleep(1.5);
			for(int isConsumers = 0; isConsumers < spawnConsumers - 1; isConsumers++){
				isExecute = pthread_create(&isClient[isThread++], NULL, client_consumer, pc_sr);
				if(isExecute != 0){
					fprintf(stderr, "%s\n", strerror(isExecute));
					exit(EXIT_FAILURE);
				}
				sleep(1.5);
			}
			pc_sr->hasProductIndex++;
		}
		pc_sr->noClients++;
		pc_sr->activeHandlers++;
		pc_sr->clientProductIndex = pc_sr->productTypeCount;
		int *resizeClientSockets = realloc(pc_sr->clientSockets, sizeof(int) * (pc_sr->noClients + 1));
		if(resizeClientSockets == NULL){
			fprintf(stderr, "Memory Allocation Failed\n");
			exit(EXIT_FAILURE);
		}
		pc_sr->clientSockets = resizeClientSockets;
		int *resizeHandlerConsumer = realloc(pc_sr->clientConsumers, sizeof(int) * (pc_sr->noClients + 1));
		if(resizeHandlerConsumer == NULL){
			fprintf(stderr, "Memory Allocation Failed\n");
			exit(EXIT_FAILURE);
		}
		pc_sr->clientConsumers = resizeHandlerConsumer;
		if(isMultipleProduce){
			free(produceConsumers);
			produceConsumers = NULL;
		}
		if(pc_sr->noClients == getClients){
			break;
		}
	}
	if(clientSocket == -1){
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	while(1){
		if(pc_sr->activeHandlers == 0){
			break;
		}
	}
	for(int thisThread = 0; thisThread < isThread; thisThread++){
		isExecute = pthread_join(isClient[thisThread], NULL);
		if(isExecute != 0){
			fprintf(stderr, "%s\n", strerror(isExecute));
			exit(EXIT_FAILURE);
		}
	}
	if(close(socketFd) == -1){
		fprintf(stderr, "%s\n", strerror(isExecute));
		exit(EXIT_FAILURE);
	}
	if(close(pc_sr->isFileDescriptor) == -1){
		fprintf(stderr, "%s\n", strerror(isExecute));
		exit(EXIT_FAILURE);
	}
	free(getResponse);
	getResponse = NULL;
	free(isClient);
	isClient = NULL;
	free(pc_sr->clientSockets);
	pc_sr->clientSockets = NULL;
	free(pc_sr->produceType);
	pc_sr->produceType = NULL;
	free(pc_sr->clientConsumers);
	pc_sr->clientConsumers = NULL;
	free(pc_sr->isSync);
	pc_sr->isSync = NULL;
	free(pc_sr);
	pc_sr = NULL;
	return 0;
}

shared_resources *init_sr(){
    shared_resources *pc_sr = calloc(1, sizeof(shared_resources));
    if(pc_sr == NULL){
        fprintf(stderr, "Memory Allocation Failed\n");
        exit(EXIT_FAILURE);
    }
	pc_sr->clientSockets = calloc(1, sizeof(int));
	if(pc_sr->clientSockets == NULL){
		fprintf(stderr, "Memory Allocation Failed\n");
        exit(EXIT_FAILURE);
	}
	pc_sr->produceType = calloc(1, sizeof(int));
    if(pc_sr->produceType == NULL){
        fprintf(stderr, "Memory Allocation Failed\n");
        exit(EXIT_FAILURE);
    }
	pc_sr->clientConsumers = calloc(1, sizeof(int));
	if(pc_sr->clientConsumers == NULL){
		fprintf(stderr, "Memory Allocation Failed\n");
		exit(EXIT_FAILURE);
	}
	pc_sr->isFileDescriptor = open("File Report.log", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if(pc_sr->isFileDescriptor == -1){
        fprintf(stderr, "%s", strerror(errno));
        exit(EXIT_FAILURE);
    }
	pc_sr->isSync = calloc(1, sizeof(synchronization *));
    if(pc_sr->isSync == NULL){
        fprintf(stderr, "Memory Allocation Failed\n");
        exit(EXIT_FAILURE);
    }
    return pc_sr;
}

void *connect_client(void *thread_Args){
    shared_resources *pc_sr = (shared_resources*)thread_Args;
    int isSocket = *(pc_sr->clientSockets + pc_sr->noClients), clientProductIndex = pc_sr->clientProductIndex, clientProductCount = pc_sr->productTypeCount, isProducts, isExecute, isClient = pc_sr->noClients;
	ssize_t recvSocket;
	int *resizeProductType = realloc(pc_sr->produceType, sizeof(int) * (pc_sr->productTypeCount + 1));
	if(resizeProductType == NULL){
		fprintf(stderr, "Memory Allocation Failed\n");
        exit(EXIT_FAILURE);
	}
	pc_sr->produceType = resizeProductType;
	memset((pc_sr->produceType + clientProductIndex), 0, sizeof(int) * (pc_sr->productTypeCount - clientProductIndex + 1));
    char *clientMessage = calloc(16, sizeof(char)), *isIdentifier = calloc(5, sizeof(char)), *endDigitPtr;
	if(clientMessage == NULL){
		fprintf(stderr, "Memory Allocation Failed\n");
		exit(EXIT_FAILURE);
	}
	while((recvSocket = recv(isSocket , clientMessage , 16 , 0)) > 0){
		*isIdentifier = clientMessage[strlen(clientMessage) - 1];
		for(int thisProducer = clientProductIndex; thisProducer < clientProductCount; thisProducer++){
			if(pc_sr->produceType[thisProducer] == 0){
				clientMessage[strlen(clientMessage) - 1] = '\0';
				pc_sr->produceType[thisProducer] = strtol(isIdentifier, &endDigitPtr, 10);
                isExecute = pthread_mutex_lock(&pc_sr->isSync[thisProducer]->getLock);
				if(isExecute != 0){
					fprintf(stderr, "%s\n", strerror(isExecute));
					exit(EXIT_FAILURE);
				}
                while(pc_sr->isSync[thisProducer]->indexQueue == pc_sr->isSync[thisProducer]->queueSize - 1){
                    isExecute = pthread_cond_wait(&pc_sr->isSync[thisProducer]->isEmpty, &pc_sr->isSync[thisProducer]->getLock);
					if(isExecute != 0){
						fprintf(stderr, "%s\n", strerror(isExecute));
						exit(EXIT_FAILURE);
					}
                }
                pc_sr->isSync[thisProducer]->productQueue[pc_sr->isSync[thisProducer]->indexQueue++] = (*clientMessage == '-') ? -1 : strtol(clientMessage, &endDigitPtr, 10);
				(*clientMessage == '-') && (pc_sr->isSync[thisProducer]->endConsume = false);
                isExecute = pthread_cond_broadcast(&pc_sr->isSync[thisProducer]->isFull);
				if(isExecute != 0){
					fprintf(stderr, "%s\n", strerror(isExecute));
					exit(EXIT_FAILURE);
				}
                isExecute = pthread_mutex_unlock(&pc_sr->isSync[thisProducer]->getLock);
				if(isExecute != 0){
					fprintf(stderr, "%s\n", strerror(isExecute));
					exit(EXIT_FAILURE);
				}
				break;
			} else if(pc_sr->produceType[thisProducer] == strtol(isIdentifier, &endDigitPtr, 10)){
                clientMessage[strlen(clientMessage) - 1] = '\0';
                isExecute = pthread_mutex_lock(&pc_sr->isSync[thisProducer]->getLock);
				if(isExecute != 0){
					fprintf(stderr, "%s\n", strerror(isExecute));
					exit(EXIT_FAILURE);
				}
                while(pc_sr->isSync[thisProducer]->indexQueue == pc_sr->isSync[thisProducer]->queueSize - 1){
                    isExecute = pthread_cond_wait(&pc_sr->isSync[thisProducer]->isEmpty, &pc_sr->isSync[thisProducer]->getLock);
					if(isExecute != 0){
						fprintf(stderr, "%s\n", strerror(isExecute));
						exit(EXIT_FAILURE);
					}
                }
                pc_sr->isSync[thisProducer]->productQueue[pc_sr->isSync[thisProducer]->indexQueue++] = (*clientMessage == '-') ? -1 : strtol(clientMessage, &endDigitPtr, 10);
				(*clientMessage == '-') && (pc_sr->isSync[thisProducer]->endConsume = false);
                isExecute = pthread_cond_broadcast(&pc_sr->isSync[thisProducer]->isFull);
				if(isExecute != 0){
					fprintf(stderr, "%s\n", strerror(isExecute));
					exit(EXIT_FAILURE);
				}
                isExecute = pthread_mutex_unlock(&pc_sr->isSync[thisProducer]->getLock);
				if(isExecute != 0){
					fprintf(stderr, "%s\n", strerror(isExecute));
					exit(EXIT_FAILURE);
				}
				break;
            }
		}
		(*clientMessage == '-') && (isProducts++);
		if(isProducts == clientProductCount - clientProductIndex){
			break;
		}
	}
	if(recvSocket == -1){
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	while(1){
		if(pc_sr->clientConsumers[isClient] == 0){
			break;
		}
	}
	for(int thisProducer = clientProductIndex; thisProducer < clientProductCount; thisProducer++){
		isExecute = pthread_mutex_destroy(&pc_sr->isSync[thisProducer]->getLock); // Error attempts to uninitialize a lock that a thread is attemptin to acquire
		if(isExecute != 0){
			fprintf(stderr, "%s\n", strerror(isExecute));
			exit(EXIT_FAILURE);
		}
		isExecute = pthread_cond_destroy(&pc_sr->isSync[thisProducer]->isFull);
		if(isExecute != 0){
			fprintf(stderr, "%s\n", strerror(isExecute));
			exit(EXIT_FAILURE);
		}
		isExecute = pthread_cond_destroy(&pc_sr->isSync[thisProducer]->isEmpty);
		if(isExecute != 0){
			fprintf(stderr, "%s\n", strerror(isExecute));
			exit(EXIT_FAILURE);
		}
		free(pc_sr->isSync[thisProducer]->productQueue);
		pc_sr->isSync[thisProducer]->productQueue = NULL;
		free(pc_sr->isSync[thisProducer]);
		pc_sr->isSync[thisProducer] = NULL;
	}
	pc_sr->activeHandlers--;
    pthread_exit(0);
}

void *client_consumer(void *thread_Args){
	shared_resources *pc_sr = (shared_resources*)thread_Args;
	int isExecute, logMessageSize, setLogMessage, bytesWritten;
    int get_Dequeue, consumeProduce = pc_sr->hasProductIndex, hasClientHandler = pc_sr->noClients;
    while(1){
        if(pc_sr->isSync[consumeProduce]->endConsume){
            break;
        }
		isExecute = pthread_mutex_lock(&pc_sr->isSync[consumeProduce]->getLock);
        if(isExecute != 0){
			fprintf(stderr, "%s\n", strerror(isExecute));
			exit(EXIT_FAILURE);
		}
        while(pc_sr->isSync[consumeProduce]->indexQueue == 0){
            isExecute = pthread_cond_wait(&pc_sr->isSync[consumeProduce]->isFull, &pc_sr->isSync[consumeProduce]->getLock);
			if(isExecute != 0){
				fprintf(stderr, "%s\n", strerror(isExecute));
				exit(EXIT_FAILURE);
			}
        }
        get_Dequeue = pc_sr->isSync[consumeProduce]->productQueue[0];
        printf("Type: %d Dequeue: %d\n", pc_sr->produceType[consumeProduce], get_Dequeue);
        if(get_Dequeue == -1){
            pc_sr->isSync[consumeProduce]->endConsume = true;
			pc_sr->clientConsumers[hasClientHandler]--;
			isExecute = pthread_mutex_unlock(&pc_sr->isSync[consumeProduce]->getLock);
			if(isExecute != 0){
				fprintf(stderr, "%s\n", strerror(isExecute));
				exit(EXIT_FAILURE);
			}
            break;
        }
        pc_sr->logCount++;
        pc_sr->isSync[consumeProduce]->indexQueue--;
		logMessageSize = snprintf(NULL, 0, "Type: %d\tThread Id: %ld\tProduction No: %d\tConsumption No: %d\n", pc_sr->produceType[consumeProduce], pthread_self(), get_Dequeue, pc_sr->logCount);
		if(logMessageSize < 0){
			fprintf(stderr, "%s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		char *logMessage = calloc(logMessageSize + 1, sizeof(char));
		if(logMessage == NULL){
			fprintf(stderr, "Memory Allocation Failed\n");
			exit(EXIT_FAILURE);
		}
		setLogMessage = snprintf(logMessage, logMessageSize, "Type: %d\tThread Id: %ld\tProduction No: %d\tConsumption No: %d\n", pc_sr->produceType[consumeProduce], pthread_self(), get_Dequeue, pc_sr->logCount);
		if(setLogMessage < 0){
			fprintf(stderr, "%s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		bytesWritten = write(pc_sr->isFileDescriptor, logMessage, strlen(logMessage) + 1);
		if(bytesWritten == -1){
			fprintf(stderr, "%s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
        isExecute = pthread_cond_signal(&pc_sr->isSync[consumeProduce]->isEmpty);
		if(isExecute != 0){
			fprintf(stderr, "%s\n", strerror(isExecute));
			exit(EXIT_FAILURE);
		}
        isExecute = pthread_mutex_unlock(&pc_sr->isSync[consumeProduce]->getLock);
		if(isExecute != 0){
			fprintf(stderr, "%s\n", strerror(isExecute));
			exit(EXIT_FAILURE);
		}
        sleep(0.5);
    }
    pthread_exit(0);
}