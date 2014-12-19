template<typename T>
void Channel<T>::send(T const &element) {
    std::unique_lock<std::mutex> ul(d_mutex);

    if (d_cap == 0 || size() >= d_cap) {    // We need to block until a receive
        while (d_receivers_present == 0) {
            if (!d_open) {
                throw ClosedException();
            }
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