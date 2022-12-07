#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<stdio.h>
#include"../headers/semative.h"


int* mutexReader;
int* mutexWriter;
int* z;// Pour être sure que les writer aient tjrs la prioritée
int* mutexReadCount;

custom_sema_t dbReader; // accès à la db
custom_sema_t dbWriter; // accès à la db

int writerCount = 0;
int readCount=0; // nombre de readers
int reading = 0;
int writing = 0;

void write_database(){
    for (int i=0; i<10000; i++);
}
void read_database(){
    for (int i=0; i<10000; i++);
}

//implement writer from reader writer problem
void* writer(){
    int run = 1;
    while(run){
        lock(mutexWriter);
        writerCount ++;
        if(writerCount == 1)wait(&dbReader);
        unlock(mutexWriter);
        wait(&dbWriter);
        // section critique, un seul writer à la fois
        if(writing < 2560){
            writing ++;
            write_database();
        }else{run = 0;}

        post(&dbWriter);
        lock(mutexWriter);
        writerCount --;
        if(writerCount == 0)post(&dbReader);
        unlock(mutexWriter);
    }
}

void* reader(){
    int run = 1;
    while(run){
        lock(z);
        wait(&dbReader);
        lock(mutexReader);
        // section critique
        readCount++;
        if (readCount==1){ 
            wait(&dbWriter); // arrivée du premier reader
        }
        unlock(mutexReader);
        post(&dbReader);
        unlock(z);
        lock(mutexReadCount);
        if(reading < 2560){
            reading ++;
            unlock(mutexReadCount);
            read_database();
            lock(mutexReader);
            readCount--;
            if(readCount==0){
                post(&dbWriter); // départ du dernier reader
            }
        }
        else{
            lock(mutexReader);
            readCount--;
            if(readCount==0){ 
                post(&dbWriter);// départ du dernier reader
            }
            run = 0;
            unlock(mutexReadCount);
        }
        unlock(mutexReader);
    }
}

int main(int argc, char const *argv[]){
    int nreader;
    int nwriter;

    sscanf(argv[2], "%d", &nreader);
    sscanf(argv[1], "%d", &nwriter);

    init(&dbReader,1);
    init(&dbWriter,1);

    mutexReader = malloc(sizeof(int));
    mutexWriter = malloc(sizeof(int));
    z = malloc(sizeof(int));
    mutexReadCount = malloc(sizeof(int));
    *mutexReader = 0;
    *mutexWriter = 0;
    *z = 0;
    *mutexReadCount = 0;

    pthread_t ReadThreads[nreader];
    pthread_t WriteThreads[nwriter];

    for (size_t i = 0; i < nwriter; i++){
        if(pthread_create(&WriteThreads[i],NULL,&writer,NULL) != 0)return 1;
    }
    for (size_t i = 0; i < nreader; i++){
        if(pthread_create(&ReadThreads[i],NULL,&reader,NULL)!=0)return 1;
    }
    for (size_t i = 0; i < nwriter; i++){
        if(pthread_join(WriteThreads[i],NULL)!= 0)return 1;
    }
    for (size_t i = 0; i < nreader; i++){
        if(pthread_join(ReadThreads[i],NULL) != 0)return 1;
    }
    free(mutexReader);
    free(mutexWriter);
    free(z);
    free(mutexReadCount);
    destroy(&dbReader);
    destroy(&dbWriter);

    return 0;
}