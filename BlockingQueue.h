/*
 * BlockingQueue.h
 *
 *  Created on: Nov 9, 2016
 *      Author: msoderen
 */
 
#ifndef SRC_ALLADTCOPRA_COMMON_BLOCKINGQUEUE_H_
#define SRC_ALLADTCOPRA_COMMON_BLOCKINGQUEUE_H_

#include <queue>
#include <condition_variable>

constexpr size_t MAX_CAPACITY = 20;


template<typename T>
class BlockingQueue
{
public:
    BlockingQueue(size_t capacity = MAX_CAPACITY) : capacity_(capacity) {}
    
    void put(const T& item);
    T take();
    
    T front();
    size_t size();
    void setCapacity(const size_t capacity);

    // conditions
    bool empty();
    bool full();

private:
    BlockingQueue(const BlockingQueue& rhs) = delete;
    BlockingQueue& operator= (const BlockingQueue& rhs) = delete;

private:
    mutable std::mutex mtx_;
    std::condition_variable cv_full_;
    std::condition_variable cv_empty_;
    std::queue<T> queue_;
    size_t capacity_;
};


#endif