/*
 * http://www.macesystems.org/svn/mace/trunk/application/parallelmc/BlockingQueue.h
 */

/*
  Blocking write and blocking read queue implementation!
*/

#ifndef __BLOCKINGQUEUE_H__
#define __BLOCKINGQUEUE_H__

#include "log4cxx/logger.h"
using namespace log4cxx;

#include <errno.h>
#include <sys/time.h>
#include <time.h>
#include <queue>
#include <pthread.h>
#include <iostream>

#include "Channel.h"

#define NANOSINSECOND (1000000000)

namespace sacre 
{

  template <typename T>
    class BlockingQueue : public Channel<T>
  {
  private:
    int size;
    unsigned micro_wait_time;
    pthread_mutex_t lock;
    pthread_cond_t non_empty;
    pthread_cond_t non_full;
    std::queue<T> backing;
    int bound;

  public:
    BlockingQueue(std::string name) : Channel<T>(name)
    {
      
      this->size = 0;
      this->micro_wait_time = 0;
      this->bound = -1;//no bound on queue
      pthread_mutex_init(&lock, NULL);
      pthread_cond_init(&non_empty, NULL);
      pthread_cond_init(&non_full, NULL);
    }


  BlockingQueue(std::string name, int bound) : Channel<T>(name)
    {
      
      this->size = 0;
      this->micro_wait_time = 0;
      this->bound = bound;
      pthread_mutex_init(&lock, NULL);
      pthread_cond_init(&non_empty, NULL);
      pthread_cond_init(&non_full, NULL);
    }
    
  BlockingQueue(std::string name, unsigned micro_wait_time) : Channel<T>(name)
    {
      this->size = 0;
      this->micro_wait_time = micro_wait_time;
      pthread_mutex_init(&lock, NULL);
      pthread_cond_init(&non_empty, NULL);
      pthread_cond_init(&non_full, NULL);
    }
    
    void write(T element) 
    {
      
      pthread_mutex_lock(&lock);
	  
      /* If queue size equal and less than bound or with no bound */
      if (this->size < bound || bound == -1 ) 
	{
	      
	  this->backing.push(element);
	  this->size += 1;
	      
	  LOG4CXX_TRACE(Logger::getLogger("sacrec"), 
			"Channel " << this->getName() << " is written." 
			);
	      
	  pthread_mutex_unlock(&lock);
	  pthread_cond_signal(&non_empty);
	      
	  return;
	}
	  
      /* If queue size is greater than bound */
      while (this->size >= bound) {
	pthread_cond_wait(&non_full, &lock);
      }
	  
      this->backing.push(element);
      this->size += 1;
	  
      LOG4CXX_TRACE(Logger::getLogger("sacrec"), 
		    "Channel " << this->getName() << " is written." 
		    );
	  
      pthread_mutex_unlock(&lock);
      pthread_cond_signal(&non_empty);
	  
      return;
	  
    }//end of write
    
    

    int read(T* result) 
    {
      pthread_mutex_lock(&lock);
      
      /* If we have a non-empty queue... */
      if (this->size > 0) 
	{
	  *result = backing.front();
	  backing.pop();
	  this->size -= 1;	  
	  LOG4CXX_TRACE(Logger::getLogger("sacrec"), 
			"Channel " << this->getName() << " is read." 
			);
	  pthread_mutex_unlock(&lock);

	  /*if there is no bound*/
	  if(bound != -1)
	    pthread_cond_signal(&non_full);

	  return 0;
	}
      
      /* Are we waiting for a specific amount of time? */
      if (this->micro_wait_time) {
	struct timeval now;
	struct timespec timeout;
	
	gettimeofday(&now, NULL);
	timeout.tv_sec = now.tv_sec;
	timeout.tv_nsec = now.tv_usec * 1000;
	
	if ((timeout.tv_nsec + (1000 * micro_wait_time)) > NANOSINSECOND) {
	  timeout.tv_sec += 1;
	  timeout.tv_nsec = (timeout.tv_nsec + (1000 * micro_wait_time)) % NANOSINSECOND;
	} else {
	  timeout.tv_nsec += (1000 * micro_wait_time);
	}
	
	while (this->size == 0) {
	  int result = pthread_cond_timedwait(&non_empty, &lock, &timeout);
	  if (result == ETIMEDOUT) {
	    pthread_mutex_unlock(&lock);
	    return ETIMEDOUT;
	  }
	}
	
	*result = backing.front();
	backing.pop();
	this->size -= 1;
	LOG4CXX_TRACE(Logger::getLogger("sacrec"), 
		      "Channel " << this->getName() << " is read." 
		      );
	pthread_mutex_unlock(&lock);
	return 0;
      }
      
      /* Otherwise we wait until something gets queued up. */
      while (this->size == 0) {
	pthread_cond_wait(&non_empty, &lock);
      }

      *result = backing.front();
      backing.pop();
      this->size -= 1;
      LOG4CXX_TRACE(Logger::getLogger("sacrec"), 
		    "Channel " << this->getName() << " is read." 
		    );
      pthread_mutex_unlock(&lock);

      /*if there is no bound*/
      if(bound != -1) 
	pthread_cond_signal(&non_full);

      return 0;
    }


    //noxim-sacre integration
    //------------------------------
    bool isEmpty() 
    {
      pthread_mutex_lock(&lock);
      
      /* If we have a non-empty queue... */
      if (this->size > 0) 
	{
	  pthread_mutex_unlock(&lock);
	  return false;
	}
      else
	{
	  pthread_mutex_unlock(&lock);
	  return true;
	}
    }
    //------------------------------
    
  };//end of class

}

#endif  /* __BLOCKING_QUEUE_H__ */
