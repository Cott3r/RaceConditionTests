//
// This test is a programm created by Daniel Gruss in SLP
// No rights reserved
//

#include <pthread.h>
#include <stdio.h>

#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

sem_t buffer_free_elements;
sem_t buffer_available_elements;
int buffer[16] = { 0 };

sem_t buffer_lock;
#define TOTAL (1024ull)
ssize_t numbers_produced = 0;
sem_t numbers_produced_lock;
ssize_t numbers_consumed = 0;
sem_t numbers_consumed_lock;
int cnt = 1;
sem_t cnt_lock;


void* producer(void* p)
{
  sem_wait(&numbers_produced_lock);
  while (numbers_produced < TOTAL)
  {
    numbers_produced++;
    sem_post(&numbers_produced_lock);
    int success = 0;
    sem_wait(&cnt_lock);
    int r = cnt++;
    sem_post(&cnt_lock);
    {
      sem_wait(&buffer_free_elements);
      sem_wait(&buffer_lock);
      for (size_t i = 0; i < 16; ++i)
      {
        if (buffer[i] == 0)
        {
          buffer[i] = r;
          success = 1;
          break;
        }
      }
      if (success == 0)
        exit(printf("ERRRRRORRRR!!!!!\n"));
      sem_post(&buffer_lock);
      sem_post(&buffer_available_elements);
    }
    sem_wait(&numbers_produced_lock);
  }
  sem_post(&numbers_produced_lock);
  return 0;
}

void* consumer(void* p)
{
  sem_wait(&numbers_consumed_lock);
  while (numbers_consumed < TOTAL)
  {
    numbers_consumed++;
    sem_post(&numbers_consumed_lock);
    int success = 0;
    int r = 0;
    {
      sem_wait(&buffer_available_elements);
      sem_wait(&buffer_lock);
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
      sem_post(&buffer_lock);
      if (success == 0)
        exit(printf("ERRRRRORRRR!!!!!\n"));
      sem_post(&buffer_free_elements);
    }
    printf("%d\n",r);
    sem_wait(&numbers_consumed_lock);
  }
  sem_post(&numbers_consumed_lock);
  return 0;
}

int main()
{
  sem_init(&buffer_free_elements,0,16);
  sem_init(&buffer_available_elements,0,0);
  sem_init(&buffer_lock,0,1);
  sem_init(&numbers_produced_lock,0,1);
  sem_init(&numbers_consumed_lock,0,1);
  sem_init(&cnt_lock,0,1);

  pthread_t t1,t2;
  for (size_t i = 0; i < 5; ++i)
  {
    pthread_create(&t1,0,consumer,0);
    pthread_detach(t1);
  }
  for (size_t i = 0; i < 5; ++i)
  {
    pthread_create(&t2,0,producer,0);
    pthread_detach(t2);
  }
  pthread_exit(0);
  return 0;
}
