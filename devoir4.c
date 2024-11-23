#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 10  

int i = 1, compteur = 1;  
sem_t mutex, priv; 

void *processus1(void *arg) {
    while (1) {
        sem_wait(&mutex);  
        printf("%d %3d\n", compteur++, i);
        i++;  
        if (i == N) {
            sem_post(&priv); 
            printf("%d %3d\n", compteur++, i);
           
        } else {
            sem_post(&mutex); 
        }
         
    }
}

void *processus2(void *arg) {
    while (1) {
        sem_wait(&priv);  
        do
        {
          i--;
          printf("%d %3d\n", compteur++, i);
        } while(i != -N);
       i++;
        sem_post(&mutex); 
    }
}

int main() {
    pthread_t t1, t2;
 
      
    sem_init(&mutex, 0, 1);  
    sem_init(&priv, 0, 0);   

    pthread_create(&t1, NULL, processus1, NULL);
    pthread_create(&t2, NULL, processus2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&mutex);
    sem_destroy(&priv);

    return 0;
}
