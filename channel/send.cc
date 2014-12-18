#include "channel.ih"

template<typename T>
void Channel<T>::send(T const &element) {
    unique_lock<mutex> ul(d_mutex);

    if (d_cap == 0 || size() >= d_cap) {    // We need to block until a receive
        while (d_receivers_present == 0) {
            d_senders.wait(ul);
        }
    }
    // Locked; receiver is present and waiting, 
    // Only sender awake is me

    push_back(element);                     // Give item
    ul.unlock();

    d_receivers.notify_all();               // Tell receiver to come get it
}
