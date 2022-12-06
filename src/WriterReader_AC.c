#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<stdio.h>
#include"../headers/semative.h"


int* mutex_reader;
int* mutex_writer;
int* z;// Pour être sure que les writer aient tjrs la prioritée
custom_sema_t db_reader; // accès à la db
custom_sema_t db_writer; // accès à la db
int writercount = 0;
int readcount=0; // nombre de readers
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
while(run)
    {
    lock(mutex_writer);
    writercount ++;
    if(writercount == 1){
        wait(&db_reader);
    }
    unlock(mutex_writer);
    
    wait(&db_writer);

    // section critique, un seul writer à la fois
    if(writing < 2560){
        writing ++;
        write_database();
    }
    else{
        run = 0;
    }
    post(&db_writer);

    lock(mutex_writer);
    writercount --;
    if(writercount == 0){
        post(&db_reader);
    }
    unlock(mutex_writer);
    }
}

void* reader()
{
    int run = 1;
    while(run)
    {
        lock(z);
        wait(&db_reader);
        lock(mutex_reader);
        // section critique
        readcount++;
        if (readcount==1)
        { // arrivée du premier reader
            wait(&db_writer);
        }
        unlock(mutex_reader);
        post(&db_reader);
        lock(mutex_reader);
        if(reading < 640){
            read_database();
            reading ++;
            readcount--;
            if(readcount==0)
            { // départ du dernier reader
                post(&db_writer);
            }
        }
        else{
            run = 0;
        }
        unlock(mutex_reader);
        unlock(z);
        }
}

int main(int argc, char const *argv[]){
    int nreader;
    int nwriter;
    sscanf(argv[2], "%d", &nreader);
    sscanf(argv[1], "%d", &nwriter);
    init(&db_reader,1);
    init(&db_writer,1);
    mutex_reader = malloc(sizeof(int));
    mutex_writer = malloc(sizeof(int));
    z = malloc(sizeof(int));
    *mutex_reader = 0;
    *mutex_writer = 0;
    *z = 0;
    pthread_t ReadThreads[nreader];
    pthread_t WriteThreads[nwriter];
    for (size_t i = 0; i < nwriter; i++)
    {
        if(0 != pthread_create(&WriteThreads[i],NULL,&writer,NULL)){
            printf("ERROR: Error while creating writer thread n°%ld\n",i);
        }
        //else printf("Writer Thread %ld created\n",i+1);
    }

    for (size_t i = 0; i < nreader; i++)
    {
        if(0 != pthread_create(&ReadThreads[i],NULL,&reader,NULL)){
            printf("ERROR: Error while creating Reader thread n°%ld",i);
        }
        //else printf("Reader Thread %ld created\n",i+1);
    }
    
    for (size_t i = 0; i < nwriter; i++)
    {
        if(0 != pthread_join(WriteThreads[i],NULL)){
            printf("ERROR: Error while joining writer thread n°%ld\n",i);
        }
    }
    for (size_t i = 0; i < nreader; i++)
    {
        if(0 != pthread_join(ReadThreads[i],NULL)){
            printf("ERROR: Error while joining reader thread n°%ld\n",i);
        }
    }
    //printf("%d writing\n",writing);
    //printf("%d reading\n",reading);
    return 0;
}