#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "Channel.h"
#include "BlockingQueue.h"

using namespace sacre;

void* t1(void* ptr);
void* t2(void* ptr);
void* t3(void* ptr);
void* t4(void* ptr);

// mutex for the channel from Source 1 to Adder
Channel<int>* s1a = new BlockingQueue<int>("s1a");
Channel<int>* s2a = new BlockingQueue<int>("s2a");
Channel<int>* as = new BlockingQueue<int>("as");

int main ()
{
  pthread_t thread1, thread2, thread3, thread4;
  const char *message1 = "Source 1";
  const char *message2 = "Source 2";
  const char *message3 = "Adder";
  const char *message4 = "Sink";
  int iret1, iret2, iret3, iret4;

  //  void* (*print_message_function_ptr)(void* ptr);
  //print_message_function_ptr = &print_message_function;

  /* Create independent threads each of which will execute function */

  iret1 = pthread_create( &thread1, NULL, t1, (void*) message1);
  iret2 = pthread_create( &thread2, NULL, t2, (void*) message2);
  iret3 = pthread_create( &thread3, NULL, t3, (void*) message3);
  iret4 = pthread_create( &thread4, NULL, t4, (void*) message4);

  /* Wait till threads are complete before main continues. Unless we  */
  /* wait we run the risk of executing an exit which will terminate   */
  /* the process and all threads before the threads have completed.   */
  
  pthread_join( thread1, NULL);
  pthread_join( thread2, NULL); 
  pthread_join( thread3, NULL); 
  pthread_join( thread4, NULL); 

  printf("Thread 1 returns: %d\n",iret1);
  printf("Thread 2 returns: %d\n",iret2);
  printf("Thread 3 returns: %d\n",iret3);
  printf("Thread 4 returns: %d\n",iret4);
  
  return 0;
}

void* t1(void* ptr)
{
  char* thread_name;
  thread_name = (char*) ptr;

  int data[] = {1, 2, 3, 4, 5};
  
  int i;
  for(i=0; i<5; i++)
    {
      // write out data
      s1a->write(data[i]);
      printf("%s : step %d \n", thread_name, i);
    }

    printf("Finished: %s \n", thread_name);
    return NULL;
}

void* t2(void* ptr)
{
  char* thread_name;
  thread_name = (char*) ptr;

  int data[] = {6, 7, 8, 9, 10};
  
  int i;
  for(i=0; i<5; i++)
    {
      // write out data
      s2a->write(data[i]);
      printf("%s : step %d \n", thread_name, i);
    }

    printf("Finished: %s \n", thread_name);
    return NULL;
}

void* t3(void* ptr)
{
  char* thread_name;
  thread_name = (char*) ptr;

  int data[5];
  
  int i;
  for(i=0; i<5; i++)
    {
      // read data from source 1 and source 2 and write out sum
      int* a = new int;
      s1a->read(a);
      int* b = new int;
      s2a->read(b);
      //data[i] = s1a->read() + s2a->read();
      data[i] = *a + *b;
      printf("%s : step %d \n", thread_name, i);
      
      as->write(data[i]);
    }

    printf("Finished: %s \n", thread_name);
    return NULL;
}

void* t4(void* ptr)
{
  char* thread_name;
  thread_name = (char*) ptr;

  int i;
  for(i=0; i<5; i++)
    {
      // read data from input and print
      printf("%s : step %d \n", thread_name, i);
      int* res = new int;
      as->read(res);
      printf("Result: %d \n", *res);
    }

    printf("Finished: %s \n", thread_name);
    return NULL;
}
