#ifndef INCLUDED_CHANNEL_
#define INCLUDED_CHANNEL_

#include <memory>
#include <condition_variable>
#include <mutex>
#include <deque>
#include <thread>

template<typename T>
class Channel: private std::unique_ptr<std::deque<T>> {
    size_t d_cap;
    size_t d_receivers_present = 0;
    std::mutex d_mutex;
    std::condition_variable d_senders;
    std::condition_variable d_receivers;

    public:
        Channel();
        explicit Channel(size_t capacity);

        size_t size() const;
        void send(T const &element);
        T receive();
        bool try_receive(T &val);
};

template<typename T>
Channel<T>::Channel():
    std::unique_ptr<std::deque<T>>(new std::deque<T>()),
    d_cap(0)
{}

template<typename T>
Channel<T>::Channel(size_t capacity):
    std::unique_ptr<std::deque<T>>(new std::deque<T>()),
    d_cap(capacity)
{}

template<typename T>
size_t Channel<T>::size() const {
    return std::unique_ptr<std::deque<T>>::get()->size();
}

template<typename T>
void Channel<T>::send(T const &element) {
    std::unique_lock<std::mutex> ul(d_mutex);

    if (d_cap == 0 || size() >= d_cap) {    // We need to block until a receive
        while (d_receivers_present == 0) {
            d_senders.wait(ul);
        }
    }
    // Locked; receiver is present and waiting, 
    // Only sender awake is me
                                            // Give item
    std::unique_ptr<std::deque<T>>::get()->push_back(element);
    ul.unlock();

    d_receivers.notify_all();               // Tell receiver to come get it
}

template<typename T>
T Channel<T>::receive() {
    std::unique_lock<std::mutex> ul(d_mutex);
    ++d_receivers_present;

    d_senders.notify_all();             // Notify senders I'm here
    while (size() == 0) {               // Wait until item
        d_receivers.wait(ul);
    }
    // Locked; there is an item

    auto storage = std::unique_ptr<std::deque<T>>::get();
    T result(std::move(storage->front()));   // Take the item
    storage->pop_front();
    --d_receivers_present;
    return result;
}

template<typename T>
bool Channel<T>::try_receive(T &result) {
    std::unique_lock<std::mutex> ul(d_mutex);
    ++d_receivers_present;

    d_senders.notify_all();                 // Notify senders I'm here

    ul.unlock();
    std::this_thread::yield();
    ul.lock();

    if (size() == 0) {
        --d_receivers_present;
        return false;
    }
    // Locked; there is an item

    auto storage = std::unique_ptr<std::deque<T>>::get();
    result = std::move(storage->front());   // Take the item
    storage->pop_front();
    --d_receivers_present;
    return true;
}

#endif
