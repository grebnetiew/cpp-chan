template<typename T>
bool Channel<T>::try_receive(T *result) {
    std::unique_lock<std::mutex> ul(d_mutex);
    ++d_receivers_present;

    try {
        d_senders.notify_all();                 // Notify senders I'm here
        ul.unlock();
        std::this_thread::yield();              // Let one send an element
        ul.lock();

        if (size() == 0 || !d_open) {           // If there is nothing, leave
            --d_receivers_present;              // within try, but can't throw
            return false;
        }
        // Locked; there is an item

        moveElement(result);
        --d_receivers_present;
        return true;
    } catch (...) {
        --d_receivers_present;
        throw;
    }
}