#include <bits/stdc++.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

using namespace std;

int readercount = 0;
int shared = 100;
sem_t x,y;
pthread_t writerthreads[100],readerthreads[100];

void* reader(void *param)
{
    int rid = *(int *) param;

    sem_wait(&x);
    readercount++;
    if(readercount == 1)
    {
        sem_wait(&y);
    }
    sem_post(&x);
    cout<<"Reader:  "<<rid<<" is reading shared value: " <<shared<<endl;

    sem_wait(&x);
    readercount--;
    if(readercount == 0)
    {
        sem_post(&y);
    }
    sem_post(&x);

    cout<<"Reader:  "<<rid<<" has finished reading\n";
    return NULL;
}

void* writer(void * param)
{
    int wid = *(int*) param;

    cout<<"Writer:  "<<wid<<" is waiting to write\n";
    sem_wait(&y);
    shared += 10;
    cout<<"Writer:  "<<wid<<" is writing with value:"<<shared<<endl;
    cout<<"Writer:  "<<wid<<" has finished writing\n"; 
    sem_post(&y);
    return NULL;
}


int main()
{
    int n_reader , n_writer;

    cout<<"Enter the number of readers: "<<endl;
    cin>>n_reader;
    cout<<"Enter the number of writers: "<<endl;
    cin>>n_writer;

    sem_init(&x,0,1);
    sem_init(&y,0,1);

    int readerids[n_reader];
    int writerids[n_writer];

    for(int i = 0 ;i< n_reader;i++)
    {
        readerids[i] = i+1;
        pthread_create(&readerthreads[i],NULL,reader,&readerids[i]);
    }

    for(int i = 0 ;i< n_writer;i++)
    {
        writerids[i] = i+1;
        pthread_create(&writerthreads[i],NULL,writer,&writerids[i]);
    }
    for(int i = 0 ;i < n_reader;i++)
    {
        pthread_join(readerthreads[i],NULL);
    }

    for(int i = i ; i < n_writer;i++)
    {
        pthread_join(writerthreads[i],NULL);
    }
    sem_destroy(&x);
    sem_destroy(&y);
    return 0;
}
