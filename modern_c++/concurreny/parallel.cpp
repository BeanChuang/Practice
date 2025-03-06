#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

std::mutex mtx;

template<typename T>
void alarm_colck(std::reference_wrapper<T> freq)
{
    std::unique_lock<std::mutex> uni_lock(mtx, std::defer_lock);
    
    for (T i = 1; i <= 100; i++) {
        if (i % freq.get() == 0) {
            // std::lock_guard<std::mutex> lock(mtx);
            // mtx.lock();
            uni_lock.lock();
            std::cout << "[" << freq << "] sleep 5 ms" << std::endl;
            uni_lock.unlock();
            // mtx.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
    }
}

int main()
{
    int t1 = 10;
    int t2 = 5;
    std::thread m_colock1(alarm_colck<int>, std::ref(t1));
    std::thread m_colock2(alarm_colck<int>, std::ref(t2));
    m_colock1.join();
    m_colock2.join();
    return 0;
}