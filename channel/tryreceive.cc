#include "channel.ih"
#include <thread>

template<typename T>
bool Channel<T>::try_receive(T &result) {
    unique_lock<mutex> ul(d_mutex);
    ++d_receivers_present;

    d_senders.notify_all();             // Notify senders I'm here

    ul.unlock();
    this_thread::yield();
    ul.lock();

    if (size() == 0) {
        --d_receivers_present;
        return false;
    }
    // Locked; there is an item

    auto storage = unique_ptr<deque<T>>::get();
    result = move(storage->front());    // Take the item
    storage->pop_front();
    --d_receivers_present;
    return true;
}
