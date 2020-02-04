/*
 * BlockingQueue.cpp
 *
 *  Created on: Nov 9, 2016
 *      Author: msoderen
 */

#include "BlockingQueue.h"

#include <functional>
#include <assert.h>


template<typename T>
void BlockingQueue<T>::put(const T& item)
{
    std::unique_lock<std::mutex> lk(mtx_);
    cv_full_.wait(lk, std::bind(&BlockingQueue<T>::queueFull, this));
    
    assert(queue_.size() < capacity_);
    queue_.push(item);
    cv_empty_.notify_all();
}

template<typename T>
T BlockingQueue<T>::take()
{
    std::unique_lock<std::mutex> lk(mtx_);
    cv_empty_.wait(lk, std::bind(&BlockingQueue<T>::empty, this));

    assert(!queue_.empty());
    T front(queue_.front());
    queue_.pop();
    cv_full_.notify_all();
    return front;
}

template<typename T>
size_t BlockingQueue<T>::size()
{
    std::lock_guard<std::mutex> lock(mtx_);
    return queue_.size();
}

template<typename T>
T BlockingQueue<T>::front()
{
    std::unique_lock<std::mutex> lk(mtx_);
    cv_empty_.wait(lk, std::bind(&BlockingQueue<T>::empty, this));

    assert(!queue_.empty());
    T front(queue_.front());
    return front;
}


/// conditions
template<typename T>
bool BlockingQueue<T>::empty()
{
    std::unique_lock<std::mutex> lock(mtx_);
    return queue_.empty();
}

template<typename T>
bool BlockingQueue<T>::full()
{
    return queue_.size() == capacity_;
}


template<typename T>
void BlockingQueue<T>::setCapacity(const size_t capacity){
    capacity_ = (capacity > 0 ? capacity : MAX_CAPACITY);
}


// template class BlockingQueue<QueueElement*>;
template class BlockingQueue<std::string>;