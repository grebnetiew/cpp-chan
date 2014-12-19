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