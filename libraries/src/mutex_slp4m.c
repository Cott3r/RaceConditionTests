//
// This test is a programm created by Daniel Gruss in SLP
// No rights reserved
//

#include <pthread.h>
#include <stdio.h>

#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

int buffer[16] = { 0 };
pthread_mutex_t buffer_lock;

#define TOTAL (1024ull)
ssize_t numbers_produced = 0;
pthread_mutex_t numbers_produced_lock;
ssize_t numbers_consumed = 0;
pthread_mutex_t numbers_consumed_lock;
int cnt = 1;
pthread_mutex_t cnt_lock;


void* producer(void* p)
{
  pthread_mutex_lock(&numbers_produced_lock);
  while (numbers_produced < TOTAL)
  {
    numbers_produced++;
    pthread_mutex_unlock(&numbers_produced_lock);
    int success = 0;
    pthread_mutex_lock(&cnt_lock);
    int r = cnt++;
    pthread_mutex_unlock(&cnt_lock);
    while (success == 0)
    {
      pthread_mutex_lock(&buffer_lock);
      for (size_t i = 0; i < 16; ++i)
      {
        if (buffer[i] == 0)
        {
          buffer[i] = r;
          success = 1;
          break;
        }
      }
      pthread_mutex_unlock(&buffer_lock);
    }
    pthread_mutex_lock(&numbers_produced_lock);
  }
  pthread_mutex_unlock(&numbers_produced_lock);
  return 0;
}

void* consumer(void* p)
{
  pthread_mutex_lock(&numbers_consumed_lock);
  while (numbers_consumed < TOTAL)
  {
    numbers_consumed++;
    pthread_mutex_unlock(&numbers_consumed_lock);
    int success = 0;
    int r = 0;
    while (success == 0)
    {
      pthread_mutex_lock(&buffer_lock);
      for (size_t i = 0; i < 16; ++i)
      {
        if (buffer[i] != 0)
        {
          r = buffer[i];
          buffer[i] = 0;
          success = 1;
          break;
        }
      }
      pthread_mutex_unlock(&buffer_lock);
    }
    printf("%d\n",r);
    pthread_mutex_lock(&numbers_consumed_lock);
  }
  pthread_mutex_unlock(&numbers_consumed_lock);
  return 0;
}

int main()
{
  pthread_mutex_init(&buffer_lock,0);
  pthread_mutex_init(&numbers_produced_lock,0);
  pthread_mutex_init(&numbers_consumed_lock,0);
  pthread_mutex_init(&cnt_lock,0);

  for (size_t i = 0; i < 5; ++i)
  {
    pthread_t t1;
    pthread_create(&t1,0,consumer,0);
    pthread_detach(t1);
  }
  for (size_t i = 0; i < 5; ++i)
  {
    pthread_t t2;
    pthread_create(&t2,0,producer,0);
    pthread_detach(t2);
  }
  pthread_exit(0);
  return 0;
}
