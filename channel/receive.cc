#include "channel.ih"

template<typename T>
T Channel<T>::receive() {
    unique_lock<mutex> ul(d_mutex);
    ++d_receivers_present;

    while (size() == 0) {           // Wait until item
        d_receivers.wait(ul);
    }
    // Locked; there is an item

    T result(move(front()));        // Take the item
    pop_front();
    --d_receivers_present;
    ul.unlock();

    d_senders.notify_all();         // Notify senders there's space again
    return result;
}