#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<stdio.h>
pthread_mutex_t mutex_reader;
pthread_mutex_t mutex_writer;
pthread_mutex_t z;// Pour être sure que les writer aient tjrs la prioritée
sem_t db_reader; // accès à la db
sem_t db_writer; // accès à la db
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
    pthread_mutex_lock(&mutex_writer);
    writercount ++;
    if(writercount == 1){
        sem_wait(&db_reader);
    }
    pthread_mutex_unlock(&mutex_writer);
    
    sem_wait(&db_writer);

    // section critique, un seul writer à la fois
    if(writing < 2560){
        writing ++;
        write_database();
    }
    else{
        run = 0;
    }
    sem_post(&db_writer);

    pthread_mutex_lock(&mutex_writer);
    writercount --;
    if(writercount == 0){
        sem_post(&db_reader);
    }
    pthread_mutex_unlock(&mutex_writer);
    }
}

void* reader()
{
    int run = 1;
    while(run)
    {
        pthread_mutex_lock(&z);
        sem_wait(&db_reader);
        pthread_mutex_lock(&mutex_reader);
        // section critique
        readcount++;
        if (readcount==1)
        { // arrivée du premier reader
            sem_wait(&db_writer);
        }
        pthread_mutex_unlock(&mutex_reader);
        sem_post(&db_reader);
        pthread_mutex_lock(&mutex_reader);
        if(reading < 640){
            read_database();
            reading ++;
            readcount--;
            if(readcount==0)
            { // départ du dernier reader
                sem_post(&db_writer);
            }
        }
        else{
            run = 0;
        }
        pthread_mutex_unlock(&mutex_reader);
        pthread_mutex_unlock(&z);
        }
}

int main(int argc, char const *argv[]){
    int nreader;
    int nwriter;
    sscanf(argv[2], "%d", &nreader);
    sscanf(argv[1], "%d", &nwriter);
    sem_init(&db_reader, 0, 1);
    sem_init(&db_writer, 0, 1);
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
