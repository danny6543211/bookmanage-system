#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>
#include <functional>

class thread_pool
{
public:
    thread_pool(size_t thread_count) : stop(false)
    {
        // 創建線程
        for (size_t i = 0; i < thread_count; i++)
        {
            threads.emplace_back([this] {
                while (true)
                {
                    std::function<void()> task;
                    
                    {
                        std::unique_lock<std::mutex> lock(queue_mutex);
                        pool_cond.wait(lock, [this]{ return this->stop || !this->task_queue.empty(); });
                        if (task_queue.empty() && stop) 
                            return;
                        task = std::move(task_queue.front());
                        task_queue.pop();
                    }

                    task();
                }
            });
        }
    }

    ~thread_pool()
    {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }
        pool_cond.notify_all();
        // 跑完再關掉
        for(std::thread &worker: threads)
        worker.join();
    }
    
    template <class F>
    auto enqueue(F task)
    {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            task_queue.emplace(task);
        }
        pool_cond.notify_one();
        
    }


private:
    std::mutex queue_mutex;
    std::condition_variable pool_cond;
    std::queue<std::function<void()>> task_queue;
    std::vector<std::thread> threads;
    bool stop;

};

#endif