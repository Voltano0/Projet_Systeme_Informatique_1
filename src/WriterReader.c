#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<stdio.h>


pthread_mutex_t mutexReader;
pthread_mutex_t mutexWriter;
pthread_mutex_t mutexReadCount;
pthread_mutex_t z;// Pour être sure que les writer aient tjrs la prioritée

sem_t dbReader; // accès à la db
sem_t dbWriter; // accès à la db

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

void* writer(){
    int run = 1;
    while(run){
        pthread_mutex_lock(&mutexWriter);
        writerCount ++;
        if(writerCount == 1)sem_wait(&dbReader);
        pthread_mutex_unlock(&mutexWriter);
        sem_wait(&dbWriter);

        // section critique, un seul writer à la fois
        if(writing < 640){
            writing ++;
            write_database();
        }
        else{
            sem_post(&dbReader);
            run = 0;
        }
        sem_post(&dbWriter);
        pthread_mutex_lock(&mutexWriter);
        writerCount --;
        if(writerCount == 0)sem_post(&dbReader);
        pthread_mutex_unlock(&mutexWriter);
    }
}

void* reader(){
    int run = 1;
    while(run){
        pthread_mutex_lock(&z);
        sem_wait(&dbReader);
        pthread_mutex_lock(&mutexReader);
        // section critique
        readCount++;
        if (readCount==1){
            sem_wait(&dbWriter);// arrivée du premier reader
        }
        pthread_mutex_unlock(&mutexReader);
        sem_post(&dbReader);
        pthread_mutex_unlock(&z);
        pthread_mutex_lock(&mutexReadCount);
        if(reading < 2560){
            reading ++;
            pthread_mutex_unlock(&mutexReadCount);
            read_database();
            pthread_mutex_lock(&mutexReader);
            readCount--;
            if(readCount==0){
                sem_post(&dbWriter);// départ du dernier reader
            }
        }
        else{
            pthread_mutex_lock(&mutexReader);
            readCount--;
            if(readCount==0){
                sem_post(&dbWriter);// départ du dernier reader
            }
            run = 0;
            pthread_mutex_unlock(&mutexReadCount);
        }
        pthread_mutex_unlock(&mutexReader);
    }
}

int main(int argc, char const *argv[]){
    int nreader;
    int nwriter;

    sscanf(argv[2], "%d", &nreader);
    sscanf(argv[1], "%d", &nwriter);

    sem_init(&dbReader, 0, 1);
    sem_init(&dbWriter, 0, 1);

    pthread_mutex_init(&mutexReader, NULL);
    pthread_mutex_init(&mutexWriter, NULL);
    pthread_mutex_init(&mutexReadCount, NULL);
    pthread_mutex_init(&z, NULL);
    
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
    return 0;
}
