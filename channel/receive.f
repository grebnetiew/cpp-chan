template<typename T>
void Channel<T>::receive(T *result) {
    std::unique_lock<std::mutex> ul(d_mutex);
    ++d_receivers_present;

    try {
        waitForSenders(ul);
        // Locked; there is an item
        moveElement(result);
        --d_receivers_present;
    } catch (...) {
        --d_receivers_present;
        throw;
    }
}