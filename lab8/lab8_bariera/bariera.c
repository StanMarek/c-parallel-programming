#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>

static pthread_mutex_t lock;
static pthread_cond_t bariera_cond;
int num_threads;
int threads_waiting;

void bariera_init(int n) {
  pthread_mutex_init(&lock,NULL);
  pthread_cond_init(&bariera_cond,NULL);
  num_threads = n;
  threads_waiting = 0;
}

void bariera() {
  pthread_mutex_lock(&lock);
  threads_waiting++;
  if(threads_waiting != num_threads)  
    pthread_cond_wait(&bariera_cond,&lock);
  else {
    threads_waiting=0;
    pthread_cond_broadcast(&bariera_cond);
  }
  pthread_mutex_unlock(&lock);

}


