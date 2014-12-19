template<typename T>
T Channel<T>::receive() {
    unique_lock<mutex> ul(d_mutex);
    ++d_receivers_present;

    d_senders.notify_all();             // Notify senders I'm here
    while (size() == 0) {               // Wait until item
        d_receivers.wait(ul);
    }
    // Locked; there is an item

    auto storage = unique_ptr<deque<T>>::get();
    T result(move(storage->front()));   // Take the item
    storage->pop_front();
    --d_receivers_present;
    return result;
}
