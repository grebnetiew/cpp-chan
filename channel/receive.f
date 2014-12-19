template<typename T>
void Channel<T>::receive(T &result) {
    std::unique_lock<std::mutex> ul(d_mutex);
    ++d_receivers_present;

    try {
        d_senders.notify_all();                 // Notify senders I'm here
        while (size() == 0) {                   // Wait until item
            d_receivers.wait(ul);
        }
        // Locked; there is an item

        auto storage = std::unique_ptr<std::deque<T>>::get();
        result = std::move(storage->front());   // Take the item
        storage->pop_front();                   // has nothrow
        --d_receivers_present;
    } catch (...) {
        --d_receivers_present;
        throw;
    }
}